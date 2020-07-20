/*!
* @file		ngFixedHashMap.h
* @brief	固定長ハッシュマップ
* @date		2018-01-12
* @author	s.fukami
*/

#ifndef __NG_CORE_FIXED_HASH_MAP_H__
#define __NG_CORE_FIXED_HASH_MAP_H__

#include "ngFixedHashMapBase.h"
#include "ngLibCore/container/stack/ngFixedStack.h"

namespace ng
{
	//! デフォルトのチェインリストのノード数を算出
	#define _CHAIN_SIZE_DEFAULT(_hashSize)	(_hashSize>>1)

	/*!
	* @brief					固定長ハッシュマップ
	* @tparam KEY				キーの型
	* @tparam T					格納する値の型
	* @tparam SIZE				最大要素数
	* @tparam CHAIN_SIZE		オープンハッシュで用いるリストサイズ
	*/
	template <typename KEY, typename T, u32 SIZE = NG_UNSPECIFIED_SIZE, u32 CHAIN_SIZE = _CHAIN_SIZE_DEFAULT(SIZE)>
	class NG_DECL CFixedHashMap : public CFixedHashMapBase<KEY, T>
	{
	public:
		typedef CFixedHashMapBase<KEY, T> BaseType;	//!< 基底クラス
		using BaseType::NodeType;		//!< 公開用ノード

	public:
		CFixedHashMap();
		~CFixedHashMap();

	private:
		/*! ノードを取り出す */
		NodeType* _pullNode();

		/*! ノードを返却 */
		void _returnNode(NodeType* pNode);

		/*! 利用可能な残りノード数取得 */
		u32 _getUsableNodeRemain() const;

	private:
		typedef CFixedHashMapBase<KEY, T> BaseType;	//!< 基底クラス

	private:
		static const u32 NODE_MAX = SIZE + CHAIN_SIZE;	//!< ノード最大数
		static const u32 BUFFER_SIZE = NG_PTR_SIZE * (SIZE+1) + BaseType::NODE_SIZE * NODE_MAX;	//!< バッファサイズ

	private:
		char m_buffer[BUFFER_SIZE];	//!< バッファ
		CFixedStack<NodeType*, NODE_MAX> m_nodeStack;	//!< ノードスタック
	};

	template <typename KEY, typename T, u32 SIZE, u32 CHAIN_SIZE>
	CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::CFixedHashMap()
	{
		size_type bufSize = NG_SIZEOF(m_buffer);

		NG_ERRCODE err = this->_poolMemory(m_buffer, bufSize);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));

		err = this->_initialize(SIZE, CHAIN_SIZE);
		NG_ASSERT_AND_ABORT(NG_SUCCEEDED(err));
	}

	template <typename KEY, typename T, u32 SIZE, u32 CHAIN_SIZE>
	CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::~CFixedHashMap()
	{
		this->_finalize();
	}

	template <typename KEY, typename T, u32 SIZE, u32 CHAIN_SIZE>
	typename CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::NodeType* CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::_pullNode()
	{
		if(m_nodeStack.Empty()) return nullptr;

		NodeType* pNode = m_nodeStack.Top();
		m_nodeStack.Pop();

		return pNode;
	}

	template <typename KEY, typename T, u32 SIZE, u32 CHAIN_SIZE>
	void CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::_returnNode(NodeType* pNode)
	{
		m_nodeStack.Push(pNode);
	}

	template <typename KEY, typename T, u32 SIZE, u32 CHAIN_SIZE>
	u32 CFixedHashMap<KEY, T, SIZE, CHAIN_SIZE>::_getUsableNodeRemain() const
	{
		return m_nodeStack.Size();
	}

	#define _NG_UNSPECIFIED		NG_UNSPECIFIED_SIZE, _CHAIN_SIZE_DEFAULT(NG_UNSPECIFIED_SIZE)

	/*!
	* @brief					固定長ハッシュマップ
	* @tparam KEY				キーの型
	* @tparam T					格納する値の型
	* @note						初期化時にバッファを指定する固定長のコンテナ
	*/
	template <typename KEY, typename T>
	class NG_DECL CFixedHashMap<KEY, T, _NG_UNSPECIFIED> : public CFixedHashMapBase<KEY, T>
	{
	public:
		typedef CFixedHashMapBase<KEY, T> BaseType;	//!< 基底クラス
		using BaseType::NodeType;

	public:
		CFixedHashMap();
		~CFixedHashMap();

		/*
		* @brief					初期化
		* @param alloc				使用するメモリアロケータ
		* @param hashMax			ハッシュマップ最大要素数
		* @param chainMax			チェインリスト最大要素数。省略した場合はデフォルト値
		* @return					NG エラーコード
		*/
		NG_ERRCODE Initialize(IMemoryAllocator& alloc, u32 hashMax, u32 chainMax);
		NG_ERRCODE Initialize(IMemoryAllocator& alloc, u32 hashMax);

		/*!
		* @brief					終了処理
		*/
		void Finalize();

	private:
		/*! ノードを取り出す */
		NodeType* _pullNode();

		/*! ノードを返却 */
		void _returnNode(NodeType* pNode);

		/*! 利用可能な残りノード数取得 */
		u32 _getUsableNodeRemain() const;

	private:
		CFixedStack<NodeType*> m_nodeStack;	//!< ノードスタック
	};

	template <typename KEY, typename T>
	CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::CFixedHashMap()
	{
	}

	template <typename KEY, typename T>
	CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::~CFixedHashMap()
	{
		Finalize();
	}

	template <typename KEY, typename T>
	NG_ERRCODE CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::Initialize(IMemoryAllocator& alloc, u32 hashMax, u32 chainMax)
	{
		if(this->_isInit()) {
			return eNG_E_LEAK;
		}

		const u32 nodeMax = hashMax + chainMax;
		size_type reqMemSize = NG_PTR_SIZE * (hashMax+1) + BaseType::NODE_SIZE * nodeMax;

		if(alloc.GetMemSize() < reqMemSize)
		{
			return eNG_E_CAPACITYLACK;
		}

		// メモリ領域をプール
		{
			NG_ERRCODE err = this->_poolMemory(alloc, reqMemSize);
			if(NG_FAILED(err)) {
				return err;
			}
		}
		// ノードスタック初期化
		{
			NG_ERRCODE err = m_nodeStack.Initialize(nodeMax, alloc);
			if(NG_FAILED(err)) {
				return err;
			}
		}

		return this->_initialize(hashMax, chainMax);
	}

	template <typename KEY, typename T>
	NG_ERRCODE CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::Initialize(IMemoryAllocator& alloc, u32 hashMax)
	{
		return Initialize(alloc, hashMax, _CHAIN_SIZE_DEFAULT(hashMax));
	}

	template <typename KEY, typename T>
	void CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::Finalize()
	{
		this->_finalize();
		
		m_nodeStack.Finalize();
	}

	template <typename KEY, typename T>
	typename CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::NodeType* CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::_pullNode()
	{
		if(m_nodeStack.Empty()) return nullptr;

		NodeType* pNode = m_nodeStack.Top();
		m_nodeStack.Pop();

		return pNode;
	}

	template <typename KEY, typename T>
	void CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::_returnNode(NodeType* pNode)
	{
		m_nodeStack.Push(pNode);
	}

	template <typename KEY, typename T>
	u32 CFixedHashMap<KEY, T, _NG_UNSPECIFIED>::_getUsableNodeRemain() const
	{
		return m_nodeStack.Size();
	}

	#undef _NG_UNSPECIFIED

}	// namespace ng

#endif	// __NG_CORE_FIXED_HASH_MAP_H__