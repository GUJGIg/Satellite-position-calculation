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

//从广播星历获得C07位置(IGSO)
void C7_position(parameter s[1375], string outfile)
{
	//输出卫星C07一天的位置（总体的第39颗星）
	//创建一天的时间序列（间隔为15分钟）
	//从0.00到23.45
	BDSTime onedaytime[96];
	double C7_position_get[96][3];
	int nearnum;//相距最近的卫星序号
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//实际时间和每一个参考时刻的差值
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 553; m < 577; m++)//因为c07在广播星历中有24个，需要一个个比较和哪一个最接近,序号从553到577
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
	//输出文件
	ofstream file_result;//创建输出文件流
	//创建输出文件地址
	string name = "/C07卫星三维坐标.txt";
	name = outfile + name;
	file_result.open(name);//自行修改文件路径
	//开始输出二维数组里的数值
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//设置保留小数位数，精确到mm，取6位
		file_result << C7_position_get[i][0] << "\t" << C7_position_get[i][1] << "\t" << C7_position_get[i][2] << "\n";
	}
	//关闭输出文件流
	file_result.close();
	cout << "已输出C07卫星广播星历得出坐标" << endl;
}
//从广播星历获得C21位置(MEO)
void C21_position(parameter s[1375], string outfile)
{
	//输出卫星C21一天的位置（总体的第52颗星）
	//创建一天的时间序列（间隔为15分钟）
	//从0.00到23.45
	BDSTime onedaytime[96];
	double C21_position_get[96][3];
	int nearnum;//相距最近的卫星序号
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//实际时间和每一个参考时刻的差值
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 864; m < 888; m++)//因为c21在广播星历中有24个，需要一个个比较和哪一个最接近,序号从864到888
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
	//输出文件
	ofstream file_result;//创建输出文件流
	//创建输出文件地址
	string name = "/C21卫星三维坐标.txt";
	name = outfile + name;
	file_result.open(name);//自行修改文件路径
	//开始输出二维数组里的数值
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//设置保留小数位数，精确到mm，取6位
		file_result << C21_position_get[i][0] << "\t" << C21_position_get[i][1] << "\t" << C21_position_get[i][2] << "\n";
	}
	//关闭输出文件流
	file_result.close();
	cout << "已输出C21卫星广播星历得出坐标" << endl;
}

//从广播星历获得C01位置(GEO)
void C01_position(parameter s[1375], string outfile)
{
	//输出卫星C01一天的位置（总体的第33颗星）
	//创建一天的时间序列（间隔为15分钟）
	//从0.00到23.45
	BDSTime onedaytime[96];
	double C01_position_get[96][3];
	int nearnum;//相距最近的卫星序号
	for (int i = 0; i < 96; i++)
	{
		double dif = 1000000;//实际时间和每一个参考时刻的差值
		CalendarTime tem;
		tem.year = 2020;
		tem.mon = 1;
		tem.day = 2;
		tem.hour = int(i / 4);
		tem.min = (i % 4) * 15;
		tem.sec = 0;
		onedaytime[i] = MJD2BDSTime(CalendarTime2MJD(tem));
		for (int m = 397; m < 421; m++)//因为c01在广播星历中有24个，需要一个个比较和哪一个最接近,序号从397到421
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
	//输出文件
	ofstream file_result;//创建输出文件流
	//创建输出文件地址
	string name = "/C01卫星三维坐标.txt";
	name = outfile + name;
	file_result.open(name);//自行修改文件路径
	//开始输出二维数组里的数值
	for (int i = 0; i < 96; i++)
	{
		file_result.flags(ios::fixed);
		file_result.precision(6);//设置保留小数位数，精确到mm，取6位
		file_result << C01_position_get[i][0] << "\t" << C01_position_get[i][1] << "\t" << C01_position_get[i][2] << "\n";
	}
	//关闭输出文件流
	file_result.close();
	cout << "已输出C01卫星广播星历得出坐标" << endl;
}
