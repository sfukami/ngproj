﻿/*!
* @file		ngRenderSystem.h
* @brief	描画システム
* @date		2020-07-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDER_SYSTEM_H__
#define __NG_GRAPHIC_RENDER_SYSTEM_H__

#include "ngLibCore/allocator/ngStackAllocator.h"
#include "ngLibCore/container/list/ngIntrusiveList.h"
#include "ngRenderCommand.h"

namespace ng
{
	class CRenderCommand;
}

namespace ng
{
	/*!
	* @brief					描画システム
	*/
	class NG_DECL CRenderSystem
	{
	public:
		CRenderSystem();
		~CRenderSystem();

		/*!
		* @brief					初期化
		* @param commandMax			描画コマンド最大数
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(u32 commandMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();
		
		/*!
		* @brief					描画コマンド追加
		*/
		void AddCommand(CRenderCommand& command);

		/*!
		* @brief					描画コマンド実行
		*/
		void ExecuteCommand();

		/*!
		* @brief					描画コマンドクリア
		*/
		void ClearCommand();

	private:
		/*! 描画コマンドリストをソート */
		void _sortCommandList();

	private:
		CStackAllocator m_cmdAlloc;	//!< 描画コマンドのアロケータ
		CIntrusiveList<CRenderCommand> m_cmdList;	//!< 描画コマンドリスト

		bool m_isSorted;	//!< ソート済みか
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDER_SYSTEM_H__