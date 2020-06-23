/*!
* @file		ngCoreSystem.h
* @brief	NGライブラリ コアシステム
* @date		2018-02-12
* @author	s.fukami
*/

#ifndef __NG_CORE_CORE_SYSTEM_H__
#define __NG_CORE_CORE_SYSTEM_H__

#include "ngLibCore/traits/ngSingleton.h"
#include "memory/ngSystemMemory.h"

namespace ng
{
	/*!
	* @brief					NGライブラリ コアシステム
	*/
	class NG_DECL CCoreSystem : public CSingleton<CCoreSystem>
	{
		NG_SINGLETON(CCoreSystem);

	public:
		// セットアップパラメータ
		struct SetupParam
		{
			SetupParam();

			CSystemMemory::InitParam sysMemInitParam;	//!< システムメモリ 初期化パラメータ
		};

	private:
		CCoreSystem();
		virtual ~CCoreSystem();

	public:
		/*!
		* @brief					セットアップ
		* @param param				セットアップパラメータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Setup(const SetupParam& param);

		/*!
		* @brief					終了処理
		*/
		void Shutdown();

		/*!
		* @brief					システムメモリアロケータ取得
		* @param type				システムメモリタイプ
		* @return					メモリアロケータ
		*/
		IMemoryAllocator* GetSysMemAlloc(eSystemMemoryType type);

	private:
		static CCoreSystem m_instance;	//!< コアシステム インスタンス

	private:
		CSystemMemory m_sysMem;	//!< システムメモリ
	};

}	// namespace ng

#endif	// __NG_CORE_CORE_SYSTEM_H__