/*!
* @file		ngMatrixOp.h
* @brief	行列演算
* @date		2015-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_MATRIX_OP_H__
#define __NG_CORE_MATRIX_OP_H__

namespace ng
{
	struct Vector3;
	struct Matrix3x3;
	typedef Matrix3x3 Matrix3; 
	struct Matrix4x4;
	typedef Matrix4x4 Matrix4;
}

namespace ng
{
	namespace MatrixOp
	{
		/*!
		* @brief					3x3行列 初期化
		*/
		void Init(
			Matrix3& dst
			, f32 _m11, f32 _m12, f32 _m13
			, f32 _m21, f32 _m22, f32 _m23
			, f32 _m31, f32 _m32, f32 _m33
			);

		/*!
		* @brief					3x3行列 単位行列算出
		*/
		void Identity(
			Matrix3& dst
			);

		/*!
		* @brief					3x3行列 スカラー加算
		*/
		void Add(
			Matrix3& dst
			, const Matrix3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3x3行列 行列加算
		*/
		void Add(
			Matrix3& dst
			, const Matrix3& lhs
			, const Matrix3& rhs
			);

		/*!
		* @brief					3x3行列 スカラー減算
		*/
		void Subtract(
			Matrix3& dst
			, const Matrix3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3x3行列 行列減算
		*/
		void Subtract(
			Matrix3& dst
			, const Matrix3& lhs
			, const Matrix3& rhs
			);

		/*!
		* @brief					3x3行列 スカラー乗算
		*/
		void Multiply(
			Matrix3& dst
			, const Matrix3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3x3行列 行列乗算
		*/
		void Multiply(
			Matrix3& dst
			, const Matrix3& lhs
			, const Matrix3& rhs
			);

		/*!
		* @brief					3x3行列 スカラー除算
		*/
		void Divide(
			Matrix3& dst
			, const Matrix3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3x3行列 行列式算出
		*/
		f32 Determinant(
			const Matrix3& src
			);

		/*!
		* @brief					3x3行列 逆行列算出
		*/
		void Inverse(
			Matrix3& dst
			, const Matrix3& src
			);

		/*!
		* @brief					3x3行列 スケーリング行列算出
		*/
		void Scaling(
			Matrix3& dst
			, f32 sx
			, f32 sy
			, f32 sz
			);

		/*!
		* @brief					3x3行列 X軸周り回転行列算出
		*/
		void RotationX(
			Matrix3& dst
			, f32 rad
			);

		/*!
		* @brief					3x3行列 Y軸周り回転行列算出
		*/
		void RotationY(
			Matrix3& dst
			, f32 rad
			);

		/*!
		* @brief					3x3行列 Z軸周り回転行列算出
		*/
		void RotationZ(
			Matrix3& dst
			, f32 rad
			);

		/*!
		* @brief					3x3行列 ヨー・ピッチ・ロールより回転行列算出
		*/
		void RotationYawPitchRoll(
			Matrix3& dst
			, f32 yaw
			, f32 pitch
			, f32 roll
			);

		/*!
		* @brief					3x3行列 転置行列算出
		*/
		void Transpose(
			Matrix3& dst
			, const Matrix3& src
			);

		/*!
		* @brief					4x4行列 初期化
		*/
		void Init(
			Matrix4& dst
			, f32 _m11, f32 _m12, f32 _m13, f32 _m14
			, f32 _m21, f32 _m22, f32 _m23, f32 _m24
			, f32 _m31, f32 _m32, f32 _m33, f32 _m34
			, f32 _m41, f32 _m42, f32 _m43, f32 _m44
			);

		/*!
		* @brief					4x4行列 単位行列算出
		*/
		void Identity(
			Matrix4& dst
			);

		/*!
		* @brief					4x4行列 スカラー加算
		*/
		void Add(
			Matrix4& dst
			, const Matrix4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4x4行列 行列加算
		*/
		void Add(
			Matrix4& dst
			, const Matrix4& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					4x4行列 スカラー減算
		*/
		void Subtract(
			Matrix4& dst
			, const Matrix4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4x4行列 行列減算
		*/
		void Subtract(
			Matrix4& dst
			, const Matrix4& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					4x4行列 スカラー乗算
		*/
		void Multiply(
			Matrix4& dst
			, const Matrix4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4x4行列 行列乗算
		*/
		void Multiply(
			Matrix4& dst
			, const Matrix4& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					4x4行列 スカラー除算
		*/
		void Divide(
			Matrix4& dst
			, const Matrix4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4x4行列 行列式算出
		*/
		f32 Determinant(
			const Matrix4& src
			);

		/*!
		* @brief					4x4行列 逆行列算出
		*/
		void Inverse(
			Matrix4& dst
			, const Matrix4& src
			);

		/*!
		* @brief					4x4行列 転置行列
		*/
		void Transpose(
			Matrix4& dst
			, const Matrix4& src
			);

		/*!
		* @brief					4x4行列 スケーリング行列算出
		*/
		void Scaling(
			Matrix4& dst
			, f32 sx
			, f32 sy
			, f32 sz
			);

		/*!
		* @brief					4x4行列 X軸周り回転行列算出
		*/
		void RotationX(
			Matrix4& dst
			, f32 rad
			);

		/*!
		* @brief					4x4行列 Y軸周り回転行列算出
		*/
		void RotationY(
			Matrix4& dst
			, f32 rad
			);

		/*!
		* @brief					4x4行列 Z軸周り回転行列算出
		*/
		void RotationZ(
			Matrix4& dst
			, f32 rad
			);

		/*!
		* @brief					4x4行列 ヨー・ピッチ・ロールより回転行列算出
		*/
		void RotationYawPitchRoll(
			Matrix4& dst
			, f32 yaw
			, f32 pitch
			, f32 roll
			);

		/*!
		* @brief					4x4行列 任意軸周りの回転行列算出
		*/
		void RotationAxis(
			Matrix4& dst
			, const Vector3& axis
			, f32 rad
			);

		/*!
		* @brief					4x4行列 トランスフォーム行列算出
		*/
		void Translate(
			Matrix4& dst
			, f32 tx
			, f32 ty
			, f32 tz
			);

		/*!
		* @brief					ビュー行列算出
		* @note						左手座標系
		*/
		void ViewLH(
			Matrix4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			);

		/*!
		* @brief					ビュー行列算出
		* @note						右手座標系
		*/
		void ViewRH(
			Matrix4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			);

		/*!
		* @brief					ビュー行列算出
		* @note						左手座標系 転置済み
		*/
		void ViewLHTransposed(
			Matrix4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			);

		/*!
		* @brief					ビュー行列算出
		* @note						右手座標系 転置済み
		*/
		void ViewRHTransposed(
			Matrix4& dst
			, const Vector3& eye
			, const Vector3& focus
			, const Vector3& up
			);

		/*!
		* @brief					プロジェクション（正射影）行列算出
		* @note						左手座標系
		*/
		void ProjOrthoLH(
			Matrix4& dst
			, f32 w
			, f32 h
			, f32 nearZ
			, f32 farZ
			);

		/*!
		* @brief					プロジェクション（正射影）行列算出
		* @note						右手座標系
		*/
		void ProjOrthoRH(
			Matrix4& dst
			, f32 w
			, f32 h
			, f32 nearZ
			, f32 farZ
			);

		/*!
		* @brief					プロジェクション（パース付）行列算出
		* @note						左手座標系
		*/
		void ProjPersLH(
			Matrix4& dst
			, f32 fov
			, f32 aspect
			, f32 nearZ
			, f32 farZ
			);

		/*!
		* @brief					プロジェクション（パース付）行列算出
		* @note						右手座標系
		*/
		void ProjPersRH(
			Matrix4& dst
			, f32 fov
			, f32 aspect
			, f32 nearZ
			, f32 farZ
			);

		/*!
		* @brief					ビューポートスケーリング行列算出
		*/
		void ViewportScaling(
			Matrix4& dst
			, f32 w
			, f32 h
			);

	}	// namespace Matrix
}	// namespace ng

#endif	// __NG_CORE_MATRIX_OP_H__