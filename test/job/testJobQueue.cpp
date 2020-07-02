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
			{
				auto job1 = ng::CSharedPtr<ng::IJob>(NG_NEW(alloc) CJob(1), alloc);
				auto job2 = NG_MAKE_SHARED_PTR(ng::IJob, alloc, CJob(2));
				auto job3 = NG_MAKE_SHARED_PTR(ng::IJob, alloc, CJob(3));

				jobQueue.AddJob(job1);
				jobQueue.AddJob(job2);
				jobQueue.AddJob(job3);
			}

			// ジョブ実行
			jobQueue.Execute();

			jobQueue.Finalize();
		}
	};

}	// namespace test