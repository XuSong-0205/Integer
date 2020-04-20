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
	string num;					// �����ֵ���ֵ��ʽ
	char sign = '+';			// �����ֵķ��� '+' '-'
	using Int_type = __int64;
	
	/**
	 * �˹��캯������һ����ʾ���ֵ��ַ�����һ�������ֵķ���
	 * ���ַ�����ʾ�����֣���λ��ǰ����λ�ں�
	 * �ַ��������ɴ��������
	 * �����ɵڶ��������ṩ
	 */
	Integer(const string& s1, char ch) :num(s1), sign(ch) {}

	/**
	 * �����ӷ�ʵ��
	 * �������붼Ϊ����
	 * ֻ����ֵ���㣬������������
	 * ��������ԶΪ��
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
	 * ��������ʵ��
	 * �������ľ���ֵ������ڼ����ľ���ֵ
	 * ֻ����ֵ���㣬������������
	 * ��������ԶΪ��
	 */
	Integer sub(const Integer& n)const
	{
		Integer tInt(this->num, '+');
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int diff = 0;					// ĳλ�Ĳ�
		int borrow = 0;					// ��λ

		while (i < len1 || j < len2 )
		{
			diff = (i < len1 ? tInt.num.at(i) : 0) - (j < len2 ? n.num.at(j) : 0) - borrow;
			borrow = diff < 0 ? 1 : 0;
			if (i < len1) tInt.num.at(i) = borrow ? 10 + diff : diff;
			else tInt.num += borrow ? 10 + diff : diff;

			++i;
			++j;
		}

		// ȥ�����λ���õ� 0
		int t = tInt.num.back();
		while (!t)
		{
			tInt.num.pop_back();
			t = tInt.num.back();
		}

		return tInt;
	}

	/**
	 * �����˷�ʵ��
	 * �������������������
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
				// ��ʱ�����ǽ�λ
				vec.at(i + j) += one.at(i) * two.at(j);
			}
		}

		// �����������н�λ
		string str(vec.size(), '\000');
		int carry = 0;
		int sum = 0;
		for (size_t i = 0; i < vec.size(); ++i)
		{
			sum = vec.at(i) + carry;
			vec.at(i) = sum >= 10 ? sum % 10 : sum;
			carry = sum / 10;

			// ���д���ַ���
			str.at(i) = vec.at(i);
		}

		// �����λΪ 0 ��ȥ��
		if (str.back() == '\000') str.pop_back();
		// �������
		const char ch = sign == n.sign ? '+' : '-';

		// ����˽�е�˫�������캯�� 
		return Integer(std::move(str), ch);
	}

	/**
	 * �����ĳ���ʵ��
	 * �������������������
	 */
	Integer div(const Integer& n)const
	{

	}

	/**
	 * ͳһ���мӼ�������ĵ��乤��
	 * ����ǰӦ��������������Ķ�����Ż���
	 * ������������Ǽӷ����ӵ�
	 * ����ִ�мӷ����Ǽ��������������ߵķ���
	 */
	Integer deploy(const Integer& n)const
	{
		if (sign == n.sign)			// ������ͬ�����ӷ�����
		{
			if (sign == '+')		return  add(n);
			else					return -add(n);
		}
		else						// ���Ų�ͬ������������
		{
			if (less(n))			// �ж���������ֵ��С��ֻ�ܽ��о���ֵ��ļ�ȥ����ֵС��
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
	 * �Ƚϸ����ľ���ֵ�Ƿ�С�ڲ����ľ���ֵ
	 */
	bool less(const Integer& n)const
	{
		if (num.size() < n.num.size())		return true;
		else if (num.size() > n.num.size()) return false;
		else
		{
			// ����Ӹ�λ��ʼ�Ƚ�
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
	// Ĭ��/���������캯��
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
	 * �˹��캯������һ����ʾ���ֵ��ַ���
	 * ���ַ�����ʾ�����֣���λ��ǰ����λ�ں�
	 * ���ַ�����һ���ַ�Ϊ���ţ��������������
	 * ����Ĭ�Ϸ���Ϊ '+'
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


	// �����
	// �������캯��
	Integer(const Integer& n) :num(n.num), sign(n.sign) {}

	// �ƶ����캯��
	Integer(Integer&& n)noexcept
	{
		num = std::move(n.num);
		sign = std::move(n.sign);
	}

	// ������ֵ�����
	Integer operator=(const Integer& n)
	{
		if (this != &n)
		{
			num = n.num;
			sign = n.sign;
		}

		return *this;
	}

	// �ƶ���ֵ�����
	Integer operator=(Integer&& n)
	{
		if (this != &n)
		{
			num = std::move(n.num);
			sign = std::move(n.sign);
		}

		return *this;
	}

	// ��������
	~Integer() = default;



	// ��ֵ�������������
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

	/**
	 * �����ӷ�
	 */
	Integer operator+(const Integer& n)const 
	{
		return deploy(n);
	}

	/**
	 * ��������
	 */
	Integer operator-(const Integer& n)const
	{
		if (n.sign == '-')	return deploy(+n);		// x - -3 = x + 3
		else				return deploy(-n);		// x - +3 = x - 3
	}

	/**
	 * �����˷�
	 */
	Integer operator*(const Integer& n)const
	{
		return mult(n);
	}

	/**
	 * ��������
	 */
	Integer operator/(const Integer& n)const
	{
		return div(n);
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
		*this = *this + n;

		return *this;
	}

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


	// �Ƚ����������
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

	// �߼����������
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
	 *                       ��Ԫ����                         *
	 **********************************************************/
	// �����������
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

		// ���������֣����
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

		// ���
		os << ((n.sign == '-' ? "-" : "") + str);

		return os;
	}


	// һԪ�߼����������
	friend bool operator!(const Integer& n) noexcept
	{
		return n == 0;
	}

	// һԪ����������
	friend Integer operator+(const Integer& n)
	{
		return Integer(n.num, '+');
	}

	friend Integer operator-(const Integer& n)
	{
		return Integer(n.num, n.sign == '+' ? '-' : '+');
	}


	// ��ֵ�������������
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

};