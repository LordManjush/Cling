#include "Editor.h"
#include "Directory.h"
#include "imgui/ImGuiFileDialog.h"
#include <iostream>
#include "imgui/imgui_stdlib.h"
#include <windows.h>
TextEditor Texteditor;
auto lang = TextEditor::LanguageDefinition::CPlusPlus();
std::string file_s;
std::string CurrentFilePath;
std::fstream file;
std::ofstream Save_file;
std::string path;
std::string code;
std::string folderPath;
TextEditor::ErrorMarkers errorMarkers;
std::string ProjectName;
#include <direct.h>
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

	if (ImGuiFileDialog::Instance()->Display("SelectFolder"))
	{

		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			folderPath = ImGuiFileDialog::Instance()->GetCurrentPath();

			printf(folderPath.c_str());
		}

		// close
		ImGuiFileDialog::Instance()->Close();

		ImGui::CloseCurrentPopup();

	}
	if (ImGuiFileDialog::Instance()->Display("SelectFile"))
	{

		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			file_s = ImGuiFileDialog::Instance()->GetCurrentFileName();
			path = ImGuiFileDialog::Instance()->GetFilePathName();
			CurrentFilePath = path;
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
			if (ImGui::MenuItem("Save")) 
			{
				printf(CurrentFilePath.c_str());
				Save_file.open(CurrentFilePath);
				code = Texteditor.GetText();
				printf("------------------------------------");
				if (Save_file.is_open())
				{
					Save_file << code.data();
					printf(code.c_str());
					Save_file.close();
				}
			}
			if (ImGui::MenuItem("Open"))
			{ 
				ImGuiFileDialog::Instance()->OpenDialog("SelectFile", "Select File", ".cpp,.hpp,.h,.glsl,.c,.py,.html", "./ ");
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				Texteditor.Undo();
			}
			if (ImGui::MenuItem("Redo"))
			{
				Texteditor.Redo();
			}
			if (ImGui::MenuItem("Select All"))
			{
				Texteditor.SelectAll();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		ImGuiFileDialog::Instance()->Close();
		ImGui::CloseCurrentPopup();
	}
}

void Cling::App::CodeEditor()
{
	ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("Editor", nullptr, flag);
	if (ImGui::Button("Run"))
	{
		system(CurrentFilePath.c_str());
	}
	Texteditor.Render("TextEditor");
	ImGui::End();
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
void Cling::App::ProjectView()
{
	ImGui::Begin("Solution Explorer");

	ImGui::End();
}

void Cling::App::Run()
{
	TaskBar();
	ProjectView();
	CodeEditor();
	Console();
}


