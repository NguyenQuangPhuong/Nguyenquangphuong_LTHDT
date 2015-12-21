#pragma once
#include <boost\algorithm\string.hpp>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "sqlite3.h"
#include "DuLieu.h"
using namespace std;
using namespace boost;

class DoiTuong
{
public:
	bool isConnected;
	string dbName;
	sqlite3* dbFile;

	DoiTuong(string name);

	//Ket noi vao database
	void connect();

	//disconnect
	void disconnect();

	//Tao bang du lieu
	void createDB();

	//insert du lieu vao bang vua tao
	void insertDB(DuLieu dl);

	//select du lieu tu bang ra
	void selectDB(DuLieu dl);
};