/*!
* @file		ngQuaternionOp.h
* @brief	クォータニオン演算
* @date		2015-10-20
* @author	s.fukami
*/

#ifndef __NG_CORE_QUATERNION_OP_H__
#define __NG_CORE_QUATERNION_OP_H__

namespace ng
{
	struct Quaternion;
	struct Vector3;
	struct Matrix4x4;
	typedef Matrix4x4 Matrix4;
}

namespace ng
{
	namespace QuaternionOp
	{
		/*!
		* @brief					クォータニオン 初期化
		*/
		NG_DECL void Init(
			Quaternion& dst
			, float _x, float _y, float _z, float _w
			);

		/*!
		* @brief					単位クォータニオン算出
		*/
		NG_DECL void Identity(
			Quaternion& dst
			);

		/*!
		* @brief					クォータニオン ベクトル取得
		*/
		NG_DECL void Vector(
			Vector3& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 回転角取得
		*/
		NG_DECL float Angle(
			const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 回転軸取得
		*/
		NG_DECL void Axis(
			Vector3& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン クォータニオン加算
		*/
		NG_DECL void Add(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			);

		/*!
		* @brief					クォータニオン クォータニオン減算
		*/
		NG_DECL void Subtract(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			);

		/*!
		* @brief					クォータニオン スカラー乗算
		*/
		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& lhs
			, float rhs
			);

		/*!
		* @brief					クォータニオン クォータニオン乗算
		*/
		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& lhs
			, const Quaternion& rhs
			);

		/*!
		* @brief					クォータニオン ベクトル乗算
		*/
		NG_DECL void Multiply(
			Quaternion& dst
			, const Quaternion& rhs
			, const Vector3& lhs
			);

		/*!
		* @brief					クォータニオン スカラー除算
		*/
		NG_DECL void Divide(
			Quaternion& dst
			, const Quaternion& lhs
			, float rhs
			);

		/*!
		* @brief					クォータニオン 内積算出
		*/
		NG_DECL float Dot(
			const Quaternion& lhs
			, const Quaternion& rhs
			);

		/*!
		* @brief					クォータニオン 長さ算出（平方前）
		*/
		NG_DECL float LengthSq(
			const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 長さ算出
		*/
		NG_DECL float Length(
			const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 正規化
		*/
		NG_DECL void Normalize(
			Quaternion& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 逆クォータニオン算出
		*/
		NG_DECL void Inverse(
			Quaternion& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 共役クォータニオン算出
		*/
		NG_DECL void Conjugate(
			Quaternion& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 任意の回転軸及び、回転角よりクォータニオンを算出
		*/
		NG_DECL void RotationAxis(
			Quaternion& dst
			, const Vector3& axis
			, float rad
			);

		/*!
		* @brief					クォータニオン クォータニオン回転
		*/
		NG_DECL void Rotate(
			Quaternion& dst
			, const Quaternion& q
			, const Quaternion& rot
			);

		/*!
		* @brief					クォータニオン ベクトル回転
		*/
		NG_DECL void Rotate(
			Vector3& dst
			, const Vector3& v
			, const Quaternion& rot
			);

		/*!
		* @brief					クォータニオン 球面線形補間
		* @attention				クォータニオンは正規化済みであること
		*/
		NG_DECL void Slerp(
			Quaternion& dst
			, const Quaternion& q1
			, const Quaternion& q2
			, float t
			);

		/*!
		* @brief					クォータニオン オイラー角へ変換
		*/
		NG_DECL void ToEulerAngle(
			Vector3& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン オイラー角から変換
		*/
		NG_DECL void FromEulerAngle(
			Quaternion& dst
			, const Vector3& eulerAngle
			);

		/*!
		* @brief					クォータニオン 4x4行列へ変換
		*/
		NG_DECL void ToMatrix(
			Matrix4& dst
			, const Quaternion& src
			);

		/*!
		* @brief					クォータニオン 4x4行列かから変換
		*/
		NG_DECL void FromMatrix(
			Quaternion& dst
			, const Matrix4& src
			);

	}	// namespace QuaternionOp
}	// namespace ng

#endif	// __NG_CORE_QUATERNION_OP_H__