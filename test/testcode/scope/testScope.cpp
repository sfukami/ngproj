/*!
* @file		testScope.cpp
* @brief	テストコード スコープ
* @date		2021-05-31
* @author	s.fukami
*/

namespace test
{
	/*!
	* @brief					スコープ テスト
	*/
	TEST_CLASS(CTestScope)
	{
	private:
		class CTest
		{
		public:
			CTest() { ng::Printf("[CTest::CTest()]\n"); }
			~CTest() { ng::Printf("[CTest::~CTest()]\n"); }
			void Print() { ng::Printf("[CTest::Print()]\n"); }
			explicit operator bool() const { return true; }
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestScope)
		{
			if(CTest t = CTest()) {
				t.Print();
			}

			ng::Printf("--------\n");

			if(CTest()) {
				ng::Printf("Print()\n");
			}
		}
	};

}	// namespace test