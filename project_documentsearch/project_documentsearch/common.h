#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<io.h>
#include<set>
#include "./sqlite3_lib/sqlite3.h"	
using namespace std;
#include<thread>
#include<chrono>
#include<windows.h>

#define DOC_DB  "doc.db"
#define DOC_TABLE "doc_tb"
#define  SQL_BUFFER_SIZE  256
#define MAX_TITLE_SIZE  128