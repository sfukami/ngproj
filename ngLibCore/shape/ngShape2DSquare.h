/*!
* @file		ngShape2DSquare.h
* @brief	2D形状 矩形
* @date		2015-10-10
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_2D_SQUARE_H__
#define __NG_CORE_SHAPE_2D_SQUARE_H__

#include "ngLibCore/geometry/vector/ngVector2.h"

namespace ng
{
	struct Shape2DSquare;
	struct Shape2DCircle;
}

namespace ng
{
	/*!
	* 2D形状 矩形
	*/
	struct NG_DECL Shape2DSquare
	{
		Vector2 center;		//!< 中心座標
		float width, height;	//!< 幅、高さ

		/*! コンストラクタ */
		Shape2DSquare() 
			: width(0.0f), height(0.0f) { }
		explicit Shape2DSquare(const Shape2DSquare& src)
			: Shape2DSquare(src.center, src.width, src.height) { }
		Shape2DSquare(const Vector2& _center, float _width, float _height)
			: center(_center), width(_width), height(_height) { }

		/*! 中心座標取得 */
		const Vector2& Center() const { return center; }

		/*! 幅取得 */
		float Width() const { return width; }
		float WidthDiv2() const { return Width()*0.5f; }

		/*! 高さ取得 */
		float Height() const { return height; }
		float HeightDiv2() const { return Height()*0.5f; }

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

		/*! 最小座標取得 */
		void MinPos(Vector2& dst) const;
		Vector2 MinPos() const;

		/*! 最大座標取得 */
		void MaxPos(Vector2& dst) const;
		Vector2 MaxPos() const;

		/*! 各頂点取得 */
		void TopLeftPos(Vector2& dst) const;
		void TopRightPos(Vector2& dst) const;
		void BottomLeftPos(Vector2& dst) const;
		void BottomRightPos(Vector2& dst) const;
		Vector2 TopLeftPos() const;
		Vector2 TopRightPos() const;
		Vector2 BottomLeftPos() const;
		Vector2 BottomRightPos() const;

		/*! 衝突判定 */
		bool CheckHit(const Shape2DSquare& other) const;
		bool CheckHit(const Shape2DCircle& other) const;
		bool CheckHit(const Vector2& other) const;
	};

	NG_INLINE void Shape2DSquare::MinPos(Vector2& dst) const
	{
		dst.x = MinX();
		dst.y = MinY();
	}
	NG_INLINE Vector2 Shape2DSquare::MinPos() const
	{
		Vector2 ret;
		MinPos(ret);
		return ret;
	}

	NG_INLINE void Shape2DSquare::MaxPos(Vector2& dst) const
	{
		dst.x = MaxX();
		dst.y = MaxY();
	}
	NG_INLINE Vector2 Shape2DSquare::MaxPos() const
	{
		Vector2 ret;
		MaxPos(ret);
		return ret;
	}

	NG_INLINE void Shape2DSquare::TopLeftPos(Vector2& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y + HeightDiv2();
	}
	NG_INLINE void Shape2DSquare::TopRightPos(Vector2& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y + HeightDiv2();
	}
	NG_INLINE void Shape2DSquare::BottomLeftPos(Vector2& dst) const
	{
		dst.x = center.x - WidthDiv2();
		dst.y = center.y - HeightDiv2();
	}
	NG_INLINE void Shape2DSquare::BottomRightPos(Vector2& dst) const
	{
		dst.x = center.x + WidthDiv2();
		dst.y = center.y - HeightDiv2();
	}
	NG_INLINE Vector2 Shape2DSquare::TopLeftPos() const
	{
		Vector2 ret;
		TopLeftPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DSquare::TopRightPos() const
	{
		Vector2 ret;
		TopRightPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DSquare::BottomLeftPos() const
	{
		Vector2 ret;
		BottomLeftPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DSquare::BottomRightPos() const
	{
		Vector2 ret;
		BottomRightPos(ret);
		return ret;
	}

}	// namespace ng

#endif	// __NG_CORE_SHAPE_2D_SQUARE_H__
