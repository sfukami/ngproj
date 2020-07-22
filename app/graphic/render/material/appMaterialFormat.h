/*!
* @file		appMaterialFormat.h
* @brief	マテリアルフォーマット
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_FORMAT_H__
#define __APP_MATERIAL_FORMAT_H__

namespace app
{
	/*!
	* @brief					テクスチャデータ
	*/
	struct TextureData
	{
		TextureData();

		char filePath[256];	//!< ファイルパス
		void* pBinary;		//!< バイナリへの参照
	};

	/*!
	* @brief					マテリアルデータ
	*/
	struct MaterialData
	{
		MaterialData();

		TextureData diffuseMap;	//!< ディフューズマップ
	};

}	// namespace app

#endif	//__APP_MATERIAL_FORMAT_H__
