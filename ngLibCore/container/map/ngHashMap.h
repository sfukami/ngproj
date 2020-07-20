/*!
* @file		ngHashMap.h
* @brief	ハッシュコンテナ インターフェース
* @date		2018-01-12
* @author	s.fukami
*/

#ifndef __NG_CORE_HASH_MAP_H__
#define __NG_CORE_HASH_MAP_H__

namespace ng
{
	/*!
	* @brief					ハッシュコンテナ インターフェース
	* @tparam KEY				キーの型
	* @tparam T					格納する値の型
	*/
	template <typename KEY, typename T>
	class NG_DECL IHashMap
	{
	public:
		typedef KEY KeyType;	//!< キーの型
		typedef T ValueType;	//!< 値の型
		template <typename T> struct INode;
		typedef INode<KeyType> INodeType;	//!< 公開用ノード

	public:
		IHashMap() { }
		virtual ~IHashMap() { }

		/*! 要素追加 */
		virtual bool Add(const KeyType& key, const ValueType& value) = 0;

		/*! 要素取得 */
		virtual bool Get(const KeyType& key, ValueType& pDst) = 0;

		/*! 要素削除 */
		virtual bool Remove(const KeyType& key) = 0;

		/*! 要素を全て削除 */
		virtual void Clear() = 0;

		/*! 要素が無いか調べる */
		virtual bool Empty() const = 0;

		/*! 空き要素数取得 */
		virtual u32 Remain() const = 0;

		/*! 要素数取得 */
		virtual u32 Size() const = 0;

		/*! 最大要素数取得 */
		virtual u32 MaxSize() const = 0;

		/*! 要素数が最大か調べる */
		virtual bool Full() const = 0;

		/*! 先頭のノードを返す */
		virtual INodeType* Begin() = 0;

		/*! 先頭のノードを返す */
		virtual const INodeType* Begin() const = 0;

		/*! 終端のノードを返す */
		virtual INodeType* End() = 0;

		/*! 終端のノードを返す */
		virtual const INodeType* End() const = 0;

		/*! 後方のノードを返す */
		virtual INodeType* Next(INodeType* pNode) = 0;

		/*! 後方のノードを返す */
		virtual const INodeType* Next(const INodeType* pNode) const = 0;

	protected:
		/*! ノード インターフェース */
		template <typename T>
		struct NG_DECL INode
		{
			template <typename KEY, typename T>
			friend class IHashMap;

			/*! 要素取得 */
			virtual ValueType& GetValue() = 0;
			virtual const ValueType& GetValue() const = 0;
			/*! キー取得 */
			virtual const KeyType& GetKey() const = 0;
			/*! mod値取得 */
			virtual u32 GetMod(u32 hashMax) const = 0;

		private:
			/*! 次ノードを取得 */
			virtual INodeType* _getNext() = 0;
			virtual const INodeType* _getNext() const = 0;
		};
		
		/*! ノード インターフェース 文字列特殊化版 */
		template <>
		struct NG_DECL INode<const char*>
		{
			template <typename KEY, typename T>
			friend class IHashMap;

			/*! 要素取得 */
			virtual ValueType& GetValue() = 0;
			virtual const ValueType& GetValue() const = 0;
			/*! キー取得 */
			virtual u32 GetKey() const = 0;
			/*! mod値取得 */
			virtual u32 GetMod(u32 hashMax) const = 0;

		private:
			/*! 次ノードを取得 */
			virtual INodeType* _getNext() = 0;
			virtual const INodeType* _getNext() const = 0;
		};

	protected:
		/*! 次ノードを取得 */
		virtual INodeType* _getNext(INodeType* pNode)
		{
			return pNode->_getNext();
		}
		virtual const INodeType* _getNext(const INodeType* pNode) const
		{
			return pNode->_getNext();
		}
	};

}	// namespace ng

#endif	// __NG_CORE_HASH_MAP_H__