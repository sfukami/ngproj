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
#include "../model/VertexLayoutFlag.h"

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

		// メッシュ
		for(const auto& mesh : document.meshes.Elements())
		{
			ModelFormat::Mesh& dstMesh = pOutput->meshes.emplace_back();
			dstMesh.name = mesh.name;

			if(!mesh.primitives.empty()) {
				// 頂点
				{
					const auto& primitive = mesh.primitives.front();
					std::string posAccId, normAccId, tanAccId, uv0AccId, uv1AccId, jointAccId, weightAccId;
					eVertexLayoutFlag layoutFlag = eVertexLayoutFlag();

					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION, posAccId)) {
						layoutFlag |= eVertexLayoutFlag::POSITION;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_NORMAL, normAccId)) {
						layoutFlag |= eVertexLayoutFlag::NORMAL;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TANGENT, tanAccId)) {
						layoutFlag |= eVertexLayoutFlag::TANGENT;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TEXCOORD_0, uv0AccId)) {
						layoutFlag |= eVertexLayoutFlag::UV0;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TEXCOORD_1, uv1AccId)) {
						layoutFlag |= eVertexLayoutFlag::UV1;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_JOINTS_0, jointAccId)) {
						layoutFlag |= eVertexLayoutFlag::JOINT;
					}
					if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_WEIGHTS_0, weightAccId)) {
						layoutFlag |= eVertexLayoutFlag::WEIGHT;
					}

					if(layoutFlag == (
						  eVertexLayoutFlag::POSITION
						| eVertexLayoutFlag::NORMAL
						| eVertexLayoutFlag::UV0
						| eVertexLayoutFlag::JOINT
						| eVertexLayoutFlag::WEIGHT
						)) {
						auto& posAcc = document.accessors.Get(posAccId);
						auto& normAcc = document.accessors.Get(normAccId);
						auto& uvAcc = document.accessors.Get(uv0AccId);
						auto& jointAcc = document.accessors.Get(jointAccId);
						auto& weightAcc = document.accessors.Get(weightAccId);

						auto posVec = resourceReader.ReadBinaryData<float>(document, posAcc);
						auto normVec = resourceReader.ReadBinaryData<float>(document, normAcc);
						auto uvVec = resourceReader.ReadBinaryData<float>(document, uvAcc);
						auto jointVec = resourceReader.ReadBinaryData<uint16_t>(document, jointAcc);
						auto weightVec = resourceReader.ReadBinaryData<float>(document, weightAcc);

						float *pPos, *pNorm, *pUV, *pWeight;
						uint16_t* pJoint;
						for(ng::u32 i = 0; i < posAcc.count; i++)
						{
							pPos = &posVec[i*3];
							pNorm = &normVec[i*3];
							pUV = &uvVec[i*2];
							pJoint = &jointVec[i*4];
							pWeight = &weightVec[i*4];
							dstMesh.vertices.emplace_back(
								ng::Vector3(*pPos, *(pPos+1), *(pPos+2)),
								ng::Vector3(*pNorm, *(pNorm+1), *(pNorm+2)),
								ng::Vector2(*pUV, *(pUV+1)),
								pJoint, pWeight
								);
						}
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

		// マテリアル
		for(const auto& material : document.materials.Elements())
		{
			std::string textureId = material.metallicRoughness.baseColorTexture.textureId;
			if(textureId.empty()) {
				textureId = material.normalTexture.textureId;
			}
			if(textureId.empty()) continue;

			auto& texture = document.textures.Get(textureId);
			auto& image = document.images.Get(texture.imageId);
			auto& imageBufferView = document.bufferViews.Get(image.bufferViewId);

			ModelFormat::Material& dstMaterial = pOutput->materials.emplace_back();
			ModelFormat::Texture& dstTexture = dstMaterial.diffuseMap;
			dstTexture.name = image.name;
			dstTexture.data = resourceReader.ReadBinaryData<char>(document, imageBufferView);
		}
	}

	void CGLTFStreamReader::_printDocumentInfo(
		const Microsoft::glTF::Document& document
		) const
	{
		ng::Printf("=====================\n");
		ng::Printf("=== Document Info ===\n");
		ng::Printf("=====================\n");
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
			if(document.scenes.Size() > 1U) {
				ng::Printf("  Scenes:\n");
				for(int i = 0; i < document.scenes.Size(); i++)
				{
					const auto& scene = document.scenes[i];
					ng::Printf("    %d: id:%s, name:%s\n", i, scene.id.c_str(), scene.name.c_str());
				}
			}
		}
		else {
			ng::Printf("\n");
		}

		// Entity Info
		ng::Printf("[Entity]\n");
		ng::Printf("  Node Count:%u\n", document.nodes.Size());
		if(document.nodes.Size() > 0U) {
			ng::Printf("  Nodes:\n");
			for(int i = 0; i < document.nodes.Size(); i++)
			{
				const auto& node = document.nodes[i];
				ng::Printf("    %d: id:%s, name:%s, isEmpty:%d", i, node.id.c_str(), node.name.c_str(), node.IsEmpty());
				if(!node.cameraId.empty()) ng::Printf(", cameraId:%s", node.cameraId.c_str());
				if(!node.skinId.empty()) ng::Printf(", skinId:%s", node.skinId.c_str());
				if(!node.meshId.empty()) ng::Printf(", meshId:%s", node.meshId.c_str());
				ng::Printf("\n");
			}
		}
		ng::Printf("  Camera Count:%u\n", document.cameras.Size());
		if(document.cameras.Size() > 0U) {
			ng::Printf("  Cameras:\n");
			for(int i = 0; i < document.cameras.Size(); i++)
			{
				const auto& camera = document.cameras[i];
				ng::Printf("    %d: id:%s, name:%s\n", i, camera.id.c_str(), camera.name.c_str());
			}
		}
		ng::Printf("  Material Count:%u\n", document.materials.Size());
		if(document.materials.Size() > 0U) {
			ng::Printf("  Materials:\n");
			for(int i = 0; i < document.materials.Size(); i++)
			{
				const auto& material = document.materials[i];
				ng::Printf("    %d: id:%s, name:%s\n", i, material.id.c_str(), material.name.c_str());
			}
		}

		// Mesh Info
		ng::Printf("[Mesh]\n");
		ng::Printf("  Mesh Count:%u\n", document.meshes.Size());
		if(document.meshes.Size() > 0U) {
			ng::Printf("  Meshes:\n");
			for(int i = 0; i < document.meshes.Size(); i++)
			{
				const auto& mesh = document.meshes[i];
				ng::Printf("    %d: id:%s, name:%s, primitives:%u, weights:%u\n", i, mesh.id.c_str(), mesh.name.c_str(), mesh.primitives.size(), mesh.weights.size());
			}
		}
		ng::Printf("  Skin Count:%u\n", document.skins.Size());
		if(document.skins.Size() > 0U) {
			ng::Printf("  Skins:\n");
			for(int i = 0; i < document.skins.Size(); i++)
			{
				const auto& skin = document.skins[i];
				ng::Printf("    %d: id:%s, name:%s, jointIds:%u\n", i, skin.id.c_str(), skin.name.c_str(), skin.jointIds.size());
			}
		}

		// Texture Info
		ng::Printf("[Texture]\n");
		ng::Printf("  Image Count:%u\n", document.images.Size());
		if(document.images.Size() > 0U) {
			ng::Printf("  Images:\n");
			for(int i = 0; i < document.images.Size(); i++)
			{
				const auto& image = document.images[i];
				ng::Printf("    %d: id:%s, name:%s, mineType:%s, uri:%s\n", i, image.id.c_str(), image.name.c_str(), image.mimeType.c_str(), image.uri.c_str());
			}
		}
		ng::Printf("  Texture Count:%u\n", document.textures.Size());
		if(document.textures.Size() > 0U) {
			ng::Printf("  Textures:\n");
			for(int i = 0; i < document.textures.Size(); i++)
			{
				const auto& texture = document.textures[i];
				ng::Printf("    %d: id:%s, name:%s, imageId:%s, samplerId:%s\n", i, texture.id.c_str(), texture.name.c_str(), texture.imageId.c_str(), texture.samplerId.c_str());
			}
		}
		ng::Printf("  Sampler Count:%u\n", document.samplers.Size());
		if(document.samplers.Size() > 0U) {
			ng::Printf("  Samplers:\n");
			for(int i = 0; i < document.samplers.Size(); i++)
			{
				const auto& sampler = document.samplers[i];
				ng::Printf("    %d: id:%s, name:%s\n", i, sampler.id.c_str(), sampler.name.c_str());
			}
		}

		// Buffer Info
		ng::Printf("[Buffer]\n");
		ng::Printf("  Buffer Count:%u\n", document.buffers.Size());
		if(document.buffers.Size() > 0U) {
			ng::Printf("  Buffers:\n");
			for(int i = 0; i < document.buffers.Size(); i++)
			{
				const auto& buffer = document.buffers[i];
				ng::Printf("    %d: id:%s, name:%s, uri:%s, byteLength:%u\n", i, buffer.id.c_str(), buffer.name.c_str(), buffer.uri.c_str(), buffer.byteLength);
			}
		}
		ng::Printf("  BufferView Count:%u\n", document.bufferViews.Size());
	#if 0
		if(document.bufferViews.Size() > 0U) {
			ng::Printf("  BufferViews:\n");
			for(int i = 0; i < document.bufferViews.Size(); i++)
			{
				const auto& bufferView = document.bufferViews[i];
				ng::Printf("    %d: id:%s, name:%s, bufferId:%s, byteLength:%u\n", i, bufferView.id.c_str(), bufferView.name.c_str(), bufferView.bufferId.c_str(), bufferView.byteLength);
			}
		}
	#endif
		ng::Printf("  Accessor Count:%u\n", document.accessors.Size());
	#if 0
		if(document.accessors.Size() > 0U) {
			ng::Printf("  Accessors:\n");
			for(int i = 0; i < document.accessors.Size(); i++)
			{
				const auto& accessor = document.accessors[i];
				ng::Printf("    %d: id:%s, name:%s, bufferViewId:%s, count:%u\n", i, accessor.id.c_str(), accessor.name.c_str(), accessor.bufferViewId.c_str(), accessor.count);
			}
		}
	#endif

		// Animation Info
		ng::Printf("[Animation]\n");
		ng::Printf("  Animation Count:%u\n", document.animations.Size());
		if(document.animations.Size() > 0U) {
			ng::Printf("  Animations:\n");
			for(int i = 0; i < document.animations.Size(); i++)
			{
				const auto& animation = document.animations[i];
				ng::Printf("    %d: id:%s, name:%s, channels:%u, samplers:%u\n", i, animation.id.c_str(), animation.name.c_str(), animation.channels.Size(), animation.samplers.Size());
			}
		}

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
		ng::Printf("=====================\n");
		ng::Printf("=== Resource Info ===\n");
		ng::Printf("=====================\n");
		ng::Printf("[Mesh]\n");
		for(const auto& mesh : document.meshes.Elements())
		{
			ng::Printf("  -Mesh Id:%s, Name:%s\n", mesh.id.c_str(), mesh.name.c_str());
			{
				const auto& primitive = mesh.primitives.front();
				std::string posAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION, posAccId)) {
					const auto& acc = document.accessors.Get(posAccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf("    Positions:%u(%u)", data.size(), data.size()/3);
				}
				std::string normAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_POSITION, normAccId)) {
					const auto& acc = document.accessors.Get(normAccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", Normals:%u", data.size());
				}
				std::string tanAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TANGENT, tanAccId)) {
					const auto& acc = document.accessors.Get(tanAccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", Tangents:%u", data.size());
				}
				std::string uv0AccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TEXCOORD_0, uv0AccId)) {
					const auto& acc = document.accessors.Get(uv0AccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", UV0s:%u", data.size());
				}
				std::string uv1AccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_TEXCOORD_1, uv1AccId)) {
					const auto& acc = document.accessors.Get(uv1AccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", UV1s:%u", data.size());
				}
				std::string colAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_COLOR_0, colAccId)) {
					const auto& acc = document.accessors.Get(colAccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", Colors:%u", data.size());
				}
				std::string jointAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_JOINTS_0, jointAccId)) {
					const auto& acc = document.accessors.Get(jointAccId);
					const auto data = resourceReader.ReadBinaryData<uint16_t>(document, acc);
					ng::Printf(", Joints:%u", data.size());
				}
				std::string weightAccId;
				if(primitive.TryGetAttributeAccessorId(Microsoft::glTF::ACCESSOR_WEIGHTS_0, weightAccId)) {
					const auto& acc = document.accessors.Get(weightAccId);
					const auto data = resourceReader.ReadBinaryData<float>(document, acc);
					ng::Printf(", Weights:%u", data.size());
				}
				ng::Printf("\n");
			}
			for(const auto& primitive : mesh.primitives)
			{
				if(!primitive.indicesAccessorId.empty()) {
					const auto& acc = document.accessors.Get(primitive.indicesAccessorId);
					const auto data = resourceReader.ReadBinaryData<uint32_t>(document, acc);
					ng::Printf("    Indices:%u, ", data.size());
				}
				ng::Printf("MaterialId:%s\n", primitive.materialId.c_str());
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
			ng::Printf("  -Image Id:%s, Name:%s (%uBytes)\n", image.id.c_str(), image.name.c_str(), data.size()*sizeof(uint8_t));
			if(!filename.empty()) {
				ng::Printf("    filename:%s\n", filename.c_str());
			}
		}

		ng::Printf("[Skin]\n");
		for(const auto& skin : document.skins.Elements())
		{
			ng::Printf("  -Skin Id:%s, Name:%s, SkeletonId:%s, JointIds:%u\n",
				skin.id.c_str(), skin.name.c_str(), skin.skeletonId.c_str(), skin.jointIds.size());
			const auto& acc = document.accessors.Get(skin.inverseBindMatricesAccessorId);
			const auto data = resourceReader.ReadBinaryData<float>(document, acc);
			ng::Printf("    InverseBindMatrices:%u\n", data.size());
		}
	}

	void CGLTFStreamReader::_printModelFormat(const ModelFormat* pModelFormat) const
	{
		NG_ASSERT_NOT_NULL(pModelFormat);

		ng::Printf("[Model Format]\n");
		// メッシュ
		ng::Printf("Mesh Count:%u\n", pModelFormat->meshes.size());
		int meshIndex = 0;
		for(const auto& mesh : pModelFormat->meshes)
		{
			ng::Printf("  -Mesh %d:%s\n", meshIndex, mesh.name.c_str());
			ng::Printf("    VertexCount:%u\n", mesh.vertices.size());
			ng::Printf("    Primitives:\n");
			int primitiveIndex = 0;
			for(const auto& primitive : mesh.primitives)
			{
				ng::Printf("      %d: IndexCount:%u, MaterialIndex:%u\n", primitiveIndex, primitive.indices.size(), primitive.materialIndex);
				primitiveIndex++;
			}
			meshIndex++;
		}
		// マテリアル
		ng::Printf("Material Count:%u\n", pModelFormat->materials.size());
		int materialIndex = 0;
		for(const auto& material : pModelFormat->materials)
		{
			ng::Printf("  -Material %d:\n", materialIndex);
			ng::Printf("    DiffuseMap:%s (%uBytes)\n", material.diffuseMap.name.c_str(), material.diffuseMap.data.size());
			materialIndex++;
		}
	}

}	// namespace glTFConv