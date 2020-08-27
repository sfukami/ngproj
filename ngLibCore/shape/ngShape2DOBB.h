/*!
* @file		ngShape2DOBB.h
* @brief	2D形状 OBB
* @date		2019-07-15
* @author	s.fukami
*/

#ifndef __NG_CORE_SHAPE_2D_OBB_H__
#define __NG_CORE_SHAPE_2D_OBB_H__

#include "ngLibCore/geometry/vector/ngVector2.h"

namespace ng
{
	/*!
	* 2D形状 OBB
	*/
	struct NG_DECL Shape2DOBB
	{
		Vector2 center;		//!< 中心座標
		Vector2 axisX, axisY;	//!< 各軸
		float width, height;	//!< 幅、高さ
		float rotation;			//!< 回転角（ラジアン）

		/*! コンストラクタ */
		Shape2DOBB() 
			: width(0.0f), height(0.0f), rotation(0.0f), axisX(1.0f, 0.0f), axisY(0.0f, 1.0f) { }
		Shape2DOBB(const Shape2DOBB& src)
			: Shape2DOBB(src.center, src.width, src.height, src.rotation) { }
		Shape2DOBB(const Vector2& _center, float _width, float _height, float _rotation)
			: center(_center), width(_width), height(_height), rotation(_rotation) { UpdateAxis(); }

		/*! 各軸更新 */
		void UpdateAxis();

		/*! 回転角設定及び、各軸更新 */
		void SetRotationAndUpdateAxis(float rad);

		/*! 中心座標取得 */
		const Vector2& Center() const { return center; }

		/*! 幅取得 */
		float Width() const { return width; }
		float WidthDiv2() const { return Width()*0.5f; }

		/*! 高さ取得 */
		float Height() const { return height; }
		float HeightDiv2() const { return Height()*0.5f; }

		/*! 回転角取得 */
		float Rotation() const { return rotation; }

		/*! 各軸取得 */
		const Vector2& AxisX() const { return axisX; }
		const Vector2& AxisY() const { return axisY; }

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
		bool CheckHit(const Shape2DOBB& other) const;
	};

	NG_INLINE void Shape2DOBB::SetRotationAndUpdateAxis(float rad)
	{
		rotation = rad;
		UpdateAxis();
	}

	NG_INLINE void Shape2DOBB::TopLeftPos(Vector2& dst) const
	{
		dst = center + axisY*HeightDiv2() - axisX*WidthDiv2();
	}
	NG_INLINE void Shape2DOBB::TopRightPos(Vector2& dst) const
	{
		dst = center + axisY*HeightDiv2() + axisX*WidthDiv2();
	}
	NG_INLINE void Shape2DOBB::BottomLeftPos(Vector2& dst) const
	{
		dst = center + -axisY*HeightDiv2() - axisX*WidthDiv2();
	}
	NG_INLINE void Shape2DOBB::BottomRightPos(Vector2& dst) const
	{
		dst = center + -axisY*HeightDiv2() + axisX*WidthDiv2();
	}
	NG_INLINE Vector2 Shape2DOBB::TopLeftPos() const
	{
		Vector2 ret;
		TopLeftPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DOBB::TopRightPos() const
	{
		Vector2 ret;
		TopRightPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DOBB::BottomLeftPos() const
	{
		Vector2 ret;
		BottomLeftPos(ret);
		return ret;
	}
	NG_INLINE Vector2 Shape2DOBB::BottomRightPos() const
	{
		Vector2 ret;
		BottomRightPos(ret);
		return ret;
	}

}	// namespace ng

#endif	// __NG_CORE_SHAPE_2D_OBB_H__
