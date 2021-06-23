/*!
* @file		testConst.cpp
* @brief	テストコード constの実験
* @date		2021-06-23
* @author	s.fukami
*/

namespace test
{
	/*!
	* @brief					constの実験
	*/
	TEST_CLASS(CTestConst)
	{
	private:
		class CTest
		{
		public:
			CTest() : m_value(0) { }
			void SetValue(int value) { m_value = value; }
			int GetValue() const { return m_value; }
			//int& GetValueRef() const { return m_value; }	// ※定義不可
			const int& GetValueRef() const { return m_value; }
			void Print() const { ng::Printf("[CTest::Print] value:%d\n", m_value); }

		private:
			int m_value;
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestConst)
		{
			CTest t;
			
			t.SetValue(100);

			const int& valueRef = t.GetValueRef();
			//valueRef = 200;

			t.Print();

			ng::Printf("--------\n");
		}
	};

}	// namespace test