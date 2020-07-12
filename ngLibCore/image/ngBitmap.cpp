/*!
* @file		ngBitmap.cpp
* @brief	ビットマップ
* @date		2019-07-31
* @author	s.fukami
*/

#include <windows.h>
#include "ngLibCore/common/ngCommon.h"
#include "ngBitmap.h"

namespace ng
{
	CBitmap::CBitmap()
		: m_width(0), m_height(0)
	{
	}
	CBitmap::~CBitmap()
	{
	}

	bool CBitmap::LoadFromFile(
		const char* pFilename
		)
	{
		HBITMAP hBitmap = (HBITMAP)::LoadImageA(0, pFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if(!hBitmap) {
			char lastErr[256] = "\0";
			GetLastErrMsgA(lastErr, sizeof(lastErr));
			NG_ERRLOG("Bitmap", "ビットマップ画像の読み込みに失敗. %s\n", lastErr);
			return false;
		}

		_buildPixel(hBitmap);

		return true;
	}
	bool CBitmap::LoadFromFile(
		const wchar_t* pFilename
		)
	{
		HBITMAP hBitmap = (HBITMAP)::LoadImageW(0, pFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if(!hBitmap) {
			wchar_t lastErr[256] = L"\0";
			GetLastErrMsgW(lastErr, sizeof(lastErr));
			NG_ERRLOG(L"Bitmap", L"ビットマップ画像の読み込みに失敗. %s\n", lastErr);
			return false;
		}

		_buildPixel(hBitmap);

		return true;
	}

	void CBitmap::_buildPixel(HBITMAP hBitmap)
	{
		m_pixelData.clear();

		BITMAP bmp;
		HDC hMemDC = ::CreateCompatibleDC(NULL);

		::SelectObject(hMemDC, hBitmap);
		::GetObject(hBitmap, sizeof(BITMAP), &bmp);
		::DeleteObject(hBitmap);

		for(int y=0; y<bmp.bmHeight; y++)
		{
			for(int x=0; x<bmp.bmWidth; x++)
			{
				COLORREF color = ::GetPixel(hMemDC, x, y);
				BYTE r = color & 0xFF;
				BYTE g = (color>>8) & 0xFF;
				BYTE b = (color>>16) & 0xFF;
				m_pixelData.push_back((r<<16) | (g<<8) | b);
			}
		}
		::DeleteObject(hMemDC);

		m_width = bmp.bmWidth;
		m_height = bmp.bmHeight;
	}

	u32* CBitmap::GetPixelData()
	{
		if(m_pixelData.empty()) return nullptr;

		return &m_pixelData[0];
	}
	const u32* CBitmap::GetPixelData() const
	{
		return const_cast<CBitmap*>(this)->GetPixelData();
	}

}	// namespace ng