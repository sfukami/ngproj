/*!
* @file		ngCamera.h
* @brief	カメラ
* @date		2019-08-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_CAMERA_H__
#define __NG_GRAPHIC_CAMERA_H__

#include "ngLibCore/geometry/vector/ngVector3.h"
#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
#include "ngLibGraphic/coordsys/ngCoordSys.h"

namespace ng
{
	/*!
	* @brief					カメラ
	*/
	class NG_DECL CCamera
	{
	public:
		CCamera();
		~CCamera();

		/*!
		* @brief					ビュー行列算出
		*/
		void CalcViewMatrix();

		/*! 座標 */
		void SetPos(const Vector3& pos);
		const Vector3& GetPos() const;

		/*! 注視点座標 */
		void SetAtPos(const Vector3& at);
		const Vector3& GetAtPos() const;

		/*! 上方ベクトル */
		void SetUpVec(const Vector3& up);
		const Vector3& GetUpVec() const;

		/*!
		* @brief					注視点と現座標の直線上を移動
		* @param length				移動距離
		*/
		void MoveStraightToAtPos(float length);

		/*!
		* @brief					注視点を中心に回転
		* @param rh					水平方向回転角（ラジアン）
		* @param rv					垂直方向回転角（ラジアン）
		*/
		void RotateAroundAtPos(float radH, float radV);

		/*! ビュー行列 */
		const Matrix4& GetViewMatrix() const;

		/*! 座標系 */
		void SetCoordSys(eCoordSys coordSys);
		eCoordSys GetCoordSys() const;
		
	private:
		Vector3 m_pos;		//!< 座標
		Vector3 m_at;		//!< 注視点座標
		Vector3 m_up;		//!< 上方ベクトル
		Matrix4 m_view;		//!< ビュー行列
		eCoordSys m_coordSys;	//!< 座標系
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_CAMERA_H__