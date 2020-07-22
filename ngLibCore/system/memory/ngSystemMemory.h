/*!
* @file		ngSystemMemory.h
* @brief	NGライブラリ システムメモリ
* @date		2018-02-19
* @author	s.fukami
*/

#ifndef __NG_CORE_SYSTEM_MEMORY_H__
#define __NG_CORE_SYSTEM_MEMORY_H__

#include "ngSystemMemoryType.h"
#include "ngLibCore/memory/pool/ngRootMemoryPool.h"
#include "ngLibCore/memory/ngMemoryManager.h"
#include "ngLibCore/memory/pointer/ngWeakPtr.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace ng
{
	/*!
	* @brief					NGライブラリ システムメモリ
	*/
	class NG_DECL CSystemMemory
	{
	public:
		//! 初期化パラメータ
		struct InitParam
		{
			InitParam();
			
			//! アロケーション情報
			struct AllocInfo
			{
				size_type allocSize;	//!< アロケーションサイズ

			} allocInfo[ static_cast<int>(eSystemMemoryType::NUM) ];

			/*! アロケーションサイズ設定 */
			void SetAllocSize(eSystemMemoryType type, size_type allocSize);

			/*! アロケーション情報取得 */
			const AllocInfo& GetAllocInfo(eSystemMemoryType type) const;

			/*! 合計アロケーションサイズ取得 */
			size_type GetTotalAllocSize() const;
		};

	public:
		CSystemMemory();
		~CSystemMemory();

		/*!
		* @brief					初期化
		* @param param				初期化パラメータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(const InitParam& param);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					メモリアロケータ取得
		* @param type				システムメモリタイプ
		* @return					メモリアロケータ
		*/
		CWeakPtr<IMemoryAllocator> GetAllocator(eSystemMemoryType type);

	private:
		CRootMemoryPool	m_memPool;	//!< メモリプール
		CMemoryManager	m_memMngr;	//!< メモリ管理
	};

}	// namespace ng

#endif	// __NG_CORE_SYSTEM_MEMORY_H__