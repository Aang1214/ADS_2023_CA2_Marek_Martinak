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

    DataMemory(string name, string length, string type, TypeEnum tag) {
		this->name = name;
		this->length = length;
		this->type = type;
		this->typeEnum = tag;
	}
    DataMemory() {
		name = "";
		length = "";
		type = "";
		typeEnum = dir;
	}
};
