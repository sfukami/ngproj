/*!
* @file		ngLocale.h
* @brief	ロケール関連
* @date		2018-10-19
* @author	s.fukami
*/

#ifndef __NG_CORE_LOCALE_H__
#define __NG_CORE_LOCALE_H__

namespace ng
{

/*
	ロケール設定
	https://msdn.microsoft.com/ja-jp/library/x99tb11d.aspx

	■カテゴリ
	・LC_ALL
		次の一覧のすべてのカテゴリ。

	・LC_COLLATE
		strcoll、_stricoll、wcscoll、_wcsicoll、strxfrm、_strncoll、_strnicoll、_wcsncoll、_wcsnicoll、および wcsxfrm の各関数。

	・LC_CTYPE
		文字処理関数の (影響を受けない isdigit、isxdigit、mbstowcs、および mbtowc を除く)。

	・LC_MONETARY
		localeconv 関数が返す通貨形式情報。

	・LC_NUMERIC
		printf などの書式化出力ルーチン、データ変換ルーチン、および localeconv が返す通貨形式以外の形式情報で使用される小数点文字。
		小数点文字に加えLC_NUMERICもセット、数千の区切り記号およびグループ化の制御によって返される文字列localeconvします。

	・LC_TIME
		strftime および wcsftime 関数。
*/
/*!
* @brief					ロケール設定
* @param category			設定するカテゴリ
* @param locale				設定する地域。 空文字でデフォルトのロケール設定
* @return					ロケールとカテゴリを示す文字列
*/
NG_DECL char* SetLocale(int category, const char* locale);

/*!
* @brief					デフォルトのロケール設定（処理系依存）
* @param category			設定するカテゴリ
* @return					ロケールとカテゴリを示す文字列
*/
NG_DECL char* SetLocaleDefault(int category);

}	// namespace ng

#endif	// __NG_CORE_LOCALE_H__