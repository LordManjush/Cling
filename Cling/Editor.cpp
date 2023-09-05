#include "Editor.h"


TextEditor Texteditor;
auto lang = TextEditor::LanguageDefinition::CPlusPlus();
void Cling::Init()
{
	Texteditor.SetLanguageDefinition(lang);
	Texteditor.SetReadOnly(false);
	Texteditor.SetPalette(TextEditor::GetDarkPalette());

}
void Cling::CodeEditor()
{
	ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration && ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("Text Editor", nullptr, flag);
	Texteditor.Render("TextEditor");
	ImGui::End();
}
