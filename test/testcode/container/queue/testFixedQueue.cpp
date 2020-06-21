/*!
* @file		testFixedQueue.cpp
* @brief	テストコード 固定長キュー
* @date		2017-09-09
* @author	s.fukami
*/

#include "ngLibCore/container/queue/ngFixedQueue.h"

namespace test
{
	/*!
	* 固定長キュー テスト
	*/
	TEST_CLASS(CTestFixedQueue)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestFixedQueue)
		{
			typedef ng::CFixedQueue<CDummy, 8> QueueType;

			QueueType queue;
			CDummy d1(1), d2(2), d3(3);

			// PushBack()
			queue.PushBack(d1);
			queue.PushBack(d2);
			queue.PushBack(d3);

			// Size(), MaxSize()
			ng::Printf("size:%d, maxSize:%d\n", queue.Size(), queue.MaxSize());

			// PopFront()
			{
				ng::Printf("pop.");
				queue.PopFront();
			}

			// []
			{
				ng::Printf("display all.\n");
				for(int i = 0; i < (int)queue.Size(); i++)
				{
					queue[i].Display();
				}
			}
			// Front()
			{
				CDummy& d = queue.Front();
				ng::Printf("front. value:%d\n", d.GetValue());
			}
			// Back()
			{
				CDummy& d = queue.Back();
				ng::Printf("back. value:%d\n", d.GetValue());
			}

			// Clear()
			ng::Printf("clear.\n");
			queue.Clear();
			ng::Printf("size:%d, maxSize:%d\n", queue.Size(), queue.MaxSize());
		}
	};

}	// namespace test