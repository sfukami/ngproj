/*!
* @file		appMemoryModule.cpp
* @brief	メモリ機能
* @date		2020-07-02
* @author	s.fukami
*/

#include "appMemoryModule.h"
#include "appApplicationMemory.h"

namespace app
{
	CApplicationMemory* CMemoryModule::s_pAppMem = nullptr;

	ng::CWeakPtr<ng::IMemoryAllocator> CMemoryModule::GetAllocator(eMemoryAllocatorId id)
	{
		if(_isValid()) {
			return s_pAppMem->GetAllocator(id);
		}

		return ng::CWeakPtr<ng::IMemoryAllocator>();
	}

	void CMemoryModule::SetApplicationMemory(CApplicationMemory* pAppMem)
	{
		s_pAppMem = pAppMem;
	}

	bool CMemoryModule::_isValid()
	{
		return (s_pAppMem != nullptr);
	}

}	// namespace app