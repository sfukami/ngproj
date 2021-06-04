/*!
* @file		ngImGuiComboItem.cpp
* @brief	ImGui コンボボックス項目
* @date		2021-06-04
* @author	s.fukami
*/

#include "ngLibApp/common/ngCommon.h"
#include "ngImGuiComboItem.h"

namespace ng
{
	CComboItem::CComboItem(const char* name, ActionType::FuncType pFunc)
		: m_action(pFunc)
	{
		NG_STRCPY(m_name, name);
	}
	CComboItem::~CComboItem()
	{
	}

	void CComboItem::DoAction()
	{
		m_action();
	}

	void CComboItem::DoAction() const
	{
		m_action();
	}

	const char* CComboItem::GetName() const
	{
		return m_name;
	}

	NG_DECL bool ComboItemGetter(void* data, int idx, const char** out_text)
	{
		if(data == nullptr) return false;

		const CComboItem* pItems = ng::PointerCast<const CComboItem*>(data);
		(*out_text) = pItems[idx].GetName();

		return true;
	}

}	// namespace ng