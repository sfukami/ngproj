/*!
* @file		appResourceSystem.h
* @brief	リソースシステム
* @date		2020-07-22
* @author	s.fukami
*/

#ifndef __APP_RESOURCE_SYSTEM_H__
#define __APP_RESOURCE_SYSTEM_H__

#include "ngLibApp/resource/ngResourceManager.h"
#include "memory/appResourceMemory.h"
#include "memory/appResourceMemoryType.h"

namespace ng
{
	class IMemoryAllocator;
	class IResourceHandle;
}

namespace app
{
	/*!
	* @brief					リソースシステム
	*/
	class CResourceSystem
	{
	public:
		CResourceSystem();
		~CResourceSystem();

		/*!
		* @brief					初期化
		* @param alloc				利用するメモリアロケータ
		* @param resMax				リソース最大数
		* @return					成否
		*/
		bool Initialize(ng::IMemoryAllocator& alloc, unsigned int resMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					リソース読み込み
		* @param fileName			ファイル名
		* @param resMemType			リソースメモリタイプ
		* @param handle				格納先のリソースハンドル
		* @return					成否
		*/
		bool LoadResource(const char* fileName, eResourceMemoryType resMemType, ng::IResourceHandle& handle);

	private:
		/*! テクスチャ読み込み */
		bool _loadTexture(const char* fileName, eResourceMemoryType resMemType, ng::IResourceHandle& handle);

	private:
		CResourceMemory m_resMem;	//!< リソースメモリ
		ng::CResourceManager m_resMngr;	//!< リソース管理
	};

}	// namespace app

#endif	//__APP_RESOURCE_SYSTEM_H__