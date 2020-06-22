/*!
* @file		testIntrusiveList.cpp
* @brief	テストコード 侵入型リスト
* @date		2017-10-23
* @author	s.fukami
*/

#include "ngLibCore/container/list/ngIntrusiveList.h"

namespace test
{
	/*!
	* 侵入型リスト テスト
	*/
	TEST_CLASS(CTestIntrusiveList)
	{
	private:
		class CTest
			: public ng::CIntrusiveListNode<CTest>
			, public CDummy
		{
		public:
			CTest() { }
			explicit CTest(int value) : CDummy(value) { }
		};

		typedef CTest TType;

	public:
		TEST_DEFINE_INITIALIZE;

		// 双方向、実体
		TEST_METHOD(TestIntrusiveList_Bidirectional_Real)
		{
			typedef ng::CIntrusiveList<TType> ListType;
			ListType list;

			_common(list);
		}

		// 双方向、ポインタ
		TEST_METHOD(TestIntrusiveList_Bidirectional_Pointer)
		{
			typedef ng::CIntrusiveList<TType*> ListType;
			ListType list;

			_common(list);
		}

	private:
		template <class T>
		void _common(T& list)
		{
			typedef T ListType;

			TType t1(1), t2(2), t3(3);

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

			// Erase
			{
				ng::Printf("delete [1] element.\n");
				TType::NodeType* pNode = list.Erase(list.Begin()->GetNext());
				ng::Printf("value:%d\n", pNode->GetElem().GetValue());
			}

			{
				ng::Printf("display all.\n");
				int count = 0;
				typename ListType::NodeType* pNode = list.Begin();
				for(; pNode != list.End(); pNode = pNode->GetNext(), count++)
				{
					TType& t = pNode->GetElem();
					ng::Printf("%d: value:%d\n", count, t.GetValue());
				}
			}
		}
	};

}	// namespace test