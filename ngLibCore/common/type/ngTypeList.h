/*!
* @file		ngTypeList.h
* @brief	型リスト
* @date		2015-12-08
* @author	s.fukami
*/

#ifndef __NG_CORE_TYPE_LIST_H__
#define __NG_CORE_TYPE_LIST_H__

/*! 型リスト生成マクロ */
#define TL0() \
	ng::Types<>
#define TL1(_t1) \
	ng::Types<_t1>
#define TL2(_t1, _t2) \
	ng::Types<_t1, _t2>
#define TL3(_t1, _t2, _t3) \
	ng::Types<_t1, _t2, _t3>
#define TL4(_t1, _t2, _t3, _t4) \
	ng::Types<_t1, _t2, _t3, _t4>
#define TL5(_t1, _t2, _t3, _t4, _t5) \
	ng::Types<_t1, _t2, _t3, _t4, _t5>
#define TL6(_t1, _t2, _t3, _t4, _t5, _t6) \
	ng::Types<_t1, _t2, _t3, _t4, _t5, _t6>
#define TL7(_t1, _t2, _t3, _t4, _t5, _t6, _t7) \
	ng::Types<_t1, _t2, _t3, _t4, _t5, _t6, _t7>
#define TL8(_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8) \
	ng::Types<_t1, _t2, _t3, _t4, _t5, _t6, _t7, _t8>

namespace ng
{

/*! 無効な型 */
struct VoidType { private: VoidType(); };

/*! 有効な型の数を示す */
struct TypeNum0 { private: TypeNum0(); };
struct TypeNum1 { private: TypeNum1(); };
struct TypeNum2 { private: TypeNum2(); };
struct TypeNum3 { private: TypeNum3(); };
struct TypeNum4 { private: TypeNum4(); };
struct TypeNum5 { private: TypeNum5(); };
struct TypeNum6 { private: TypeNum6(); };
struct TypeNum7 { private: TypeNum7(); };
struct TypeNum8 { private: TypeNum8(); };

/*!
* 型リスト
* 複数の型を指定
*/
/*! 型リスト 有効数8 */
template
<
	typename TType1 = VoidType,
	typename TType2 = VoidType,
	typename TType3 = VoidType,
	typename TType4 = VoidType,
	typename TType5 = VoidType,
	typename TType6 = VoidType,
	typename TType7 = VoidType,
	typename TType8 = VoidType
>
struct Types
{
	typedef TypeNum8 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef TType4 T4;
	typedef TType5 T5;
	typedef TType6 T6;
	typedef TType7 T7;
	typedef TType8 T8;
};

/*! 型リスト 有効数7 */
template
<
	typename TType1,
	typename TType2,
	typename TType3,
	typename TType4,
	typename TType5,
	typename TType6,
	typename TType7
>
struct Types<TType1, TType2, TType3, TType4, TType5, TType6, TType7, VoidType>
{
	typedef TypeNum7 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef TType4 T4;
	typedef TType5 T5;
	typedef TType6 T6;
	typedef TType7 T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数6 */
template
<
	typename TType1,
	typename TType2,
	typename TType3,
	typename TType4,
	typename TType5,
	typename TType6
>
struct Types<TType1, TType2, TType3, TType4, TType5, TType6, VoidType, VoidType>
{
	typedef TypeNum6 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef TType4 T4;
	typedef TType5 T5;
	typedef TType6 T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数5 */
template
<
	typename TType1,
	typename TType2,
	typename TType3,
	typename TType4,
	typename TType5
>
struct Types<TType1, TType2, TType3, TType4, TType5, VoidType, VoidType, VoidType>
{
	typedef TypeNum5 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef TType4 T4;
	typedef TType5 T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数4 */
template
<
	typename TType1,
	typename TType2,
	typename TType3,
	typename TType4
>
struct Types<TType1, TType2, TType3, TType4, VoidType, VoidType, VoidType, VoidType>
{
	typedef TypeNum4 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef TType4 T4;
	typedef VoidType T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数3 */
template
<
	typename TType1,
	typename TType2,
	typename TType3
>
struct Types<TType1, TType2, TType3, VoidType, VoidType, VoidType, VoidType, VoidType>
{
	typedef TypeNum3 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef TType3 T3;
	typedef VoidType T4;
	typedef VoidType T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数2 */
template
<
	typename TType1,
	typename TType2
>
struct Types<TType1, TType2, VoidType, VoidType, VoidType, VoidType, VoidType, VoidType>
{
	typedef TypeNum2 TypeNum;
	typedef TType1 T1;
	typedef TType2 T2;
	typedef VoidType T3;
	typedef VoidType T4;
	typedef VoidType T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数1 */
template
<
	typename TType1
>
struct Types<TType1, VoidType, VoidType, VoidType, VoidType, VoidType, VoidType, VoidType>
{
	typedef TypeNum1 TypeNum;
	typedef TType1 T1;
	typedef VoidType T2;
	typedef VoidType T3;
	typedef VoidType T4;
	typedef VoidType T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

/*! 型リスト 有効数0 */
template <>
struct Types<VoidType, VoidType, VoidType, VoidType, VoidType, VoidType, VoidType, VoidType>
{
	typedef TypeNum0 TypeNum;
	typedef VoidType T1;
	typedef VoidType T2;
	typedef VoidType T3;
	typedef VoidType T4;
	typedef VoidType T5;
	typedef VoidType T6;
	typedef VoidType T7;
	typedef VoidType T8;
};

}	// namespace ng

#endif	// __NG_CORE_TYPE_LIST_H__
