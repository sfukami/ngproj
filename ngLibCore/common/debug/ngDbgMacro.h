/*!
* @file		ngDbgMacro.h
* @brief	デバッグマクロ定義
* @date		2016-08-22
* @author	s.fukami
*/

#ifndef __NG_CORE_DBG_MACRO_H__
#define __NG_CORE_DBG_MACRO_H__

#include <crtdbg.h>
#include <assert.h>
#include <tchar.h>
#include "ngDebug.h"
#include "../std/ngStdMacro.h"
#include "../std/ngStdIO.h"
#include "../std/msgbox/ngMsgBoxMacro.h"
#include "ngLibCore/debug/ngStackTrace.h"
/*
#include "ngLibCore/common/std/console/ngConsoleMacro.h"
*/

/*!
* @brief					デバッグ表示
* @param _format			書式
* @param ...				可変長引数
* @note						NG_DEBUG 未定義時は削除される
*/
#if defined(NG_DEBUG)
	#define NG_DPRINTF(_format, ...)	ng::DPrintf(_format, __VA_ARGS__)
#else
	#define NG_DPRINTF(_format, ...)
#endif

/*!
* @brief					デバッグ表示（呼び出し元付き）
* @param _format			書式
* @param ...				可変長引数
* @note						NG_DEBUG 未定義時は削除される
*/
#if defined(NG_DEBUG)
	#define NG_DPRINTF_S(_format, ...) \
	{ \
		ng::DPrintf(_format, __VA_ARGS__); \
		ng::DPrintf("\t%s\n", NG_FILE_LINE); \
	}
#else
	#define NG_DPRINTF_S(_format, ...)
#endif

/*!
* @brief					ログ出力
* @param _category			カテゴリ
*/
#define NG_LOG(_category, _msg, ...) \
	{ \
		NG_DPRINTF("[%s] ", _category); \
		NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
	}

/*!
* @brief					エラーログ出力
* @param _category			カテゴリ
*/
#define NG_ERRLOG(_category, _msg, ...) \
	{ \
		NG_DPRINTF("(!)NG_ERRLOG [%s] ", _category); \
		NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
	}

/*!
* @brief					エラーログ出力（エラーコード付き）
* @param _category			カテゴリ
* @param _errcode			エラーコード
*/
#define NG_ERRLOG_C(_category, _errcode, _msg, ...) \
	{ \
		NG_DPRINTF("(!)NG_ERRLOG [%s] code:(%s) ", _category, ng::ErrorCodeToString(_errcode)); \
		NG_DPRINTF(_msg, __VA_ARGS__); NG_DPRINTF_S("\n"); \
	}

/*!
* @brief					アサート
* @param _expr				条件
* @param ...				書式文字列
* @note						NG_DEBUG 未定義時は削除される
*/
#if defined(NG_DEBUG)
	#define NG_ASSERT(_expr, ...) \
		{ \
			NG_ASSERT2(_expr, __VA_ARGS__, ""); \
		}
	#define NG_ASSERT2(_expr, _format, ...) \
		if( ! (_expr)) { \
			NG_DPRINTF("(!)ASSERT expr:%s, msg:", NG_TO_STRING(_expr)); \
			NG_DPRINTF("" _format ,__VA_ARGS__); \
			NG_DPRINTF_S("\n"); \
			ng::PrintStackTrace(); \
			NG_AUTO_BREAK_POINT(); \
			assert(_expr); \
		}
#else
	#define NG_ASSERT(_expr, ...)
#endif

/*!
* @brief					アサート 必ず失敗
* @param ...				書式文字列
*/
#define NG_ASSERT_FAIL(...) \
		NG_ASSERT(false, __VA_ARGS__)

/*!
* @brief					アサート Nullである場合に成功
* @param _p					ポインタ
* @param ...				書式文字列
*/
#define NG_ASSERT_NULL(_p, ...) \
		NG_ASSERT((_p) == nullptr, __VA_ARGS__)

/*!
* @brief					アサート Nullでない場合に成功
* @param _p					ポインタ
* @param ...				書式文字列
*/
#define NG_ASSERT_NOT_NULL(_p, ...) \
		NG_ASSERT((_p) != nullptr, __VA_ARGS__)

/*!
* @brief					アサート 比較
* @param _actual			実際の値
* @param _expected			想定の値
* @param ...				書式文字列
*/
#define NG_ASSERT_EQUAL(_actual, _expected, ...) \
		NG_ASSERT((_actual) == (_expected), __VA_ARGS__)

/*!
* @brief					アサート 大小比較
* @param _lhs				左辺値
* @param _op				比較演算子
* @param _rhs				右辺値
* @param ...				書式文字列
*/
#define NG_ASSERT_COMPARE(_lhs, _op, _rhs, ...) \
		NG_ASSERT((_lhs) _op (_rhs), __VA_ARGS__)

/*!
* @brief					アサート 範囲
* @param _min				最小値
* @param _minop				最小値に対する比較演算子
* @param _value				比較する値
* @param _maxop				最大値に対する比較演算子
* @param _max				最大値
* @param ...				書式文字列
*/
#define NG_ASSERT_RANGE(_min, _minop, _value, _maxop, _max, ...) \
		NG_ASSERT(((_min) _minop (_value)) && ((_value) _maxop (_max)), __VA_ARGS__)

/*!
* @brief					異常終了
* @param ...				書式文字列
*/
#define NG_ABORT(...) \
	{ \
		NG_ABORT2(__VA_ARGS__, ""); \
	}
#define NG_ABORT2(_format, ...) \
	{ \
		NG_DPRINTF("(!)ABORT msg:"); \
		NG_DPRINTF("" _format, __VA_ARGS__); \
		NG_DPRINTF_S("\n"); \
		ng::PrintStackTrace(); \
		NG_AUTO_BREAK_POINT(); \
		::abort(); \
	}

/*!
* @brief					警告
* @param ...				書式文字列
* @note						NG_DEBUG 未定義時は削除される
*/
#if defined(NG_DEBUG)
	#define NG_WARNING(...) \
		{ \
			NG_WARNING2(__VA_ARGS__, ""); \
		}
	#define NG_WARNING2(_format, ...) \
		{ \
			NG_DPRINTF("(!)WARNING msg:"); \
			NG_DPRINTF("" _format, __VA_ARGS__); \
			NG_DPRINTF_S("\n"); \
		}
#else
	#define NG_WARNING(...)
#endif

/*!
* @brief					アサート + 異常終了
* @param _expr				条件
* @param ...				書式文字列
*/
#define NG_ASSERT_AND_ABORT(_expr, ...) \
	{ \
		NG_ASSERT(_expr, __VA_ARGS__, ""); \
		if( ! (_expr)) { \
			NG_ABORT(__VA_ARGS__, ""); \
		} \
	}

/*!
* @brief					静的アサート
* @param _expr				条件
* @param _msg				メッセージ
* @attention				メッセージは全て半角でなければ文字化けする
*							C++11以前の場合は、メッセージは出力されない
*/
#if defined(NG_DEBUG)
	// C++11ならば static_assert が使用可能
	#if NG_CHECK_CPLUSPLUS_COMPILER_SUPPORT(11)
		#define NG_STATIC_ASSERT(_expr, _msg) \
			static_assert(_expr, _msg)
	#else
		#define NG_STATIC_ASSERT(_expr, _msg) \
			typedef char NG_JOIN(static_assert__, __LINE__)[ (_expr) ? 1 : -1 ]
	#endif
#else
	#define NG_STATIC_ASSERT(_expr, _msg)
#endif

/*!
* @brief					ブレークポイントの設定
* @note						NG_DEBUG 未定義時は削除される
*/
#ifdef NG_DEBUG
	#define NG_BREAK_POINT() { ng::SetBreakPoint(); }
#else
	#define NG_BREAK_POINT() { }
#endif

/*!
* @brief					ブレークポイントの自動設定
*/
#ifdef NG_CONFIG_ENABLE_AUTO_BREAK_POINT
	#define NG_AUTO_BREAK_POINT()	NG_BREAK_POINT()
#else
	#define NG_AUTO_BREAK_POINT()
#endif

/*!
* @brief					ハードウェアブレークポイントの設定
* @note						NG_DEBUG 未定義時は削除される
*/
#ifdef NG_DEBUG
	#define NG_SET_HARDWARE_BREAK_POINT(_address) { ng::SetHardwareBreakPoint((ng::ptr_type)_address); }
#else
	#define NG_SET_HARDWARE_BREAK_POINT(_address) { }
#endif

/*!
* @brief					ハードウェアブレークポイントの削除
* @note						NG_DEBUG 未定義時は削除される
*/
#ifdef NG_DEBUG
	#define NG_CLEAR_HARDWARE_BREAK_POINT() { ng::ClearHardwareBreakPoint(); }
#else
	#define NG_CLEAR_HARDWARE_BREAK_POINT() { }
#endif

/*!
* メモリリークチェック用マクロ
*/
#ifdef NG_DEBUG
	#define NG_CHECK_MEMLEAK() \
		{ ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); }
#else
	#define NG_CHECK_MEMLEAK() { }
#endif

/*!
* @brief					コンソール起動
* @param _isCloseMenu		閉じるボタン有効か
* @return					成否
* @note						デバッグ用
*/
#ifdef NG_DEBUG
	#define NG_DBGCON_BOOT(_isCloseMenu)	NG_CONSOLE_BOOT(_isCloseMenu)
#else
	#define NG_DBGCON_BOOT(_isCloseMenu)
#endif

/*!
* @brief					コンソール終了
* @return					成否
* @note						デバッグ用
*/
#ifdef NG_DEBUG
	#define NG_DBGCON_SHUTDOWN()	NG_CONSOLE_SHUTDOWN()
#else
	#define NG_DBGCON_SHUTDOWN()
#endif

/*!
* @brief					コンソール一時停止
* @note						デバッグ用
*/
#ifdef NG_DEBUG
	#define NG_DBGCON_PAUSE()	NG_CONSOLE_PAUSE()
#else
	#define NG_DBGCON_PAUSE()
#endif

/*!
* @brief					デバッグ メッセージボックス
* @param _message			メッセージ
*/
#ifdef NG_DEBUG
	#define NG_DMSGBOX(_message)		NG_MSGBOX(_message, _T("DebugMessage"), MB_ICONINFORMATION|MB_OK)
#else
	#define NG_DMSGBOX(_message)
#endif

/*!
* @brief					Win32API エラーコード詳細 デバッグ表示
*/
#if defined(NG_DEBUG)
	namespace ng { void _DPrintLastErrMsg(); }
	#define NG_DPRINT_LASTERRMSG()			ng::_DPrintLastErrMsg()
#else
	#define NG_DPRINT_LASTERRMSG()
#endif

/*!
* @brief					Win32API エラーコード詳細 メッセージボックス表示
*/
#if defined(NG_DEBUG)
	namespace ng { void _DMsgBoxLastErrMsg(); }
	#define NG_DMSGBOX_LASTERRMSG()			ng::_DMsgBoxLastErrMsg()
#else
	#define NG_DMSGBOX_LASTERRMSG()
#endif

#endif	// __NG_CORE_DBG_MACRO_H__
