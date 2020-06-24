/*!
* @file		ngWindow.h
* @brief	アプリケーションウィンドウ
* @date		2015-04-18
* @author	s.fukami
*/

#ifndef __NG_APP_WINDOW_H__
#define __NG_APP_WINDOW_H__

namespace ng
{
	/*!
	* @brief					アプリケーションウィンドウ
	*/
	class NG_DECL CWindow
	{
	public:
		static const int CLASS_NAME_LENGTH = 255;	// ウィンドウクラス名 文字列長
		static const int WINDOW_NAME_LENGTH = 255;	// ウィンドウ名 文字列長

	public:
		CWindow();
		~CWindow();

		/*!
		* @brief					ウィンドウ生成
		*
		* @param clientWidth		クライアント領域幅
		* @param clientHeight		クライアント領域高さ
		* @param className			ウィンドウクラス名
		* @param windowName			ウィンドウ名
		* @param pWndProc			ウィンドウプロシージャ
		* @return					成否
		* @retval false				ウィンドウ生成失敗
		*/
		bool Create(
			unsigned int clientWidht,
			unsigned int clientHeight,
			LPCTSTR className,
			LPCTSTR windowName,
			WNDPROC pWndProc
			);

		/*!
		* @brief					ウィンドウ表示
		*/
		void Show();

		/*!
		* @brief					ウィンドウクラス登録解除
		*/
		void UnregisterClass();

		/*!
		* @brief					ウィンドウ破棄
		*/
		void Destroy();

		/*! ウィンドウハンドル取得 */
		HWND GetHandle() const { return m_hWnd; }

		/*! クライアント領域幅取得 */
		unsigned int GetClientWidth() const { return m_clientWidth; }

		/*! クライアント領域高さ取得 */
		unsigned int GetClientHeight() const { return m_clientHeight; }

		/*! ウィンドウクラス名取得 */
		LPCTSTR GetClassName() const { return m_className; }

		/*! ウィンドウ名取得 */
		LPCTSTR GetWindowName() const { return m_windowName; }

	private:
		HWND m_hWnd;	//!< ウィンドウハンドル
		unsigned int m_clientWidth;		//!< クライアント領域幅
		unsigned int m_clientHeight;	//!< クライアント領域高さ
		TCHAR m_className[CLASS_NAME_LENGTH + 1];		//!< ウィンドウクラス名
		TCHAR m_windowName[WINDOW_NAME_LENGTH + 1];		//!< ウィンドウ名
	};

}	// namespace ng

#endif	// __NG_APP_WINDOW_H__