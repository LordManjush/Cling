#include "Editor.h"


TextEditor Texteditor;
auto lang = TextEditor::LanguageDefinition::CPlusPlus();

void Cling::App::Init()
{
	Texteditor.SetLanguageDefinition(lang);
	Texteditor.SetReadOnly(false);
	Texteditor.SetPalette(TextEditor::GetDarkPalette());

}
void Cling::App::CodeEditor()
{
	ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration && ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("Text Editor", nullptr, flag);
	Texteditor.Render("TextEditor");
	ImGui::End();
}

void Cling::App::ProjectView()
{
	ImGui::Begin("Solution Explorer", nullptr);
	ImGui::End();
}

void Cling::App::TaskBar()
{
	if (ImGui::BeginMainMenuBar())
	{

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Project", "Ctrl+N")) {
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
			}
			if (ImGui::MenuItem("Build", "Ctrl+B")) {
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Cling::App::Console()
{
	ImGui::Begin("Console", nullptr);
	if (ImGui::Button("Errors"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("Logs"))
	{

	}
	ImGui::SameLine();
	if (ImGui::Button("Build Errors"))
	{

	}
	ImGui::End();
}

void Cling::App::Run()
{
	TaskBar();
	CodeEditor();
	ProjectView();
	Console();
}

