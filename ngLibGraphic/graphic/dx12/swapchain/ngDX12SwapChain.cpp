/*!
* @file		ngDX12SwapChain.cpp
* @brief	DX12スワップチェイン
* @date		2017-09-18
* @author	s.fukami
*/

#include <d3d12.h>
#include <DXGI.h>
#include <DXGI1_2.h>	// for DXGI_SWAP_CHAIN_DESC1
#include <DXGI1_4.h>	// for IDXGIFactory4
#include "ngLibCore/common/ngCommon.h"
#include "../common/ngDX12Common.h"
#include "../command/queue/ngDX12CommandQueue.h"
#include "../device/ngDX12Device.h"
#include "ngDX12SwapChain.h"

namespace ng
{
	CDX12SwapChain::CDX12SwapChain()
		: m_pISwapChain(nullptr)
		, m_bufferCount(0U)
		, m_bufferWidth(0U)
		, m_bufferHeight(0U)
	{
	}

	CDX12SwapChain::~CDX12SwapChain()
	{
		Destroy();
	}

	NG_ERRCODE CDX12SwapChain::Create(
		CDX12Device& device,
		CDX12CommandQueue& cmdQueue,
		HWND hWnd,
		u32 bufferCount,
		u32 bufferWidth,
		u32 bufferHeight,
		DXGI_FORMAT format,
		bool isFullscreen
		)
	{
		NG_ERRCODE ret = NG_ERRCODE_DEFAULT;

		// DXGI1.1ファクトリを生成
		IDXGIFactory4* pIFactory = nullptr;
		if(NG_FAILED(ret = CreateDXGIFactory1(IID_PPV_ARGS(&pIFactory)))) {
			NG_DXERRLOG("DX12SwapChain", ret, CreateDXGIFactory1, "DXGI1.1ファクトリの作成に失敗しました.");
			return ret;
		}

		// DX12スワップチェイン生成
		DXGI_SWAP_CHAIN_DESC1 desc = {};
		desc.Width = bufferWidth;
		desc.Height = bufferHeight;
		desc.Format = format;
		desc.Stereo = false;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = bufferCount;
		desc.Scaling = DXGI_SCALING_NONE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc = {};
		fullscreenDesc.RefreshRate.Numerator = 60;
		fullscreenDesc.RefreshRate.Denominator = 1;
		fullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		fullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		fullscreenDesc.Windowed = ! isFullscreen;

		IDXGISwapChain1* pISwapChain1 = nullptr;
		if(NG_FAILED(ret = pIFactory->CreateSwapChainForHwnd(
			cmdQueue.Interface(),
			hWnd,
			&desc,
			&fullscreenDesc,
			nullptr,
			&pISwapChain1
			))) {
			NG_DXERRLOG("DX12SwapChain", ret, CreateSwapChainForHwnd, "DX12スワップチェインの作成に失敗しました.");
			return ret;
		}

		if(NG_FAILED(ret = pISwapChain1->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&m_pISwapChain))) {
			NG_DXERRLOG("DX12SwapChain", ret, QueryInterface, "インターフェースがサポートされていません.");
			return ret;
		}

		NG_SAFE_RELEASE(pISwapChain1);
		NG_SAFE_RELEASE(pIFactory);

		m_bufferCount = bufferCount;
		m_bufferWidth = bufferWidth;
		m_bufferHeight = bufferHeight;

		// DX12レンダーターゲットビュー生成
		for(u32 i = 0; i < bufferCount; i++)
		{
			if(NG_FAILED(ret = m_rtvs[i].Create(
				device,
				*this,
				i
				))) {
				NG_ERRLOG_C("DX12SwapChain", ret, "DX12レンダーターゲットビューの生成に失敗しました. index:%u", i);
				return ret;
			}
		}

		return ret;
	}

	NG_ERRCODE CDX12SwapChain::Present(u32 syncInterval, u32 flags)
	{
		return m_pISwapChain->Present(syncInterval, flags);
	}

	void CDX12SwapChain::Destroy()
	{
		for(int i = 0; i < NG_ARRAY_SIZE(m_rtvs); i++)
		{
			m_rtvs[i].Destroy();
		}

		if(IsValid()) {
			// フルスクリーン状態で解放処理を行うとエラーが発生する
			BOOL isFullscreen = FALSE;
			m_pISwapChain->GetFullscreenState(&isFullscreen, NULL);
			if(isFullscreen) {
				m_pISwapChain->SetFullscreenState(FALSE, NULL);
			}
		}

		NG_SAFE_RELEASE(m_pISwapChain);
	}

	u32 CDX12SwapChain::GetCurrentBackBufferIndex() const
	{
		return m_pISwapChain->GetCurrentBackBufferIndex();
	}

	CDX12RenderTarget& CDX12SwapChain::GetCurrentRenderTarget()
	{
		return m_rtvs[ GetCurrentBackBufferIndex() ];
	}
	const CDX12RenderTarget& CDX12SwapChain::GetCurrentRenderTarget() const
	{
		return const_cast<CDX12SwapChain*>(this)->GetCurrentRenderTarget();
	}

	bool CDX12SwapChain::IsValid() const
	{
		return (m_pISwapChain != nullptr);
	}

	IDXGISwapChain3* CDX12SwapChain::Interface()
	{
		return m_pISwapChain;
	}
	const IDXGISwapChain3* CDX12SwapChain::Interface() const
	{
		return m_pISwapChain;
	}

	u32 CDX12SwapChain::GetBackBufferCount() const
	{
		return m_bufferCount;
	}

	u32 CDX12SwapChain::GetBackBufferWidth() const
	{
		return m_bufferWidth;
	}

	u32 CDX12SwapChain::GetBackBufferHeight() const
	{
		return m_bufferHeight;
	}

}	// namespace ng
