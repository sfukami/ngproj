/*!
* @file		appDebugMenuItemScene.cpp
* @brief	デバッグメニュー項目 シーン関連
* @date		2021-06-01
* @author	s.fukami
*/

#include "ngLibCore/action/ngAction.h"
#include "ngLibApp/ui/imgui/ngImGui.h"
#include "app/common/appCommon.h"
#include "app/scene/appSceneModule.h"
#include "appDebugMenuItemScene.h"
// Scene
#include "app/scene/root/appSceneRoot.h"
#include "app/scene/test/appSceneTest.h"
#include "app/scene/test/appSceneGraphicPipelineTest.h"
#include "app/scene/test/appSceneImGuiTest.h"
#include "app/scene/test/appSceneGameTest.h"

namespace app
{
	/*! シーンの分類 */
	enum class eSceneCategory : int
	{
		MAIN,	//!< メインシーン
		TEST,	//!< テストシーン
		NUM,
	};

	/*! シーン項目 */
	class CSceneItem : public ng::CComboItem
	{
	public:
		CSceneItem(const char* name, ActionType::FuncType pFunc) : CComboItem(name, pFunc) { }
	};

	/*! シーン遷移関数 */
	template <class T>
	void ChangeScene()
	{
		auto scenePtr = ng::StaticCast<IScene>(NG_MAKE_SHARED_PTR(T, APP_GET_MEMALLOC(APPLICATION)));
		CSceneModule::RequestChangeScene(eSceneId::GAME, scenePtr);
	}

	/*! シーン項目生成マクロ */
	#define MAKE_SCENE_ITEM(_name) \
		CSceneItem(NG_TO_STRING(_name), ChangeScene<NG_JOIN(C, _name)>)

	/*! シーン項目テーブル */
	// メイン
	static const CSceneItem g_mainSceneItems[] = {
		MAKE_SCENE_ITEM(SceneRoot),
	};
	// テスト
	static const CSceneItem g_testSceneItems[] = {
		MAKE_SCENE_ITEM(SceneGameTest),
		MAKE_SCENE_ITEM(SceneGraphicPipelineTest),
		MAKE_SCENE_ITEM(SceneImGuiTest),
		MAKE_SCENE_ITEM(SceneTest),
	};

	/*! 項目データ */
	struct ItemData
	{
		ItemData(eSceneCategory _category, const char* _name, const CSceneItem* _pItems, int _itemsSize)
			: category(_category), pItems(_pItems), itemsSize(_itemsSize), selectedIndex(0)
		{ NG_STRCPY(name, _name); }

		eSceneCategory category;
		char name[32];
		const CSceneItem* pItems;
		int itemsSize;
		int selectedIndex;
	};

	/*! 項目データ生成マクロ */
	#define MAKE_ITEM_DATA(_category, _name, _pItems) \
		ItemData(eSceneCategory::##_category, _name, _pItems, NG_ARRAY_SIZE(_pItems))

	/*! 項目データテーブル */
	static ItemData g_itemDataTable[] = {
		MAKE_ITEM_DATA(MAIN, "main", g_mainSceneItems),
		MAKE_ITEM_DATA(TEST, "test", g_testSceneItems),
	};

	CDebugMenuItemScene::CDebugMenuItemScene()
	{
	}
	CDebugMenuItemScene::~CDebugMenuItemScene()
	{
	}

	void CDebugMenuItemScene::_update()
	{
	}

	void CDebugMenuItemScene::_render()
	{
		if(ImGui::CollapsingHeader("Scene")) {
			// シーンの分類選択
			ImGui::Text("category");
			for(int i = 0; i < (int)eSceneCategory::NUM; i++)
			{
				const ItemData& data = g_itemDataTable[i];
				ImGui::SameLine();
				ImGui::RadioButton(data.name, &m_sceneCategory, (int)data.category);
			}

			/// シーン選択
			{
				ItemData& data = g_itemDataTable[m_sceneCategory];
				ImGui::Combo("scene", &(data.selectedIndex), ng::ComboItemGetter, (void*)(data.pItems), data.itemsSize);
			}

			// シーン遷移
			if(ImGui::Button("Load")) {
				const ItemData& data = g_itemDataTable[m_sceneCategory];
				int index = data.selectedIndex;
				if(index >= 0 && index < data.itemsSize) {
					const CSceneItem& item = data.pItems[index];
					item.DoAction();
				}
				else {
					NG_WARNLOG("DebugMenuItemScene", "シーン項目のインデックスが範囲外です.");
				}
			}
		}
	}

}	// namespace app