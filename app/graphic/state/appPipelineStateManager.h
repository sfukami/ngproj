/*!
* @file		appPipelineStateManager.h
* @brief	パイプラインステート管理
* @date		2020-07-29
* @author	s.fukami
*/

#ifndef __APP_PIPELINE_STATE_MANAGER_H__
#define __APP_PIPELINE_STATE_MANAGER_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "../appGraphicConst.h"

namespace ng
{
	template <class T> class CWeakPtr;
	class IMemoryAllocator;
	class CDX12PipelineState;
	class CDX12PipelineStateDesc;
}

namespace app
{
	/*!
	* @brief					パイプラインステート管理
	*/
	class CPipelineStateManager
	{
	public:
		CPipelineStateManager();
		~CPipelineStateManager();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12パイプラインステート追加
		* @param name				DX12パイプラインステートの名前
		* @param statePtr			DX12パイプラインステートへの参照
		* @return					成否
		*/
		bool Add(const char* name, const ng::CSharedPtr<ng::CDX12PipelineState>& statePtr);

		/*!
		* @brief					DX12パイプラインステートを生成し追加
		* @param alloc				使用するメモリアロケータ
		* @param name				DX12パイプラインステートの名前
		* @param stateDesc			DX12パイプラインステート記述子
		* @return					成否
		*/
		bool CreateAndAdd(ng::IMemoryAllocator& alloc, const char* name, const ng::CDX12PipelineStateDesc& stateDesc);

		/*!
		* @brief					DX12パイプラインステート取得
		* @param name				DX12パイプラインステートの名前
		* @param dstPtr				取得したDX12パイプラインステートの格納先
		* @return					成否
		*/
		bool Get(const char* name, ng::CWeakPtr<ng::CDX12PipelineState>& dstPtr) const;

	private:
		//! DX12パイプラインステート ハッシュマップ
		ng::CFixedHashMap<const char*, ng::CSharedPtr<ng::CDX12PipelineState>, APP_GRAPHIC_PIPELINE_STATE_MAX> m_stateMap;
	};

}	// namespace app

#endif	// __APP_PIPELINE_STATE_MANAGER_H__