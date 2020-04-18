#pragma once

namespace sx
{
	namespace io
	{
		// ���ø���ģʽ
		namespace reset
		{
			constexpr auto reset_all		=	"\033[0m";			// ��������ģʽ
			constexpr auto reset_fg_color	=	"\033[39m";			// ����ǰ��ɫ
			constexpr auto reset_bg_color	=	"\033[49m";			// ���ñ���ɫ
		}
		
		// ǰ��ɫ ������ɫ
		namespace fg
		{
			constexpr auto black	=	"\033[30m";			// Black
			constexpr auto red		=	"\033[31m";			// RED
			constexpr auto green	=	"\033[32m";			// GREEN
			constexpr auto yellow	=	"\033[33m";			// YELLOW
			constexpr auto blue		=	"\033[34m";			// BLUE
			constexpr auto magenta	=	"\033[35m";			// MAGENTA
			constexpr auto cyan		=	"\033[36m";			// CYAN
			constexpr auto white	=	"\033[37m";			// WHITE
		}

		// ����ɫ ������ɫ
		namespace bg
		{
			constexpr auto black	=	"\033[40m";
			constexpr auto red		=	"\033[41m";
			constexpr auto green	=	"\033[42m";
			constexpr auto yellow	=	"\033[43m";
			constexpr auto blue		=	"\033[44m";
			constexpr auto magenta	=	"\033[45m";
			constexpr auto cyan		=	"\033[46m";
			constexpr auto white	=	"\033[47m";
		}

		// ����
		namespace font
		{
			constexpr auto bold			=	"\033[1m";			// ����
			constexpr auto half_bold	=	"\033[2m";			// ���ȼ���
			// constexpr auto italic		=	"\033[3m";			// б��				����Ч
			constexpr auto underline	=	"\033[4m";			// �»���
			// constexpr auto twinkle		=	"\033[5m";			// ��˸				����Ч
		    // constexpr auto flash		=   	"\033[6m";			// ����				����Ч
			constexpr auto anti_display =	"\033[7m";			// ����
			constexpr auto blanking		=	"\033[8m";			// ����
			// constexpr auto delete_line	=	"\033[9m";			// ɾ����			����Ч
		}

	}

}



//#define		RESET			"\033[0m"
//#define		BLACK			"\033[30m"			/* Black */
//#define		RED				"\033[31m"			/* Red */
//#define		GREEN			"\033[32m"			/* Green */
//#define		YELLOW			"\033[33m"			/* Yellow */
//#define		BLUE			"\033[34m"			/* Blue */
//#define		MAGENTA			"\033[35m"			/* Magenta */
//#define		CYAN			"\033[36m"			/* Cyan */
//#define		WHITE			"\033[37m"			/* White */
//#define		BOLDBLACK		"\033[1m\033[30m"	/* Bold Black */
//#define		BOLDRED			"\033[1m\033[31m"	/* Bold Red */
//#define		BOLDGREEN		"\033[1m\033[32m"	/* Bold Green */
//#define		BOLDYELLOW		"\033[1m\033[33m"	/* Bold Yellow */
//#define		BOLDBLUE		"\033[1m\033[34m"	/* Bold Blue */
//#define		BOLDMAGENTA		"\033[1m\033[35m"	/* Bold Magenta */
//#define		BOLDCYAN		"\033[1m\033[36m"	/* Bold Cyan */
//#define		BOLDWHITE		"\033[1m\033[37m"	/* Bold White */


//C / C++�ı��ն�����������ɫ��Linux��(2014 - 03 - 07 12:50 : 30)ת�ب�
//��ǩ�� c / c linux ���� ��ɫ ansi������
//�򵥵�˵����ESC[*m��ESC�İ˽���Ϊ\033�� * �����Ƕ�����Ե���ϣ��÷ֺŸ�����
//
//����
//#include
//int main()
//{
//	printf("\033[31mThis is RED.\n\033[0m");
//	return 0;
//}
//31m��������Ϊ��ɫ��0m����ر��������ԡ�
//
//���õ�ANSI���������£���Щ��֧�֣���
//\033[0m �ر���������
//\033[1m ����
//\033[2m ���ȼ���
//\033[3m б��
//\033[4m �»���
//\033[5m ��˸
//\033[6m ����
//\033[7m ����
//\033[8m ����
//\033[9m �м�һ������
//10 - 19 ���������
//21 - 29 ������1 - 9�����෴
//30 - 37 ����ǰ��ɫ
//40 - 47 ���ñ���ɫ
//30 : ��
//31 : ��
//32 : ��
//33 : ��
//34 : ��ɫ
//35 : ��ɫ
//36 : ����
//37 : ��ɫ
//38 ���»���, ����Ĭ��ǰ��ɫ
//39 �ر��»���, ����Ĭ��ǰ��ɫ
//40 ��ɫ����
//41 ��ɫ����
//42 ��ɫ����
//43 ��ɫ����
//44 ��ɫ����
//45 Ʒ�챳��
//46 ��ȸ������
//47 ��ɫ����
//48 ��֪��ʲô����
//49 ����Ĭ�ϱ���ɫ
//50 - 89 û��
//90 - 109 ��������ǰ�������ģ���֮ǰ����ɫǳ
//\033[nA �������n��
//\033[nB �������n��
//\033[nC �������n��
//\033[nD �������n��
//\033[y; xH���ù��λ��
//\033[2J ����
//\033[K ����ӹ�굽��β������
//\033[s ������λ��
//\033[u �ָ����λ��
//\033[? 25l ���ع��
//\033[? 25h ��ʾ���
