/*!
* @file		appSpriteObject.h
* @brief	スプライトオブジェクト
* @date		2021-06-21
* @author	s.fukami
*/

#ifndef __APP_SPRITE_OBJECT_H__
#define __APP_SPRITE_OBJECT_H__

#include "app/graphic/render/appRenderable.h"
#include "app/transform/appTransformObject.h"
#include "app/graphic/render/sprite/appSpriteRender.h"

namespace ng
{
	struct Matrix4x4;
}
namespace app
{
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					スプライトオブジェクト
	*/
	class CSpriteObject : public IRenderable, public CTransformObject
	{
	public:
		CSpriteObject();
		~CSpriteObject();

		/*!
		* @brief					生成
		* @param width				幅
		* @param height				高さ
		* @param imageFilePath		画像ファイルのパス
		* @return					成否
		*/
		bool Create(
			ng::u32 width
			, ng::u32 height
			, const char* imageFilePath
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					ワールド変換行列取得
		*/
		void GetWorldMatrix(ng::Matrix4x4& dst);

		/*!
		* @brief					描画可能か
		*/
		void SetVisible(bool visible);
		bool IsVisible() const;

	private:
		/*! 描画 */
		void _render(const RenderParam& param);

	private:
		CSpriteRender m_sprite;	//!< スプライト描画
		bool m_isVisible;	//!< 描画可能か
	};

}	// namespace app

#endif	// __APP_SPRITE_OBJECT_H__