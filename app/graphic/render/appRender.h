/*!
* @file		appRender.h
* @brief	描画オブジェクト インターフェース
* @date		2021-06-21
* @author	s.fukami
*/

#ifndef __APP_RENDER_H__
#define __APP_RENDER_H__

namespace app
{
	struct RenderParam;
}

namespace app
{
	/*!
	* @brief					描画オブジェクト インターフェース
	*/
	class IRender
	{
	public:
		IRender();
		virtual ~IRender();

		/*!
		* @brief					描画
		* @param param				描画パラメータ
		*/
		void Render(const RenderParam& param);

		/*!
		* @brief					描画可能か
		*/
		virtual bool IsEnable() const = 0;

	private:
		/*! 描画 */
		virtual void _render(const RenderParam& param) = 0;
	};

}	// namespace app

#endif	// __APP_RENDER_H__