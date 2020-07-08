/*!
* @file		ngRenderCommand.h
* @brief	描画コマンド
* @date		2020-07-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDER_COMMAND_H__
#define __NG_GRAPHIC_RENDER_COMMAND_H__

#include "ngLibCore/container/list/intrusive/ngIntrusiveListNode.h"

namespace ng
{
	class IRenderable;
}

namespace ng
{
	/*!
	* @brief					描画コマンド
	*/
	class NG_DECL CRenderCommand : public CIntrusiveListNode<CRenderCommand>
	{
	public:
		/*!
		* @brief					コンストラクタ
		* @param pRenderable		描画可能オブジェクト
		*/
		CRenderCommand(IRenderable* pRenderable);

		/*! デストラクタ */
		~CRenderCommand();

		/*!
		* @brief					実行
		*/
		void Execute();

	private:
		IRenderable* m_pRenderable;	//!< 描画可能オブジェクト
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDER_COMMAND_H__