/*!
* @file		appRootSignatureInfo.h
* @brief	ルートシグネチャ記述子情報
* @date		2020-07-26
* @author	s.fukami
*/

#ifndef __APP_ROOT_SIGNATURE_INFO_H__
#define __APP_ROOT_SIGNATURE_INFO_H__

struct CD3DX12_ROOT_SIGNATURE_DESC;

namespace app
{
	/*!
	* @brief					ルートシグネチャ記述子情報
	*/
	struct RootSignatureInfo
	{
		const char* name;	//!< 名前
		const CD3DX12_ROOT_SIGNATURE_DESC* pDesc;	//!< ルートシグネチャ記述子
	};

	/*!
	* @brief					ルートシグネチャ記述子情報取得
	*/
	const RootSignatureInfo* GetRootSignatureInfo(unsigned int index);

	/*!
	* @brief					ルートシグネチャ記述子情報の数を取得
	*/
	unsigned int GetRootSignatureInfoNum();

}	// namespace app

#endif	// __APP_ROOT_SIGNATURE_INFO_H__