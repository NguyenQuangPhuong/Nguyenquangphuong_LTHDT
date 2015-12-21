//#pragma warning(disable:4996);
#include "DoiTuong.h"
#include "DuLieu.h"
#include <fstream>
#include <iostream>
#include <boost\algorithm\string.hpp>
#include <vector>
using namespace std;
using namespace boost;


DoiTuong::DoiTuong(string name)
{
	dbName = name;
	isConnected = false;
}

void DoiTuong::connect()
{
	if (sqlite3_open(dbName.c_str(), &dbFile) == SQLITE_OK)
	{
		isConnected = true;
	}
}

void DoiTuong::disconnect()
{
	if (isConnected == true)
	{
		sqlite3_close(dbFile);
		isConnected = false;
	}
}

void DoiTuong::createDB()
{
	sqlite3_exec(dbFile, "drop table nvxt;", NULL, NULL, NULL);
	sqlite3_exec(dbFile, "create table nvxt(sbd varchar(9), nvso int, manv varchar(4), diemxt double precision);", NULL, NULL, NULL);
}

void DoiTuong::insertDB(DuLieu dl)
{
	if (isConnected == true)
	{
		string querry;
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			if (dl.diemXetTuyenNV[i] >= 0) count++;
		}
		for (int i = 0; i < count; i++)
		{
			querry = "";
			querry += "insert into nvxt values('" + dl.soBaoDanh + "','" + to_string(i + 1) + "','" + dl.nv[i] + "','" + to_string(dl.diemXetTuyenNV[i]) + "');";
			sqlite3_exec(dbFile, querry.c_str(), NULL, NULL, NULL);
		}
	}
	else cout << " Error!" << endl;
}

void DoiTuong::selectDB(DuLieu dl)
{
	sqlite3_stmt *statement;
	string querry;
	querry += "select * from nvxt where sbd = '" + dl.soBaoDanh + "'";
	if (sqlite3_prepare_v2(dbFile, querry.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);
			if (result == SQLITE_ROW)
			{
				for (int col = 0; col < cols; col++)
				{
					string s = (char*)sqlite3_column_text(statement, col);
					cout << s << " ";
				}
				cout << endl;
			}
			else
			{
				break;
			}
		}
		sqlite3_finalize(statement);
	}
}