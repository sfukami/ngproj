/*!
* @file		testVector.cpp
* @brief	テストコード ベクトル
* @date		2020-06-21
* @author	s.fukami
*/

#include "ngLibCore/geometry/ngGeometry.h"

namespace test
{
	/*!
	* ベクトル テスト
	*/
	TEST_CLASS(CTestVector)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestVector2)
		{
			ng::Vector2 v1{0.f, 0.f};
			ng::Vector2 v2{0.f, 0.f};
			//ng::Vector2 v {.x = 0.f, .y = 0.f};	// need C++20

			ng::VectorOp::Init(v1, 1.f, 2.f);
			ng::VectorOp::Init(v2, 2.f, 3.f);
		}
	};

}	// namespace ng