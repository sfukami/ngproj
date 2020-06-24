/*!
* @file		ngDX12CommandAllocator.h
* @brief	DX12コマンドアロケーター
* @date		2017-09-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_H__
#define __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_H__

#include <d3d12.h>

struct ID3D12CommandAllocator;

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドアロケーター
	*/
	class NG_DECL CDX12CommandAllocator
	{
	public:
		CDX12CommandAllocator();
		~CDX12CommandAllocator();

		/*!
		* @brief					DX12コマンドアロケーター生成
		* @param device				DX12デバイス
		* @param type				コマンドリストのタイプ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(CDX12Device& device, D3D12_COMMAND_LIST_TYPE type);
		
		/*!
		* @brief					メモリ再利用のためのリセット処理
		* @return					NG エラーコード
		*/
		NG_ERRCODE Reset();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;
		
		/*!
		* @brief					DX12コマンドアロケーター インターフェース取得
		*/
		ID3D12CommandAllocator* Interface();
		const ID3D12CommandAllocator* Interface() const;

		/*!
		* @brief					コマンドリストのタイプ取得
		*/
		D3D12_COMMAND_LIST_TYPE GetCommandListType() const;
		
	private:
		ID3D12CommandAllocator* m_pIAllocator;	//!< DX12コマンドアロケーター インターフェース
		D3D12_COMMAND_LIST_TYPE m_cmdListType;	//!< コマンドリストのタイプ
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_ALLOCATOR_H__