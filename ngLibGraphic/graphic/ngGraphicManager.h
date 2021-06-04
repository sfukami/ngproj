/*!
* @file		ngGraphicManager.h
* @brief	グラフィック管理
* @date		2020-06-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_GRAPHIC_MANAGER_H__
#define __NG_GRAPHIC_GRAPHIC_MANAGER_H__

#include "ngLibCore/traits/ngSingleton.h"
#include "ngLibGraphic/render/ngRenderSystem.h"

namespace ng
{
	class IGraphic;
	class IRenderable;
	struct RenderParam;
}

namespace ng
{
	/*!
	* @brief					グラフィック管理
	*/
	class NG_DECL CGraphicManager : public CSingleton<CGraphicManager>
	{
		NG_SINGLETON(CGraphicManager);

	private:
		CGraphicManager();
		~CGraphicManager();

	public:
		/*!
		* @brief					初期化
		* @param commandMax			描画コマンド最大数
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(u32 commandMax);
		
		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					グラフィック割り当て
		*/
		void AssignGraphic(IGraphic* pGraphic);

		/*!
		* @brief					描画可能オブジェクトを追加
		*/
		void AddRenderable(IRenderable& renderable);

		/*!
		* @brief					登録済みの全描画可能オブジェクトの描画コマンドを送出
		* @param pParam				描画パラメータ
		*/
		void DispatchRenderCommand(const RenderParam* pParam);

		/*!
		* @brief					描画開始処理
		*/
		void BeginRender();

		/*!
		* @brief					描画処理
		*/
		void ExecuteRender();

		/*!
		* @brief					描画終了処理
		*/
		void EndRender();
	
		/*!
		* @brief					グラフィック割り当て解除
		*/
		void UnassignGraphic();

		/*!
		* @brief					グラフィックが割り当て済みか
		*/
		bool IsAssigned() const;

		/*!
		* @brief					割り当て済みのグラフィックを取得
		*/
		IGraphic* GetGraphic();
		const IGraphic* GetGraphic() const;

	private:
		/*! 初期化済みか */
		bool _isInit() const;

	private:
		static CGraphicManager m_instance;	//!< グラフィック管理 インスタンス

	private:
		IGraphic* m_pGraphic;	//!< グラフィック
		CRenderSystem m_renderSys;	//!< 描画システム

		bool m_isInit;	//!< 初期化済みか
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_GRAPHIC_MANAGER_H__