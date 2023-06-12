#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include "parameter.h"
#include "statement.h"
#include <cmath>
using namespace std;
int main()
{
	//声明所有的星历对象数组
	parameter s[1375];

	//规定文件地址
	string broadcastfile = "D:/北斗卫星位置计算/北斗卫星星历/brdm0010.20p";//广播星历文件位置
	string outfile = "D:/北斗卫星位置计算/北斗卫星位置数据";//输出文件位置

	//读取广播星历
	readeph(s, broadcastfile);
	//导出位置文件
	C7_position(s, outfile);
	C21_position(s, outfile);
	C01_position(s, outfile);
	cout << "已输出C01卫星轨道平面坐标" << endl;
	cout << "已输出C07卫星轨道平面坐标" << endl;
	cout << "已输出C21卫星轨道平面坐标" << endl;
	return 0;
}
