/*!
* @file		appGraphic.h
* @brief	アプリケーショングラフィック
* @date		2020-06-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_H__
#define __APP_GRAPHIC_H__

#include <Windows.h>
#include "ngLibGraphic/graphic/dx12/ngDX12Graphic.h"
#include "material/appMaterialLibrary.h"
#include "rootsign/appRootSignatureManager.h"
#include "state/appPipelineStateManager.h"
#include "shader/effect/factory/appShaderEffectFactory.h"

namespace app
{
	class CGraphicPipeline;
}

namespace app
{
	/*!
	* @brief					アプリケーショングラフィック
	*/
	class CGraphic
	{
	public:
		CGraphic();
		~CGraphic();

		/*!
		* @brief					初期化
		* @param hWnd				ウィンドウハンドル
		* @param clientWidth		クライアント領域幅
		* @param clientHeight		クライアント領域高さ
		* @param isFullScreen		フルスクリーンか
		* @return					成否
		*/
		bool Initialize(
			HWND hWnd,
			unsigned int clientWidth,
			unsigned int clientHeight,
			bool isFullScreen
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					グラフィックパイプライン設定
		*/
		void SetPipeline(CGraphicPipeline* pPipeline);

		/*! DX12グラフィック取得 */
		ng::CDX12Graphic& GetDX12Graphic();
		const ng::CDX12Graphic& GetDX12Graphic() const;

		/*! マテリアルライブラリ取得 */
		CMaterialLibrary& GetMaterialLibrary();
		const CMaterialLibrary& GetMaterialLibrary() const;

		/*! ルートシグネチャ管理取得 */
		const CRootSignatureManager& GetRootSignatureManager() const;

		/*! パイプラインステート管理取得 */
		CPipelineStateManager& GetPipelineStateManager();
		const CPipelineStateManager& GetPipelineStateManager() const;

		/*! シェーダーエフェクトファクトリ取得 */
		const CShaderEffectFactory& GetShaderEffectFactory() const;

	private:
		/*! 初期化済みか */
		bool _isInit() const;

		/*! グラフィックパイプラインが有効か */
		bool _isValidPipeline() const;

	private:
		bool m_isInit;	//!< 初期化済みか
		
		ng::CDX12Graphic m_dx12Graphic;	//!< DX12グラフィック
		CGraphicPipeline* m_pPipeline;	//!< グラフィックパイプライン
		CMaterialLibrary m_matLib;	//!< マテリアルライブラリ
		CRootSignatureManager m_rootSignMngr;	//!< ルートシグネチャ管理
		CPipelineStateManager m_plStateMngr;	//!< パイプラインステート管理
		CShaderEffectFactory m_shEffFac;	//!< シェーダーエフェクトファクトリ
	};

}	// namespace app

#endif	// __APP_GRAPHIC_H__