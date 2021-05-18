/*!
* @file		testSort.cpp
* @brief	テストコード ソート
* @date		2021-05-12
* @author	s.fukami
*/

#include <algorithm>
#include <vector>

namespace test
{
	/*!
	* @brief					ソート テスト
	*/
	TEST_CLASS(CTestSort)
	{
	private:
	public:
		TEST_DEFINE_INITIALIZE;

		TEST_METHOD(TestSortInteger)
		{
			int array[] = {5,4,3,0,1,2};

			std::sort(array, array + NG_ARRAY_SIZE(array));

			for(int i = 0; i < NG_ARRAY_SIZE(array); i++)
			{
				ng::Printf("%d:%d\n", i, array[i]);
			}
		}

		TEST_METHOD(TestSortStruct)
		{
			struct Elem
			{
			public:
				Elem(int _key, int _value) : key(_key), value(_value) { }
				int key;
				int value;
			};

			Elem elems[] = {
				Elem(1, 300),
				Elem(2, 200),
				Elem(3, 100),
			};

			class CCompare
			{
			public:
				bool operator()(const Elem& lhs, const Elem& rhs)
				{
					return lhs.key > rhs.key;
				}
			};

			std::sort(elems, elems + NG_ARRAY_SIZE(elems), CCompare());

			for(int i = 0; i < NG_ARRAY_SIZE(elems); i++)
			{
				ng::Printf("%d:%d\n", i, elems[i].value);
			}
		}
	};

}	// namespace test