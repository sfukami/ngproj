/*!
* @file		ngOutputStream.h
* @brief	出力ストリーム インターフェース
* @date		2020-06-19
* @author	s.fukami
*/

#ifndef __NG_CORE_OUTPUT_STREAM_H__
#define __NG_CORE_OUTPUT_STREAM_H__

namespace ng
{
	class NG_DECL IOutputStream
	{
	public:
		IOutputStream() { }
		virtual ~IOutputStream() { }

		virtual void Write(const char*) = 0;
		virtual void Write(const wchar_t*) = 0;
	};

}	// namespace ng

#endif	// __NG_CORE_OUTPUT_STREAM_H__