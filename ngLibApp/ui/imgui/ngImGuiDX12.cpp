/*!
* @file		ngImGuiDX12.cpp
* @brief	ImGuiラッパー DirectX12版
* @date		2020-07-04
* @author	s.fukami
*/

#include <d3d12.h>
#include <dxgi.h>
#include "ngLibGraphic/graphic/dx12/device/ngDX12Device.h"
#include "ngLibGraphic/graphic/dx12/command/list/ngDX12CommandList.h"
#include "ngLibApp/common/ngCommon.h"
#include "ngImGuiDX12.h"
// ImGui
#include "imgui_src/imgui.h"
#include "imgui_src/imgui_impl_win32.h"
#include "imgui_src/imgui_impl_dx12.h"

namespace ng
{
	CImGuiDX12::CImGuiDX12()
	{
	}
	CImGuiDX12::~CImGuiDX12()
	{
	}

	NG_ERRCODE CImGuiDX12::Setup(
		HWND hWnd
		, CDX12Device& device
		, enum DXGI_FORMAT formatRTV
		, int numFramesInFlight
		, bool enableKeyboard
		, bool enableMouse
		)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if(enableKeyboard) {
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			}
			if(enableMouse) {
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			}
		}
		
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// ImGui Win32 初期化
		if(!ImGui_ImplWin32_Init(hWnd)) {
			NG_ERRLOG("ImGuiDX12", "ImGui Win32 の初期化に失敗しました.");
			return eNG_E_FAIL;
		}

		// DX12ディスクリプタヒープ生成
		{
			NG_ERRCODE ret = m_descHeapSRV.Create(
				device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
				);
			if(NG_FAILED(ret)) {
				NG_ERRLOG_C("ImGuiDX12", ret, "DX12ディスクリプタヒープの生成に失敗しました.");
				return ret;
			}
		}
		// ImGuiDX12 初期化
		if(!ImGui_ImplDX12_Init(
			device.Interface(),
			numFramesInFlight,
			formatRTV,
			m_descHeapSRV.Interface(),
			m_descHeapSRV.GetCPUDescriptorHandleForHeapStart(),
			m_descHeapSRV.GetGPUDescriptorHandleForHeapStart()
			)) {
			NG_ERRLOG("ImGuiDX12", "ImGuiDX12 の初期化に失敗しました.");
			return eNG_E_FAIL;
		}

		return eNG_S_OK;
	}

	void CImGuiDX12::NewFrame()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void CImGuiDX12::Render(CDX12CommandList& commandList)
	{
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.Interface());
	}

	void CImGuiDX12::EndFrame()
	{
		ImGui::EndFrame();
	}

	void CImGuiDX12::Shutdown()
	{
		m_descHeapSRV.Destroy();

		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	LRESULT CImGuiDX12::WinProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	}

}	// namespace ng