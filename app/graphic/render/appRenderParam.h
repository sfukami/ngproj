/*!
* @file		appRenderParam.h
* @brief	描画パラメータ
* @date		2020-07-19
* @author	s.fukami
*/

#ifndef __APP_RENDER_PARAM_H__
#define __APP_RENDER_PARAM_H__

#include "ngLibCore/geometry/ngGeometry.h"
#include "ngLibGraphic/render/ngRenderParam.h"
#include "../command/appGraphicCommandListId.h"

namespace app
{
	/*!
	* @brief					描画パラメータ
	*/
	struct RenderParam : public ng::RenderParam
	{
		RenderParam();
		void CalcViewProjMatrix();
		void CalcWorldViewProjMatrix();
		
		eGraphicCommandListId cmdListId;	//!< グラフィックコマンドリストID
		ng::Matrix4 worldMat;	//!< ワールドトランスフォーム行列
		ng::Matrix4 viewMat;	//!< ビュー行列
		ng::Matrix4 projMat;	//!< 射影行列
		ng::Matrix4 vpMat;		//!< ビュー行列 x 射影行列
		ng::Matrix4 wvpMat;		//!< ワールドトランスフォーム行列 x ビュー行列 x 射影行列
	};

}	// namespace app

#endif	// __APP_RENDER_PARAM_H__