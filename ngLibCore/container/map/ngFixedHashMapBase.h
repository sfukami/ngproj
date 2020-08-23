/*!
* @file		ngFixedHashMapBase.h
* @brief	固定長ハッシュマップ ベースクラス
* @date		2018-01-12
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_HASH_MAP_BASE_H__
#define __NG_CORE_FIXED_HASH_MAP_BASE_H__

#include "ngLibCore/common/ngCommon.h"
#include "ngLibCore/allocator/ngMemoryAllocator.h"
#include "ngLibCore/memory/pool/ngMemoryPool.h"
#include "ngHashMap.h"
#include "ngLibCore/math/crc/ngCrc.h"

namespace ng
{
	/*!
	* @brief					固定長ハッシュマップ ベースクラス
	* @tparam KEY				キーの型
	* @tparam T					格納する値の型
	*/
	template <typename KEY, typename T>
	class NG_DECL CFixedHashMapBase : public IHashMap<KEY, T>
	{
	public:
		typedef IHashMap<KEY, T> BaseType;	//!< 基底クラス
		using typename BaseType::KeyType;	//!< キーの型
		using typename BaseType::ValueType;	//!< 値の型
		using typename BaseType::INodeType;	//!< 公開用ノード

	public:
		CFixedHashMapBase();
		virtual ~CFixedHashMapBase();

		/*! 要素追加 */
		virtual bool Add(const KeyType& key, const ValueType& value);

		/*! 要素取得 */
		virtual bool Get(const KeyType& key, ValueType& pDst) const;

		/*! 要素削除 */
		virtual bool Remove(const KeyType& key);

		/*! 要素を全て削除 */
		virtual void Clear();

		/*! 要素が無いか調べる */
		virtual bool Empty() const;

		/*! 空き要素数取得 */
		virtual u32 Remain() const;

		/*! 要素数取得 */
		virtual u32 Size() const;

		/*! 最大要素数取得 */
		virtual u32 MaxSize() const;

		/*! 要素数が最大か調べる */
		virtual bool Full() const;

		/*! 先頭のノードを返す */
		virtual INodeType* Begin();

		/*! 先頭のノードを返す */
		virtual const INodeType* Begin() const;

		/*! 終端のノードを返す */
		virtual INodeType* End();

		/*! 終端のノードを返す */
		virtual const INodeType* End() const;

		/*! 後方のノードを返す */
		virtual INodeType* Next(INodeType* pNode);

		/*! 後方のノードを返す */
		virtual const INodeType* Next(const INodeType* pNode) const;

		/*! 要素を探す */
		virtual INodeType* Find(const KeyType& key);

		/*! 要素を探す */
		virtual const INodeType* Find(const KeyType& key) const;

		/*! 要素取得 */
		ValueType& operator[](const KeyType& key);
		const ValueType& operator[](const KeyType& key) const;

	protected:
		/*! 初期化 */
		NG_ERRCODE _initialize(u32 hashMax, u32 chainMax);

		/*! 終了処理 */
		void _finalize();

		/*! 初期化済みかを調べる */
		bool _isInit() const;

		/*! メモリをプールする */
		NG_ERRCODE _poolMemory(void* pMemory, size_type memSize);
		NG_ERRCODE _poolMemory(IMemoryAllocator& alloc, size_type memSize);

	protected:
		template <typename T> struct Node;
		typedef Node<KeyType> NodeType;		//!< ノード

	private:
		/*! ノードを生成 */
		NodeType* _createNode(void* p);

		/*! テーブルよりノード取得 */
		NodeType* _getNode(const KeyType& key);
		const NodeType* _getNode(const KeyType& key) const;

		/*! テーブルよりノードへの参照を取得 */
		NodeType** _getNodeRef(const KeyType& key);
		NodeType** _getNodeRef(const KeyType& key, NodeType*& pPrevNode);

		/*! メモリ領域を取得 */
		void* _getMemory();
		const void* _getMemory() const;

		/*! ノードを取り出す */
		virtual NodeType* _pullNode() = 0;

		/*! ノードを返却 */
		virtual void _returnNode(NodeType* pNode) = 0;

		/*! 利用可能な残りノード数取得 */
		virtual u32 _getUsableNodeRemain() const = 0;

	private:
		using typename BaseType::INode;
		/*! ノード */
		template <typename T>
		struct NG_DECL Node : public INode<T>
		{
			char key[ NG_SIZEOF(KeyType) ];		//!< キー
			char value[ NG_SIZEOF(ValueType) ];	//!< 要素
			NodeType* pNext;	//!< 次ノード

			/*! コンストラクタ */
			Node() : pNext(nullptr) { }
			/*! 生成 */
			void Create(const KeyType& _key, const ValueType& _value)
			{
				NG_PLACEMENT_NEW(key) KeyType(_key);
				NG_PLACEMENT_NEW(value) ValueType(_value);
			}
			/*! 破棄 */
			void Destroy()
			{
				NG_PLACEMENT_DELETE(key, &GetKey());
				NG_PLACEMENT_DELETE(value, &GetValue());
				pNext = nullptr;
			}
			/*! 要素取得 */
			ValueType& GetValue() { return *PointerCast<ValueType*>(value); }
			const ValueType& GetValue() const { return *PointerCast<const ValueType*>(value); }
			/*! キー取得 */
			KeyType& GetKey() { return *PointerCast<KeyType*>(key); }
			const KeyType& GetKey() const { return *PointerCast<const KeyType*>(key); }
			/*! キーが等しいかチェック */
			bool CheckKey(const KeyType& _key) const { return (GetKey() == _key); }
			/*! mod値取得 */
			u32 GetMod(u32 hashSize) const { return CalcMod(GetKey(), hashSize); }
			/*! mod値算出 */
			static u32 CalcMod(const KeyType& _key, u32 hashSize) { return static_cast<u32>(_key) % hashSize; }

		private:
			/*! 次ノードを取得 */
			INodeType* _getNext() { return pNext; }
			const INodeType* _getNext() const { return pNext; }
		};

		/*! ノード 文字列特殊化版 */
		template <>
		struct NG_DECL Node<const char*> : public INode<const char*>
		{
			u32 hash;					//!< ハッシュ値
			char value[ NG_SIZEOF(ValueType) ];	//!< 要素
			NodeType* pNext;					//!< 次ノード

			/*! コンストラクタ */
			Node() : pNext(nullptr) { }
			/*! 生成 */
			void Create(const char* _key, const ValueType& _value)
			{
				hash = CalcCRC32Hash(_key, ::strlen(_key));
				NG_PLACEMENT_NEW(value) ValueType(_value);
			}
			/*! 破棄 */
			void Destroy()
			{
				NG_PLACEMENT_DELETE(value, &GetValue());
				pNext = nullptr;
			}
			/*! 要素取得 */
			ValueType& GetValue() { return *PointerCast<ValueType*>(value); }
			const ValueType& GetValue() const { return *PointerCast<const ValueType*>(value); }
			/*! キー取得 */
			u32 GetKey() const { return hash; }
			/*! キーが等しいかチェック */
			bool CheckKey(const char* _key) const { return (hash == CalcCRC32Hash(_key, ::strlen(_key))); }
			/*! mod値取得 */
			u32 GetMod(u32 hashSize) const { return hash % hashSize; }
			/*! mod値算出 */
			static u32 CalcMod(const char* _key, u32 hashSize) { return CalcCRC32Hash(_key, ::strlen(_key)) % hashSize; }

		private:
			/*! 次ノードを取得 */
			INodeType* _getNext() { return pNext; }
			const INodeType* _getNext() const { return pNext; }
		};

	protected:
		static const size_type VALUE_SIZE = NG_SIZEOF(ValueType);	//!< 値のサイズ
		static const size_type NODE_SIZE = NG_SIZEOF(NodeType);	//!< ノードのサイズ

	private:
		CMemoryPool m_memPool;	//!< メモリプール
		NodeType* m_pNodes;		//!< 各ノード配列
		NodeType** m_pTable;	//!< 登録ノードテーブル
		u32 m_hashMax;			//!< ハッシュノード最大数
		u32 m_chainMax;			//!< チェインノード最大数
	};

	template <typename KEY, typename T>
	CFixedHashMapBase<KEY, T>::CFixedHashMapBase()
		: m_pNodes(nullptr)
		, m_pTable(nullptr)
		, m_hashMax(0)
		, m_chainMax(0)
	{
	}

	template <typename KEY, typename T>
	CFixedHashMapBase<KEY, T>::~CFixedHashMapBase()
	{
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::Add(const KeyType& key, const ValueType& value)
	{
		NG_ASSERT_AND_ABORT(_isInit());
		
		if(Remain() == 0) {
			return false;
		}

		NodeType** ppNodeRef = _getNodeRef(key);
		// 既に登録済み
		if(*ppNodeRef) {
			return false;
		}

		// 新規登録
		(*ppNodeRef) = _pullNode();
		NG_ASSERT_NOT_NULL(*ppNodeRef);

		(*ppNodeRef)->Create(key, value);

		return true;
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::Get(const KeyType& key, ValueType& pDst) const
	{
		NG_ASSERT_AND_ABORT(_isInit());

		const NodeType* pNode = _getNode(key);
		if(!pNode) {
			return false;
		}

		pDst = pNode->GetValue();

		return true;
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::Remove(const KeyType& key)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		NodeType* pPrevNode = nullptr;
		NodeType** ppNodeRef = _getNodeRef(key, pPrevNode);
		// 登録されていない
		if(!*ppNodeRef) {
			return false;
		}

		NodeType* pNext = (*ppNodeRef)->pNext;

		// ノード削除
		(*ppNodeRef)->Destroy();
		_returnNode(*ppNodeRef);

		// チェインノードのリンクを設定
		if(pPrevNode) {
			pPrevNode->pNext = pNext;
		} else {
			(*ppNodeRef) = pNext;
		}

		return true;
	}

	template <typename KEY, typename T>
	void CFixedHashMapBase<KEY, T>::Clear()
	{
		NodeType *pNode, *pNext;
		pNode = pNext = nullptr;

		// 全ノード破棄
		for(u32 i = 0; i < m_hashMax; i++)
		{
			pNode = m_pTable[i];
			if(pNode) {
				pNext = pNode->pNext;

				pNode->Destroy();
				_returnNode(pNode);

				// チェインノードを破棄
				pNode = pNext;
				while(pNode)
				{
					pNext = pNode->pNext;

					pNode->Destroy();
					_returnNode(pNode);

					pNode = pNext;
				}

				m_pTable[i] = nullptr;
			}
		}
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::Empty() const
	{
		return (Size() == 0);
	}

	template <typename KEY, typename T>
	u32 CFixedHashMapBase<KEY, T>::Remain() const
	{
		return _getUsableNodeRemain();
	}

	template <typename KEY, typename T>
	u32 CFixedHashMapBase<KEY, T>::Size() const
	{
		return (MaxSize() - Remain());
	}

	template <typename KEY, typename T>
	u32 CFixedHashMapBase<KEY, T>::MaxSize() const
	{
		return m_hashMax + m_chainMax;
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::Full() const
	{
		return (Size() == MaxSize());
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Begin()
	{
		NodeType** ppCur = &m_pTable[0];

		// ノードテーブルの先頭を探す
		for(u32 i = 0; i < m_hashMax; i++)
		{
			if(*ppCur) break;
			ppCur++;
		}

		return *ppCur;
	}

	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Begin() const
	{
		return const_cast<CFixedHashMapBase<KEY, T>*>(this)->Begin();
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::End()
	{
		return m_pTable[m_hashMax];

		/*
		// ※末尾の要素を返す。Last() は未実装予定
		NodeType** ppCur = &m_pTable[m_hashMax-1];

		// ノードテーブルの末尾を探す
		for(u32 i = 0; i < m_hashMax; i++)
		{
			if(*ppCur) break;
			ppCur--;
		}

		// チェインノードの末尾を探す
		if(*ppCur) {
			while((*ppCur)->pNext)
			{
				ppCur = &((*ppCur)->pNext);
			}
		}

		return *ppCur;
		*/
	}

	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::End() const
	{
		return const_cast<CFixedHashMapBase<KEY, T>*>(this)->End();
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Next(INodeType* pNode)
	{
		// チェインノードを取得
		INodeType *pNext = this->_getNext(pNode);

		// チェインノードが無い場合はノードテーブルから取得
		if(!pNext) {
			u32 i = pNode->GetMod(m_hashMax) + 1;
			NodeType** ppCur = &m_pTable[i];
			for(; i < m_hashMax; i++)
			{
				if(*ppCur) break;
				ppCur++;
			}
			pNext = (*ppCur);
		}

		return pNext;
	}

	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Next(const INodeType* pNode) const
	{
		return const_cast<CFixedHashMapBase<KEY, T>*>(this)->Next(const_cast<INodeType*>(pNode));
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Find(const KeyType& key)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		return _getNode(key);
	}

	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::INodeType* CFixedHashMapBase<KEY, T>::Find(const KeyType& key) const
	{
		return const_cast<CFixedHashMapBase<KEY, T>*>(this)->Find(key);
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::ValueType& CFixedHashMapBase<KEY, T>::operator[](const KeyType& key)
	{
		NG_ASSERT_AND_ABORT(_isInit());

		NodeType* pNode = _getNode(key);
		NG_ASSERT_NOT_NULL(pNode);

		return pNode->GetValue();
	}
	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::ValueType& CFixedHashMapBase<KEY, T>::operator[](const KeyType& key) const
	{
		return (*const_cast<CFixedHashMapBase<KEY, T>*>(this))[key];
	}
	
	template <typename KEY, typename T>
	NG_ERRCODE CFixedHashMapBase<KEY, T>::_initialize(u32 hashMax, u32 chainMax)
	{
		void* pMemory = m_memPool.GetMemory();
		size_type memSize = m_memPool.GetSize();

		NG_ASSERT_NOT_NULL(pMemory);
		if( ! pMemory)
		{
			return eNG_E_INVALIDMEMORY;
		}

		const u32 nodeMax = hashMax + chainMax;
		const u32 tableSize = (hashMax+1) * NG_PTR_SIZE;	// 末尾が必要なため+1
		const u32 capacity = (u32)((memSize - tableSize) / NODE_SIZE);

		NG_ASSERT(nodeMax <= capacity);
		if(nodeMax > capacity)
		{
			return eNG_E_CAPACITYLACK;
		}

		void* pCur = pMemory;

		// ノード登録テーブル作成
		{
			m_pTable = PointerCast<NodeType**>(pCur);
			NG_ZERO_MEMORY(m_pTable, tableSize);
			pCur = PointerOffset<void*>(pCur, tableSize);
		}
		// ノード作成
		{
			NodeType* pNode = PointerCast<NodeType*>(pCur);
			m_pNodes = pNode;

			for(u32 i = 0; i < nodeMax; i++)
			{
				pNode = _createNode(pNode);
				pNode++;
			}
		}
		// 利用に備えてノードを返却
		{
			for(u32 i = 0; i < hashMax + chainMax; i++)
			{
				_returnNode(&m_pNodes[i]);
			}
		}

		m_hashMax = hashMax;
		m_chainMax = chainMax;

		return eNG_S_OK;
	}

	template <typename KEY, typename T>
	void CFixedHashMapBase<KEY, T>::_finalize()
	{
		Clear();

		m_hashMax = 0;
		m_chainMax = 0;
		
		m_memPool.Unpool();
	}

	template <typename KEY, typename T>
	bool CFixedHashMapBase<KEY, T>::_isInit() const
	{
		return (_getMemory() != nullptr);
	}

	template <typename KEY, typename T>
	NG_ERRCODE CFixedHashMapBase<KEY, T>::_poolMemory(void* pMemory, size_type memSize)
	{
		return m_memPool.Pool(pMemory, memSize);
	}
	template <typename KEY, typename T>
	NG_ERRCODE CFixedHashMapBase<KEY, T>::_poolMemory(IMemoryAllocator& alloc, size_type memSize)
	{
		return m_memPool.Pool(alloc, memSize);
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::NodeType* CFixedHashMapBase<KEY, T>::_createNode(void* p)
	{
		return NG_PLACEMENT_NEW(p) NodeType();
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::NodeType* CFixedHashMapBase<KEY, T>::_getNode(const KeyType& key)
	{
		NodeType** ppNode = _getNodeRef(key);

		return (ppNode) ? *ppNode : nullptr;
	}

	template <typename KEY, typename T>
	typename const CFixedHashMapBase<KEY, T>::NodeType* CFixedHashMapBase<KEY, T>::_getNode(const KeyType& key) const
	{
		return const_cast<CFixedHashMapBase<KEY, T>*>(this)->_getNode(key);
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::NodeType** CFixedHashMapBase<KEY, T>::_getNodeRef(const KeyType& key)
	{
		u32 index = NodeType::CalcMod(key, m_hashMax);

		NodeType** ppNode = &(m_pTable[ index ]);

		// キーが一致するノードを検索
		// 存在しない場合は格納先となるノードの参照を返す
		if(*ppNode) {
			while(!(*ppNode)->CheckKey(key))
			{
				ppNode = &(*ppNode)->pNext;
				if(!*ppNode) break;
			}
		}

		return ppNode;
	}

	template <typename KEY, typename T>
	typename CFixedHashMapBase<KEY, T>::NodeType** CFixedHashMapBase<KEY, T>::_getNodeRef(const KeyType& key, NodeType*& pPrevNode)
	{
		u32 index = NodeType::CalcMod(key, m_hashMax);

		NodeType** ppNode = &(m_pTable[ index ]);

		// キーが一致するノードを検索
		// 存在しない場合は格納先となるノードの参照を返す
		if(*ppNode) {
			while(!(*ppNode)->CheckKey(key))
			{
				pPrevNode = (*ppNode);
				ppNode = &(*ppNode)->pNext;
				if(!*ppNode) break;
			}
		}

		return ppNode;
	}

	template <typename KEY, typename T>
	void* CFixedHashMapBase<KEY, T>::_getMemory()
	{
		return m_memPool.GetMemory();
	}
	template <typename KEY, typename T>
	const void* CFixedHashMapBase<KEY, T>::_getMemory() const
	{
		return m_memPool.GetMemory();
	}

}	// namespace ng

#endif	// __NG_CORE_FIXED_HASH_MAP_BASE_H__