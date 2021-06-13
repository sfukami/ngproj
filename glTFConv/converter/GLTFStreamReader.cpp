/*!
* @file		GLTFStreamReader.cpp
* @brief	glTFファイル読み込み
* @date		2021-06-07
* @author	s.fukami
*/

// ■参考URL:https://github.com/microsoft/glTF-SDK/blob/master/GLTFSDK.Samples/Deserialize/Source/main.cpp

#include <filesystem>
#include <fstream>
#include <sstream>

#include <GLTFSDK/GLTF.h>
#include <GLTFSDK/GLTFResourceReader.h>
#include <GLTFSDK/GLBResourceReader.h>
#include <GLTFSDK/Deserialize.h>

#include "GLTFStreamReader.h"
#include "../model/ModelFormat.h"

namespace glTFConv
{
	class CStreamReader : public Microsoft::glTF::IStreamReader
	{
	public:
		CStreamReader(std::filesystem::path path) : m_path(std::move(path))
		{
			NG_ASSERT(m_path.has_root_path());
		}

		std::shared_ptr<std::istream> GetInputStream(const std::string& filename) const override
		{
			auto streamPath = m_path / std::filesystem::u8path(filename);
			auto stream = std::make_shared<std::ifstream>(streamPath, std::ios_base::binary);

			return stream;
		}
		
	private:
		std::filesystem::path m_path;
	};

	CGLTFStreamReader::CGLTFStreamReader()
	{
	}
	CGLTFStreamReader::~CGLTFStreamReader()
	{
	}

	bool CGLTFStreamReader::Read(const char* pFilePath, ModelFormat* pOutput) const
	{
		std::filesystem::path path(pFilePath);
		
		//ng::DPrintf(L"Directory:%ls\n", path.parent_path().c_str());
		//ng::DPrintf(L"Filename:%ls\n", path.filename().c_str());
		//ng::DPrintf(L"Stem:%ls\n", path.stem().c_str());
		//ng::DPrintf(L"Extension:%ls\n", path.extension().c_str());
		//ng::DPrintf(L"Native format:%ls\n", path.native().c_str());
		//ng::DPrintf(L"Generic format:%ls\n", path.generic_wstring().c_str());
		//ng::DPrintf("%s\n", (path.is_absolute() ? "絶対パス" : "相対パス"));

		auto streamReader = std::make_unique<CStreamReader>(path.parent_path());

		std::filesystem::path pathFile = path.filename();
		std::filesystem::path pathFileExt = path.extension();

		std::string manifest;

		auto makePathExt = [](const std::string& ext)
		{
			return "." + ext;
		};

		std::unique_ptr<Microsoft::glTF::GLTFResourceReader> resourceReader;

		// 拡張子が ".gltf" の場合
		if(pathFileExt == makePathExt(Microsoft::glTF::GLTF_EXTENSION)) {
			auto gltfStream = streamReader->GetInputStream(pathFile.u8string());
			auto gltfResourceReader = std::make_unique<Microsoft::glTF::GLTFResourceReader>(std::move(streamReader));

			std::stringstream manifestStream;

			manifestStream << gltfStream->rdbuf();
			manifest = manifestStream.str();

			resourceReader = std::move(gltfResourceReader);
		}
		// 拡張子が ".glb" の場合
		else if(Microsoft::glTF::GLB_EXTENSION) {
			auto glbStream = streamReader->GetInputStream(pathFile.u8string());
			auto glbResourceReader = std::make_unique<Microsoft::glTF::GLBResourceReader>(std::move(streamReader), std::move(glbStream));

			manifest = glbResourceReader->GetJson();

			resourceReader = std::move(glbResourceReader);
		}

		if(!resourceReader) {
			throw std::runtime_error("Argument path filename extension must be .gltf or .glb");
		}

		Microsoft::glTF::Document document;

		try
		{
			document = Microsoft::glTF::Deserialize(manifest);
		}
		catch(const Microsoft::glTF::GLTFException& ex)
		{
			std::stringstream ss;
			ss << "Microsoft::glTF::Deserialize failed: ";
			ss << ex.what();
			throw std::runtime_error(ss.str());
		}

		_printDocumentInfo(document);
		_printResourceInfo(document, *resourceReader);

		_toModelFormat(document, *resourceReader, pOutput);

		_printModelFormat(pOutput);

		return true;
	}

	void CGLTFStreamReader::_toModelFormat(
		const Microsoft::glTF::Document& document, const Microsoft::glTF::GLTFResourceReader& resourceReader, ModelFormat* pOutput
		) const
	{
		NG_ASSERT_NOT_NULL(pOutput);

		for(const auto& mesh : document.meshes.Elements())
		{
			ModelFormat::Mesh& dstMesh = pOutput->meshes.emplace_back();
			dstMesh.name = mesh.name;

			if(!mesh.primitives.empty()) {
				// 頂点
				{
					const auto& primitive = mesh.primitives.front();

					auto& posId = primitive.GetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION);
					auto& posAcc = document.accessors.Get(posId);

					auto& normId = primitive.GetAttributeAccessorId(Microsoft::glTF::ACCESSOR_NORMAL);
					auto& normAcc = document.accessors.Get(normId);

					auto& uvId = primitive.GetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TEXCOORD_0);
					auto& uvAcc = document.accessors.Get(uvId);

					auto posVec = resourceReader.ReadBinaryData<float>(document, posAcc);
					auto normVec = resourceReader.ReadBinaryData<float>(document, normAcc);
					auto uvVec = resourceReader.ReadBinaryData<float>(document, uvAcc);

					for(ng::u32 i = 0; i < posAcc.count; i++)
					{
						float* pPos = &posVec[i*3];
						float* pNorm = &normVec[i*3];
						float* pUV = &uvVec[i*2];
						dstMesh.vertices.emplace_back(
							ng::Vector3(*pPos, *(pPos+1), *(pPos+2)),
							ng::Vector3(*pNorm, *(pNorm+1), *(pNorm+2)),
							ng::Vector2(*pUV, *(pUV+1))
							);
					}
				}
				// インデックス
				for(const auto& primitive : mesh.primitives)
				{
					ng::u32 materialIndex = static_cast<ng::u32>(document.materials.GetIndex(primitive.materialId));
					auto found = std::find_if(dstMesh.primitives.begin(), dstMesh.primitives.end(), [materialIndex](const auto& p){ return p.materialIndex == materialIndex; });

					ModelFormat::Primitive* pDstPrimitive = nullptr;
					if(found == dstMesh.primitives.end()) {
						pDstPrimitive = &dstMesh.primitives.emplace_back();
					}
					else {
						pDstPrimitive = &*found;
					}

					auto& idxId = primitive.indicesAccessorId;
					auto& idxAcc = document.accessors.Get(idxId);

					auto indices = resourceReader.ReadBinaryData<uint32_t>(document, idxAcc);
					pDstPrimitive->indices.insert(pDstPrimitive->indices.end(), indices.begin(), indices.end());
					pDstPrimitive->materialIndex = materialIndex;
				}
			}
		}
	}

	void CGLTFStreamReader::_printDocumentInfo(
		const Microsoft::glTF::Document& document
		) const
	{
		ng::Printf("=== Document Info ===\n");
		// Asset Info
		ng::Printf("[Asset]\n");
		ng::Printf("  Version:%s\n", document.asset.version.c_str());
		ng::Printf("  MinVersion:%s\n", document.asset.minVersion.c_str());
		ng::Printf("  Generator:%s\n", document.asset.generator.c_str());
		ng::Printf("  Copyright:%s\n", document.asset.copyright.c_str());

		// Scene Info
		ng::Printf("[Scene]\n");
		ng::Printf("  Scene Count:%u\n", document.scenes.Size());
		if(document.scenes.Size() > 0U) {
			ng::Printf("  Default Scene Index:%s\n", document.GetDefaultScene().id.c_str());
		}
		else {
			ng::Printf("\n");
		}

		// Entity Info
		ng::Printf("[Entity]\n");
		ng::Printf("  Node Count:%u\n", document.nodes.Size());
		ng::Printf("  Camera Count:%u\n", document.cameras.Size());
		ng::Printf("  Material Count:%u\n", document.materials.Size());

		// Mesh Info
		ng::Printf("[Mesh]\n");
		ng::Printf("  Mesh Count:%u\n", document.meshes.Size());
		ng::Printf("  Skin Count:%u\n", document.skins.Size());

		// Texture Info
		ng::Printf("[Texture]\n");
		ng::Printf("  Image Count:%u\n", document.images.Size());
		ng::Printf("  Texture Count:%u\n", document.textures.Size());
		ng::Printf("  Sampler Count:%u\n", document.samplers.Size());

		// Buffer Info
		ng::Printf("[Buffer]\n");
		ng::Printf("  Buffer Count:%u\n", document.buffers.Size());
		ng::Printf("  BufferView Count:%u\n", document.bufferViews.Size());
		ng::Printf("  Accessor Count:%u\n", document.accessors.Size());

		// Animation Info
		ng::Printf("[Animation]\n");
		ng::Printf("  Animation Count:%u\n", document.animations.Size());

		// Extension
		ng::Printf("[Extension]\n");
		for(const auto& extension : document.extensionsUsed)
		{
			ng::Printf("  Extension Used:%s\n", extension.c_str());
		}
		for(const auto& extension : document.extensionsRequired)
		{
			ng::Printf("  Extension Required:%s\n", extension.c_str());
		}
	}

	void CGLTFStreamReader::_printResourceInfo(
		const Microsoft::glTF::Document& document, const Microsoft::glTF::GLTFResourceReader& resourceReader
		) const
	{
		ng::Printf("=== Resource Info ===\n");
		ng::Printf("[Mesh]\n");
		for(const auto& mesh : document.meshes.Elements())
		{
			ng::Printf("  -Mesh Id:%s, Name:%s\n", mesh.id.c_str(), mesh.name.c_str());

			for(const auto& primitive : mesh.primitives)
			{
				std::string posAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION, posAccId)) {
					const Microsoft::glTF::Accessor& posAcc = document.accessors.Get(posAccId);
					const auto posData = resourceReader.ReadBinaryData<float>(document, posAcc);
					const ng::size_type posDataBytes = posData.size() * sizeof(float);

					const Microsoft::glTF::Accessor& idxAcc = document.accessors.Get(primitive.indicesAccessorId);
					const auto idxData = resourceReader.ReadBinaryData<uint32_t>(document, idxAcc);

					ng::Printf("    Positions:%u (%ubytes), Indices:%u, MaterialId:%s\n", posData.size(), posDataBytes, idxData.size(), primitive.materialId.c_str());
				}
			}
		}

		ng::Printf("[Image]\n");
		for(const auto& image : document.images.Elements())
		{
			std::string filename;
			std::string::const_iterator itBegin, itEnd;
			if(image.uri.empty()) {
				NG_ASSERT(!image.bufferViewId.empty());

				auto& bufferView = document.bufferViews.Get(image.bufferViewId);
				auto& buffer = document.buffers.Get(bufferView.bufferId);

				filename += buffer.uri;
			}
			else if(Microsoft::glTF::IsUriBase64(image.uri, itBegin, itEnd)) {
				filename = "Data URI";
			}
			else {
				filename = image.uri;
			}

			auto data = resourceReader.ReadBinaryData(document, image);
			ng::Printf("  -Image Id:%s, Name:%s (%ubytes)\n", image.id.c_str(), image.name.c_str(), data.size());
			if(!filename.empty()) {
				ng::Printf("    filename:%s\n", filename.c_str());
			}
		}
	}

	void CGLTFStreamReader::_printModelFormat(const ModelFormat* pModelFormat) const
	{
		NG_ASSERT_NOT_NULL(pModelFormat);

		ng::Printf("[Model Format]\n");
		int meshIndex = 0;
		for(const auto& mesh : pModelFormat->meshes)
		{
			ng::Printf("  -Mesh %d:%s\n", meshIndex, mesh.name.c_str());
			ng::Printf("    VertexCount:%u\n", mesh.vertices.size());
			ng::Printf("    Primitives:\n");
			int primitiveIndex = 0;
			for(const auto& primitive : mesh.primitives)
			{
				ng::Printf("      %d: IndexCount:%u, MaterialIndex:%u\n", primitiveIndex, primitive.indices.size(), primitiveIndex);
				primitiveIndex++;
			}
			meshIndex++;
		}
	}

}	// namespace glTFConv