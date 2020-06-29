/*!
* @file		ngProjection.h
* @brief	射影変換
* @date		2019-08-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_PROJECTION_H__
#define __NG_GRAPHIC_PROJECTION_H__

#include "ngLibCore/geometry/matrix/ngMatrix4x4.h"
#include "ngLibGraphic/coordsys/ngCoordSys.h"

namespace ng
{
	/*!
	* @brief					射影変換
	*/
	class NG_DECL CProjection
	{
	public:
		/*! 投影方法 */
		enum eProjMethod
		{
			PERSPECTIVE,	//!< 透視投影
			ORTHOGONAL,		//!< 平行投影
		};

	public:
		CProjection();
		~CProjection();

		/*!
		* @brief					プロジェクション行列算出
		*/
		void CalcProjMatrix();

		/*! スクリーン幅 */
		void SetWidth(int width);
		int GetWidth() const;

		/*! スクリーン高さ */
		void SetHeight(int height);
		int GetHeight() const;

		/*! ニア面 */
		void SetNear(float _near);
		float GetNear() const;

		/*! ファー面 */
		void SetFar(float _far);
		float GetFar() const;

		/*! 視野角 */
		void SetFOV(float rad);
		float GetFOV() const;

		/*! プロジェクション行列取得 */
		const Matrix4& GetProjMatrix() const;

		/*! 座標系 */
		void SetCoordSys(eCoordSys coordSys);
		eCoordSys GetCoordSys() const;

		/*! 投影方法 */
		void SetProjMethod(eProjMethod projMethod);
		eProjMethod GetProjMethod() const;
		
	private:
		int m_width;	//!< スクリーン幅
		int m_height;	//!< スクリーン高さ
		float m_near;	//!< ニア面
		float m_far;	//!< ファー面
		float m_fov;	//!< 視野角
		Matrix4 m_proj;	//!< プロジェクション行列
		eCoordSys m_coordSys;	//!< 座標系
		eProjMethod m_projMethod;	//!< 投影方法
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_PROJECTION_H__