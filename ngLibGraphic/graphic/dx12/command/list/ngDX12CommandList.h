/*!
* @file		ngDX12CommandList.h
* @brief	DX12コマンドリスト
* @date		2017-09-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_LIST_H__
#define __NG_GRAPHIC_DX12_COMMAND_LIST_H__

#include "../allocator/ngDX12CommandAllocator.h"

struct ID3D12GraphicsCommandList;
struct D3D12_GPU_DESCRIPTOR_HANDLE;

namespace ng
{
	class CDX12Device;
	class CDX12CommandAllocator;
}

namespace ng
{
	/*!
	* @brief					DX12コマンドリスト
	*/
	class NG_DECL CDX12CommandList
	{
	public:
		typedef ID3D12GraphicsCommandList DX12IfType;	//!< DX12インターフェースの型

	public:
		CDX12CommandList();
		~CDX12CommandList();

		/*!
		* @brief					DX12コマンドリスト生成
		* @param device				DX12デバイス
		* @param allocator			DX12コマンドアロケータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			CDX12CommandAllocator& allocator
			);

		/*!
		* @brief					コマンドの記録を終了
		*/
		NG_ERRCODE Close();

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12コマンドリスト インターフェース取得
		*/
		DX12IfType* Interface();
		const DX12IfType* Interface() const;

	private:
		DX12IfType* m_pIList;	//!< DX12コマンドリスト インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_LIST_H__