/*!
* @file		ngGraphic.h
* @brief	グラフィック インターフェース
* @date		2020-06-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_GRAPHIC_H__
#define __NG_GRAPHIC_GRAPHIC_H__

namespace ng
{
	/*!
	* @brief					グラフィック インターフェース
	*/
	class NG_DECL IGraphic
	{
	public:
		/*!
		* @brief					描画開始処理
		*/
		virtual void BeginRender() = 0;

		/*!
		* @brief					描画処理
		*/
		virtual void ExecuteRender() = 0;

		/*!
		* @brief					描画終了処理
		*/
		virtual void EndRender() = 0;
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_GRAPHIC_H__