/*!
* @file		appMaterialUtil.h
* @brief	マテリアル ユーティリティ
* @date		2021-06-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_UTIL_H__
#define __APP_MATERIAL_UTIL_H__

namespace app
{
	struct MaterialFormat;
}

namespace app
{
namespace MaterialUtil
{
	/*!
	* @brief					スプライト用のマテリアルフォーマットを取得
	*/
	void GetMaterialFormatSprite(MaterialFormat* pDst);

	/*!
	* @brief					モデル用のマテリアルフォーマットを取得
	*/
	void GetMaterialFormatModel(MaterialFormat* pDst);

}	// namespace MaterialUtil
}	// namespace app

#endif	// __APP_MATERIAL_UTIL_H__