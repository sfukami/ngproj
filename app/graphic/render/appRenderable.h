/*!
* @file		appRenderable.h
* @brief	描画可能オブジェクト インターフェース
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_RENDERABLE_H__
#define __APP_RENDERABLE_H__

#include "ngLibGraphic/render/ngRenderable.h"

namespace ng
{
	struct RenderParam;
	struct Matrix4x4;
}
namespace app
{
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					描画可能オブジェクト インターフェース
	*/
	class IRenderable : ng::IRenderable
	{
	public:
		IRenderable();
		virtual ~IRenderable();

		/*!
		* @brief					描画登録
		*/
		void RegisterRender();

		/*!
		* @brief					描画
		* @param pParam				描画パラメータ
		*/
		void Render(const ng::RenderParam* pParam);

		/*!
		* @brief					ワールド変換行列取得
		*/
		virtual void GetWorldMatrix(ng::Matrix4x4& dst) = 0;

		/*!
		* @brief					描画可能か
		*/
		virtual void SetVisible(bool visible) = 0;
		virtual bool IsVisible() const = 0;

	private:
		/*! 描画 */
		virtual void _render(const RenderParam& param) = 0;
	};

}	// namespace app

#endif	// __APP_RENDERABLE_H__