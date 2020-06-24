/*!
* @file		ngDX12CommandQueueType.h
* @brief	DX12コマンドキュータイプ
* @date		2018-02-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_COMMAND_QUEUE_TYPE_H__
#define __NG_GRAPHIC_DX12_COMMAND_QUEUE_TYPE_H__

#include <D3D12.h>

namespace ng
{
	/*!
	* @brief					DX12コマンドキュータイプ
	*/
	enum class eDX12CommandQueueType : u32
	{
		GRAPHIC	= 0,		//!< グラフィックコマンドキュー
	//	BUNDLE,				//!< バンドルコマンドキュー
		COMPUTE,			//!< コンピュートコマンドキュー
		COPY,				//!< コピーコマンドキュー

		NUM
	};

	/*!
	* @brief					DX12コマンドキュータイプを対応するDX12コマンドリストタイプに変換
	* @param type				DX12コマンドキュータイプ
	* @return					DX12コマンドリストタイプ
	*/
	NG_DECL D3D12_COMMAND_LIST_TYPE DX12ToCommandListType(eDX12CommandQueueType type);

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_COMMAND_QUEUE_TYPE_H__