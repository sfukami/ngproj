/*!
* @file		ngDX12ResourceBarrier.h
* @brief	DX12リソースバリア
* @date		2018-01-09
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_RESOURCE_BARRIER_H__
#define __NG_GRAPHIC_DX12_RESOURCE_BARRIER_H__

#include <d3dx12.h>

namespace ng
{
	/*!
	* @brief					DX12リソースバリア
	*/
	class NG_DECL CDX12ResourceBarrier
	{
	public:
		CDX12ResourceBarrier();
		~CDX12ResourceBarrier();

		/*!
		* @brief					DX12リソースバリア取得
		*/
		const D3D12_RESOURCE_BARRIER& GetResourceBarrier() const;

	protected:
		D3D12_RESOURCE_BARRIER m_barrier;	//!< DX12リソースバリア
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_RESOURCE_BARRIER_H__