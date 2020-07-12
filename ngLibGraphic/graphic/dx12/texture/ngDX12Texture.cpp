/*!
* @file		ngDX12Texture.cpp
* @brief	DX12テクスチャ
* @date		2019-07-31
* @author	s.fukami
*/

#include <d3dx12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "../descriptor/ngDX12DescriptorHeap.h"
#include "ngDX12Texture.h"

namespace ng
{
	CDX12Texture::CDX12Texture()
	{
	}
	CDX12Texture::~CDX12Texture()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Texture::Create(
			CDX12Device& device,
			const void* pTexData,
			u32 width,
			u32 height
			)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// テクスチャリソースを生成
		if(NG_FAILED(ret = m_resource.CreateTextureBuffer(
			device, pTexData, width, height
			))) {
			return ret;
		}

		return ret;
	}

	void CDX12Texture::CreateResourceView(
		CDX12Device& device,
		CDX12DescriptorHeap& heap,
		u32 heapIdx
		)
	{
		if(!IsValid()) return;

		// シェーダーリソースビューを作成
		D3D12_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
		viewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		viewDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipLevels = 1;
		viewDesc.Texture2D.MostDetailedMip = 0;
		viewDesc.Texture2D.PlaneSlice = 0;
		viewDesc.Texture2D.ResourceMinLODClamp = 0.0F;
		viewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		device.Interface()->CreateShaderResourceView(
			m_resource.Interface(),
			&viewDesc,
			heap.GetCPUDescriptorHandle(heapIdx)
			);
	}

	void CDX12Texture::Destroy()
	{
		m_resource.Destroy();
	}

	bool CDX12Texture::IsValid() const
	{
		return m_resource.IsValid();
	}

	CDX12Resource& CDX12Texture::GetResource()
	{
		return m_resource;
	}
	const CDX12Resource& CDX12Texture::GetResource() const
	{
		return m_resource;
	}

}	// namespace ng