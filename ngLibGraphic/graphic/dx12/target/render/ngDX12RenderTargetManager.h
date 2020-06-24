/*!
* @file		ngDX12RenderTargetManager.h
* @brief	DX12レンダーターゲットマネージャ
* @date		2018-05-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RENDER_TARGET_MANAGER_H__
#define __NG_GRAPHIC_DX12_RENDER_TARGET_MANAGER_H__

//#include "../../common/ngDX12Common.h"
#include "ngDX12RenderTargetId.h"
#include "ngDX12RenderTarget.h"

namespace ng
{
	class CDX12Device;
	class CDX12SwapChain;
	class CDX12RenderTarget;
}

namespace ng
{
	/*!
	* @brief					DX12レンダーターゲットマネージャ
	*/
	class NG_DECL CDX12RenderTargetManager
	{
	public:
		CDX12RenderTargetManager();
		~CDX12RenderTargetManager();

		/*!
		* @brief					DX12レンダーターゲット生成
		* @param device				DX12デバイス
		* @param swapChain			DX12スワップチェイン
		* @param bufferIndex		レンダリングバッファのインデックス
		* @param id					DX12レンダーターゲットID
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateRenderTargetView(
			CDX12Device& device,
			CDX12SwapChain& swapChain,
			u32 bufferIndex,
			eDX12RenderTargetId id
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12レンダーターゲット取得
		*/
		CDX12RenderTarget* GetRenderTarget(eDX12RenderTargetId id);
		const CDX12RenderTarget* GetRenderTarget(eDX12RenderTargetId id) const;

	private:
		CDX12RenderTarget m_rts[ static_cast<u32>(eDX12RenderTargetId::ID_NUM) ];	//!< DX12レンダーターゲット配列
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RENDER_TARGET_MANAGER_H__