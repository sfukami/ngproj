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
		* @brief					描画
		*/
		virtual void Render() = 0;
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_GRAPHIC_H__