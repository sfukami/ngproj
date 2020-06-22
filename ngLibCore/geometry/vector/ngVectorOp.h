/*!
* @file		ngVectorOp.h
* @brief	ベクトル演算
* @date		2013-10-18
* @author	s.fukami
*/

#ifndef __NG_CORE_VECTOR_OP_H__
#define __NG_CORE_VECTOR_OP_H__

namespace ng
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix3x3;
	typedef Matrix3x3 Matrix3; 
	struct Matrix4x4;
	typedef Matrix4x4 Matrix4;
}

namespace ng
{
	namespace VectorOp
	{
		/*!
		* @brief					2次元ベクトル 初期化
		*/
		NG_DECL void Init(
			Vector2& dst
			, f32 _x, f32 _y
			);

		/*!
		* @brief					2次元ベクトル スカラー加算
		*/
		NG_DECL void Add(
			Vector2& dst
			, Vector2& lhs
			, f32 rhs
			);

		/*!
		* @brief					2次元ベクトル ベクトル加算
		*/
		NG_DECL void Add(
			Vector2& dst
			, const Vector2& lhs
			, const Vector2& rhs
			);

		/*!
		* @brief					2次元ベクトル スカラー減算
		*/
		NG_DECL void Subtract(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			);

		/*!
		* @brief					2次元ベクトル ベクトル減算
		*/
		NG_DECL void Subtract(
			Vector2& dst
			, const Vector2& lhs
			, const Vector2& rhs
			);

		/*!
		* @brief					2次元ベクトル スカラー乗算
		*/
		NG_DECL void Multiply(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			);

		/*!
		* @brief					2次元ベクトル スカラー除算
		*/
		NG_DECL void Divide(
			Vector2& dst
			, const Vector2& lhs
			, f32 rhs
			);

		/*!
		* @brief					2次元ベクトル 反転
		*/
		NG_DECL void Reverse(
			Vector2& dst
			, const Vector2& src
			);

		/*!
		* @brief					2次元ベクトル 内積算出
		*/
		NG_DECL f32 Dot(
			const Vector2& lhs
			, const Vector2& rhs
			);
		NG_DECL f32 Dot(
			const Vector2& self
			);

		/*!
		* @brief					2次元ベクトル 外積算出
		*/
		NG_DECL f32 Cross(
			const Vector2& lhs
			, const Vector2& rhs
			);

		/*!
		* @brief					2次元ベクトル 長さ算出（平方）
		*/
		NG_DECL f32 LengthSq(
			const Vector2& src
			);
		NG_DECL f32 LengthSq(
			const Vector2& pos1, const Vector2& pos2
			);

		/*!
		* @brief					2次元ベクトル 長さ算出
		*/
		NG_DECL f32 Length(
			const Vector2& src
			);
		NG_DECL f32 Length(
			const Vector2& pos1, const Vector2& pos2
			);

		/*!
		* @brief					2次元ベクトル 正規化
		*/
		NG_DECL void Normalize(
			Vector2& dst
			, const Vector2& src
			);

		/*!
		* @brief					2次元ベクトル ベクトル間の線形補間
		*/
		NG_DECL void Lerp(
			Vector2& dst
			, const Vector2& a
			, const Vector2& b
			, f32 s
			);

		/*!
		* @brief					回転角（ラジアン）を指定し回転
		*/
		NG_DECL void Rotate(
			Vector2& dst
			, const Vector2& src
			, float rad
			);

		/*!
		* @brief					2次元ベクトル 3x3行列による変換
		*/
		NG_DECL void Transform(
			Vector2& dst
			, const Vector2& src
			, const Matrix3& mat
			);

		/*!
		* @brief					3次元ベクトル 初期化
		*/
		NG_DECL void Init(
			Vector3& dst
			, f32 _x, f32 _y, f32 _z
			);

		/*!
		* @brief					3次元ベクトル スカラー加算
		*/
		NG_DECL void Add(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3次元ベクトル ベクトル加算
		*/
		NG_DECL void Add(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			);

		/*!
		* @brief					3次元ベクトル スカラー減算
		*/
		NG_DECL void Subtract(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3次元ベクトル ベクトル減算
		*/
		NG_DECL void Subtract(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			);

		/*!
		* @brief					3次元ベクトル スカラー乗算
		*/
		NG_DECL void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3次元ベクトル スカラー除算
		*/
		NG_DECL void Divide(
			Vector3& dst
			, const Vector3& lhs
			, f32 rhs
			);

		/*!
		* @brief					3次元ベクトル 反転
		*/
		NG_DECL void Reverse(
			Vector3& dst
			, const Vector3& src
			);

		/*!
		* @brief					3次元ベクトル 内積算出
		*/
		NG_DECL f32 Dot(
			const Vector3& lhs
			, const Vector3& rhs
			);
		NG_DECL f32 Dot(
			const Vector3& self
			);

		/*!
		* @brief					3次元ベクトル 外積算出
		*/
		NG_DECL void Cross(
			Vector3& dst
			, const Vector3& lhs
			, const Vector3& rhs
			);

		/*!
		* @brief					3次元ベクトル 長さ算出（平方）
		*/
		NG_DECL f32 LengthSq(
			const Vector3& src
			);
		NG_DECL f32 LengthSq(
			const Vector3& pos1, const Vector3& pos2
			);

		/*!
		* @brief					3次元ベクトル 長さ算出
		*/
		NG_DECL f32 Length(
			const Vector3& src
			);
		NG_DECL f32 Length(
			const Vector3& pos1, const Vector3& pos2
			);

		/*!
		* @brief					3次元ベクトル 正規化
		*/
		NG_DECL void Normalize(
			Vector3& dst
			, const Vector3& src
			);

		/*!
		* @brief					3次元ベクトル ベクトル間の線形補間
		*/
		NG_DECL void Lerp(
			Vector3& dst
			, const Vector3& a
			, const Vector3& b
			, f32 s
			);

		/*!
		* @brief					3次元ベクトル 3x3行列による変換
		*/
		NG_DECL void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix3& rhs
			);

		/*!
		* @brief					3次元ベクトル 3x3行列による変換
		*/
		NG_DECL void Multiply(
			Vector3& dst
			, const Matrix3& lhs
			, const Vector3& rhs
			);

		/*!
		* @brief					3次元ベクトル 4x4行列による変換
		*/
		NG_DECL void Multiply(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					3次元ベクトル 4x4行列による変換
		*/
		NG_DECL void Multiply(
			Vector3& dst
			, const Matrix4& lhs
			, const Vector3 rhs
			);

		/*!
		* @brief					3次元ベクトル 4x4行列による変換
		* @note						z=1としてトランスフォーム変換を行う
		*/
		NG_DECL void Transform(
			Vector3& dst
			, const Vector3& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					4次元ベクトル 初期化
		*/
		NG_DECL void Init(
			Vector4& dst
			, f32 _x, f32 _y, f32 _z, f32 _w
			);

		/*!
		* @brief					4次元ベクトル スカラー加算
		*/
		NG_DECL void Add(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4次元ベクトル ベクトル加算
		*/
		NG_DECL void Add(
			Vector4& dst
			, const Vector4& lhs
			, const Vector4& rhs
			);

		/*!
		* @brief					4次元ベクトル スカラー減算
		*/
		NG_DECL void Subtract(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4次元ベクトル ベクトル減算
		*/
		NG_DECL void Subtract(
			Vector4& dst
			, const Vector4& lhs
			, const Vector4& rhs
			);

		/*!
		* @brief					4次元ベクトル スカラー乗算
		*/
		NG_DECL void Multiply(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4次元ベクトル スカラー除算
		*/
		NG_DECL void Divide(
			Vector4& dst
			, const Vector4& lhs
			, f32 rhs
			);

		/*!
		* @brief					4次元ベクトル 反転
		*/
		NG_DECL void Reverse(
			Vector4& dst
			, const Vector4& src
			);

		/*!
		* @brief					4次元ベクトル 4x4行列による変換
		*/
		NG_DECL void Multiply(
			Vector4& dst
			, const Vector4& lhs
			, const Matrix4& rhs
			);

		/*!
		* @brief					4次元ベクトル 4x4行列による変換
		*/
		NG_DECL void Multiply(
			Vector4& dst
			, const Matrix4& lhs
			, const Vector4& rhs
			);
		
	}	// namespace VectorOp
}	// namespace ng

#endif	// __NG_CORE_VECTOR_OP_H__