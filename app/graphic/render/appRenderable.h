/*!
* @file		appRenderable.h
* @brief	描画可能オブジェクト
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_RENDERABLE_H__
#define __APP_RENDERABLE_H__

#include "ngLibGraphic/render/ngRenderable.h"

namespace ng
{
	struct RenderParam;
}
namespace app
{
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					描画可能オブジェクト
	*/
	class CRenderable : ng::IRenderable
	{
	public:
		CRenderable();
		~CRenderable();

		/*!
		* @brief					描画登録
		*/
		void RegisterRender();

		/*!
		* @brief					描画
		* @param pParam				描画パラメータ
		* @note						描画コマンドの発行を行う
		*/
		void Render(const ng::RenderParam* pParam);

		/*!
		* @brief					描画可能か
		*/
		virtual bool IsEnable() const;

	private:
		/*! 描画 */
		virtual void _render(const RenderParam* pParam);
	};

}	// namespace app

#endif	// __APP_RENDERABLE_H__