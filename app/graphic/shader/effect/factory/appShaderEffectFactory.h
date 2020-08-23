/*!
* @file		appShaderEffectFactory.h
* @brief	シェーダーエフェクト ファクトリ
* @date		2020-07-28
* @author	s.fukami
*/

#ifndef __APP_SHADER_EFFECT_FACTORY_H__
#define __APP_SHADER_EFFECT_FACTORY_H__

#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "app/graphic/appGraphicConst.h"

namespace ng
{
	class IMemoryAllocator;
}

namespace app
{
	class CShaderEffect;
}

namespace app
{
	/*!
	* @brief					シェーダーエフェクト ファクトリ
	*/
	class CShaderEffectFactory
	{
	public:
		CShaderEffectFactory();
		~CShaderEffectFactory();

		/*!
		* @brief					初期化
		* @return					成否
		*/
		bool Initialize();

		/*!
		* @brief					終了処理
		*/
		void Finalize();

		/*!
		* @brief					シェーダーエフェクト生成
		* @param alloc				使用するメモリアロケータ
		* @param name				シェーダーエフェクトの名前
		* @param dstPtr				生成したシェーダーエフェクトの格納先
		* @return					成否
		*/
		bool Create(
			ng::IMemoryAllocator& alloc, const char* name, ng::CSharedPtr<CShaderEffect>& dstPtr
			) const;

	private:
		/*! シェーダーエフェクト生成 */
		template <class T>
		CShaderEffect* _createShaderEffect(ng::IMemoryAllocator& alloc) const;

	private:
		using FuncType = CShaderEffect*(CShaderEffectFactory::*)(ng::IMemoryAllocator&)const;	//!< シェーダーエフェクト生成関数

	private:
		ng::CFixedHashMap<const char*, FuncType, APP_GRAPHIC_SHADER_EFFECT_FACTORY_MAX> m_funcMap;	//!< シェーダーエフェクト生成関数マップ
	};

	template <class T>
	CShaderEffect* CShaderEffectFactory::_createShaderEffect(ng::IMemoryAllocator& alloc) const
	{
		return NG_NEW(alloc) T;
	}

}	// namespace app

#endif	// __APP_SHADER_EFFECT_FACTORY_H__