/*!
* @file		ngMemMacro.h
* @brief	メモリ操作マクロ定義
* @date		2017-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_MEM_MACRO_H__
#define __NG_CORE_MEM_MACRO_H__

#include <stdlib.h>

/*!
* @brief					メモリ内容初期化
* @param _ptr				初期化するメモリ領域の先頭アドレス
* @param _size				初期化するメモリ領域のサイズ
*/
#define NG_ZERO_MEMORY(_ptr, _size)		::SecureZeroMemory(_ptr, _size)

/*!
* @brief					メモリ内容をセット
* @param _dst				設定先のメモリ領域の先頭アドレス
* @param _value				設定する値
* @param _size				設定するメモリサイズ
*/
#define NG_MEMSET(_dst, _value, _size)	::memset(_dst, _value, _size)

/*!
* @brief					メモリ内容コピー
* @param _dst				コピー先のメモリ領域の先頭アドレス
* @param _src				コピー元のメモリ領域の先頭アドレス
* @param _size				コピーするメモリサイズ
*/
#define NG_MEMCPY(_dst, _src, _size)	::memcpy(_dst, _src, _size)

/*!
* @brief					メモリ確保
* @param _size				確保するメモリ領域のサイズ
* @remarks					メモリ領域の0クリアは行わない
* @attention				必ずNG_FREEマクロで解放する
*/
#define NG_MALLOC(_size)	::malloc(_size)

/*!
* @brief					メモリ確保
* @param _num				確保するメモリブロックの数
* @param _size				1メモリブロックのサイズ
* @remarks					メモリ領域の0クリアを行う
* @attention				必ずNG_FREEマクロで解放する
*/
#define NG_CALLOC(_num, _size)	::calloc(_num, _size)

/*!
* @brief					メモリ再確保
* @param _ptr				対象のメモリ領域へのポインタ
* @param _size				確保するメモリ領域のサイズ
* @remarks					古い領域が可能な限り新たな領域にコピーされる
* @attention				必ずNG_FREEマクロで解放する
*/
#define NG_REALLOC(_ptr, _size)	::realloc(_ptr, _size)

/*!
* @brief					メモリ解放
* @param _ptr				解放するメモリ領域へのポインタ
*/
#define NG_FREE(_ptr)	::free(_ptr)

#endif	// __NG_CORE_MEM_MACRO_H__
