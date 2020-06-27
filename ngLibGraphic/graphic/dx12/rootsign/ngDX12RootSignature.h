/*!
* @file		ngDX12RootSignature.h
* @brief	DX12ルートシグネチャ
* @date		2017-09-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_ROOT_SIGNATURE_H__
#define __NG_GRAPHIC_DX12_ROOT_SIGNATURE_H__

struct ID3D12RootSignature;
struct CD3DX12_ROOT_SIGNATURE_DESC;

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12ルートシグネチャ
	*/
	class NG_DECL CDX12RootSignature
	{
	public:
		CDX12RootSignature();
		~CDX12RootSignature();

		/*!
		* @brief					DX12ルートシグネチャ生成
		* @param device				DX12デバイス
		* @param desc				DX12ルートシグネチャ記述子
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(CDX12Device& device, const CD3DX12_ROOT_SIGNATURE_DESC& desc);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12ルートシグネチャ インターフェース取得
		*/
		ID3D12RootSignature* Interface();
		const ID3D12RootSignature* Interface() const;

	private:
		ID3D12RootSignature* m_pISignature;	//!< DX12ルートシグネチャ インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_ROOT_SIGNATURE_H__