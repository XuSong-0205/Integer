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

	/**
	 * �Ƚϸ����ľ���ֵ�Ƿ�С�ڲ����ľ���ֵ
	 */
	bool less(const Integer& n)const noexcept
	{
		if (num.size() < n.num.size()) return true;
		else if (num.size() > n.num.size()) return false;
		else return num < n.num;
	}

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
	 * ��������ʵ��
	 * �������ľ���ֵ������ڼ����ľ���ֵ
	 * ֻ����ֵ���㣬������������
	 */
	Integer sub(const Integer& n)const
	{
		Integer tInt(*this);
		int i = 0;
		int j = 0;
		const int len1 = tInt.num.size();
		const int len2 = n.num.size();
		int diff = 0;					// ĳλ�Ĳ�
		int borrow = 0;					// ��λ

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
	 * �����˷�ʵ��
	 * �������������������
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

public:
	// Ĭ��/���������캯��
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
			sign = std::move(sign);
		}

		return *this;
	}

	// ��������
	~Integer() {}



	// ��ֵ�������������
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
	 * �����ӷ�
	 */
	Integer operator+(const Integer& n)const
	{
		// ����������ͬ���ӷ�����
		//  1 +  3 = 4
		// -1 + -3 = -(1 + 3) = -4
		// �������Ų�ͬ��������
		//  1 + -3 = -(3 - 1) = -2
		// -1 +  3 =   3 - 1  =  2
		//  3 + -1 =  3 -  1  =  2
		// -3 +  1 = -(3 - 1) = -2

		if (sign == n.sign)		// ������ͬ���ӷ�
		{
			if (sign == '+') return add(n);				//  1 +  3 = 4
			else return -add(n);						// -1 + -3 = -(1 + 3) = -4
		}
		else					// ���Ų�ͬ������
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
			else				// ���Ų�ͬ�Ҿ���ֵ���
			{
				return Integer("0", '+');				// -x + x �� x + -x
			}
		}
	}

	/**
	 * ��������
	 */
	Integer operator-(const Integer& n)const
	{
		// ����������ӷ�
		//  1 - -3 =    1 + 3  =  4
		// -1 -  3 =  -(1 + 3) = -4
		// ����ͬ��������
		// -1 - -3 = - 1 + 3  =  3 - 1 = 2
		//  1 -  3 = -(3 - 1) = -2
		// -3 - -1 = -3 + 1 = -(3 - 1) = -2
		//  3 -  1 = 2

		if (sign != n.sign)	// ���Ų�ͬ
		{
			if (n.sign == '-') return add(n);				//  1 - -3 =    1 + 3  =  4
			else return -add(n);							// -1 -  3 =  -(1 + 3) = -4
		}
		else				// ������ͬ
		{
			if (less(n))			// *this �ľ���ֵС�� n �ľ���ֵ
			{
				if (sign == '-') return n.sub(*this);		// -1 - -3 =   3 - 1  = 2
				else return -n.sub(*this);					//  1 -  3 = -(3 - 1) = 2
			}
			else if(n.less(*this))	// n �ľ���ֵС�� *this �ľ���ֵ
			{
				if (sign == '-') return -sub(n);			// -3 - -1 = -3 + 1 = -(3 - 1) = -2
				else return sub(n);							//  3 -  1 = 2
			}
			else					// ����ֵ���		
			{
				return Integer("0", '+');					// -x - -x  �� x - x
			}
		}
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


	// ��ϵ���������
	bool operator==(int x)const
	{
		return *this == Integer(x);
	}

	bool operator!=(int x)const
	{
		return *this != Integer(x);
	}

	bool operator<=(int x)const
	{
		return *this <= Integer(x);
	}

	bool operator>=(int x)const
	{
		return *this >= Integer(x);
	}

	bool operator<(int x)const
	{
		return *this < Integer(x);
	}

	bool operator>(int x)const
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

	bool operator<=(const Integer& n)const
	{
		if (*this == n) return true;
		return *this < n;
	}

	bool operator>=(const Integer& n)const
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

	bool operator>(const Integer& n)const
	{
		return n < *this;
	}

	// �߼����������
	bool operator&&(int x)const
	{
		return *this && Integer(x);
	}

	bool operator||(int x)const
	{
		return *this || Integer(x);
	}

	bool operator&&(const Integer& n)const
	{
		if (*this == 0) return false;
		else if (n == 0) return false;
		else return true;
	}

	bool operator||(const Integer& n)const
	{
		if (*this != 0) return true;
		else return n != 0;
	}

	/**********************************************************
	 *                       ��Ԫ����                         *
	 **********************************************************/
	// >> <<���������
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
		os << (n.sign == '-' ? "-" : "") + str;

		return os;
	}


	// һԪ�߼����������
	friend bool operator!(const Integer& n)
	{
		return n == 0;
	}

	// һԪ����������
	friend Integer operator+(const Integer& n)
	{
		Integer tInt(n);
		tInt.sign = '+';

		return tInt;
	}

	friend Integer operator-(const Integer& n)
	{
		Integer tInt(n);
		tInt.sign = n < 0 ? '+' : '-';

		return tInt;
	}


	// ��ֵ�������������
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