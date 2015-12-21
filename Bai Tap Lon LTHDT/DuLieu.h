#pragma once
#include <boost\algorithm\string.hpp>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "sqlite3.h"
//#include "DoiTuong.h"
#include <exception>
using namespace std;
class DuLieu
{
public:
	string soBaoDanh;
	string khuVuc;
	string doiTuong;
	string uuTien;
	string nv[4];
	string toHop[12];
	double diemXetTuyenNV[4];
	double diemCong;
	double bangDiem[13];
	double diemNV[4][4];

	//Phuong thuc khoi tao
	DuLieu();
	
	//Phuong thuc huy bo
	~DuLieu();


	//Doc du lieu thong tin nguyen vong tu file Excel(dangkynv-bk) lay ra du lieu nv va diem nv cua tung mon tung nv cua tung doi tuong
	void layDuLieuNV(int stt);

	//Doc du lieu thong tin thi sinh tu file Excel(csdl-bk) lay ra du lieu sbd,kv,uu tien,doi tuong va tinh diem xet tuyen cho tung doi tuong
	void layDuLieuDiem(int stt);

	//Lay ra du lieu bang diem cua tung doi tuong
	double layDiem(string monHoc);

};