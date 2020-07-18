/*!
* @file		testJobQueue.cpp
* @brief	テストコード ジョブキュー
* @date		2020-07-02
* @author	s.fukami
*/

#include "ngLibCore/job/ngJob.h"
#include "ngLibCore/job/ngJobQueue.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* @brief					ジョブキュー テスト
	*/
	TEST_CLASS(CTestJobQueue)
	{
	private:
		class CJob : public ng::IJob
		{
		public:
			CJob(int i) : m_i(i) { }
			void Execute()
			{
				ng::Printf("[CJob::Execute] %d\n", m_i);
			}

		private:
			int m_i;
		};

	private:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestJobQueue)
		{
			ng::CDefaultAllocator alloc;
			ng::CJobQueue jobQueue;

			NG_ERRCODE err = jobQueue.Initialize(32, alloc);
			if(NG_FAILED(err)) {
				NG_ERRLOG_C("TestJobQueue", err, "ジョブキューの初期化に失敗しました.")
				return;
			}

			// ジョブ追加
			CJob* pJob1 = NG_NEW(alloc) CJob(1);
			CJob* pJob2 = NG_NEW(alloc) CJob(2);
			CJob* pJob3 = NG_NEW(alloc) CJob(3);
			
			jobQueue.EnqueueJob(pJob1);
			jobQueue.EnqueueJob(pJob2);
			jobQueue.EnqueueJob(pJob3);

			// ジョブ実行
			jobQueue.Execute();

			// 後始末
			NG_DELETE(alloc, pJob1);
			NG_DELETE(alloc, pJob2);
			NG_DELETE(alloc, pJob3);

			jobQueue.Finalize();
		}
	};

}	// namespace test