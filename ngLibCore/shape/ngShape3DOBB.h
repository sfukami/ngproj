/*!
* @file		ngShape3DOBB.h
* @brief	3D形状 OBB
* @date		2016-03-08
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_OBB_H__
#define __NG_CORE_SHAPE_3D_OBB_H__

#include "ngLibCore/geometry/vector/ngVector3.h"

namespace ng
{
	struct Shape3DPlane;
}

namespace ng
{
	/*!
	* 3D形状 OBB
	*/
	struct NG_DECL Shape3DOBB
	{
		Vector3 center;		//!< 中心座標
		float width, height, depth;		//!< 幅、高さ、奥行き
		Vector3 axisX, axisY, axisZ;	//!< 各軸
		float rotX, rotY, rotZ;		//!< 回転角

		/*! コンストラクタ */
		Shape3DOBB()
			: width(0.0f), height(0.0f), depth(0.0f), rotX(0.0f), rotY(0.0f), rotZ(0.0f) { }
		Shape3DOBB(const Shape3DOBB& src)
			: Shape3DOBB(src.center, src.width, src.height, src.depth, src.rotX, src.rotY, src.rotZ) { }
		Shape3DOBB(const Vector3& _center, float _width, float _height, float _depth, float _rotX, float _rotY, float _rotZ)
			: center(_center), width(_width), height(_height), depth(_depth), rotX(_rotX), rotY(_rotY), rotZ(_rotZ) { UpdateAxis(); }

		/*! 各軸更新 */
		void UpdateAxis();

		/*! 回転角設定及び、各軸更新 */
		void SetRotationAndUpdateAxis(float x, float y, float z);
		void SetRotXAndUpdateAxis(float rad);
		void SetRotYAndUpdateAxis(float rad);
		void SetRotZAndUpdateAxis(float rad);

		/*! 中心座標取得 */
		const Vector3& Center() const { return center; }

		/*! 幅取得 */
		float Width() const { return width; }
		float WidthDiv2() const { return Width()*0.5f; }

		/*! 高さ取得 */
		float Height() const { return height; }
		float HeightDiv2() const { return Height()*0.5f; }

		/*! 奥行き取得 */
		float Depth() const { return depth; }
		float DepthDiv2() const { return Depth()*0.5f; }

		/*! 回転角取得 */
		float RotX() const { return rotX; }
		float RotY() const { return rotY; }
		float RotZ() const { return rotZ; }

		/*! 各軸取得 */
		const Vector3& AxisX() const { return axisX; }
		const Vector3& AxisY() const { return axisY; }
		const Vector3& AxisZ() const { return axisZ; }

		/*! 各頂点取得 */
		void TopLeftNearPos(Vector3& dst) const;
		void TopLeftFarPos(Vector3& dst) const;
		void TopRightNearPos(Vector3& dst) const;
		void TopRightFarPos(Vector3& dst) const;
		void BottomLeftNearPos(Vector3& dst) const;
		void BottomLeftFarPos(Vector3& dst) const;
		void BottomRightNearPos(Vector3& dst) const;
		void BottomRightFarPos(Vector3& dst) const;
		Vector3 TopLeftNearPos() const;
		Vector3 TopLeftFarPos() const;
		Vector3 TopRightNearPos() const;
		Vector3 TopRightFarPos() const;
		Vector3 BottomLeftNearPos() const;
		Vector3 BottomLeftFarPos() const;
		Vector3 BottomRightNearPos() const;
		Vector3 BottomRightFarPos() const;

		/*! 衝突判定 */
		bool CheckHit(const Shape3DOBB& other) const;
		bool CheckHit(const Shape3DPlane& other) const;
	};

	NG_INLINE void Shape3DOBB::SetRotationAndUpdateAxis(float x, float y, float z)
	{
		rotX = x;
		rotY = y;
		rotZ = z;
		UpdateAxis();
	}

	NG_INLINE void Shape3DOBB::SetRotXAndUpdateAxis(float rad)
	{
		rotX = rad;
		UpdateAxis();
	}
	NG_INLINE void Shape3DOBB::SetRotYAndUpdateAxis(float rad)
	{
		rotY = rad;
		UpdateAxis();
	}
	NG_INLINE void Shape3DOBB::SetRotZAndUpdateAxis(float rad)
	{
		rotZ = rad;
		UpdateAxis();
	}

	NG_INLINE void Shape3DOBB::TopLeftNearPos(Vector3& dst) const
	{
		dst = center - axisX*WidthDiv2() + axisY*HeightDiv2() - axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::TopLeftFarPos(Vector3& dst) const
	{
		dst = center - axisX*WidthDiv2() + axisY*HeightDiv2() + axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::TopRightNearPos(Vector3& dst) const
	{
		dst = center + axisX*WidthDiv2() + axisY*HeightDiv2() - axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::TopRightFarPos(Vector3& dst) const
	{
		dst = center + axisX*WidthDiv2() + axisY*HeightDiv2() + axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::BottomLeftNearPos(Vector3& dst) const
	{
		dst = center - axisX*WidthDiv2() - axisY*HeightDiv2() - axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::BottomLeftFarPos(Vector3& dst) const
	{
		dst = center - axisX*WidthDiv2() - axisY*HeightDiv2() + axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::BottomRightNearPos(Vector3& dst) const
	{
		dst = center + axisX*WidthDiv2() - axisY*HeightDiv2() - axisZ*DepthDiv2();
	}
	NG_INLINE void Shape3DOBB::BottomRightFarPos(Vector3& dst) const
	{
		dst = center + axisX*WidthDiv2() - axisY*HeightDiv2() + axisZ*DepthDiv2();
	}
	NG_INLINE Vector3 Shape3DOBB::TopLeftNearPos() const
	{
		Vector3 ret;
		TopLeftNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::TopLeftFarPos() const
	{
		Vector3 ret;
		TopLeftFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::TopRightNearPos() const
	{
		Vector3 ret;
		TopRightNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::TopRightFarPos() const
	{
		Vector3 ret;
		TopRightFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::BottomLeftNearPos() const
	{
		Vector3 ret;
		BottomLeftNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::BottomLeftFarPos() const
	{
		Vector3 ret;
		BottomLeftFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::BottomRightNearPos() const
	{
		Vector3 ret;
		BottomRightNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DOBB::BottomRightFarPos() const
	{
		Vector3 ret;
		BottomRightFarPos(ret);
		return ret;
	}

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_OBB_H__
