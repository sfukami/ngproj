/*!
* @file		testCommon.h
* @brief	test共通ダミークラス
* @date		2017-08-09
* @author	s.fukami
*/

#ifndef __TEST_DUMMY_H__
#define __TEST_DUMMY_H__

namespace test
{
	/*!
	* @brief					テスト用ダミークラス
	*/
	class CDummy
	{
	public:
		/*! コンストラクタ */
		CDummy() : m_value(0) { ng::Printf("[CDummy::CDummy()]\n"); }
		explicit CDummy(int value) : m_value(value) { ng::Printf("[CDummy::CDummy(int)] value:%d\n", value); }
		explicit CDummy(const CDummy& src) : m_value(src.m_value) { ng::Printf("[CDummy::CDummy(const CDummy&)]\n"); }
		/*! デストラクタ */
		~CDummy() { ng::Printf("[CDummy::~CDummy()] value:%d\n", m_value); }

		/*! 値表示 */
		void Display() const { ng::Printf("[CDummy::display] value:%d\n", m_value); }

		/*! 値設定 */
		void SetValue(int value) { m_value = value; }

		/*! 値取得 */
		int GetValue() const { return m_value; }

		/*! 代入演算子のオーバーロード */
		void operator=(const CDummy& rhs)
		{
			ng::Printf("[CDummy::operator=]\n");
			m_value = rhs.m_value;
		}

		/*! 比較演算子のオーバーロード */
		bool operator==(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator==] %d == %d [%d]\n", m_value, rhs.m_value, (m_value == rhs.m_value));
			return (m_value == rhs.m_value);
		}
		bool operator!=(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator!=]\n");
			return (m_value != rhs.m_value);
		}
		bool operator<(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator<]\n");
			return (m_value < rhs.m_value);
		}
		bool operator>(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator>]\n");
			return (m_value > rhs.m_value);
		}
		bool operator<=(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator<=] %d <= %d [%d]\n", m_value, rhs.m_value, (m_value <= rhs.m_value));
			return (m_value <= rhs.m_value);
		}
		bool operator>=(const CDummy& rhs) const
		{
			ng::Printf("[CDummy::operator>=]\n");
			return (m_value >= rhs.m_value);
		}

	private:
		int m_value;	//!< 値
	};

}	// namespace test

#endif// __TEST_DUMMY_H__
