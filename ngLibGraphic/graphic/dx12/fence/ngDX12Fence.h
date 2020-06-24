/*!
* @file		ngDX12Fence.h
* @brief	DX12フェンス
* @date		2017-09-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_FENCE_H__
#define __NG_GRAPHIC_DX12_FENCE_H__

struct ID3D12Fence;

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12フェンス
	*/
	class NG_DECL CDX12Fence
	{
	public:
		CDX12Fence();
		~CDX12Fence();

		/*!
		* @brief					DX12フェンス生成
		* @param device				DX12デバイス
		* @param flags				フェンスオプション
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(CDX12Device& device, D3D12_FENCE_FLAGS flags = D3D12_FENCE_FLAG_NONE);
		
		/*!
		* @brief					現在のフェンス値を取得
		*/
		u64 GetCompletedValue();

		/*!
		* @brief					指定のフェンス値となった際にシグナル状態となるイベントを設定
		* @param value				シグナル状態となるフェンス値
		* @param hEvent				イベントハンドラ
		*/
		NG_ERRCODE SetEventOnCompletion(u64 value, HANDLE hEvent);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					有効か
		*/
		bool IsValid() const;
		
		/*!
		* @brief					DX12フェンス インターフェース取得
		*/
		ID3D12Fence* Interface();
		const ID3D12Fence* Interface() const;

	private:
		ID3D12Fence* m_pIFence;	//!< DX12フェンス インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_FENCE_H__