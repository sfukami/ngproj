/*!
* @file		testFixedStack.cpp
* @brief	テストコード 固定長スタック
* @date		2018-12-09
* @author	s.fukami
*/

#include "ngLibCore/container/stack/ngFixedStack.h"

namespace test
{
	/*!
	* @brief					固定長スタック テスト
	*/
	TEST_CLASS(CTestFixedStack)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestFixedStack)
		{
			typedef CDummy TType;
			typedef ng::CFixedStack<TType, 8> StackType;

			StackType stack;
			TType t1(1), t2(2), t3(3);

			stack.Push(t1);
			stack.Push(t2);
			stack.Push(t3);

			ng::Printf("size:%d, maxSize:%d\n", stack.Size(), stack.MaxSize());

			// Top()
			{
				TType& t = stack.Top();
				ng::Printf("top. value:%d\n", t.GetValue());
			}

			// Pop()
			{
				ng::Printf("pop.");
				stack.Pop();
			}

			{
				ng::Printf("display all.\n");
				for(int i = 0; i < (int)stack.Size(); i++)
				{
					stack[i].Display();
				}
			}

			// Clear()
			ng::Printf("clear.\n");
			stack.Clear();

			ng::Printf("size:%d, maxSize:%d\n", stack.Size(), stack.MaxSize());
		}
	};

}	// namespace test