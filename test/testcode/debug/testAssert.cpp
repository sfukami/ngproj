/*!
* @file		testAssert.cpp
* @brief	�e�X�g�R�[�h �A�T�[�g
* @date		2018-10-24
* @author	s.fukami
*/

namespace test
{
	/*!
	* �A�T�[�g �e�X�g
	*/
	TEST_CLASS(CTestAssert)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_ATTRIBUTE_TRAIT(TestAssertFail, "Debug")
		TEST_METHOD(TestAssertFail)
		{
			TEST_LOGMSG("�K�����s");
			NG_ASSERT_FAIL();
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertNull, "Debug")
		TEST_METHOD(TestAssertNull)
		{
			int n = 100;
			//int* p = &n;
			int* p = nullptr;

			TEST_LOGMSG("Null�ł���ꍇ�ɐ���");
			NG_ASSERT_NULL(p);
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertNotNull, "Debug")
		TEST_METHOD(TestAssertNotNull)
		{
			int n = 100;
			int* p = &n;

			TEST_LOGMSG("Null�łȂ��ꍇ�ɐ���");
			NG_ASSERT_NOT_NULL(p);
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertEqual, "Debug")
		TEST_METHOD(TestAssertEqual)
		{
			int n = 100;

			TEST_LOGMSG("��r");
			NG_ASSERT_EQUAL(n, 100);
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertCompare, "Debug")
		TEST_METHOD(TestAssertCompare)
		{
			int n = 100;

			TEST_LOGMSG("�召��r");
			NG_ASSERT_COMPARE(0, < , n);
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertRange, "Debug")
		TEST_METHOD(TestAssertRange)
		{
			//int n = 100;
			int n = 101;

			TEST_LOGMSG("�͈�");
			NG_ASSERT_RANGE(0, < , n, <= , 100);
		}

		TEST_ATTRIBUTE_TRAIT(TestAssertAndAbort, "Debug")
		TEST_METHOD(TestAssertAndAbort)
		{
			TEST_LOGMSG("�A�T�[�g + �ُ�I��");
			NG_ASSERT_AND_ABORT(false);
		}
	};

}	// namespace test