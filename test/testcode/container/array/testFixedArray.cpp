/*!
* @file		testFixedArray.cpp
* @brief	テストコード 固定長配列
* @date		2019-02-09
* @author	s.fukami
*/

#include "ngLibCore/container/array/ngFixedArray.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* @brief					固定長配列 テスト
	*/
	TEST_CLASS(CTestFixedArray)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		// 宣言時サイズ指定
		TEST_METHOD(TestFixedArray1)
		{
			typedef ng::CFixedArray<CDummy, 8> ArrayType;
			ArrayType array;

			_common(array);
		}

		// 初期化時サイズ指定
		TEST_METHOD(TestFixedArray2)
		{
			ng::CDefaultAllocator alloc;

			typedef ng::CFixedArray<CDummy> ArrayType;
			ArrayType array;
			
			NG_ERRCODE err = ng::eNG_E_FAIL;
			if(NG_FAILED(err = array.Initialize(8, alloc))) {
				NG_ERRLOG_C("FixedArray", err, "固定長配列の初期化に失敗");
			}

			_common(array);
		}

	private:
		void _common(ng::IArray<CDummy>& array)
		{
			ng::Printf("size:%d\n", array.Size());

			// []
			{
				ng::Printf("display all.\n");
				for(int i = 0; i < (int)array.Size(); i++)
				{
					array[i].SetValue(i);
					array[i].Display();
				}
			}
			// Front()
			{
				CDummy& d = array.Front();
				ng::Printf("front. value:%d\n", d.GetValue());
			}
			// Back()
			{
				CDummy& d = array.Back();
				ng::Printf("back. value:%d\n", d.GetValue());
			}
		}
	};

}	// namespace test