/*!
* @file		testFunctor.cpp
* @brief	テストコード ファンクタ
* @date		2018-11-3
* @author	s.fukami
*/

#include "ngLibCore/functor/ngFunctor.h"

namespace test
{
	void _func1() { ng::Printf("call %s. \n", NG_FUNCTION); }
	void _func2(int i) { ng::Printf("call %s. \n", NG_FUNCTION); }
	void _func3(int i, float f) { ng::Printf("call %s. \n", NG_FUNCTION); }

	/*!
	* @brief					ファンクタ テスト
	*/
	TEST_CLASS(CTestFunctor)
	{
	private:
		class CTest
		{
		public:
			void Func1() { ng::Printf("call %s. \n", NG_FUNCTION); }
			void Func2(char c) { ng::Printf("call %s. \n", NG_FUNCTION); }
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestFunctor)
		{
			ng::CFunctor<void, TL0()> f1(_func1);
			ng::CFunctor<void, TL1(int)> f2(_func2);
			ng::CFunctor<void, TL2(int, float)> f3(_func3);

			f1();
			f2(100);
			f3(100, 1.23f);
		}

		TEST_METHOD(TestClassFunctor)
		{
			CTest t;
			ng::CClassFunctor<CTest, void, TL0()> f1(&t, &CTest::Func1);
			ng::CClassFunctor<CTest, void, TL1(char)> f2(&t, &CTest::Func2);

			f1();
			f2('c');
		}
	};

}	// namespace test