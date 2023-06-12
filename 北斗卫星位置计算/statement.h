#pragma once
//用来声明
//声明函数
void readeph(parameter s[1392], string broadcastfile);
MJD CalendarTime2MJD(CalendarTime calT);
BDSTime MJD2BDSTime(MJD mjd);
double calculate_x(BDSTime dstBDST, parameter ep);
double calculate_y(BDSTime dstBDST, parameter ep);
double calculate_z(BDSTime dstBDST, parameter ep);
void C7_position(parameter s[1392], string outfile);
void C21_position(parameter s[1392], string outfile);
void C01_position(parameter s[1392], string outfile);