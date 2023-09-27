#pragma once
#include <vector>
#include <string>
#include "ImguiHelper.h"

struct Languages
{
	bool CPlusPlus;
	bool Python;
	bool C;

	void SetUpLanguage(TextEditor& editor);
};
struct File
{
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