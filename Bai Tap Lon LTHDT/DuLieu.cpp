#pragma warning( disable : 4996 )
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "sqlite3.h"
#include "DuLieu.h"
#include "DoiTuong.h"
#include <boost\algorithm\string.hpp>
#include <boost\tokenizer.hpp>
using namespace std;


DuLieu::DuLieu()
{
	auto soBaoDanh = new string;
	auto nv = new string[4];
}


DuLieu::~DuLieu()
{
}


void DuLieu::layDuLieuNV(int stt)
{
	fstream a;
	a.open(R"(C:\Users\TungNguyen\Desktop\LTHDT-master\dangkynv-bk.csv)", ios::in);
	char b[500];
	for (int i = 1; i < 5000; i++)
	{
		a.getline(b, 500);
		if (i == stt){ break; }
	}
	std::vector<string> m;
	boost::split(m, b, boost::is_any_of(","));
	// bo sung de vecto du 21 thanh phan
	int bu = 21 - m.size();
	if (bu > 0)
	{
		for (int i = 0; i < bu; i++)
		{
			m.insert(m.end(), "NA");
		}
	}
	// nguyen vong
	soBaoDanh = boost::replace_all_copy(m[0], "\"", "");
	for (int k = 0, h = 1; k < 4; k++, h = h + 5)
	{
		nv[k] = boost::replace_all_copy(m[h], "\"", "");
	}
	int i, j;
	for (i = 0, j = 2; i < 12; i++, j++)
	{
		if (i == 3) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
		if (i == 6) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
		if (i == 9) { j += 2; toHop[i] = boost::replace_all_copy(m[j], "\"", ""); }
		else toHop[i] = boost::replace_all_copy(m[j], "\"", "");
	}
	// he so nhan
	for (i = 0, j = 5; i < 4; i++, j = j + 5)
	{
		if (boost::replace_all_copy(m[j], "\"", "") != "NA") diemNV[i][3] = stod(boost::replace_all_copy(m[j], "\"", ""));
		else{ diemNV[i][3] = 0;}
	}
}

void DuLieu::layDuLieuDiem(int stt)
{
	fstream a;
	char b[500];
	a.open(R"(C:\Users\TungNguyen\Desktop\LTHDT-master\csdl-bk.csv)", ios::in);
	for (int i = 1; i < 5000; i++)
	{
		a.getline(b, 500);
		if (i == stt){ break; }
	}
	std::vector<string> n;
	boost::split(n, b, boost::is_any_of(","));
	//loai bo ki tu "
	for each (string var in n)
	{
		var = boost::replace_all_copy(var, "\"", "");
	}

	doiTuong = n[4];
	khuVuc = n[3];
    uuTien = n[5];
	//dien bang diem
	for (int i = 0, j = 6; i < 13; i++, j++)
	{
		if (n[j] == "NA") bangDiem[i] = -1;
		else bangDiem[i] = stod(n[j]);
	}
	int i, j = 0;
	// bang diem cac nguyen vong
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[0][i] = layDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[1][i] = layDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[2][i] = layDiem(toHop[j]);
	}
	for (i = 0; i < 3; i++, j++)
	{
		diemNV[3][i] = layDiem(toHop[j]);
	}
	// s la bien diem cong
	double s=0;
	if (khuVuc == "\"KV1\"") { s +=1.5; }
	if (khuVuc == "\"KV2-NT\"") { s += 1.0; }
	if (khuVuc == "\"KV2\"") { s += 0.5; }
	if (doiTuong == "\"NDT1\"") { s += 2.0; }
	if (doiTuong == "\"NDT2\"") { s += 1.0; }
	// tinh diem uu tien
	if (uuTien == "\"Co\"") { diemCong = s / 3 + 1.0; }
	if (uuTien == "\"Khong\"") { diemCong = s / 3; }
	for (int i = 0; i < 4; i++)
	{
		double s;
		if (diemNV[i][3] == 1)
		{
			s = (diemNV[i][0] * 2 + diemNV[i][1] + diemNV[i][2]) / 4 + diemCong;
		}
		else
		{
			s = (diemNV[i][0] + diemNV[i][1] + diemNV[i][2]) / 3 + diemCong;
		}
		if (s >= 0){ diemXetTuyenNV[i] = round(s * 100) / 100; }
		else { diemXetTuyenNV[i] = -1; }
	}
}

double DuLieu::layDiem(string monHoc)
{
	if (monHoc == "Toan") return bangDiem[0];
	if (monHoc == "Van") return bangDiem[1];
	if (monHoc == "Ly") return bangDiem[2];
	if (monHoc == "Hoa") return bangDiem[3];
	if (monHoc == "Sinh") return bangDiem[4];
	if (monHoc == "Su") return bangDiem[5];
	if (monHoc == "Dia") return bangDiem[6];
	if (monHoc == "Anh") return bangDiem[7];
	if (monHoc == "Nga") return bangDiem[8];
	if (monHoc == "Phap") return bangDiem[9];
	if (monHoc == "Trung") return bangDiem[10];
	if (monHoc == "Duc") return bangDiem[11];
	if (monHoc == "Nhat") return bangDiem[12];
	if (monHoc == "NA") return -1;
}

