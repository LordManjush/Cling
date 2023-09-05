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
	ImGui::Begin("##Text Editor");
	Texteditor.Render("TextEditor");
	ImGui::End();
}
