/*!
* @file		ngDX12Graphic.cpp
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#include "ngLibCore/common/ngCommon.h"
#include "common/ngDX12Common.h"
#include "ngDX12Util.h"
#include "ngDX12Graphic.h"
#include "command/queue/ngDX12CommandQueue.h"

namespace ng
{
	CDX12Graphic::CreateParam::CreateParam()
		: hWnd(nullptr)
		, clientWidth(0)
		, clientHeight(0)
		, isFullscreen(false)
		, commandListNum(1)
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
		// DX12コマンドキューマネージャ初期化
		{
			NG_DX12LOG("DX12Graphic", "DX12コマンドキューマネージャ初期化を開始...");
			if(NG_FAILED(ret = m_cmdQueueMngr.Initialize(m_device))) {
				NG_ERRLOG_C("DX12Graphic", ret, "DX12コマンドキューマネージャの初期化に失敗しました.");
				return ret;
			}
		}
		// DX12スワップチェイン生成
		{
			bool isFullscreen = param.isFullscreen;
			// TODO: 要調査
			// Warpデバイスの場合はフルスクリーン不可?
			const CDX12Device::CreateDesc& createDesc = m_device.GetCreateDesc();
			if(createDesc.driverType == eDX12DriverType::SOFTWARE) {
				isFullscreen = false;
			}

			NG_DX12LOG("DX12Graphic", "DX12スワップチェイン生成を開始...");
			const u32 bufferCount = 2;
			if(NG_FAILED(ret = m_swapChain.Create(
				m_device,
				*m_cmdQueueMngr.GetCommandQueue(eDX12CommandQueueType::GRAPHIC),
				param.hWnd,
				bufferCount,
				param.clientWidth,
				param.clientHeight,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				isFullscreen
				))) {
				NG_ERRLOG_C("DX12Graphic", ret, "DX12スワップチェインの生成に失敗しました.");
				return ret;
			}
		}
		// DX12コマンドアロケータ生成
		NG_DX12LOG("DX12Graphic", "DX12コマンドアロケータの生成を開始...");
		for(u32 i = 0; i < param.commandListNum; i++)
		{
			if(NG_FAILED(ret = _createCommandAllocator(
				m_device,
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				i
				))) {
				return ret;
			}
		}
		// DX12コマンドリスト生成
		NG_DX12LOG("DX12Graphic", "DX12コマンドリストの生成を開始...");
		for(u32 i = 0; i < param.commandListNum; i++)
		{
			if(NG_FAILED(ret = _createCommandList(
				m_device,
				i, i
				))) {
				return ret;
			}
		}
		// バックバッファ用のレンダーターゲット生成
		{
			if(NG_FAILED(ret = _createRTBackBuffer(
				m_device,
				m_swapChain,
				0, eDX12RenderTargetId::ID_BACK_BUFFER_01
				))) {
				return ret;
			}
			if(NG_FAILED(ret = _createRTBackBuffer(
				m_device,
				m_swapChain,
				1, eDX12RenderTargetId::ID_BACK_BUFFER_02
				))) {
				return ret;
			}
		}
		// DX12深度ステンシル生成
		{
			if(NG_FAILED(ret = m_dsMngr.CreateDepthStencil(
				m_device,
				param.clientWidth,
				param.clientHeight,
				eDX12DepthStencilId::ID_01
				))) {
				return ret;
			}
		}

		return ret;
	}

	void CDX12Graphic::Destroy()
	{
		m_cmdListMngr.Finalize();
		m_cmdAllocMngr.Finalize();
		m_cmdQueueMngr.Finalize();
		m_dsMngr.Finalize();
		m_rtMngr.Finalize();
		m_swapChain.Destroy();
		m_device.Destroy();
	}

	void CDX12Graphic::BeginRender()
	{
		// 全コマンドアロケータリセット
		ng::DX12Util::ResetAllCommandAllocator();
	}

	void CDX12Graphic::ExecuteRender()
	{
		// 全コマンドリスト実行
		ng::DX12Util::ExecuteAllCommandList(ng::eDX12CommandQueueType::GRAPHIC);
	}

	void CDX12Graphic::EndRender()
	{
		// バックバッファを表示
		m_swapChain.Present(1);
		
		// 描画完了待ち
		CDX12CommandQueue* pCmdQueue = m_cmdQueueMngr.GetCommandQueue(ng::eDX12CommandQueueType::GRAPHIC);
		NG_ASSERT(pCmdQueue != nullptr);
		pCmdQueue->WaitForFence();
	}

	CDX12Device& CDX12Graphic::GetDevice()
	{
		return m_device;
	}
	const CDX12Device& CDX12Graphic::GetDevice() const
	{
		return m_device;
	}

	CDX12SwapChain& CDX12Graphic::GetSwapChain()
	{
		return m_swapChain;
	}
	const CDX12SwapChain& CDX12Graphic::GetSwapChain() const
	{
		return m_swapChain;
	}

	CDX12CommandQueueManager& CDX12Graphic::GetCommandQueueMngr()
	{
		return m_cmdQueueMngr;
	}
	const CDX12CommandQueueManager& CDX12Graphic::GetCommandQueueMngr() const
	{
		return m_cmdQueueMngr;
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

	CDX12RenderTargetManager& CDX12Graphic::GetRenderTargetMngr()
	{
		return m_rtMngr;
	}
	const CDX12RenderTargetManager& CDX12Graphic::GetRenderTargetMngr() const
	{
		return m_rtMngr;
	}

	CDX12DepthStencilManager& CDX12Graphic::GetDepthStencilMngr()
	{
		return m_dsMngr;
	}
	const CDX12DepthStencilManager& CDX12Graphic::GetDepthStencilMngr() const
	{
		return m_dsMngr;
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

	NG_ERRCODE CDX12Graphic::_createRTBackBuffer(CDX12Device& device, CDX12SwapChain& swapChain, u32 bufferIndex, eDX12RenderTargetId id)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;
		
		if(NG_FAILED(ret = m_rtMngr.CreateRenderTargetView(
			device,
			swapChain,
			bufferIndex,
			id
			))) {
			NG_ERRLOG_C("DX12Graphic", ret, "DX12レンダーターゲット（バックバッファ）の生成に失敗. bufferIndex:%u, id:%u", bufferIndex, id);
			return ret;
		}

		return ret;
	}

}	//namespace ng