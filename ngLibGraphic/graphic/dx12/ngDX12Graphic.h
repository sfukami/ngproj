/*!
* @file		ngDX12Graphic.h
* @brief	DX12グラフィックス
* @date		2017-08-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_GRAPHIC_H__
#define __NG_GRAPHIC_DX12_GRAPHIC_H__

#include "../ngGraphic.h"

namespace ng
{
	/*!
	* @brief					DirectX12グラフィック
	*/
	class NG_DECL CDX12Graphic : public IGraphic
	{
	public:
		struct CreateParam
		{
			CreateParam();

			HWND hWnd;		//!< ウィンドウハンドル
			u32 clientWidth;	//!< クライアント領域幅
			u32 clientHeight;	//!< クライアント領域高さ
			bool isFullscreen;	//!< フルスクリーンか
		//	DX12DeviceCreateParam devCP;	//!< DX12デバイス生成パラメータ
		};

	public:
		CDX12Graphic();
		~CDX12Graphic();

		/*!
		* @brief					DirectX12グラフィック生成
		* @param param				生成パラメータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(const CreateParam& param);

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					破棄
		*/
		void Destroy();
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_GRAPHIC_H__