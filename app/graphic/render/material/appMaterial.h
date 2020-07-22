/*!
* @file		appMaterial.h
* @brief	マテリアル
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_MATERIAL_H__
#define __APP_MATERIAL_H__

#include "ngLibApp/resource/ngResourceHandle.h"
#include "app/resource/texture/appTexture.h"

namespace app
{
	struct MaterialData;
}

namespace app
{
	/*!
	* @brief					マテリアル
	*/
	class CMaterial
	{
	public:
		CMaterial();
		~CMaterial();

		/*!
		* @brief					マテリアル構築
		* @param data				マテリアルデータ
		* @return					成否
		*/
		bool Build(const MaterialData& data);

		/*!
		* @brief					破棄
		*/
		void Destroy();

	private:
		ng::CResourceHandle<CTexture> m_diffuseMap;	//!< ディフューズマップ
	};

}	// namespace app

#endif	// __APP_MATERIAL_H__