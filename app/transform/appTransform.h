/*!
* @file		appTransform.h
* @brief	トランスフォーム
* @date		2020-08-23
* @author	s.fukami
*/

#ifndef __APP_TRANSFORM_H__
#define __APP_TRANSFORM_H__

#include "ngLibCore/geometry/ngGeometry.h"

namespace app
{
	/*!
	* @brief					トランスフォーム
	*/
	class CTransform
	{
	public:
		CTransform();
		~CTransform();

		/*! 座標設定 */
		void SetPosition(const ng::Vector3& position);

		/*! スケール設定 */
		void SetScale(const ng::Vector3& scale);

		/*! 回転設定 */
		void SetRotation(const ng::Quaternion& rotation);

		/*! 座標取得 */
		const ng::Vector3& GetPosition() const;

		/*! スケール取得 */
		const ng::Vector3& GetScale() const;

		/*! 回転取得 */
		const ng::Quaternion& GetRotation() const;

		/*! ワールド変換行列取得 */
		const ng::Matrix4& GetWorldMatrix();

	private:
		/*! ワールド変換行列算出 */
		void _calcWorldMatrix();

	private:
		ng::Vector3 m_position;	//!< 座標
		ng::Vector3 m_scale;	//!< スケール
		ng::Quaternion m_rotation;	//!< 回転
		ng::Matrix4 m_worldMat;	//!< ワールド変換行列
		bool m_isChanged;	//!< 変更済みか
	};

}	// namespace app

#endif	// __APP_TRANSFORM_H__