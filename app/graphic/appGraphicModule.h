/*!
* @file		appGraphicModule.h
* @brief	グラフィック機能
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_MODULE_H__
#define __APP_GRAPHIC_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"

namespace app
{
	class CGraphic;
	class CGraphicPipeline;
}

namespace app
{
	/*!
	* @brief					グラフィック機能
	*/
	class CGraphicModule : public ng::CNonInstantiable
	{
		friend class CGame;

	public:
		/*!
		* @brief					グラフィックパイプライン設定
		*/
		static void SetGraphicPipeline(CGraphicPipeline* pPipeline);

	private:
		/*! グラフィックのインスタンスを設定 */
		static void SetGraphic(CGraphic* pGraphic);

	private:
		static CGraphic* s_pGraphic;	//!< グラフィックへの参照
	};

}	// namespace app

#endif	// __APP_GRAPHIC_MODULE_H__