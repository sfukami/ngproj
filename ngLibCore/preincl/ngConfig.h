/*!
* @file		ngConfig.h
* @brief	NGライブラリ設定
* @date		2017-07-31
* @author	s.fukami
*/

#ifndef __NG_CORE_CONFIG_H__
#define __NG_CORE_CONFIG_H__

/*
	メモリアロケータ
*/
//! アライメント有効
#define NG_CONFIG_ENABLE_MEMALLOC_ALIGNMENT

#ifdef NG_DEBUG
	// for Debug
	/*
		デバッグ機能
	*/
	//! メモリアロケーション デバッグ情報有効
	#define NG_CONFIG_MEMORY_DBGINFO

	//! メモリアロケーション アロケーションprintf表示有効
	#define NG_CONFIG_MEMORY_PRINT_LOG

	//! アサーション、アボートでブレークポイントを自動設定
	#define NG_CONFIG_ENABLE_AUTO_BREAK_POINT
#else
	// for Release
#endif	// NG_DEBUG

#endif	// __NG_CORE_CONFIG_H__