#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Integer
{
private:
	string num;					// 该数字的数值形式
	char sign = '+';			// 该数字的符号 '+' '-'

	/**
	 * 比较该数的绝对值是否小于参数的绝对值
	 */
	bool less(const Integer& n)const noexcept
	{
		if (num.size() < n.num.size()) return true;
		else if (num.size() > n.num.size()) return false;
		else return num < n.num;
	}

	/**
	 * 此构造函数接收一个表示数字的字符串，一个该数字的符号
	 * 该字符串表示的数字，低位在前，高位在后
	 * 字符串必须由纯数字组成
	 * 符号由第二个参数提供
	 */
	Integer(const string& s1, char ch) :num(s1), sign(ch) {}

	/**
	 * 大数加法实现
	 * 两数必须都为正数
	 * 只做数值运算，不做符号运算
	 */
	Integer add(const Integer& n)const
	{
		Integer tInt(*this);
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int sum = 0;
		int carry = 0;

		while (i < len1 && j < len2 || carry)
		{
			sum = (i < len1 ? tInt.num.at(i) : 0) + (j < len2 ? n.num.at(j) : 0) + carry;
			carry = sum / 10;
			if (i < len1) tInt.num.at(i) = sum % 10;
			else tInt.num += sum % 10;

			++i;
			++j;
		}

		return tInt;
	}

	/**
	 * 大数减法实现
	 * 被减数的绝对值必须大于减数的绝对值
	 * 只做数值运算，不做符号运算
	 */
	Integer sub(const Integer& n)const
	{
		Integer tInt(*this);
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int diff = 0;					// 某位的差
		int borrow = 0;					// 借位

		while (i < len1 && j < len2 || borrow)
		{
			diff = (i < len1 ? tInt.num.at(i) : 0) - (j < len2 ? n.num.at(j) : 0) - borrow;
			borrow = diff < 0 ? 1 : 0;
			if (i < len1) tInt.num.at(i) = borrow ? 10 + diff : diff;
			else tInt.num += borrow ? 10 + diff : diff;

			++i;
			++j;
		}

		return tInt;
	}

	/**
	 * 大数乘法实现
	 * 两数的正负可是任意的
	 */
	Integer mult(const Integer& n)const
	{
		const auto& one = num;
		const auto& two = n.num;
		const auto len1 = one.size();
		const auto len2 = two.size();
		vector<int> vec(len1 + len2, 0);

		for (size_t i = 0; i < len1; ++i)
		{
			for (size_t j = 0; j < len2; ++j)
			{
				// 暂时不考虑进位
				vec.at(i + j) += one.at(i) * two.at(j);
			}
		}

		// 单独处理所有进位
		string str(vec.size(), '\000');
		int carry = 0;
		int sum = 0;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			sum = vec.at(i) + carry;
			vec.at(i) = sum >= 10 ? sum % 10 : sum;
			carry = sum / 10;

			// 结果写入字符串
			str.at(i) = vec.at(i);
		}

		// 若最高位为 0 ，去除
		if (str.back() == '\000') str.pop_back();
		// 计算符号
		const char ch = sign == n.sign ? '+' : '-';

		// 调用私有的双参数构造函数 
		return Integer(std::move(str), ch);
	}

	/**
	 * 大数的除法实现
	 * 两数的正负可是任意的
	 */
	Integer div(const Integer& n)const
	{

	}

public:
	// 默认/单参数构造函数
	Integer(int x = 0)
	{
		sign = x < 0 ? '-' : '+';
		if (!x)
		{
			num += '\000';
			return;
		}

		while (x)
		{
			num += x % 10;
			x /= 10;
		}
	}

	/**
	 * 此构造函数接收一个表示数字的字符串
	 * 该字符串表示的数字，高位在前，低位在后
	 * 若字符串第一个字符为符号，则符号由它决定
	 * 否则默认符号为 '+'
	 */
	explicit Integer(const string& s1)
	{
		if (s1.empty())
		{
			num += '\000';
			return;
		}

		bool isNum = true;
		if (s1.at(0) >= '0' && s1.at(0) <= '9')
		{
			num += s1.at(0) - '0';
			sign = '+';
		}
		else if (s1.at(0) == '+') sign = '+';
		else if (s1.at(0) == '-') sign = '-';
		else isNum = false;

		if (isNum)
		{
			for (size_t i = 1; i < s1.size(); ++i)
			{
				if (s1.at(i) < '0' || s1.at(i) > '9')
				{
					isNum = false;
					break;
				}

				num += s1.at(i) - '0';
			}
		}

		if (isNum)
		{
			std::reverse(num.begin(), num.end());
		}
		else
		{
			num.clear();
			sign = '+';
		}
	}


	// 五大函数
	// 拷贝构造函数
	Integer(const Integer& n) :num(n.num), sign(n.sign) {}

	// 移动构造函数
	Integer(Integer&& n)noexcept
	{
		num = std::move(n.num);
		sign = std::move(n.sign);
	}

	// 拷贝赋值运算符
	Integer operator=(const Integer& n)
	{
		if (this != &n)
		{
			num = n.num;
			sign = n.sign;
		}

		return *this;
	}

	// 移动赋值运算符
	Integer operator=(Integer&& n)
	{
		if (this != &n)
		{
			num = std::move(n.num);
			sign = std::move(sign);
		}

		return *this;
	}

	// 析构函数
	~Integer() {}



	// 数值计算运算符重载
	Integer operator+(int x)const
	{
		return *this + Integer(x);
	}

	Integer operator-(int x)const
	{
		return *this - Integer(x);
	}

	Integer operator*(int x)const
	{
		return *this * Integer(x);
	}

	Integer operator/(int x)const
	{
		return *this / Integer(x);
	}

	/**
	 * 大数加法
	 */
	Integer operator+(const Integer& n)const
	{
		// 两数符号相同做加法运算
		//  1 +  3 = 4
		// -1 + -3 = -(1 + 3) = -4
		// 两数符号不同则做减法
		//  1 + -3 = -(3 - 1) = -2
		// -1 +  3 =   3 - 1  =  2
		//  3 + -1 =  3 -  1  =  2
		// -3 +  1 = -(3 - 1) = -2

		if (sign == n.sign)		// 符号相同做加法
		{
			if (sign == '+') return add(n);				//  1 +  3 = 4
			else return -add(n);						// -1 + -3 = -(1 + 3) = -4
		}
		else					// 符号不同做减法
		{
			if (less(n))
			{
				if (sign == '+') return -n.sub(*this);	//  1 + -3 = -(3 - 1) = -2
				else return n.sub(*this);				// -1 +  3 =   3 - 1  =  2
			}
			else if (n.less(*this))
			{
				if (sign == '+') return sub(n);			//  3 + -1 =  3 -  1  =  2
				else return -sub(n);					// -3 +  1 = -(3 - 1) = -2
			}
			else				// 符号不同且绝对值相等
			{
				return Integer("0", '+');				// -x + x 或 x + -x
			}
		}
	}

	/**
	 * 大数减法
	 */
	Integer operator-(const Integer& n)const
	{
		// 两数异号做加法
		//  1 - -3 =    1 + 3  =  4
		// -1 -  3 =  -(1 + 3) = -4
		// 两数同号做减法
		// -1 - -3 = - 1 + 3  =  3 - 1 = 2
		//  1 -  3 = -(3 - 1) = -2
		// -3 - -1 = -3 + 1 = -(3 - 1) = -2
		//  3 -  1 = 2

		if (sign != n.sign)	// 符号不同
		{
			if (n.sign == '-') return add(n);				//  1 - -3 =    1 + 3  =  4
			else return -add(n);							// -1 -  3 =  -(1 + 3) = -4
		}
		else				// 符号相同
		{
			if (less(n))			// *this 的绝对值小于 n 的绝对值
			{
				if (sign == '-') return n.sub(*this);		// -1 - -3 =   3 - 1  = 2
				else return -n.sub(*this);					//  1 -  3 = -(3 - 1) = 2
			}
			else if(n.less(*this))	// n 的绝对值小于 *this 的绝对值
			{
				if (sign == '-') return -sub(n);			// -3 - -1 = -3 + 1 = -(3 - 1) = -2
				else return sub(n);							//  3 -  1 = 2
			}
			else					// 绝对值相等		
			{
				return Integer("0", '+');					// -x - -x  或 x - x
			}
		}
	}

	/**
	 * 大数乘法
	 */
	Integer operator*(const Integer& n)const
	{
		return mult(n);
	}

	/**
	 * 大数除法
	 */
	Integer operator/(const Integer& n)const
	{
		return div(n);
	}

	Integer& operator+=(int x)
	{
		*this += Integer(x);

		return *this;
	}

	Integer& operator-=(int x)
	{
		*this -= Integer(x);

		return *this;
	}

	Integer& operator*=(int x)
	{
		*this *= Integer(x);

		return *this;
	}

	Integer& operator/=(int x)
	{
		*this /= Integer(x);

		return *this;
	}

	Integer& operator+=(const Integer& n)
	{
		*this = *this + n;

		return *this;
	}

	Integer& operator-=(const Integer& n)
	{
		*this = *this - n;

		return *this;
	}

	Integer& operator*=(const Integer& n)
	{
		*this = *this * n;

		return *this;
	}

	Integer& operator/=(const Integer& n)
	{
		*this = *this / n;

		return *this;
	}


	// 关系运算符重载
	bool operator==(int x)const noexcept
	{
		return *this == Integer(x);
	}

	bool operator!=(int x)const noexcept
	{
		return *this != Integer(x);
	}

	bool operator<=(int x)const noexcept
	{
		return *this <= Integer(x);
	}

	bool operator>=(int x)const noexcept
	{
		return *this >= Integer(x);
	}

	bool operator<(int x)const noexcept
	{
		return *this < Integer(x);
	}

	bool operator>(int x)const noexcept
	{
		return *this > Integer(x);
	}

	bool operator==(const Integer& n)const noexcept
	{
		if (sign == n.sign && num == n.num) return true;
		return false;
	}

	bool operator!=(const Integer& n)const noexcept
	{
		return !(*this == n);
	}

	bool operator<=(const Integer& n)const noexcept
	{
		if (*this == n) return true;
		return *this < n;
	}

	bool operator>=(const Integer& n)const noexcept
	{
		if (*this == n) return true;
		return n < *this;
	}

	bool operator<(const Integer& n)const noexcept
	{
		if (sign == '-' && n.sign == '+')		return true;
		else if (sign == '-' && n.sign == '-')	return n.less(*this);
		else if (sign == '+' && n.sign == '+')	return less(n);
		else									return false;
	}

	bool operator>(const Integer& n)const noexcept
	{
		return n < *this;
	}

	// 逻辑运算符重载
	bool operator&&(int x)const noexcept
	{
		return *this && Integer(x);
	}

	bool operator||(int x)const noexcept
	{
		return *this || Integer(x);
	}

	bool operator&&(const Integer& n)const noexcept
	{
		if (*this == 0) return false;
		else if (n == 0) return false;
		else return true;
	}

	bool operator||(const Integer& n)const noexcept
	{
		if (*this != 0) return true;
		else return n != 0;
	}

	/**********************************************************
	 *                       友元函数                         *
	 **********************************************************/
	// >> <<运算符重载
	friend istream& operator>>(istream& in, Integer& n)
	{
		string str;
		in >> str;
		if (str.empty()) return in;

		bool isNum = true;
		if (str.at(0) >= '0' && str.at(0) <= '9')
		{
			n.num += str.at(0) - '0';
			n.sign = '+';
		}
		else if (str.at(0) == '+') n.sign = '+';
		else if (str.at(0) == '-') n.sign = '-';
		else isNum = false;


		if (isNum)
		{
			for (size_t i = 1; i < str.size(); ++i)
			{
				if (str.at(i) < '0' || str.at(i) > '9')
				{
					isNum = false;
					break;
				}

				n.num += str.at(i) - '0';
			}
		}
		else
		{
			isNum = false;
		}

		// 若不是数字，清空
		if (!isNum)
		{
			n.num.clear();
			n.sign = '+';
		}

		return in;
	}

	friend ostream& operator<<(ostream& os, const Integer& n)
	{
		string str(n.num);
		for (auto& ch : str) ch += '0';
		std::reverse(str.begin(), str.end());

		// 输出
		os << (n.sign == '-' ? "-" : "") + str;

		return os;
	}


	// 一元逻辑运算符重载
	friend bool operator!(const Integer& n) noexcept
	{
		return n == 0;
	}

	// 一元正负号重载
	friend Integer operator+(const Integer& n) noexcept
	{
		Integer tInt(n);
		tInt.sign = '+';

		return tInt;
	}

	friend Integer operator-(const Integer& n) noexcept
	{
		Integer tInt(n);
		tInt.sign = n < 0 ? '+' : '-';

		return tInt;
	}


	// 数值计算运算符重载
	friend Integer operator+(int x,const Integer& n)
	{
		return n + x;
	}

	friend Integer operator-(int x, const Integer& n)
	{
		return n - x;
	}

	friend Integer operator*(int x, const Integer& n)
	{
		return n * x;
	}
	
	friend Integer operator/(int x, const Integer& n)
	{
		return n / x;
	}

};