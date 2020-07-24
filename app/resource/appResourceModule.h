/*!
* @file		appResourceModule.h
* @brief	リソースモジュール
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_MODULE_H__
#define __APP_RESOURCE_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "memory/appResourceMemoryType.h"

namespace ng
{
	class IResourceHandle;
}
namespace app
{
	class CResourceSystem;
}

namespace app
{
	/*!
	* @brief					リソースモジュール
	*/
	class CResourceModule : public ng::CNonInstantiable
	{
		friend class CApplication;

	public:
		/*!
		* @brief					リソース読み込み
		* @param fileName			ファイル名
		* @param resMemType			リソースメモリタイプ
		* @param pBuildParam		ビルドパラメータ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		static bool LoadResource(
			const char* fileName, eResourceMemoryType resMemType, const void* pBuildParam, ng::IResourceHandle& handle
			);

	private:
		/*! リソースシステムへの参照を設定 */
		static void SetResourceSystem(CResourceSystem* pResSys);

		/*! 有効か */
		static bool _isValid();

	private:
		static CResourceSystem* s_pResSys;	//!< リソースシステムへの参照
	};

}	// namespace app

#endif	// __APP_RESOURCE_MODULE_H__