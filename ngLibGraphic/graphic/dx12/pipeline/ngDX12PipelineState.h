/*!
* @file		ngDX12PipelineState.h
* @brief	DX12パイプラインステート
* @date		2019-03-24
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_PIPELINE_STATE_H__
#define __NG_GRAPHIC_DX12_PIPELINE_STATE_H__

struct ID3D12PipelineState;

namespace ng
{
	class CDX12Device;
	class CDX12GraphicPipelineStateDesc;
}

namespace ng
{
	/*!
	* @brief					DX12パイプラインステート
	*/
	class NG_DECL CDX12PipelineState
	{
	public:
		CDX12PipelineState();
		~CDX12PipelineState();

		/*!
		* @brief					DX12パイプラインステート生成
		* @param device				DX12デバイス
		* @param desc				
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(
			CDX12Device& device,
			const CDX12GraphicPipelineStateDesc& desc
			);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					有効か
		*/
		bool IsValid() const;

		/*!
		* @brief					DX12パイプラインステート インターフェース取得
		*/
		ID3D12PipelineState* Interface();
		const ID3D12PipelineState* Interface() const;

	private:
		ID3D12PipelineState* m_pIState;	//!< DX12パイプラインステート インターフェース
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_PIPELINE_STATE_H__