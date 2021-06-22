/*!
* @file		appModelRender.h
* @brief	モデル描画
* @date		2021-06-21
* @author	s.fukami
*/

#ifndef __APP_MODEL_RENDER_H__
#define __APP_MODEL_RENDER_H__

#include "ngLibApp/resource/ngResourceHandle.h"
#include "../appRender.h"
#include "app/graphic/model/appModel.h"
#include "app/resource/memory/appResourceMemoryType.h"

namespace app
{
	class CMesh;
	class CMaterial;
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					モデル描画
	*/
	class CModelRender : public IRender
	{
	public:
		CModelRender();
		~CModelRender();

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
		* @brief					描画可能か
		*/
		bool IsEnable() const;

	private:
		/*! 描画 */
		void _render(const RenderParam& param);
		/*! メッシュ描画 */
		void _renderMesh(const RenderParam& param, const CMesh& mesh, CMaterial* pMaterial);

	private:
		ng::CResourceHandle<CModel> m_handle;	//!< モデルのリソースハンドル
	};

}	// namespace app

#endif	// __APP_MODEL_RENDER_H__