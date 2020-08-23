/*!
* @file		appMaterialLibrary.h
* @brief	マテリアルライブラリ
* @date		2020-07-30
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_LIBRARY_H__
#define __APP_MATERIAL_LIBRARY_H__

#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "../appGraphicConst.h"
#include "appMaterial.h"

namespace app
{
	class CMaterial;
}

namespace app
{
	/*!
	* @brief					マテリアルライブラリ
	*/
	class CMaterialLibrary
	{
	public:
		CMaterialLibrary();
		~CMaterialLibrary();

		/*!
		* @brief					マテリアル追加
		* @param name				マテリアル名
		* @param material			追加するマテリアル
		* @return					成否
		*/
		bool Add(const char* name, const CMaterial& material);

		/*!
		* @brief					マテリアルコピー
		* @param name				マテリアル名
		* @param dst				マテリアルのコピー先
		* @return					成否
		*/
		bool Copy(const char* name, CMaterial& dst);

		/*!
		* @brief					全てのマテリアルを削除
		*/
		void Clear();

	private:
		ng::CFixedHashMap<const char*, CMaterial, APP_GRAPHIC_MATERIAL_MAX> m_matMap;	//! マテリアル ハッシュマップ
	};

}	// namespace app

#endif	// __APP_MATERIAL_LIBRARY_H__