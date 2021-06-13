/*!
* @file		preInclude.h
* @brief	プリインクルードヘッダ
* @date		2021-06-07
* @author	s.fukami
*/

#ifndef __GLTFCONV_PRE_INCLUDE_H__
#define __GLTFCONV_PRE_INCLUDE_H__

// GLTF-SDK の std::min(), std::max() 呼び出しのため
// Windows.h のインクルードより前に定義する
#define NOMINMAX

#include "ngLibCore/ngLibCore.h"
#include "ngLibApp/ngLibApp.h"
#include "ngLibGraphic/ngLibGraphic.h"

#endif	// __GLTFCONV_PRE_INCLUDE_H__