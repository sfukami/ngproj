/*!
* @file		appScene.h
* @brief	シーン インターフェース
* @date		2020-06-30
* @author	s.fukami
*/

#ifndef __APP_SCENE_H__
#define __APP_SCENE_H__

namespace app
{
	/*!
	* @brief					シーン インターフェース
	*/
	class IScene
	{
	public:
		IScene() { }
		virtual ~IScene() { }

		/*!
		* @brief					初期化
		* @return					成否
		*/
		virtual bool Initialize() = 0;

		/*!
		* @brief					終了処理
		*/
		virtual void Finalize() = 0;

		/*!
		* @brief					更新
		* @param deltaTime			フレーム更新間隔
		*/
		virtual void Update(float deltaTime) = 0;

		/*!
		* @brief					描画
		*/
		virtual void Render() = 0;

		/*!
		* @brief					名称取得
		*/
		virtual const char* GetName() const = 0 { return nullptr; }
	};

}	// namespace app

#endif	// __APP_SCENE_H__