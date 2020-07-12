/*!
* @file		ngDX12Resource.cpp
* @brief	DX12リソース
* @date		2019-08-03
* @author	s.fukami
*/

#include <d3dx12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../device/ngDX12Device.h"
#include "ngDX12Resource.h"

namespace ng
{
	CDX12Resource::CDX12Resource()
		: m_pIResource(nullptr)
	{
	}

	CDX12Resource::~CDX12Resource()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Resource::CreatePrimitiveBuffer(
		CDX12Device& device,
		const void* pData,
		u32 size
		)
	{
		// D3D12_CPU_PAGE_PROPERTY_WRITE_BACK
		// D3D12_MEMORY_POOL_L0
		CD3DX12_HEAP_PROPERTIES heapProp(
			D3D12_HEAP_TYPE_UPLOAD
			);
		// D3D12_RESOURCE_DIMENSION_BUFFER
		// D3D12_TEXTURE_LAYOUT_ROW_MAJOR
		CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(
			size
			);
		return CreateAndCopyData(
			device,
			heapProp,
			resDesc,
			pData,
			size
			);
	}

	NG_ERRCODE CDX12Resource::CreateTextureBuffer(
			CDX12Device& device,
			const void* pTexData,
			u32 width,
			u32 height,
			DXGI_FORMAT format
			)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// D3D12_HEAP_TYPE_CUSTOM
		CD3DX12_HEAP_PROPERTIES heapProp(
			D3D12_CPU_PAGE_PROPERTY_WRITE_BACK
			, D3D12_MEMORY_POOL_L0
			);
		// D3D12_RESOURCE_DIMENSION_TEXTURE2D
		CD3DX12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Tex2D(
			format
			, width, height
			, 1		// arraySize
			, 1		// mipLevels
			//, 1	// sampleCount
			//, 0	// sampleQuality
			);
		if(NG_FAILED(ret = Create(
			device,
			heapProp,
			resDesc
			))) {
			return ret;
		}

		// 画像データをサブリソースへコピー
		D3D12_BOX box = {0, 0, 0, (UINT)width, (UINT)height, 1};
		if(NG_FAILED(ret = m_pIResource->WriteToSubresource(
			0,
			&box,
			pTexData,
			sizeof(UINT)*width,
			sizeof(UINT)*width * sizeof(UINT)*height
			))) {
			NG_DXERRLOG("DX12Resource", ret, WriteToSubresource, "サブリソースへのデータコピーに失敗しました.");
			return false;
		}

		return ret;
	}

	NG_ERRCODE CDX12Resource::Create(
		CDX12Device& device,
		const D3D12_HEAP_PROPERTIES& heapProp,
		const D3D12_RESOURCE_DESC& resDesc,
		D3D12_RESOURCE_STATES resState,
		const D3D12_CLEAR_VALUE* pClearValue
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(IsValid()) Destroy();

		if(NG_FAILED(ret = device.Interface()->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			resState,
			pClearValue,
			IID_PPV_ARGS(&m_pIResource)))
			) {
			NG_DXERRLOG("DX12Resource", ret, CreateCommittedResource, "サブリソースの生成に失敗しました.");
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12Resource::CreateAndCopyData(
		CDX12Device& device,
		const D3D12_HEAP_PROPERTIES& heapProp,
		const D3D12_RESOURCE_DESC& resDesc,
		const void* pData,
		u32 size
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = Create(
			device, heapProp, resDesc
			))) {
			return ret;
		}
		if(pData && size > 0) {
			if(NG_FAILED(ret = CopyData(
				pData, size
				))) {
				return ret;
			}
		}

		return ret;
	}

	NG_ERRCODE CDX12Resource::CopyData(
		const void* pData,
		u32 size
		)
	{
		NG_ASSERT_NOT_NULL(pData);
		NG_ASSERT(IsValid());

		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// バッファにデータコピー
		UINT8* pDataBegin = nullptr;
		D3D12_RANGE readRange = {0, 0};
		if(NG_FAILED(ret = m_pIResource->Map(0, &readRange, reinterpret_cast<void**>(&pDataBegin)))) {
			NG_DXERRLOG("DX12Resource", ret, Map, "サブリソースへのポインタの取得に失敗しました.");
			return ret;
		}
		NG_MEMCPY(pDataBegin, pData, size);
		m_pIResource->Unmap(0, nullptr);

		return ret;
	}

	void CDX12Resource::Destroy()
	{
		NG_SAFE_RELEASE(m_pIResource);
	}

	bool CDX12Resource::IsValid() const
	{
		return (m_pIResource != nullptr);
	}

	ID3D12Resource* CDX12Resource::Interface()
	{
		return m_pIResource;
	}
	const ID3D12Resource* CDX12Resource::Interface() const
	{
		return m_pIResource;
	}

}	// namespace