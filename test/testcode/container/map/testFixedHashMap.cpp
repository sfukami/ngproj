/*!
* @file		testFixedHashMap.cpp
* @brief	テストコード 固定長ハッシュマップ
* @date		2017-08-09
* @author	s.fukami
*/

#include "ngLibCore/container/map/ngFixedHashMap.h"
#include "ngLibCore/allocator/ngDefaultAllocator.h"

namespace test
{
	/*!
	* 固定長ハッシュマップ テスト
	*/
	TEST_CLASS(CTestFixedHashMap)
	{
	public:
		TEST_DEFINE_INITIALIZE;

		typedef CDummy TType;

		TEST_METHOD(TestFixedHashMap1)
		{
			typedef ng::CFixedHashMap<int, TType, 8> HashMapType;

			HashMapType hashmap;

			_common(hashmap);
		}

		TEST_METHOD(TestFixedHashMap2)
		{
			typedef ng::CFixedHashMap<int, TType> HashMapType;

			ng::CDefaultAllocator alloc;
			HashMapType hashmap;

			hashmap.Initialize(alloc, 8);

			_common(hashmap);
		}

		template <class HashMap>
		void _common(HashMap& hashmap)
		{
			TType t1(1), t2(9), t3(3);

			_add(hashmap, t1);
			_add(hashmap, t2);
			_add(hashmap, t3);

			ng::Printf("size:%d maxSize:%d\n", hashmap.Size(), hashmap.MaxSize());

			// Get()
			{
				TType t;
				_get(hashmap, t1.GetValue(), t);
				_get(hashmap, t2.GetValue(), t);
				_get(hashmap, t3.GetValue(), t);
				//_get(hashmap, 100, t);
			}

			// Remove()
			{
				//_remove(hashmap, t2.GetValue());
				//_remove(hashmap, t3.GetValue());
			}

			// traverse
			{
				ng::Printf("display all.\n");
				ng::Printf("size:%d maxSize:%d\n", hashmap.Size(), hashmap.MaxSize());

				typename HashMap::INodeType* pNode = hashmap.Begin();
				for(; pNode != hashmap.End(); pNode = hashmap.Next(pNode))
				{
					pNode->GetValue().Display();
				}
			}

			// Clear()
			ng::Printf("clear.\n");
			hashmap.Clear();

			ng::Printf("size:%d maxSize:%d\n", hashmap.Size(), hashmap.MaxSize());
		}

		template <class HashMap>
		void _add(HashMap& map, CDummy& dummy)
		{
			if(map.Add(dummy.GetValue(), dummy)) {
				ng::Printf("Add() Success. key:%d\n", dummy.GetValue());
			} else {
				ng::Printf("Add() Fail. key:%d\n", dummy.GetValue());
			}
		}

		template <class HashMap>
		void _get(HashMap& map, int key, CDummy& dummy)
		{
			if(map.Get(key, dummy)) {
				ng::Printf("Get() Success. key:%d value:%d\n", key, dummy.GetValue());
			} else {
				ng::Printf("Get() Fail. key:%d value:%d\n", key, dummy.GetValue());
			}
		}

		template <class HashMap>
		void _remove(HashMap& map, int key)
		{
			if(map.Remove(key)) {
				ng::Printf("Remove() Success. key:%d\n", key);
			} else {
				ng::Printf("Remove() Fail. key:%d\n", key);
			}
		}
	};

}	// namespace test