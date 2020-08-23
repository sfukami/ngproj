/*!
* @file		appRootSignatureInfo.cpp
* @brief	ルートシグネチャ記述子情報
* @date		2020-07-26
* @author	s.fukami
*/

#include "appRootSignatureInfo.h"
#include "desc/appRootSignatureDescSprite.h"

namespace app
{
	//! ルートシグネチャ記述子
	static CRootSignatureDescSprite s_sprite;

	//! ルートシグネチャ記述子情報テーブル
	const RootSignatureInfo s_rootSignInfoTable[] =
	{
		{ "sprite",	&s_sprite },
	};

	const RootSignatureInfo* GetRootSignatureInfo(unsigned int index)
	{
		NG_ASSERT(index < GetRootSignatureInfoNum());

		return &s_rootSignInfoTable[index];
	}

	unsigned int GetRootSignatureInfoNum()
	{
		return NG_ARRAY_SIZE(s_rootSignInfoTable);
	}

}	// namespace app