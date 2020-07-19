/*!
* @file		ngRenderable.h
* @brief	描画可能オブジェクト インターフェース
* @date		2020-07-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDERABLE_H__
#define __NG_GRAPHIC_RENDERABLE_H__

namespace ng
{
	struct RenderParam;
}

namespace ng
{
	/*!
	* @brief					描画可能オブジェクト インターフェース
	*/
	class NG_DECL IRenderable
	{
	public:
		IRenderable() { }
		virtual ~IRenderable() { }

		/*!
		* @brief					描画
		* @param pParam				描画パラメータ
		* @note						描画コマンドの発行を行う
		*/
		virtual void Render(const RenderParam* pParam) = 0;
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDERABLE_H__