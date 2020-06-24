/*!
* @file		ngDX12Device.h
* @brief	DX12デバイス
* @date		2017-08-23
* @author	s.fukami
*/

#ifndef __NG_GRAPHIC_DX12_DEVICE_H__
#define __NG_GRAPHIC_DX12_DEVICE_H__

#include <D3DCommon.h>
#include <DXGI.h>
#include "ngDX12DeviceDriverType.h"

struct ID3D12Device;
struct IDXGIAdapter;

namespace ng
{
	/*!
	* @brief					DX12デバイス
	*/
	class NG_DECL CDX12Device
	{
	public:
		//! 生成パラメータ
		struct CreateParam
		{
			CreateParam();

			D3D_FEATURE_LEVEL featureLevel;	//!< 指定の機能レベル
			bool isUseWarpDevice;	//!< Warpデバイスを使用するか

			static const D3D_FEATURE_LEVEL FeatureLevelDefault;		//!< デフォルトの機能レベル
		};

		//! DX12デバイス生成詳細
		struct CreateDesc
		{
			friend class CDX12Device;

			CreateDesc();

			eDX12DriverType driverType;		//!< ドライバー種類
			D3D_FEATURE_LEVEL featureLevel;	//!< 有効な機能レベル
			DXGI_ADAPTER_DESC1 adapterDesc;	//!< ビデオアダプタの詳細

		private:
			/*! 設定 */
			void Set(D3D_FEATURE_LEVEL level, IDXGIAdapter1* pIAdapter);
			/*! リセット */
			void Reset();
		};

	public:
		CDX12Device();
		~CDX12Device();

		/*!
		* @brief					DX12デバイス生成
		* @param param				生成パラメータ
		* @return					NG エラーコード
		*/
		NG_ERRCODE Create(const CreateParam& param);

		/*!
		* @brief					破棄
		*/
		void Destroy();
		
		/*!
		* @brief					デバイス生成詳細取得
		*/
		const CreateDesc& GetCreateDesc() const;
		
		/*!
		* @brief					有効か
		*/
		bool IsValid() const;
		
		/*!
		* @brief					DX12デバイス インターフェース取得
		*/
		ID3D12Device* Interface();
		const ID3D12Device* Interface() const;
		
	private:
		/*!
		* @brief					デバイス生成
		* @param pIAdapter			IDXGIAdapterインターフェース
		* @param featureLevel		指定の機能レベル
		* @return					NG エラーコード
		*/
		NG_ERRCODE _createDevice(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel);

		/*!
		* @brief					機能レベルを優先し、デバイス生成
		* @param pIAdapter			IDXGIAdapterインターフェース
		* @param featureLevel		指定の機能レベル
		* @return					NG エラーコード
		* @note						指定の機能レベルを優先して生成する。失敗した場合はサポートする機能レベル一覧から
		*							上位のレベルを優先して生成する
		*/
		NG_ERRCODE _createDeviceInOrder(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel);

		/*!
		* @brief					指定の機能レベルでデバイスが生成可能か確認
		* @param pIAdapter			IDXGIAdapterインターフェース
		* @param featureLevel		指定の機能レベル
		* @return					NG エラーコード
		*/
		NG_ERRCODE _checkCreatableDevice(IDXGIAdapter1* pIAdapter, D3D_FEATURE_LEVEL featureLevel);

	private:
		ID3D12Device* m_pIDevice;	//!< DX12デバイス インターフェース
		CreateDesc m_createDesc;	//!< デバイス生成詳細
	};

}	// namespace ng

#endif	// __NG_GRAPHIC_DX12_DEVICE_H__