/*!
* @file		testUniquePtr.cpp
* @brief	テストコード UniquePtr
* @date		2020-07-02
* @author	s.fukami
*/

#include <memory>
#include "ngLibCore/memory/pointer/ngUniquePtr.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* @brief					UniquePtr テスト
	*/
	TEST_CLASS(CTestUniquePtr)
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
		class CTestPtr : public std::unique_ptr<T, deleter_for_storage<T> >
		{
		public:
			typedef std::unique_ptr<T, deleter_for_storage<T> > BaseType;
			explicit CTestPtr(T* p) noexcept : BaseType(p)
			{
				ng::Printf("CTestPtr::ctor(T*)\n");
			}
		};

	public:
		TEST_DEFINE_INITIALIZE;

		TEST_ATTRIBUTE_TRAIT(TestUniquePtr, "Pointer")
		TEST_METHOD(TestUniquePtr)
		{
			//CTestPtr<CDummy> ptr(new CDummy());

			ng::CDefaultAllocator alloc;
			ng::CUniquePtr<CDummy> ptr(NG_NEW(alloc) CDummy(), alloc);
		}
	};

}	// namespace test