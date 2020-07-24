/*!
* @file		ngResource.h
* @brief	リソース インターフェース
* @date		2020-07-20
* @author	s.fukami
*/

#ifndef __NG_APP_RESOURCE_H__
#define __NG_APP_RESOURCE_H__

namespace ng
{
	/*!
	* @brief					リソース インターフェース
	*/
	class NG_DECL IResource
	{
	public:
		IResource() { }
		virtual ~IResource() { }

		/*!
		* @brief					リソース構築
		* @param pBinary			リソースバイナリ
		* @param size				リソースバイナリのサイズ
		* @param pBuildParam		ビルドパラメータ
		* @return					成否
		*/
		virtual bool Build(const void* pBinary, ng::size_type size, const void* pBuildParam) = 0;
	};

}	// namespace ng

#endif	// __NG_APP_RESOURCE_H__