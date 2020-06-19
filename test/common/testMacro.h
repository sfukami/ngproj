/*!
* @file		testMacro.h
* @brief	テスト用マクロ
* @date		2018-10-24
* @author	s.fukami
*/

#ifndef __TEST_MACRO_H__
#define __TEST_MACRO_H__

#include "ngLibCore/locale/ngLocale.h"
#include "test/setup/testSetup.h"

#define TEST_ATTRIBUTE_NAME_TRAIT	L"Trait"

/*!
* テストメソッド 特徴設定
*
* @param _method			関数名
* @param _owner				所有者
* @param _priority			優先度
* @param _trait				特徴
*/
#define TEST_ATTRIBUTE(_method, _owner, _priority, _trait) \
	BEGIN_TEST_METHOD_ATTRIBUTE(_method) \
		TEST_OWNER(L##_owner) \
		TEST_PRIORITY(_priority) \
		TEST_METHOD_ATTRIBUTE(TEST_ATTRIBUTE_NAME_TRAIT, L##_trait) \
	END_TEST_METHOD_ATTRIBUTE()

/*!
* テストメソッド 特徴設定
*
* @param _method			関数名
* @param _trait				特徴
*/
#define TEST_ATTRIBUTE_TRAIT(_method, _trait) \
	BEGIN_TEST_METHOD_ATTRIBUTE(_method) \
		TEST_METHOD_ATTRIBUTE(TEST_ATTRIBUTE_NAME_TRAIT, L##_trait) \
	END_TEST_METHOD_ATTRIBUTE()

/*!
* テストメソッド テスト不可
*
* @param _method			関数名
*/
#define TEST_ATTRIBUTE_IGNORE(_method) \
	BEGIN_TEST_METHOD_ATTRIBUTE(_method) \
		TEST_IGNORE() \
	END_TEST_METHOD_ATTRIBUTE()

/*!
* テストクラスのデフォルトの初期化関数定義
*/
#define TEST_DEFINE_INITIALIZE \
	TEST_CLASS_INITIALIZE(Initialize) { TEST_SETUP(); }

/*!
* セットアップ
*/
#define TEST_SETUP()			test::Setup()

/*!
* ロケール設定
*/
#define TEST_SET_LOCALE()		ng::SetLocaleDefault(LC_ALL)

/*!
* ログ出力
*/
#define TEST_LOGMSG(_msg)		Logger::WriteMessage(_msg)

#endif	// __TEST_MACRO_H__
