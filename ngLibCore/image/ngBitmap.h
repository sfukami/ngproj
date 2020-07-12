/*!
* @file		ngBitmap.h
* @brief	ビットマップ画像
* @date		2019-07-31
* @author	s.fukami
*/

#ifndef __NG_CORE_BITMAP_H__
#define __NG_CORE_BITMAP_H__

#include <vector>	// TODO:

namespace ng
{
	/*!
	* @brief					ビットマップ画像
	*/
	class NG_DECL CBitmap
	{
	public:
		CBitmap();
		~CBitmap();

		/*!
		* @brief					ファイルからビットマップ画像読み込み
		* @param pFilename			ファイル名
		* @return					成否
		*/
		bool LoadFromFile(
			const char* pFilename
			);
		bool LoadFromFile(
			const wchar_t* pFilename
			);

		/*!
		* @brief					ビットマップデータ取得
		*/
		u32* GetPixelData();
		const u32* GetPixelData() const;

		/*! 画像幅取得 */
		u32 GetWidth() const { return m_width; }

		/*! 画像高さ取得 */
		u32 GetHeight() const { return m_height; }

		/*! 画像のデータサイズを取得 */
		size_type GetDataSize() const;

	private:
		/*! ピクセル構築処理 */
		void _buildPixel(HBITMAP hBitmap);

	private:
		u32 m_width;	//!< 画像幅
		u32 m_height;	//!< 画像高さ
		// TODO: 一旦vectorで
		std::vector<u32> m_pixelData;	//!< ピクセルデータ
	};

}	// namespace ng

#endif	// __NG_CORE_BITMAP_H__