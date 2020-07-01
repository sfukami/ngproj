/*!
* @file		appSceneId.h
* @brief	シーンID
* @date		2020-06-30
* @author	s.fukami
*/

#ifndef __APP_SCENE_ID_H__
#define __APP_SCENE_ID_H__

namespace app
{
	/*!
	* @brief					シーンID
	*/
	enum class eSceneId : unsigned int
	{
		//ROOT,		//!< ルートシーン

		GAME,		//!< ゲームシーン
		DEBUG,		//!< デバッグシーン
		NUM
	};

}	// namespace app

#endif	// __APP_SCENE_ID_H__