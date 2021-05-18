/*!
* @file		ngRenderCommandBuffer.h
* @brief	描画コマンドバッファ
* @date		2020-05-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDER_COMMAND_BUFFER_H__
#define __NG_GRAPHIC_RENDER_COMMAND_BUFFER_H__

#include "ngLibCore/allocator/ngStackAllocator.h"

namespace ng
{
	class IMemoryAllocator;
	struct RenderCommand;
	struct RenderParam;
}

namespace ng
{
	/*!
	* @brief					描画コマンドバッファ
	*/
	class NG_DECL CRenderCommandBuffer
	{
	public:
		CRenderCommandBuffer();
		~CRenderCommandBuffer();

		/*!
		* @brief					初期化
		* @param alloc				使用するメモリアロケータ
		* @param commandMax			描画コマンド最大数
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(IMemoryAllocator& alloc, u32 commandMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					描画コマンド追加
		* @param command			追加する描画コマンド
		*/
		void AddCommand(const RenderCommand& command);

		/*!
		* @brief					描画コマンドソート
		*/
		void SortCommand();

		/*!
		* @brief					描画コマンド実行
		* @param pParam				描画パラメータ
		*/
		void ExecuteCommand(const RenderParam* pParam);

		/*!
		* @brief					描画コマンドクリア
		*/
		void ClearCommand();

	private:
		CStackAllocator m_cmdAlloc;	//!< 描画コマンドのアロケータ
		RenderCommand* m_pCmdBuf;	//!< 描画コマンドのバッファの先頭アドレス
		u32 m_cmdMax;	//!< 描画コマンドの最大数
		u32 m_cmdNum;	//!< 描画コマンドの数
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDER_COMMAND_BUFFER_H__