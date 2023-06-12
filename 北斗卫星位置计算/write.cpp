#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include "parameter.h"
#include <cmath>
using namespace std;
MJD CalendarTime2MJD(CalendarTime calT);
BDSTime MJD2BDSTime(MJD mjd);
double calculate_x(BDSTime dstBDST, parameter ep);
double calculate_y(BDSTime dstBDST, parameter ep);
double calculate_z(BDSTime dstBDST, parameter ep);
double Lagrange(double arrX[], double arrY[], double n, double x);

//�ӹ㲥�������C07λ��(IGSO)
void C7_position(parameter s[1375], string outfile)
{
	//�������C07һ���λ�ã�����ĵ�39���ǣ�
	//����һ���ʱ�����У����Ϊ15���ӣ�
	//��0.00��23.45
	BDSTime onedaytime[96];
	double C7_position_get[96][3];
	int nearnum;//���������������
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//ʵ��ʱ���ÿһ���ο�ʱ�̵Ĳ�ֵ
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 553; m < 577; m++)//��Ϊc07�ڹ㲥��������24������Ҫһ�����ȽϺ���һ����ӽ�,��Ŵ�553��577
		{
			if (abs(onedaytime[i].tos - s[m].TOE) < dif)
			{
				dif = abs(onedaytime[i].tos - s[m].TOE);
				nearnum = m;
			}
		}
		C7_position_get[i][0] = calculate_x(onedaytime[i], s[nearnum]);
		C7_position_get[i][1] = calculate_y(onedaytime[i], s[nearnum]);
		C7_position_get[i][2] = calculate_z(onedaytime[i], s[nearnum]);

	}
	//����ļ�
	ofstream file_result;//��������ļ���
	//��������ļ���ַ
	string name = "/C07������ά����.txt";
	name = outfile + name;
	file_result.open(name);//�����޸��ļ�·��
	//��ʼ�����ά���������ֵ
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//���ñ���С��λ������ȷ��mm��ȡ6λ
		file_result << C7_position_get[i][0] << "\t" << C7_position_get[i][1] << "\t" << C7_position_get[i][2] << "\n";
	}
	//�ر�����ļ���
	file_result.close();
	cout << "�����C07���ǹ㲥�����ó�����" << endl;
}
//�ӹ㲥�������C21λ��(MEO)
void C21_position(parameter s[1375], string outfile)
{
	//�������C21һ���λ�ã�����ĵ�52���ǣ�
	//����һ���ʱ�����У����Ϊ15���ӣ�
	//��0.00��23.45
	BDSTime onedaytime[96];
	double C21_position_get[96][3];
	int nearnum;//���������������
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//ʵ��ʱ���ÿһ���ο�ʱ�̵Ĳ�ֵ
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 864; m < 888; m++)//��Ϊc21�ڹ㲥��������24������Ҫһ�����ȽϺ���һ����ӽ�,��Ŵ�864��888
		{
			if (abs(onedaytime[i].tos - s[m].TOE) < dif)
			{
				dif = abs(onedaytime[i].tos - s[m].TOE);
				nearnum = m;
			}
		}
		C21_position_get[i][0] = calculate_x(onedaytime[i], s[nearnum]);
		C21_position_get[i][1] = calculate_y(onedaytime[i], s[nearnum]);
		C21_position_get[i][2] = calculate_z(onedaytime[i], s[nearnum]);

	}
	//����ļ�
	ofstream file_result;//��������ļ���
	//��������ļ���ַ
	string name = "/C21������ά����.txt";
	name = outfile + name;
	file_result.open(name);//�����޸��ļ�·��
	//��ʼ�����ά���������ֵ
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//���ñ���С��λ������ȷ��mm��ȡ6λ
		file_result << C21_position_get[i][0] << "\t" << C21_position_get[i][1] << "\t" << C21_position_get[i][2] << "\n";
	}
	//�ر�����ļ���
	file_result.close();
	cout << "�����C21���ǹ㲥�����ó�����" << endl;
}

//�ӹ㲥�������C01λ��(GEO)
void C01_position(parameter s[1375], string outfile)
{
	//�������C01һ���λ�ã�����ĵ�33���ǣ�
	//����һ���ʱ�����У����Ϊ15���ӣ�
	//��0.00��23.45
	BDSTime onedaytime[96];
	double C01_position_get[96][3];
	int nearnum;//���������������
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//ʵ��ʱ���ÿһ���ο�ʱ�̵Ĳ�ֵ
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 397; m < 421; m++)//��Ϊc01�ڹ㲥��������24������Ҫһ�����ȽϺ���һ����ӽ�,��Ŵ�397��421
		{
			if (abs(onedaytime[i].tos - s[m].TOE) < dif)
			{
				dif = abs(onedaytime[i].tos - s[m].TOE);
				nearnum = m;
			}
		}
		C01_position_get[i][0] = calculate_x(onedaytime[i], s[nearnum]);
		C01_position_get[i][1] = calculate_y(onedaytime[i], s[nearnum]);
		C01_position_get[i][2] = calculate_z(onedaytime[i], s[nearnum]);

	}
	//����ļ�
	ofstream file_result;//��������ļ���
	//��������ļ���ַ
	string name = "/C01������ά����.txt";
	name = outfile + name;
	file_result.open(name);//�����޸��ļ�·��
	//��ʼ�����ά���������ֵ
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//���ñ���С��λ������ȷ��mm��ȡ6λ
		file_result << C01_position_get[i][0] << "\t" << C01_position_get[i][1] << "\t" << C01_position_get[i][2] << "\n";
	}
	//�ر�����ļ���
	file_result.close();
	cout << "�����C01���ǹ㲥�����ó�����" << endl;
}
