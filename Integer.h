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
	using Int_type = __int64;	// 接受的最大整型的类型
	
	/**
	 * 此构造函数接收一个表示数字的字符串，一个该数字的符号
	 * 该字符串表示的数字，低位在前，高位在后
	 * 字符串必须由纯数字组成
	 * 符号由第二个参数提供
	 */
	Integer(const string& s1, char ch) :num(s1), sign(ch) {}

	/**
	 * 参数同上，为它的右值参数形式
	 */
	Integer(string&& s1, char ch)
	{
		num = std::move(s1);
		sign = std::move(ch);
	}

	/**
	 * 大数加法实现
	 * 两数必须都为正数
	 * 只做数值运算，不做符号运算
	 * 运算结果永远为正
	 */
	Integer add(const Integer& n)const
	{
		Integer tInt(this->num, '+');
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int sum = 0;
		int carry = 0;

		while (i < len1 || j < len2 || carry)
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
	 * 运算结果永远为正
	 */
	Integer sub(const Integer& n)const
	{
		Integer tInt(this->num, '+');
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int diff = 0;					// 某位的差
		int borrow = 0;					// 借位

		while (i < len1 || j < len2 )
		{
			diff = (i < len1 ? tInt.num.at(i) : 0) - (j < len2 ? n.num.at(j) : 0) - borrow;
			borrow = diff < 0 ? 1 : 0;
			if (i < len1) tInt.num.at(i) = borrow ? 10 + diff : diff;
			else tInt.num += borrow ? 10 + diff : diff;

			++i;
			++j;
		}

		// 去除最高位无用的 0
		int t = tInt.num.back();
		while (!t)
		{
			tInt.num.pop_back();
			t = tInt.num.back();
		}

		return tInt;
	}

	/**
	 * 大数乘法实现
	 * 两数的正负可是任意的
	 */
	Integer mult(const Integer& n)const
	{
		if (*this == 0 || n == 0) return Integer(0);

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
	 * 大数除法的辅助函数
	 * a b 均为逆序存储的数字数组
	 * 即低位在前，高位在后
	 * 若 a的绝对值大于b的绝对值
	 * 即 a能够减去b，则返回 true,否则返回 false
	 */
	bool help_sub(vector<int>& a, const vector<int>& b,const int startb)const
	{
		const int lena = a.size();						// a 的长度 真实的长度 也是实际要进行计算的长度
		const int lenb = b.size() - startb;				// b 从 startb 到结尾的长度 此长度为实际要进行计算的长度
		if (lena < lenb) return false;					// 若 a小于b ，则返回 false

		if (lena == lenb)								// 长度相等，进行大小比较
		{
			int i = lena - 1;
			int j = lenb - 1;
			while (i >= 0 || j >= 0)
			{
				if (a.at(i) > b.at(j + startb)) break;
				else if (a.at(i) < b.at(j + startb)) return false;	// a小于b ，返回 false

				--i;
				--j;
			}
		}

		int ia = 0;
		int ib = startb;
		int diff = 0;
		const int tlb = b.size();
		// 因为是逆序存储的，所以需要从前往后减
		while (ia < lena || ib < tlb)
		{
			diff = (ia < lena ? a.at(ia) : 0) - (ib < tlb ? b.at(ib) : 0);
			a.at(ia) = diff < 0 ? 10 + diff : diff;
			// 因为a一定大于等于b，若有借位则一定还在数组下标范围内，保证不会越界
			if (diff < 0) --a.at(ia + 1);

			++ia;
			++ib;
		}

		for (int i = lena - 1; i >= 0; --i)
		{
			if (a.at(i)) return true;		// 返回结果 true
			else a.pop_back();				// 去掉最高位的 0
		}

		return true;						// 两数相等返回 true
	}

	/**
	 * 大数的除法实现
	 * 两数的正负可是任意的
	 * 可选择返回商或余数
	 * 默认返回商
	 * 若指定第二个参数为 false 则返回余数
	 */
	Integer div(const Integer& n,bool isMer=true)const
	{
		// 判断是否有数字为 0
		if (*this == 0) return Integer(0);
		else if (n == 0) throw "divide by zero";

		// 被除数与除数的大小判断
		if (less(n)) return isMer ? Integer(0) : *this;

		// 到这里说明被除数是大于除数的，则商至少为1
		// 注意，下面的 被除数 除数 商 均为倒序存储的

		const int lent = num.size() - n.num.size();			// 被除数与除数的长度差
		vector<int> na(num.begin(), num.end());				// 被除数
		// 直接将 nb 分配为和 na 一样长 相当于将它扩大了 10^lent 倍
		vector<int> nb(na.size(), 0);						// 除数
		vector<int> nr(lent + 1, 0);						// 商
		
		// 初始化 nb 的值
		for (size_t i = lent; i < nb.size(); ++i)
		{
			nb.at(i) = n.num.at(i - lent);
		}

		// 被除数与除数的长度差为 0 也可以减，所以是循环进行 lent+1 次
		int lenb = 0;
		for (int i = 0; i <= lent; ++i)
		{
			// 两数相减，判断是否足够减
			while (help_sub(na, nb, lenb))
			{
				// 该位的商增加一 商是逆序存储的
				++nr.at(lent - i);
			}

			// 该位减完，减数去掉一位(减数减少十倍)
			++lenb;
		}

		// 得出计算结果
		if (isMer)
		{
			string mer;						// 存储商
			int index = 0;
			for (index = nr.size() - 1; index >= 0; --index)
			if (nr.at(index)) break;		// 低位在前，所以从后往前找第一个非 0 的值，即是结果的开始位置

			// 任然按逆序将商存入 string
			for (int i = 0; i <= index; ++i) mer += nr.at(i);

			// 计算符号
			const char ch = sign == n.sign ? '+' : '-';

			// 返回构造结果
			return Integer(std::move(mer), ch);
		}
		else
		{
			if (na.empty()) return Integer(0);		// 余数为 0

			// 逆序存储余数
			string ram;								// 存储余数
			for (size_t i = 0; i < na.size(); ++i)	ram += na.at(i);

			// 计算符号	余数的符号与被除数的符号相同
			const char ch = sign;

			// 返回构造结果
			return Integer(std::move(ram), ch);
		}
	}

	/**
	 * 统一进行加减法运算的调配工作
	 * 调用前应将参数和运算符的多余符号化简
	 * 调用者与参数是加法连接的
	 * 具体执行加法还是减法，决定于两者的符号
	 */
	Integer deploy(const Integer& n)const
	{
		if (sign == n.sign)			// 符号相同，做加法运算
		{
			if (sign == '+')		return  add(n);
			else					return -add(n);
		}
		else						// 符号不同，做减法运算
		{
			if (less(n))			// 判断两数绝对值大小，只能进行绝对值大的减去绝对值小的
			{
				if (sign == '+')	return -n.sub(*this);
				else				return	n.sub(*this);
			}
			else if (n.less(*this))
			{
				if (sign == '+')	return  sub(n);
				else				return -sub(n);
			}
			else
			{
									return Integer(0);
			}
		}

		return Integer(0);
	}

	/**
	 * 比较该数的绝对值是否小于参数的绝对值
	 */
	bool less(const Integer& n)const
	{
		if (num.size() < n.num.size())		return true;
		else if (num.size() > n.num.size()) return false;
		else
		{
			// 逆序从高位开始比较
			for (int i = num.size() - 1; i >= 0; --i)
			{
				if (num.at(i) == n.num.at(i)) continue;
				else if (num.at(i) < n.num.at(i)) return true;
				else return false;
			}
			return false;
		}
	}


public:
	// 默认/单参数构造函数
	Integer(Int_type x = 0)
	{
		sign = x < 0 ? '-' : '+';
		x = abs(x);

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
	Integer operator=(Integer&& n)noexcept
	{
		if (this != &n)
		{
			num = std::move(n.num);
			sign = std::move(n.sign);
		}

		return *this;
	}

	// 析构函数
	~Integer() = default;



	// 数值计算运算符重载
	Integer operator+(Int_type x)const
	{
		return *this + Integer(x);
	}

	Integer operator-(Int_type x)const
	{
		return *this - Integer(x);
	}

	Integer operator*(Int_type x)const
	{
		return *this * Integer(x);
	}

	Integer operator/(Int_type x)const
	{
		return *this / Integer(x);
	}

	Integer operator%(Int_type x)const
	{
		return *this % Integer(x);
	}

	/**
	 * 大数加法
	 */
	Integer operator+(const Integer& n)const 
	{
		return deploy(n);
	}

	/**
	 * 大数减法
	 */
	Integer operator-(const Integer& n)const
	{
		if (n.sign == '-')	return deploy(+n);		// x - -3 = x + 3
		else				return deploy(-n);		// x - +3 = x - 3
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

	/**
	 * 大数取余
	 */
	Integer operator%(const Integer& n)const
	{
		return div(n, false);
	}

	Integer& operator+=(Int_type x)
	{
		*this += Integer(x);

		return *this;
	}

	Integer& operator-=(Int_type x)
	{
		*this -= Integer(x);

		return *this;
	}

	Integer& operator*=(Int_type x)
	{
		*this *= Integer(x);

		return *this;
	}

	Integer& operator/=(Int_type x)
	{
		*this /= Integer(x);

		return *this;
	}

	Integer& operator%=(Int_type x)
	{
		*this %= Integer(x);

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

	Integer& operator%=(const Integer& n)
	{
		*this = *this % n;

		return *this;
	}

	// 一元自增自减运算符重载
	Integer& operator++()
	{
		*this += 1;

		return *this;
	}

	Integer operator++(int)
	{
		Integer tInt(*this);
		*this += 1;

		return tInt;
	}

	Integer& operator--()
	{
		*this -= 1;

		return *this;
	}

	Integer operator--(int)
	{
		Integer tInt(*this);
		*this += 1;

		return tInt;
	}


	// 比较运算符重载
	bool operator==(Int_type x)const noexcept
	{
		return *this == Integer(x);
	}

	bool operator!=(Int_type x)const noexcept
	{
		return *this != Integer(x);
	}

	bool operator<=(Int_type x)const noexcept
	{
		return *this <= Integer(x);
	}

	bool operator>=(Int_type x)const noexcept
	{
		return *this >= Integer(x);
	}

	bool operator<(Int_type x)const noexcept
	{
		return *this < Integer(x);
	}

	bool operator>(Int_type x)const noexcept
	{
		return *this > Integer(x);
	}

	bool operator==(const Integer& n)const noexcept
	{
		// +0 == -0
		if (num.size() == 1 && num.back() == 0 &&
			n.num.size() == 1 && n.num.back() == 0)	return true;
		else if (sign == n.sign && num == n.num)	return true;
		else										return false;
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
	bool operator&&(Int_type x)const noexcept
	{
		return *this && Integer(x);
	}

	bool operator||(Int_type x)const noexcept
	{
		return *this || Integer(x);
	}

	bool operator&&(const Integer& n)const noexcept
	{
		if (*this == 0 || n == 0) return false;
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

	// 流运算符重载
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
		os << ((n.sign == '-' ? "-" : "") + str);

		return os;
	}


	// 一元逻辑运算符重载
	friend bool operator!(const Integer& n) noexcept
	{
		return n == 0;
	}

	// 一元正负号重载
	friend Integer operator+(const Integer& n)
	{
		return Integer(n.num, '+');
	}

	friend Integer operator-(const Integer& n)
	{
		return Integer(n.num, n.sign == '+' ? '-' : '+');
	}


	// 数值计算运算符重载
	friend Integer operator+(Int_type x,const Integer& n)
	{
		return n + x;
	}

	friend Integer operator-(Int_type x, const Integer& n)
	{
		return n - x;
	}

	friend Integer operator*(Int_type x, const Integer& n)
	{
		return n * x;
	}
	
	friend Integer operator/(Int_type x, const Integer& n)
	{
		return n / x;
	}

	friend Integer operator%(Int_type x, const Integer& n)
	{
		return n % x;
	}

};