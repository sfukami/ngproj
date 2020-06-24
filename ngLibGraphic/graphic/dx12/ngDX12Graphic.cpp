/*!
* @file		ngDX12Graphic.cpp
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "ngLibGraphic/graphic/dx12/common/ngDX12Common.h"
#include "ngDX12Graphic.h"

namespace ng
{
	CDX12Graphic::CreateParam::CreateParam()
		: hWnd(nullptr)
		, clientWidth(0)
		, clientHeight(0)
		, isFullscreen(false)
	{
	}

	CDX12Graphic::CDX12Graphic()
	{
	}

	CDX12Graphic::~CDX12Graphic()
	{
		Destroy();
	}

	NG_ERRCODE CDX12Graphic::Create(const CreateParam& param)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DX12デバッグレイヤー有効化
		NG_DX12_ENABLE_DEBUG_LAYER();

		// DX12デバイス生成
		{
			NG_DX12LOG("DX12Graphic", "DX12デバイスの生成を開始...");
			if(NG_FAILED(ret = m_device.Create(param.deviceParam))) {
				NG_ERRLOG_C("DX12Graphic", ret, "DX12デバイスの生成に失敗しました.");
				return ret;
			}
		}

		// DX12コマンドアロケータ生成
		{
			NG_DX12LOG("DX12Graphic", "DX12コマンドアロケータの生成を開始...");
			if(NG_FAILED(ret = _createCommandAllocator(
				m_device,
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				0
				))) {
				return ret;
			}
		}
		// DX12コマンドリスト生成
		{
			NG_DX12LOG("DX12Graphic", "DX12コマンドリストの生成を開始...");
			if(NG_FAILED(ret = _createCommandList(
				m_device,
				0,
				0
				))) {
				return ret;
			}
		}

		return ret;
	}

	void CDX12Graphic::Render()
	{

	}

	void CDX12Graphic::Destroy()
	{
		m_cmdListMngr.Finalize();
		m_cmdAllocMngr.Finalize();
		m_device.Destroy();
	}

	CDX12Device& CDX12Graphic::GetDevice()
	{
		return m_device;
	}
	const CDX12Device& CDX12Graphic::GetDevice() const
	{
		return m_device;
	}

	CDX12CommandAllocatorManager& CDX12Graphic::GetCommandAllocatorMngr()
	{
		return m_cmdAllocMngr;
	}
	const CDX12CommandAllocatorManager& CDX12Graphic::GetCommandAllocatorMngr() const
	{
		return m_cmdAllocMngr;
	}

	CDX12CommandListManager& CDX12Graphic::GetCommandListMngr()
	{
		return m_cmdListMngr;
	}
	const CDX12CommandListManager& CDX12Graphic::GetCommandListMngr() const
	{
		return m_cmdListMngr;
	}

	NG_ERRCODE CDX12Graphic::_createCommandAllocator(CDX12Device& device, D3D12_COMMAND_LIST_TYPE type, u32 index)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		if(NG_FAILED(ret = m_cmdAllocMngr.CreateCommandAllocator(
			device,
			type,
			index
			))) {
			NG_ERRLOG_C("DX12Graphic", ret, "DX12コマンドアロケータの生成に失敗しました. index:%u", index);
			return ret;
		}

		return ret;
	}

	NG_ERRCODE CDX12Graphic::_createCommandList(CDX12Device& device, u32 cmdAllocIdx, u32 cmdListIdx)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		CDX12CommandAllocator* pCmdAlloc = m_cmdAllocMngr.GetCommandAllocator(cmdAllocIdx);
		if(pCmdAlloc == nullptr) {
			NG_ERRLOG("DX12Graphic", "DX12コマンドアロケータの取得に失敗しました. index:%u", cmdAllocIdx);
			return eNG_E_FAIL;
		}

		if(NG_FAILED(ret = m_cmdListMngr.CreateCommandList(
			device,
			*pCmdAlloc,
			cmdListIdx
		))) {
			NG_ERRLOG_C("DX12Graphic", ret, "DX12コマンドリストの生成に失敗しました. index:%u", cmdListIdx);
			return ret;
		}

		return ret;
	}

}	//namespace ng