/*!
* @file		ngInputManager.cpp
* @brief	デバイス入力管理
* @date		2020-06-23
* @author	s.fukami
*/

#include "ngInputManager.h"
#include "ngInput.h"

namespace ng
{
	CInputManager CInputManager::m_instance;

	CInputManager::CInputManager()
		: m_pInput(nullptr)
	{
	}
	CInputManager::~CInputManager()
	{
	}

	void CInputManager::AssignInput(IInput* pInput)
	{
		if(pInput == nullptr) return;

		m_pInput = pInput;
	}

	void CInputManager::Update()
	{
		if(!IsAssigned()) return;

		m_pInput->Update();
	}

	void CInputManager::UnassignInput()
	{
		m_pInput = nullptr;
	}

	bool CInputManager::CheckKeyboardInput(
		eKeyCode code,
		eInputState state
		) const
	{
		if(!IsAssigned()) return false;

		return m_pInput->CheckKeyboardInput(code, state);
	}

	bool CInputManager::CheckMouseInput(
		eMouseCode code,
		eInputState state
		) const
	{
		if(!IsAssigned()) return false;

		return m_pInput->CheckMouseInput(code, state);
	}

	bool CInputManager::IsAssigned() const
	{
		return (m_pInput != nullptr);
	}

	CInputManager* CInputManager::_createInstance()
	{
		return &m_instance;
	}

	void CInputManager::_destroyInstance(CInputManager* pInst)
	{
		// 空定義
	}

}	// namespace ng