/*!
* @file		ngImGuiDX12.h
* @brief	ImGuiラッパー DirectX12版
* @date		2020-07-04
* @author	s.fukami
*/

#ifndef __NG_APP_IMGUI_DX12_H__
#define __NG_APP_IMGUI_DX12_H__

#include <Windows.h>
#include "ngLibGraphic/graphic/dx12/descriptor/ngDX12DescriptorHeap.h"

namespace ng
{
	class CDX12Device;
	class CDX12CommandList;
}

namespace ng
{
	/*!
	* @brief					ImGui DirectX12版
	*/
	class NG_DECL CImGuiDX12
	{
	public:
		CImGuiDX12();
		~CImGuiDX12();

		/*!
		* @brief					セットアップ
		* @param hWnd				ウィンドウハンドル
		* @param device				DX12デバイス
		* @param formatRTV			レンダーターゲットのフォーマット
		* @param numFramesInFlight	フレームリソースの数
		* @param enableKeyboard		キーボードを使用するか
		* @param enableMouse		マウスを利用するか
		* @return					NG エラーコード
		*/
		NG_ERRCODE Setup(
			HWND hWnd
			, CDX12Device& device
			, enum DXGI_FORMAT formatRTV
			, int numFramesInFlight
			, bool enableKeyboard
			, bool enableMouse
			);

		/*!
		* @brief					ImGui描画前処理
		* @note						そのフレームの描画前に1度だけ呼び出す
		*/
		void NewFrame();

		/*!
		* @brief					描画
		*/
		void Render(CDX12CommandList& commandList);

		/*!
		* @brief					ImGui描画後処理
		* @note						そのフレームの描画後に1度だけ呼び出す
		*/
		void EndFrame();

		/*!
		* @brief					終了処理
		*/
		void Shutdown();

		/*!
		* @brief					ImGui ウィンドウプロシージャ
		* @note						ウィンドウプロシージャ内で呼び出す。キーボード、マウスを用いる場合は必須
		*/
		static LRESULT WinProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		CDX12DescriptorHeap m_descHeapSRV;	//!< DX12ディスクリプタヒープ
	};

}	// namespace ng

#endif	// __NG_APP_IMGUI_DX12_H__