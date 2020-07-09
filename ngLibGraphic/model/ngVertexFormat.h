/*!
* @file		ngVertexFormat.h
* @brief	頂点フォーマット
* @date		2019-08-13
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_VERTEX_FORMAT_H__
#define __NG_GRAPHIC_VERTEX_FORMAT_H__

#include "ngLibCore/geometry/ngGeometry.h"

namespace ng
{
	namespace VertexFormat
	{
		/*! スプライトの頂点フォーマット */
		struct Sprite
		{
			Vector3 pos;
			Vector4 color;
			Vector2 uv;
		};

		/*! スタティックメッシュの頂点フォーマット */
		struct Static
		{
			Vector3 pos;
			Vector3 normal;
			Vector2 uv;
		};

		/*! スケルタルメッシュの頂点フォーマット */
		struct Skeletal
		{
			Vector3 pos;
			Vector3 normal;
			Vector2 uv;
			u16 bones[4];
			f32 weights[4];
		};

	}	// namespace VertexFormat
}	// namespace ng

#endif	// __NG_GRAPHIC_VERTEX_FORMAT_H__