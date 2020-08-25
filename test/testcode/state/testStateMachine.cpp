/*!
* @file		testStateMachine.cpp
* @brief	テストコード ステートマシン
* @date		2020-07-18
* @author	s.fukami
*/

#include "ngLibCore/action/ngAction.h"
#include "ngLibApp/state/ngStateMachine.h"

namespace test
{
	/*!
	* @brief					ステートマシン テスト
	*/
	TEST_CLASS(CTestStateMachine)
	{
	private:
		class CTest
		{
		public:
			//enum State
			enum class State : unsigned int
			{
				FIRST, SECOND, THIRD,
				NUM,
				DEFAULT = SECOND,
			};

		public:
			void First() { ng::Printf("%s\n", NG_FUNCTION); }
			void Second() { ng::Printf("%s\n", NG_FUNCTION); }
			void Third() { ng::Printf("%s\n", NG_FUNCTION); }
		};

	private:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestStateMachine)
		{
			CTest t;

			ng::CClassStateMachine<CTest, CTest::State, CTest::State::NUM> sm(&t, CTest::State::DEFAULT);

			// ステート設定
			sm.SetState(CTest::State::FIRST, ng::CClassAction<CTest>(&t, &CTest::First));
			sm.SetState(CTest::State::SECOND, &CTest::Second);
			sm.SetState(CTest::State::THIRD, &CTest::Third);

			// 実行
			sm.Execute();

			sm.ChangeState(CTest::State::FIRST);

			sm.Execute();

			sm.ChangeState(CTest::State::THIRD);

			sm.Execute();
		}
	};

}	// namespace test