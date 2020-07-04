/*!
* @file		appJobModule.h
* @brief	ジョブ機能
* @date		2020-07-03
* @author	s.fukami
*/

#ifndef __APP_JOB_MODULE_H__
#define __APP_JOB_MODULE_H__

#include "ngLibCore/traits/ngNonInstantiable.h"
#include "appJobManager.h"
#include "appJobProcess.h"

namespace ng
{
	class IJob;
	template <class T> class CSharedPtr;
}

namespace app
{
	class CJobManager;
}

namespace app
{
	/*!
	* @brief					ジョブ機能
	*/
	class CJobModule : public ng::CNonInstantiable
	{
		friend class CGame;

	public:
		/*!
		* @brief					ジョブ追加
		* @param jobPtr				追加するジョブ
		* @param jobProc			ジョブ処理定義
		* @return					成否
		*/
		static bool AddJob(
			ng::CSharedPtr<ng::IJob>& jobPtr,
			eJobProcess jobProc = eJobProcess::UPDATE
			);

	private:
		/*! ジョブ管理のインスタンスを設定 */
		static void SetJobManager(CJobManager* pJobMngr);

		/*! 有効か */
		static bool _isValid();
		
	private:
		static CJobManager* s_pJobMngr;	//!< ジョブ管理への参照
	};

}	// namespace app

#endif	// __APP_JOB_MODULE_H__