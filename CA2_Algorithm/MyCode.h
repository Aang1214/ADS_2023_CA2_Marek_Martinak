#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
enum TypeEnum
{
    dir,
    file,
    name,
    length,
    type,


};

struct DataMemory {
    string name;
    string length;
    string type;
    TypeEnum typeEnum;

    DataMemory(TypeEnum tag) {
		name = "";
		length = "";
		type = "";
		typeEnum = tag;
	}
};