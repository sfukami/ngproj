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
		* @brief					描画
		* @param pParam				描画パラメータ
		*/
		void Render(const RenderParam* pParam);

		/*!
		* @brief					描画の後処理
		*/
		void CleanupRender();

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
		static CGraphicManager m_instance;	//!< グラフィック管理 インスタンス

	private:
		IGraphic* m_pGraphic;	//!< グラフィック
		CRenderSystem m_renderSys;	//!< 描画システム
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_GRAPHIC_MANAGER_H__