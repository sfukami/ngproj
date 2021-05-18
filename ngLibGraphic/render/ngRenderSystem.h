/*!
* @file		ngRenderSystem.h
* @brief	描画システム
* @date		2020-07-07
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_RENDER_SYSTEM_H__
#define __NG_GRAPHIC_RENDER_SYSTEM_H__

#include "ngRenderCommandBuffer.h"

namespace ng
{
	class IRenderable;
	struct RenderCommand;
	struct RenderParam;
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
		* @param command			追加する描画コマンド
		*/
		void AddCommand(const RenderCommand& command);

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
		//! バッファインデックス
		enum class BufferIndex : u32
		{
			PRIMARY,	//!< 第1バッファ
			SECONDARY,	//!< 第2バッファ
			NUM
		};

		//! コマンドバッファ
		class CCommandBuffer
		{
		public:
			CCommandBuffer();
			~CCommandBuffer();

			/*! 現在の描画コマンドバッファを指定 */
			void SetCurrBuffer(BufferIndex index);
			/*! 描画コマンドバッファを入れ替え */
			void SwapBuffer();

			/*! 描画コマンドバッファ取得 */
			CRenderCommandBuffer& GetCurrBuffer();
			const CRenderCommandBuffer& GetCurrBuffer() const;
			CRenderCommandBuffer& GetBuffer(BufferIndex index);
			const CRenderCommandBuffer& GetBuffer(BufferIndex index) const;

		private:
			CRenderCommandBuffer m_cmdBufs[ static_cast<int>(BufferIndex::NUM) ];	//!< 描画コマンドバッファ
			BufferIndex m_currIndex;	//!< 現在のバッファインデックス
		};

	private:
		CCommandBuffer m_cmdBuf;	//!< コマンドバッファ
		bool m_isSorted;	//!< 描画コマンドがソート済みか
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_RENDER_SYSTEM_H__