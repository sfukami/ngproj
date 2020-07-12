/*!
* @file		ngDX12TextureLoaderFlag.h
* @brief	DX12テクスチャローダー フラグ
* @date		2020-07-12
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_TEXTURE_LOADER_FLAG_H__
#define __NG_GRAPHIC_DX12_TEXTURE_LOADER_FLAG_H__

namespace ng
{
	/*!
	* @brief					DX12テクスチャローダー WIC(Windows Imaging Component)フラグ
	*/
	enum class NG_WIC_FLAGS : u32
	{
		NONE				 = 0x0,		// WIC_FLAGS_NONE                  = 0x0,

		FORCE_RGB			 = 0x1,		// WIC_FLAGS_FORCE_RGB             = 0x1,
										// Loads DXGI 1.1 BGR formats as DXGI_FORMAT_R8G8B8A8_UNORM to avoid use of optional WDDM 1.1 formats

		NO_X2_BIAS			 = 0x2,		// WIC_FLAGS_NO_X2_BIAS            = 0x2,
										// Loads DXGI 1.1 X2 10:10:10:2 format as DXGI_FORMAT_R10G10B10A2_UNORM

		NO_16BPP			 = 0x4,		// WIC_FLAGS_NO_16BPP              = 0x4,
										// Loads 565, 5551, and 4444 formats as 8888 to avoid use of optional WDDM 1.2 formats

		ALLOW_MONO			 = 0x8,		// WIC_FLAGS_ALLOW_MONO            = 0x8,
										// Loads 1-bit monochrome (black & white) as R1_UNORM rather than 8-bit grayscale

		ALL_FRAMES			 = 0x10,	// WIC_FLAGS_ALL_FRAMES            = 0x10,
										// Loads all images in a multi-frame file, converting/resizing to match the first frame as needed, defaults to 0th frame otherwise

		IGNORE_SRGB			 = 0x20,	// WIC_FLAGS_IGNORE_SRGB           = 0x20,
										// Ignores sRGB metadata if present in the file

		FORCE_SRGB			 = 0x40,	// WIC_FLAGS_FORCE_SRGB            = 0x40,
										// Writes sRGB metadata into the file reguardless of format

		FORCE_LINEAR		 = 0x80,	// WIC_FLAGS_FORCE_LINEAR          = 0x80,
										// Writes linear gamma metadata into the file reguardless of format

		DEFAULT_SRGB		 = 0x100,	// WIC_FLAGS_DEFAULT_SRGB          = 0x100,
		 								// If no colorspace is specified, assume sRGB

		DITHER				 = 0x10000,	// WIC_FLAGS_DITHER                = 0x10000,
										// Use ordered 4x4 dithering for any required conversions

		DITHER_DIFFUSION	 = 0x20000,	// WIC_FLAGS_DITHER_DIFFUSION      = 0x20000,
										// Use error-diffusion dithering for any required conversions

		FILTER_POINT		 = 0x100000,	// WIC_FLAGS_FILTER_POINT          = 0x100000,
		FILTER_LINEAR		 = 0x200000,	// WIC_FLAGS_FILTER_LINEAR         = 0x200000,
		FILTER_CUBIC		 = 0x300000,	// WIC_FLAGS_FILTER_CUBIC          = 0x300000,
		FILTER_FANT			 = 0x400000,	// WIC_FLAGS_FILTER_FANT           = 0x400000, // Combination of Linear and Box filter
											// Filtering mode to use for any required image resizing (only needed when loading arrays of differently sized images; defaults to Fant)
	};

	/*!
	* @brief					DX12テクスチャローダー DDSフラグ
	*/
	enum class NG_DDS_FLAGS : u32
	{
		NONE				 = 0x0,		// DDS_FLAGS_NONE                  = 0x0,

		LEGACY_DWORD		 = 0x1,		// DDS_FLAGS_LEGACY_DWORD          = 0x1,
										// Assume pitch is DWORD aligned instead of BYTE aligned (used by some legacy DDS files)

		NO_LEGACY_EXPANSION	 = 0x2,		// DDS_FLAGS_NO_LEGACY_EXPANSION   = 0x2,
										// Do not implicitly convert legacy formats that result in larger pixel sizes (24 bpp, 3:3:2, A8L8, A4L4, P8, A8P8)

		NO_R10B10G10A2_FIXUP = 0x4,		// DDS_FLAGS_NO_R10B10G10A2_FIXUP  = 0x4,
										// Do not use work-around for long-standing D3DX DDS file format issue which reversed the 10:10:10:2 color order masks

		FORCE_RGB			 = 0x8,		// DDS_FLAGS_FORCE_RGB             = 0x8,
										// Convert DXGI 1.1 BGR formats to DXGI_FORMAT_R8G8B8A8_UNORM to avoid use of optional WDDM 1.1 formats

		NO_16BPP			 = 0x10,	// DDS_FLAGS_NO_16BPP              = 0x10,
										// versions avoid use of 565, 5551, and 4444 formats and instead expand to 8888 to avoid use of optional WDDM 1.2 formats

		EXPAND_LUMINANCE	 = 0x20,	// DDS_FLAGS_EXPAND_LUMINANCE      = 0x20,
										// When loading legacy luminance formats expand replicating the color channels rather than leaving them packed (L8, L16, A8L8)

		BAD_DXTN_TAILS		 = 0x40,	// DDS_FLAGS_BAD_DXTN_TAILS        = 0x40,
										// Some older DXTn DDS files incorrectly handle mipchain tails for blocks smaller than 4x4

		FORCE_DX10_EXT		 = 0x10000,	// DDS_FLAGS_FORCE_DX10_EXT        = 0x10000,
										// Always use the 'DX10' header extension for DDS writer (i.e. don't try to write DX9 compatible DDS files)

		FORCE_DX10_EXT_MISC2 = 0x20000,	// DDS_FLAGS_FORCE_DX10_EXT_MISC2  = 0x20000,
										// DDS_FLAGS_FORCE_DX10_EXT including miscFlags2 information (result may not be compatible with D3DX10 or D3DX11)

		FORCE_DX9_LEGACY	 = 0x40000,	// DDS_FLAGS_FORCE_DX9_LEGACY      = 0x40000,
										// Force use of legacy header for DDS writer (will fail if unable to write as such)
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_TEXTURE_LOADER_FLAG_H__