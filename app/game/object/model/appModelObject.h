/*!
* @file		appModelObject.h
* @brief	モデルオブジェクト
* @date		2021-06-21
* @author	s.fukami
*/

#ifndef __APP_MODEL_OBJECT_H__
#define __APP_MODEL_OBJECT_H__

#include "app/graphic/render/appRenderable.h"
#include "app/transform/appTransformObject.h"
#include "app/graphic/render/model/appModelRender.h"
#include "app/resource/memory/appResourceMemoryType.h"

namespace ng
{
	struct Matrix4x4;
}
namespace app
{
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					モデルオブジェクト
	*/
	class CModelObject : public IRenderable, public CTransformObject
	{
	public:
		CModelObject();
		~CModelObject();

		/*!
		* @brief					生成
		* @param modelFilePath		モデルファイルのパス
		* @param resMemType			リソースメモリタイプ
		* @return					成否
		*/
		bool Create(const char* modelFilePath, eResourceMemoryType resMemType);

		/*!
		* @brief					破棄
		*/
		void Destroy();

		/*!
		* @brief					ワールド変換行列取得
		*/
		void GetWorldMatrix(ng::Matrix4x4& dst);

		/*!
		* @brief					描画可能か
		*/
		void SetVisible(bool visible);
		bool IsVisible() const;

		/*!
		* @brief					モデル描画取得
		*/
		CModelRender& GetRender();
		const CModelRender& GetRender() const;

	private:
		/*! 描画 */
		void _render(const RenderParam& param);

	private:
		CModelRender m_model;	//!< モデル描画
		bool m_isVisible;	//!< 描画可能か
	};

}	// namespace app

#endif	// __APP_MODEL_OBJECT_H__