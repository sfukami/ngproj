/*!
* @file		testAction.cpp
* @brief	テストコード アクション
* @date		2020-07-18
* @author	s.fukami
*/

#include "ngLibCore/action/ngAction.h"

namespace test
{
	void Func1() { ng::Printf("call %s. \n", NG_FUNCTION); }
	void Func2(char c) { ng::Printf("call %s. \n", NG_FUNCTION); }
	template <typename T> void Func3() { ng::Printf("call %s. \n", NG_FUNCTION); }

	/*!
	* @brief					アクション テスト
	*/
	TEST_CLASS(CTestAction)
	{
	private:
		class CTest
		{
		public:
			void Func1() { ng::Printf("call %s. \n", NG_FUNCTION); }
			void Func2(int n) { ng::Printf("call %s. \n", NG_FUNCTION); }
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestAction)
		{
			ng::CAction<void> a1(Func1);
			ng::CAction<void, char> a2(Func2);
			ng::CAction<void> a3(Func3<int>);

			a1();
			a2('A');
			a3();

			a1(std::make_tuple());
			a2(std::make_tuple('B'));
			a3(std::make_tuple());
		}

		TEST_METHOD(TestClassAction)
		{
			CTest t;

			ng::CClassAction<CTest, void> a1(&t, &CTest::Func1);
			ng::CClassAction<CTest, void, int> a2(&t, &CTest::Func2);

			a1();
			a2(100);

			a1(std::make_tuple());
			a2(std::make_tuple(200));
			a2(ng::CClassAction<CTest, void, int>::ArgsType(100));
		}
	};

}	// namespace test