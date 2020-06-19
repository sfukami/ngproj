/*!
* @file		testUnitTest.cpp
* @brief	単体テスト テストコード
* @date		2018-10-10
* @author	s.fukami
*/

namespace test
{
	TEST_CLASS(CTestUnitTest)
	{
	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			TEST_LOGMSG("Initialize");
		}

		TEST_ATTRIBUTE_TRAIT(Test1, "Test")
		TEST_METHOD(Test1)
		{
			TEST_LOGMSG("test1");
		}

		TEST_ATTRIBUTE_TRAIT(Test2, "Test")
		TEST_METHOD(Test2)
		{
			TEST_LOGMSG("test2");
		}

		TEST_ATTRIBUTE_TRAIT(Test3, "Test")
		TEST_METHOD(Test3)
		{
			TEST_SETUP();

			NG_DPRINTF("test3");
		}
	};

}	//namespace test