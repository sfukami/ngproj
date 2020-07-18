/*!
* @file		testSharedPtr.cpp
* @brief	テストコード SharedPtr
* @date		2020-07-02
* @author	s.fukami
*/

#include <memory>
#include "ngLibCore/memory/pointer/ngSharedPtr.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* @brief					SharedPtr テスト
	*/
	TEST_CLASS(CTestSharedPtr)
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

		TEST_ATTRIBUTE_TRAIT(TestSharedPtr, "Pointer")
		TEST_METHOD(TestSharedPtr)
		{
			//CTestPtr<CDummy> ptr(new CDummy());

			ng::CDefaultAllocator alloc;
			ng::CSharedPtr<CDummy> ptr(NG_NEW(alloc) CDummy(), alloc);
		}
	};

}	// namespace test