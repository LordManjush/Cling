#include "Directory.h"

bool C_Ok = false;
bool Cpp_Ok = false;
bool Pyton_Ok = false;
void Languages::SetUpLanguage(TextEditor& editor)
{
	if (CPlusPlus == true && Cpp_Ok == false)
	{
		C = false;
		Python = false;
		Cpp_Ok = true;
	}
	if (Python == true)
	{
		C = false;
		CPlusPlus = false;
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Python());
	}
	if (C == true)
	{
		Python = false;
		CPlusPlus = false;
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::C());
	}
}
