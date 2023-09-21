#include "Editor.h"
#include "Directory.h"
#include "imgui/ImGuiFileDialog.h"
#include <iostream>

TextEditor Texteditor;
auto lang = TextEditor::LanguageDefinition::CPlusPlus();
std::string file_s;
std::fstream file;
std::string path;
std::string code;
void Cling::App::Init()
{
	Texteditor.SetLanguageDefinition(lang);
	Texteditor.SetReadOnly(false);
	Texteditor.SetPalette(TextEditor::GetDarkPalette());

}

void Cling::App::TaskBar()
{
	ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".cpp", ImVec4(1.0f, 0.0f, 1.0f, 0.9f));
	ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".h", ImVec4(0.0f, 1.0f, 1.0f, 0.9f));
	ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".glsl", ImVec4(0.0f, 1.0f, 1.0f, 0.9f));
	ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".c", ImVec4(0.0f, 1.0f, 1.0f, 0.9f));
	ImGuiFileDialog::Instance()->SetFileStyle(IGFD_FileStyleByExtention, ".py", ImVec4(0.0f, 1.0f, 1.0f, 0.9f));

	if (ImGuiFileDialog::Instance()->Display("SelectFile"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			file_s = ImGuiFileDialog::Instance()->GetCurrentFileName();
			path = ImGuiFileDialog::Instance()->GetFilePathName();
			// action
			file.open(path, std::ios_base::in);
			code = "";
			if (file.is_open()) {   //checking whether the file is open
				std::string tp;
				while (getline(file, tp)) { //read data from file object and put it into string.
					code = code + tp + "\n";
				}
				file.close(); //close the file object.
			}
			Texteditor.SetText(code);
		}

		// close
		ImGuiFileDialog::Instance()->Close();

		ImGui::CloseCurrentPopup();

	}
	if (ImGui::BeginMainMenuBar())
	{

		if (ImGui::BeginMenu("File"))
		{
			file.open(path, std::ios_base::out);
			if (ImGui::MenuItem("Save")) 
			{
				if (file.is_open())
				{
					file << code.data();
					file.close();
				}
			}
			if (ImGui::MenuItem("Open"))
			{ 
				ImGuiFileDialog::Instance()->OpenDialog("SelectFile", "Select File", ".hpp,.h,.cpp,.glsl,.c,.py", "./ ");
			}
			ImGui::EndMenu();
		}
	
		ImGui::EndMainMenuBar();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		ImGuiFileDialog::Instance()->Close();
	}
}

void Cling::App::CodeEditor()
{
	ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar;
	ImGui::Begin("Editor", nullptr, flag);
	Texteditor.Render("TextEditor");
	ImGui::End();
}
std::vector<Folder> folders;
Folder* selectedFolder = nullptr;

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
	Console();
}

