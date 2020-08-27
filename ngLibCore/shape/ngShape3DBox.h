/*!
* @file		ngShape3DBox.h
* @brief	3D形状 Box(AABB)
* @date		2016-02-10
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_3D_BOX_H__
#define __NG_CORE_SHAPE_3D_BOX_H__

#include "ngLibCore/geometry/vector/ngVector3.h"

namespace ng
{
	struct Shape3DSphere;
	struct Vector3;
	struct Shape3DPlane;
}

namespace ng
{
	/*!
	* 3D形状 Box(AABB)
	*/
	struct NG_DECL Shape3DBox
	{
		Vector3 center;		//!< 中心座標
		float width, height, depth;	//!< 幅、高さ、奥行き

		/*! コンストラクタ */
		Shape3DBox()
			: width(0.0f), height(0.0f), depth(0.0f) { }
		explicit Shape3DBox(const Shape3DBox& src)
			: Shape3DBox(src.center, src.width, src.height, src.depth) { }
		Shape3DBox(const Vector3& _center, float _width, float _height, float _depth)
			: center(_center), width(_width), height(_height), depth(_depth) { }

		/*! 中心座標取得 */
		const Vector3& Center() const { return center; }

		/*! 幅取得 */
		float Width() const { return width; }
		float WidthDiv2() const { return Width()*0.5f; }

		/*! 高さ取得 */
		float Height() const { return height; }
		float HeightDiv2() const { return Height()*0.5f; }

		/*! 奥行取得 */
		float Depth() const { return depth; }
		float DepthDiv2() const { return Depth()*0.5f; }

		/*! X軸方向 最小値取得 */
		float MinX() const { return (center.x - WidthDiv2()); }
		float Left() const { return MinX(); }

		/*! X軸方向 最大値取得 */
		float MaxX() const { return (center.x + WidthDiv2()); }
		float Right() const { return MaxX(); }

		/*! Y軸方向 最小値取得 */
		float MinY() const { return (center.y - HeightDiv2()); }
		float Bottom() const { return MinY(); }

		/*! Y軸方向 最大値取得 */
		float MaxY() const { return (center.y + HeightDiv2()); }
		float Top() const { return MaxY(); }

		/*! Z軸方向 最小値取得 */
		float MinZ() const { return (center.z - DepthDiv2()); }
		float Near() const { return MinZ(); }

		/*! Z軸方向 最大値取得 */
		float MaxZ() const { return (center.z + DepthDiv2()); }
		float Far() const { return MaxZ(); }

		/*! 最小座標取得 */
		void MinPos(Vector3& dst) const;
		Vector3 MinPos() const;

		/*! 最大座標取得 */
		void MaxPos(Vector3& dst) const;
		Vector3 MaxPos() const;

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
		bool CheckHit(const Shape3DBox& other) const;
		bool CheckHit(const Shape3DSphere& other) const;
		bool CheckHit(const Vector3& other) const;
		bool CheckHit(const Shape3DPlane& other) const;
	};

	/*! 最小座標取得 */
	NG_INLINE void Shape3DBox::MinPos(Vector3& dst) const
	{
		dst.x = MinX();
		dst.y = MinY();
		dst.z = MinZ();
	}
	NG_INLINE Vector3 Shape3DBox::MinPos() const
	{
		Vector3 ret;
		MinPos(ret);
		return ret;
	}

	/*! 最大座標取得 */
	NG_INLINE void Shape3DBox::MaxPos(Vector3& dst) const
	{
		dst.x = MinX();
		dst.y = MinY();
		dst.z = MinZ();
	}
	NG_INLINE Vector3 Shape3DBox::MaxPos() const
	{
		Vector3 ret;
		MaxPos(ret);
		return ret;
	}

	/*! 各頂点取得 */
	NG_INLINE void Shape3DBox::TopLeftNearPos(Vector3& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y + HeightDiv2();
		dst.z = center.z - DepthDiv2();
	}
	NG_INLINE void Shape3DBox::TopLeftFarPos(Vector3& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y + HeightDiv2();
		dst.z = center.z + DepthDiv2();
	}
	NG_INLINE void Shape3DBox::TopRightNearPos(Vector3& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y + HeightDiv2();
		dst.z = center.z - DepthDiv2();
	}
	NG_INLINE void Shape3DBox::TopRightFarPos(Vector3& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y + HeightDiv2();
		dst.z = center.z + DepthDiv2();
	}
	NG_INLINE void Shape3DBox::BottomLeftNearPos(Vector3& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y - HeightDiv2();
		dst.z = center.z - DepthDiv2();
	}
	NG_INLINE void Shape3DBox::BottomLeftFarPos(Vector3& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y - HeightDiv2();
		dst.z = center.z + DepthDiv2();
	}
	NG_INLINE void Shape3DBox::BottomRightNearPos(Vector3& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y - HeightDiv2();
		dst.z = center.z - DepthDiv2();
	}
	NG_INLINE void Shape3DBox::BottomRightFarPos(Vector3& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y - HeightDiv2();
		dst.z = center.z + DepthDiv2();
	}
	NG_INLINE Vector3 Shape3DBox::TopLeftNearPos() const
	{
		Vector3 ret;
		TopLeftNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::TopLeftFarPos() const
	{
		Vector3 ret;
		TopLeftFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::TopRightNearPos() const
	{
		Vector3 ret;
		TopRightNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::TopRightFarPos() const
	{
		Vector3 ret;
		TopRightFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::BottomLeftNearPos() const
	{
		Vector3 ret;
		BottomLeftNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::BottomLeftFarPos() const
	{
		Vector3 ret;
		BottomLeftFarPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::BottomRightNearPos() const
	{
		Vector3 ret;
		BottomRightNearPos(ret);
		return ret;
	}
	NG_INLINE Vector3 Shape3DBox::BottomRightFarPos() const
	{
		Vector3 ret;
		BottomRightFarPos(ret);
		return ret;
	}

}	// namespace ng

#endif	// __NG_CORE_SHAPE_3D_BOX_H__
