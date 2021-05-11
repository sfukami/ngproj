/*!
* @file		appMaterialDataPreset.h
* @brief	マテリアルデータのプリセット
* @date		2021-05-11
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_DATA_PRESET_H__
#define __APP_MATERIAL_DATA_PRESET_H__

namespace app
{
	class CMaterialData;
}

namespace app
{
	/*!
	* @brief					マテリアルデータのプリセット取得 スプライト
	*/
	const CMaterialData& GetMaterialDataPresetSprite();

}	// namespace app

#endif	// __APP_MATERIAL_DATA_PRESET_H__