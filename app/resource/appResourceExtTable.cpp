/*!
* @file		appResourceExtTable.cpp
* @brief	リソース 拡張子テーブル
* @date		2020-08-03
* @author	s.fukami
*/

namespace ng
{
	class IResourceHandle;
}
namespace app
{
	class CResourceSystem;
}

namespace app
{
	//! リソースの拡張子テーブル宣言
	#define _RESEXT_TABLE(_resName) \
		static const char* s_pExtTbl_##_resName[]

	//! 各リソースの拡張子テーブル
	_RESEXT_TABLE(Texture) = {".bmp"};	//!< テクスチャ
	_RESEXT_TABLE(Shader) = {".hlsl"};	//!< シェーダー
	_RESEXT_TABLE(Material) = {".mat"};	//!< マテリアル

	//! リソース読み込み設定テーブル宣言
	#define _LOAD_SETTING_TABLE() \
		static const LoadSetting s_loadSettings[] = { \
			_LOAD_SETTING(Texture), \
			_LOAD_SETTING(Shader), \
			_LOAD_SETTING(Material), \
		};

}	// namespace app

namespace app
{
	//! リソース読み込み設定
	#define _LOAD_SETTING(_resName) \
		{ &CResourceSystem::_loadResource<C##_resName>, s_pExtTbl_##_resName, NG_ARRAY_SIZE(s_pExtTbl_##_resName) }

	//! リソース読み込み設定
	struct LoadSetting
	{
		using FuncType = bool(CResourceSystem::*)(const char*, ng::IMemoryAllocator&, const void*, ng::IResourceHandle&);

		const FuncType func;	//!< リソース読み込み関数
		const char** ppExtTable;	//!< 拡張子テーブル
		unsigned int extTableSize;	//!< 拡張子テーブルのサイズ
	};

}	// namespace app