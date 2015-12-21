// Tinh diem tuyen sinh.cpp : Defines the entry point for the console application.
//

//#pragma warning(disable:4996);
#include <fstream>
#include <iostream>
#include <string.h>
#include "DuLieu.h"
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string.hpp>
#include <vector>
#include "DoiTuong.h"
using namespace std;
using namespace boost;

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	// tao tao 1 doi tuong de thuc hien ket noi den database
	DoiTuong mydb("30.db");
	// ket noi toi database 30.db. Neu chua co se tu dong tao moi
	mydb.connect();
	// tao bang nvxt trong 30.db
	mydb.createDB();
	// khoi tao mang chua thong tin 100 thi sinh
	/*DoiTuong dsDoiTuong[100];*/
	DuLieu dsDuLieu[100];
	for (int i = 0; i < 100; i++)
	{
		//lay thong tin thi sinh tu so 3000 den 3099 trong danh sach
		//tinh toan diem cho thi sinh
		dsDuLieu[i].layDuLieuNV(3000 + i);
		dsDuLieu[i].layDuLieuDiem(3000 + i);
		/*dsDoiTuong[i].chiTietDoiTuong(dsDuLieu[i]);*/
		/*dsDoiTuong[i].tinhDiemNV(dsDuLieu[i]);*/
		//them vao csdl
		mydb.insertDB(dsDuLieu[i]);
		//hien thi thong tin da them vao
		mydb.selectDB(dsDuLieu[i]);
	}
	//ngat ket noi toi database
	mydb.disconnect();
	system("pause");
}


