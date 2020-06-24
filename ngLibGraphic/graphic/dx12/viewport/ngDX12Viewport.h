/*!
* @file		ngDX12Viewport.h
* @brief	DX12ビューポート
* @date		2018-01-20
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_VIEWPORT_H__
#define __NG_GRAPHIC_DX12_VIEWPORT_H__

#include <d3d12.h>

namespace ng
{
	/*!
	* @brief					DX12ビューポート
	*/
	class NG_DECL CDX12Viewport
	{
	public:
		CDX12Viewport();
		~CDX12Viewport();

		/*!
		* @param				初期化
		* @param topLeftX		ビューポート左上X座標
		* @param topLeftY		ビューポート左上Y座標
		* @param width			ビューポート幅
		* @param height			ビューポート高さ
		* @param minDepth		ビューポート深度最小値[0,1]
		* @param maxDepth		ビューポート深度最大値[0,1]
		*/
		void Initialize(
			float topLeftX,
			float topLeftY,
			float width,
			float height,
			float minDepth,
			float maxDepth
			);
		
		/*!
		* @param				DX12ビューポート取得
		*/
		const D3D12_VIEWPORT& GetViewport() const;

	private:
		D3D12_VIEWPORT m_viewport;	//!< DX12ビューポート
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_VIEWPORT_H__