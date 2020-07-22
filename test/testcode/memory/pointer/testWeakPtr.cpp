/*!
* @file		testWeakPtr.cpp
* @brief	テストコード WeakPtr
* @date		2020-07-21
* @author	s.fukami
*/

#include <memory>
#include "ngLibCore/memory/pointer/ngWeakPtr.h"
#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* @brief					WeakPtr テスト
	*/
	TEST_CLASS(CTestWeakPtr)
	{
	private:
		// 検証用
		template <class T>
		struct deleter_for_storage {
			void operator()(T* ptr_) {
				ng::Printf("deleter_for_storage::operator()(T*)\n");
			}
		};
		template <class T>
		class CTestPtr : public std::shared_ptr<T>
		{
		public:
			typedef std::shared_ptr<T> BaseType;
			explicit CTestPtr(T* p) noexcept : BaseType(p, deleter_for_storage<T>())
			{
				ng::Printf("CTestPtr::ctor(T*)\n");
			}
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_ATTRIBUTE_TRAIT(TestWeakPtr, "Pointer")
		TEST_METHOD(TestWeakPtr)
		{
			ng::CDefaultAllocator alloc;
			ng::CSharedPtr<CDummy> sp(NG_NEW(alloc) CDummy(1), alloc);

			{
				ng::CWeakPtr<CDummy> wp1;
				ng::CWeakPtr<CDummy> wp2(sp);
				ng::CWeakPtr<CDummy> wp3(wp2);
				ng::CWeakPtr<CDummy> wp4(std::move(wp2));

				ng::Printf("wp1 count:%d, null:%d\n", wp1.use_count(), wp1 == nullptr);
				ng::Printf("wp2 count:%d value:%d\n", wp2.use_count(), wp2->GetValue());
				ng::Printf("wp3 count:%d value:%d\n", wp3.use_count(), wp3->GetValue());
				ng::Printf("wp4 count:%d value:%d\n", wp4.use_count(), wp4->GetValue());
			}

			ng::Printf("end.\n");
		}
	};

}	// namespace test