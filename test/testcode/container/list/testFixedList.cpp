/*!
* @file		testFixedList.cpp
* @brief	テストコード 固定長リスト
* @date		2017-12-23
* @author	s.fukami
*/

#include "ngLibCore/container/list/ngFixedList.h"

namespace test
{
	/*!
	* 固定長リスト テスト
	*/
	TEST_CLASS(CTestFixedList)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestFixedList_Bidirectional)
		{
			typedef CDummy TType;
			typedef ng::CFixedList<TType, ng::BidirectionalLinked, 8> ListType;

			ListType list;

			TType t1(1), t2(2), t3(3);

			ng::Printf("push back.");
			list.PushBack(t1);
			list.PushBack(t2);
			list.PushBack(t3);

			// Front()
			{
				TType& t = list.Front();
				ng::Printf("front. value:%d\n", t.GetValue());
			}
			// Back()
			{
				TType& t = list.Back();
				ng::Printf("back. value:%d\n", t.GetValue());
			}

			// Erase()
			{
				ng::Printf("delete [1] element.\n");
				ListType::NodeType* pNode = list.Erase(list.Begin()->GetNext());
				ng::Printf(" next value:%d\n", pNode->GetElem().GetValue());
			}

			{
				ng::Printf("display all.\n");
				int count = 0;
				ListType::NodeType* pNode = list.Begin();
				for(; pNode != list.End(); pNode = pNode->GetNext(), count++)
				{
					TType& t = pNode->GetElem();
					ng::Printf(" %d: value:%d\n", count, t.GetValue());
				}
			}
		}

		TEST_METHOD(TestFixedList_Forward)
		{
			typedef CDummy TType;
			typedef ng::CFixedList<TType, ng::ForwardLinked, 8> ListType;

			ListType list;

			TType t1(1), t2(2), t3(3);

			ng::Printf("push front.");
			list.PushFront(t1);
			list.PushFront(t2);
			list.PushFront(t3);

			// Front()
			{
				TType& t = list.Front();
				ng::Printf("front. value:%d\n", t.GetValue());
			}

			{
				ng::Printf("display all.\n");
				int count = 0;
				ListType::NodeType* pNode = list.Begin();
				for(; pNode != list.End(); pNode = pNode->GetNext(), count++)
				{
					TType& t = pNode->GetElem();
					ng::Printf(" %d: value:%d\n", count, t.GetValue());
				}
			}
		}
	};

}	// namespace test