/*!
* @file		ngDX12Scissor.h
* @brief	DX12シザー矩形
* @date		2018-01-20
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_SCISSOR_H__
#define __NG_GRAPHIC_DX12_SCISSOR_H__

#include <d3dx12.h>

namespace ng
{
	/*!
	* @brief					DX12シザー矩形
	*/
	class NG_DECL CDX12Scissor
	{
	public:
		CDX12Scissor();
		~CDX12Scissor();

		/*!
		* @param				初期化
		* @param left			シザー矩形左辺
		* @param top			シザー矩形上辺
		* @param right			シザー矩形右辺
		* @param bottom			シザー矩形下辺
		*/
		void Initialize(
			LONG left,
			LONG top,
			LONG right,
			LONG bottom
			);
		
		/*!
		* @param				DX12シザー矩形取得
		*/
		const CD3DX12_RECT& GetScissorRect() const;

	private:
		CD3DX12_RECT m_rect;	//!< DX12矩形
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_SCISSOR_H__