/*!
* @file		ngDX12CommandAllocator.cpp
* @brief	DX12コマンドアロケーター
* @date		2017-09-24
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "ngDX12CommandAllocator.h"

namespace ng
{
	CDX12CommandAllocator::CDX12CommandAllocator()
		: m_pIAllocator(nullptr)
		, m_cmdListType(D3D12_COMMAND_LIST_TYPE_DIRECT)
	{
	}

	CDX12CommandAllocator::~CDX12CommandAllocator()
	{
		Destroy();
	}

	NG_ERRCODE CDX12CommandAllocator::Create(CDX12Device& device, D3D12_COMMAND_LIST_TYPE type)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドアロケータ生成
		if(NG_FAILED(ret = device.Interface()->CreateCommandAllocator(
			type,
			IID_PPV_ARGS(&m_pIAllocator)
			))) {
			NG_DXERR("DX12CommandAllocator", ret, CreateCommandAllocator, "DX12コマンドアロケーターの生成に失敗しました.");
			return ret;
		}

		m_cmdListType = type;

		return ret;
	}

	NG_ERRCODE CDX12CommandAllocator::Reset()
	{
		return m_pIAllocator->Reset();
	}

	void CDX12CommandAllocator::Destroy()
	{
		NG_SAFE_RELEASE(m_pIAllocator);
	}

	bool CDX12CommandAllocator::IsValid() const
	{
		return (m_pIAllocator != nullptr);
	}

	ID3D12CommandAllocator* CDX12CommandAllocator::Interface()
	{
		return m_pIAllocator;
	}
	const ID3D12CommandAllocator* CDX12CommandAllocator::Interface() const
	{
		return m_pIAllocator;
	}

	D3D12_COMMAND_LIST_TYPE CDX12CommandAllocator::GetCommandListType() const
	{
		return m_cmdListType;
	}

}	// namespace ng