/*!
* @file		ngDX12ResourceBarrierTransition.h
* @brief	DX12リソースバリア トランジション
* @date		2018-01-09
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RESOURCE_BARRIER_TRANSITION_H__
#define __NG_GRAPHIC_DX12_RESOURCE_BARRIER_TRANSITION_H__

#include <d3dx12.h>
#include "ngDX12ResourceBarrier.h"

struct ID3D12Resource;

namespace ng
{
	/*!
	* @brief					DX12リソースバリア トランジション
	*/
	class NG_DECL CDX12ResourceBarrierTransition : public CDX12ResourceBarrier
	{
	public:
		CDX12ResourceBarrierTransition();
		~CDX12ResourceBarrierTransition();

		/*!
		* @brief					初期化
		* @param pResource			DX12リソース
		* @param stateBefore		バリア前のリソース使用方法を指定するステート
		* @param stateAfter			バリア後のリソース使用方法を指定するステート
		* @param subresource		サブリソースのインデックス
		* @param flags				リソースバリアのフラグ
		*/
		void Initialize(
			ID3D12Resource* pResource,
			D3D12_RESOURCE_STATES stateBefore,
			D3D12_RESOURCE_STATES stateAfter,
			UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
			D3D12_RESOURCE_BARRIER_FLAGS flags = D3D12_RESOURCE_BARRIER_FLAG_NONE
			);
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RESOURCE_BARRIER_TRANSITION_H__