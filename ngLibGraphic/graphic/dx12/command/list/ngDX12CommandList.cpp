/*!
* @file		ngDX12CommandList.cpp
* @brief	DX12コマンドリスト
* @date		2017-09-24
* @author	s.fukami
*/

#include <d3d12.h>
#include "ngLibCore/common/ngCommon.h"
#include "../../common/ngDX12Common.h"
#include "../../device/ngDX12Device.h"
#include "../allocator/ngDX12CommandAllocator.h"
#include "ngDX12CommandList.h"

namespace ng
{
	CDX12CommandList::CDX12CommandList()
		: m_pIList(nullptr)
	{
	}

	CDX12CommandList::~CDX12CommandList()
	{
		Destroy();
	}

	NG_ERRCODE CDX12CommandList::Create(
		CDX12Device& device,
		CDX12CommandAllocator& allocator
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12コマンドリスト生成
		if(NG_FAILED(ret = device.Interface()->CreateCommandList(
			0,
			allocator.GetCommandListType(),
			allocator.Interface(),
			nullptr,
			IID_PPV_ARGS(&m_pIList)
			))) {
			NG_DXERRLOG("DX12CommandList", ret, CreateCommandList, "コマンドリストの生成に失敗しました.");
			return ret;
		}

		Close();

		return ret;
	}
	
	NG_ERRCODE CDX12CommandList::Close()
	{
		return m_pIList->Close();
	}

	void CDX12CommandList::Destroy()
	{
		NG_SAFE_RELEASE(m_pIList);
	}
	
	bool CDX12CommandList::IsValid() const
	{
		return (m_pIList != nullptr);
	}

	CDX12CommandList::DX12IfType* CDX12CommandList::Interface()
	{
		return m_pIList;
	}
	const CDX12CommandList::DX12IfType* CDX12CommandList::Interface() const
	{
		return m_pIList;
	}

}	// namespace ng