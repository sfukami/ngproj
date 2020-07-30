/*!
* @file		appGraphicModule.h
* @brief	グラフィック機能
* @date		2020-07-01
* @author	s.fukami
*/

#ifndef __APP_GRAPHIC_MODULE_H__
#define __APP_GRAPHIC_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"

namespace ng
{
	template <class T> class CSharedPtr;
	template <class T> class CWeakPtr;
	class CDX12RootSignature;
	class CDX12PipelineState;
	class CDX12PipelineStateDesc;
}
namespace app
{
	class CGraphic;
	class CGraphicPipeline;
	class CMaterial;
	class CShaderEffect;
}

namespace app
{
	/*!
	* @brief					グラフィック機能
	*/
	class CGraphicModule : public ng::CNonInstantiable
	{
		friend class CApplication;

	public:
		/*!
		* @brief					グラフィックパイプライン設定
		*/
		static void SetGraphicPipeline(CGraphicPipeline* pPipeline);

		/*!
		* @brief					マテリアル追加
		* @param name				マテリアル名
		* @param material			追加するマテリアル
		* @return					成否
		*/
		static bool AddMaterial(const char* name, const CMaterial& material);

		/*!
		* @brief					マテリアル追加
		* @param name				マテリアル名
		* @param dst				マテリアルのコピー先
		* @return					成否
		*/
		static bool CopyMaterial(const char* name, CMaterial& dst);

		/*!
		* @brief					DX12ルートシグネチャ取得
		* @param name				DX12ルートシグネチャの名前
		* @param dstPtr				取得したDX12ルートシグネチャの格納先
		* @return					成否
		*/
		static bool GetRootSignature(const char* name, ng::CWeakPtr<ng::CDX12RootSignature>& dstPtr);

		/*!
		* @brief					DX12パイプラインステート取得
		* @param name				DX12パイプラインステートの名前
		* @param dstPtr				取得したDX12パイプラインステートの格納先
		* @return					成否
		*/
		static bool GetPipelineState(const char* name, ng::CWeakPtr<ng::CDX12PipelineState>& dstPtr);

		/*!
		* @brief					DX12パイプラインステートを生成し追加
		* @param name				DX12パイプラインステートの名前
		* @param stateDesc			DX12パイプラインステート記述子
		* @return					成否
		*/
		static bool CreateAndAddPipelineState(const char* name, const ng::CDX12PipelineStateDesc& stateDesc);

		/*!
		* @brief					シェーダーエフェクト生成
		* @param name				シェーダーエフェクトの名前
		* @param dstPtr				生成したシェーダーエフェクトの格納先
		* @return					成否
		*/
		static bool CreateShaderEffect(const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr);

	private:
		/*! グラフィックのインスタンスを設定 */
		static void SetGraphic(CGraphic* pGraphic);

		/*! 有効か */
		static bool _isValid();
		
	private:
		static CGraphic* s_pGraphic;	//!< グラフィックへの参照
	};

}	// namespace app

#endif	// __APP_GRAPHIC_MODULE_H__