/*!
* @file		appGraphicPipeline.h
* @brief	グラフィックパイプライン 基底クラス
* @date		2020-08-24
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_PIPELINE_H__
#define __APP_GRAPHIC_PIPELINE_H__

#include "../command/appGraphicCommandListId.h"

namespace ng
{
	class CDX12CommandList;
}

namespace app
{
	/*!
	* @brief					グラフィックパイプライン 基底クラス
	*/
	class CGraphicPipeline
	{
	public:
		CGraphicPipeline();
		virtual ~CGraphicPipeline();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					実行
		*/
		void Execute();

		/*! 初期化済みか */
		bool IsInit() const;

	protected:
		/*! DX12コマンドリスト取得 */
		ng::CDX12CommandList* _getDX12CommandList(eGraphicCommandListId id) const;

	private:
		/*! 初期化 */
		virtual bool _initialize();

		/*! 終了処理 */
		virtual void _finalize();
		
		/*! 実行 */
		virtual void _execute();

		/*!
		* @brief					パイプライン実行 事前処理
		*/
		void _preprocessPipeline();

		/*!
		* @brief					パイプライン実行 事後処理
		*/
		void _postprocessPipeline();

	private:
		bool m_isInit;	//!< 初期化済みか
	};

}	// namespace app

#endif	// __APP_GRAPHIC_PIPELINE_H__