/*
Date: 2020.12.18
Author: XODRJh
*/
#include <iostream>
using namespace std;
#include <fstream>
#include <string>

string line;
string old_str = "    yyerrstatus--;";
string new_str = "  Process(key);                     ";

int main()
{
	fstream fp;
	fp.open("Syntax.tab.c");
	while(!fp.eof()) {
		getline(fp, line);
		if(!line.compare(old_str)) {
			fp.seekg(-8, ios::cur);
			fp << new_str;
			break;
		}
			
	}
	fp.close();
	return 0;
}
