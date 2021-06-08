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

	bool CGLTFStreamReader::Read(const char* pFilePath)
	{
		std::filesystem::path path(pFilePath);
		
		ng::DPrintf(L"Directory:%ls\n", path.parent_path().c_str());
		ng::DPrintf(L"Filename:%ls\n", path.filename().c_str());
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

		return true;
	}

	void CGLTFStreamReader::_printDocumentInfo(
		const Microsoft::glTF::Document& document
		)
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
		)
	{
		ng::Printf("=== Resource Info ===\n");
		ng::Printf("[Mesh]\n");
		for(const auto& mesh : document.meshes.Elements())
		{
			ng::Printf("  -Mesh Id:%s, Name:%s\n", mesh.id.c_str(), mesh.name.c_str());

			for(const auto& meshPrimitive : mesh.primitives)
			{
				std::string accessorId;
				if(meshPrimitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION, accessorId)) {
					const Microsoft::glTF::Accessor& accessor = document.accessors.Get(accessorId);
					const auto data = resourceReader.ReadBinaryData<float>(document, accessor);
					const auto dataByteLength = data.size() * sizeof(float);
					ng::Printf("    Positions:%u (%ubytes)\n", data.size(), dataByteLength);
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

}	// namespace glTFConv