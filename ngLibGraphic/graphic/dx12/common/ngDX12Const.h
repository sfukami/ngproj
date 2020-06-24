/*!
* @file		ngDX12Const.h
* @brief	DX12 定数
* @date		2017-09-18
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_CONST_H__
#define __NG_GRAPHIC_DX12_CONST_H__

// DX12 機能レベル
#define D3D_FEATURE_LEVEL_NONE	(D3D_FEATURE_LEVEL)0

// DX12コマンドアロケータ 最大数
#define DX12_COMMAND_ALLOCATOR_MAX	(32)

// DX12コマンドリスト 最大数
#define DX12_COMMAND_LIST_MAX		(32)

// DX12ルートシグネチャ 最大数
#define DX12_ROOT_SIGNATURE_MAX		(32)

// DX12パイプラインステート 最大数
#define DX12_PIPELINE_STATE_MAX		(32)

// DX12ビューポート 最大設定数
#define DX12_VIEWPORT_MAX_PER_PIPELINE		(D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)

// DX12シザー矩形 最大設定数
#define DX12_SCISSORRECT_MAX_PER_PIPELINE	(D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)

// DX12メッシュ 頂点レイアウト入力エレメント記述子 最大数
#define NG_DX12_MESH_INPUT_ELEMENT_DESC_MAX		(8)

// DX12ディスクリプタヒープ 最大数
#define DX12_DESCRIPTOR_HEAP_MAX	(8)

#endif	// __NG_GRAPHIC_DX12_CONST_H__