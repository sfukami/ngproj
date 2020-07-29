/*!
* @file		appRootSignatureManager.h
* @brief	ルートシグネチャ管理
* @date		2020-07-26
* @author	s.fukami
*/

#ifndef __APP_ROOT_SIGNATURE_MANAGER_H__
#define __APP_ROOT_SIGNATURE_MANAGER_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "../appGraphicConst.h"

namespace ng
{
	template <class T> class CWeakPtr;
	class IMemoryAllocator;
	class CDX12Device;
	class CDX12RootSignature;
}

namespace app
{
	/*!
	* @brief					ルートシグネチャ管理
	*/
	class CRootSignatureManager
	{
	public:
		CRootSignatureManager();
		~CRootSignatureManager();

		/*!
		* @brief					初期化
		* @param alloc				使用するメモリアロケータ
		* @param device				DX12デバイス
		* @return					成否
		*/
		bool Initialize(ng::IMemoryAllocator& alloc, ng::CDX12Device& device);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12ルートシグネチャ取得
		* @param name				DX12ルートシグネチャの名前
		* @param dstPtr				取得したDX12ルートシグネチャの格納先
		* @return					成否
		*/
		bool Get(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr) const;

	private:
		//! DX12ルートシグネチャ ハッシュマップ
		ng::CFixedHashMap<const char*, ng::CSharedPtr<ng::CDX12RootSignature>, APP_GRAPHIC_ROOT_SIGNATURE_MAX> m_rootSignMap;
	};

}	// namespace app

#endif	// __APP_ROOT_SIGNATURE_MANAGER_H__