/*!
* @file		appSpriteRender.h
* @brief	スプライト描画
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_SPRITE_RENDER_H__
#define __APP_SPRITE_RENDER_H__

#include "../appRender.h"
#include "ngLibGraphic/graphic/dx12/polygon/shape/ngDX12ShapeSquare.h"
#include "app/graphic/material/appMaterial.h"
#include "app/resource/memory/appResourceMemoryType.h"

namespace app
{
	struct RenderParam;
	struct MaterialFormat;
}

namespace app
{
	/*!
	* @brief					スプライト描画
	*/
	class CSpriteRender : public IRender
	{
	public:
		CSpriteRender();
		~CSpriteRender();

		/*!
		* @brief					生成
		* @param width				幅
		* @param height				高さ
		* @param imageFilePath		画像ファイルのパス
		* @param resMemType			リソースメモリタイプ
		* @return					成否
		*/
		bool Create(
			ng::u32 width
			, ng::u32 height
			, const char* imageFilePath
			, eResourceMemoryType resMemType
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					描画可能か
		*/
		bool IsEnable() const;

	private:
		/*! 描画 */
		void _render(const RenderParam& param);

		/*! マテリアルフォーマットを取得 */
		void _getMaterialFormat(MaterialFormat* pDst);

	private:
		ng::CDX12ShapeSquare m_square;	//!< DX12ポリゴン 矩形
		CMaterial m_material;	//!< マテリアル
	};

}	// namespace app

#endif	// __APP_SPRITE_RENDER_H__