/*!
* @file		ngDX12Std.h
* @brief	DX12 標準機能
* @date		2017-09-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_STD_H__
#define __NG_GRAPHIC_DX12_STD_H__

enum D3D_FEATURE_LEVEL;

namespace ng
{
	/*!
	* @brief					サポート可能なDX12機能レベルを取得
	* @return					終端を D3D_FEATURE_LEVEL_NONE とする機能レベルの配列
	*							インデックスが若いほど上位の機能レベル
	*/
	NG_DECL const D3D_FEATURE_LEVEL* GetSupportedDX12FeatureLevels();

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_STD_H__