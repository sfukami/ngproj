/*!
* @file		testConsole.cpp
* @brief	テストコード コンソール
* @date		2018-10-15
* @author	s.fukami
*/

#include "ngLibCore/io/console/ngConsoleMacro.h"

namespace test
{
	/*!
	* コンソール テスト
	*/
	TEST_CLASS(CTestConsole)
	{
	public:
		TEST_ATTRIBUTE_IGNORE(TestConsole)
		TEST_METHOD(TestConsole)
		{
			NG_CONSOLE_BOOT(true);

			ng::Printf("Hello Work!\n");

			NG_CONSOLE_PAUSE();

			NG_CONSOLE_SHUTDOWN();
		}
	};

}	// namespace test