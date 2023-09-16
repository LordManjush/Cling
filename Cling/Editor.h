#pragma once
#include <imgui.h>
#include <TextEditor.h>
#include "ImguiHelper.h"

namespace Cling
{
	struct App
	{
	private:
		void CodeEditor();
		void ProjectView();
		void TaskBar();
		void Console();
		std::vector<std::string>kwords = {
		"print", "find", "count", "clear", "vector", "string", "to_string",
		"puts", "max", "min", "even", "for_each", "map", "foldl", "sum",
		"product", "take", "take_while", "drop", "drop_while", "reduce",
		"filter", "join", "reverse", "generate_range", "concat", "collate",
		"zip_with", "zip", "call_exists", "retro", "throw", "Map", "Container",
		"Const_Range", "Function", "Map_Pair", "Object", "Range", "Type_Info",
		"class","if","do","while","else","var","auto","def","try",
		"catch", "attr", "break", "fun", "for"
		};
	public:
		void Init();
		void Run();
	};
}
