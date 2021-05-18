/*!
* @file		ngRenderCommand.h
* @brief	描画コマンド
* @date		2020-07-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDER_COMMAND_H__
#define __NG_GRAPHIC_RENDER_COMMAND_H__

namespace ng
{
	class IRenderable;
	struct RenderParam;
}

namespace ng
{
	/*!
	* @brief					描画コマンド
	*/
	struct NG_DECL RenderCommand
	{
		RenderCommand();

		/*!
		* @brief					コンストラクタ
		* @param _order				描画順
		* @param _pRenderable		描画可能オブジェクト
		*/
		RenderCommand(u32 _order, IRenderable* _pRenderable);

		/*!
		* @brief					描画コマンド実行
		* @param pParam				描画パラメータ
		*/
		void Execute(const RenderParam* pParam);

		u32 order;	//!< 描画順
		IRenderable* pRenderable;	//!< 描画可能オブジェクト
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDER_COMMAND_H__