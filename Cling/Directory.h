#pragma once
#include <vector>
#include <string>


struct File
{
	char buf[255];
	std::string name = "NewFile";
	std::string code;
};
struct Folder
{
	int ID;
	char buf[255]{};
	std::vector<File> files;
	std::string name{ "NewFolder" };

};