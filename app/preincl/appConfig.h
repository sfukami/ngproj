﻿/*!
* @file		appConfig.h
* @brief	アプリケーション設定
* @date		2021-06-01
* @author	s.fukami
*/

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include "appDefine.h"

#ifdef APP_DEBUG
/*	デバッグ	*/
//! デバッグメニューが有効か
#define APP_ENABLE_DEBUG_MENU
#endif	// APP_DEBUG

#endif	// __APP_CONFIG_H__