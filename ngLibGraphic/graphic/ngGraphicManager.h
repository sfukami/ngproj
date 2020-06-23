/*!
* @file		ngGraphicManager.h
* @brief	グラフィック管理
* @date		2020-06-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_GRAPHIC_MANAGER_H__
#define __NG_GRAPHIC_GRAPHIC_MANAGER_H__

#include "ngLibCore/traits/ngSingleton.h"

namespace ng
{
	class IGraphic;
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
		* @brief					グラフィック割り当て
		*/
		void AssignGraphic(IGraphic* pGraphic);

		/*!
		* @brief					描画
		*/
		void Render();

		/*!
		* @brief					グラフィック割り当て解除
		*/
		void UnassignGraphic();

		/*!
		* @brief					グラフィックが割り当て済みか
		*/
		bool IsAssigned() const;

	private:
		static CGraphicManager m_instance;	//!< グラフィック管理 インスタンス

	private:
		IGraphic* m_pGraphic;	//!< グラフィック
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_GRAPHIC_MANAGER_H__