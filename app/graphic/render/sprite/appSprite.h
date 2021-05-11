/*!
* @file		appSprite.h
* @brief	スプライト
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_SPRITE_H__
#define __APP_SPRITE_H__

#include "../appRenderable.h"
#include "ngLibGraphic/graphic/dx12/polygon/shape/ngDX12ShapeSquare.h"
#include "app/transform/appTransformObject.h"
#include "app/graphic/material/appMaterial.h"

namespace app
{
	class CMaterialData;
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					スプライト
	*/
	class CSprite : public CRenderable, public CTransformObject
	{
	public:
		CSprite();
		~CSprite();

		/*!
		* @brief					生成
		* @param width				幅
		* @param height				高さ
		* @param pMaterialData		マテリアルデータ。nullptr の場合は、デフォルトのマテリアルデータを使用する
		* @return					成否
		*/
		bool Create(
			unsigned int width
			, unsigned int height
			, const CMaterialData* pMaterialData = nullptr
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
		void _render(const RenderParam* pParam);

		/*! 生成済みか */
		bool _isCreate() const;

	private:
		ng::CDX12ShapeSquare m_square;	//!< DX12ポリゴン 矩形
		CMaterial m_material;	//!< マテリアル
	};

}	// namespace app

#endif	// __APP_SPRITE_H__