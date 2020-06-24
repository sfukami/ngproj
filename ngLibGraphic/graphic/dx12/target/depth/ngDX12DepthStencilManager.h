/*!
* @file		ngDX12DepthStencilManager.h
* @brief	DX12深度ステンシルマネージャ
* @date		2019-08-14
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DEPTH_STENCIL_MANAGER_H__
#define __NG_GRAPHIC_DX12_DEPTH_STENCIL_MANAGER_H__

#include "ngDX12DepthStencil.h"
#include "ngDX12DepthStencilId.h"

namespace ng
{
	class CDX12Device;
}

namespace ng
{
	/*!
	* @brief					DX12深度ステンシルマネージャ
	*/
	class NG_DECL CDX12DepthStencilManager
	{
	public:
		CDX12DepthStencilManager();
		~CDX12DepthStencilManager();

		/*!
		* @brief					DX12深度ステンシル生成
		* @param device				DX12デバイス
		* @param width				幅
		* @param height				高さ
		* @param id					DX12深度ステンシルID
		* @return					NG エラーコード
		*/
		NG_ERRCODE CreateDepthStencil(
			CDX12Device& device,
			u32 width,
			u32 height,
			eDX12DepthStencilId id
			);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					DX12深度ステンシル取得
		*/
		CDX12DepthStencil* GetDepthStencil(eDX12DepthStencilId id);
		const CDX12DepthStencil* GetDepthStencil(eDX12DepthStencilId id) const;

	private:
		CDX12DepthStencil m_dss[ static_cast<u32>(eDX12DepthStencilId::ID_NUM) ];	//!< DX12深度ステンシル配列
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DEPTH_STENCIL_MANAGER_H__