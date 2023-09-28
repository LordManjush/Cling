#include "Editor.h"
#include <iostream>
#include <direct.h>
#include <windows.h>

TextEditor Texteditor;
//For showing the current file name
std::string file_s;
//Path used for loading file to editor
std::string CurrentFilePath;

std::fstream Selectfile;
std::fstream newFileOpen;
std::fstream OnOpenNewFile;
std::ofstream Save_file;


std::string path;

std::string code;

//New file
std::string folderpath;
std::string NewFileName;

bool OnOpen = false;
void Cling::App::Init()
{
	Texteditor.SetReadOnly(false);
	Texteditor.SetPalette(Texteditor.GetDarkPalette());
	Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
	OnOpen = true;
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
			CurrentFilePath = path;
			// action
			Selectfile.open(path, std::ios_base::in);
			code = "";
			if (Selectfile.is_open()) {   //checking whether the file is open
				std::string tp;
				while (getline(Selectfile, tp)) { //read data from file object and put it into string.
					code = code + tp + "\n";
				}
				Selectfile.close(); //close the file object.
			}
			Texteditor.SetText(code);
		}
		// close
		ImGuiFileDialog::Instance()->Close();

		ImGui::CloseCurrentPopup();

	}
	if (ImGui::IsKeyPressed(ImGuiKey_Escape))
	{
		ImGuiFileDialog::Instance()->Close();
		ImGui::CloseCurrentPopup();
	}
	if (OnOpen == true)
	{

		if (ImGui::BeginPopupModal("Open/Create File"))
		{
			if (ImGui::BeginPopupModal("Create File"))
			{
				if (ImGuiFileDialog::Instance()->Display("SelectFolder"))
				{
					// action if OK
					if (ImGuiFileDialog::Instance()->IsOk())
					{
						folderpath = ImGuiFileDialog::Instance()->GetCurrentPath();
					}

					// close
					ImGuiFileDialog::Instance()->Close();
				}
				ImGui::InputText("##FileName", &NewFileName);

				if (ImGui::Button("SelectFolder"))
				{
					ImGuiFileDialog::Instance()->OpenDialog("SelectFolder", "Select Folder", nullptr, ".\ ");
				}
				std::string temppath = folderpath + "\\" + NewFileName;
				ImGui::Text(temppath.c_str());


				if (ImGui::Button("Create") && folderpath.length() >= 3 && NewFileName.length() > 0)
				{
					std::ofstream file(folderpath + "\\" + NewFileName);
					CurrentFilePath = folderpath + "\\" + NewFileName;
					// action
					OnOpenNewFile.open(CurrentFilePath, std::ios_base::in);
					code = "";
					if (OnOpenNewFile.is_open()) {   //checking whether the file is open
						std::string g;
						while (getline(OnOpenNewFile, g))
						{ //read data from file object and put it into string.
							code = code + g + "\n";
						}
						OnOpenNewFile.close(); //close the file object.
					}
					Texteditor.SetText(code);
					file_s = NewFileName;
					NewFileName = "";
					folderpath = "";
					OnOpen = false;
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::IsKeyPressed(ImGuiKey_Escape))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			if (ImGuiFileDialog::Instance()->Display("OpenFile"))
			{

				// action if OK
				if (ImGuiFileDialog::Instance()->IsOk())
				{
					file_s = ImGuiFileDialog::Instance()->GetCurrentFileName();
					path = ImGuiFileDialog::Instance()->GetFilePathName();
					CurrentFilePath = path;
					// action
					Selectfile.open(path, std::ios_base::in);
					code = "";
					if (Selectfile.is_open()) {   //checking whether the file is open
						std::string tp;
						while (getline(Selectfile, tp)) { //read data from file object and put it into string.
							code = code + tp + "\n";
						}
						Selectfile.close(); //close the file object.
					}
					Texteditor.SetText(code);
					OnOpen = false;
				}

				// close
				ImGuiFileDialog::Instance()->Close();

				ImGui::CloseCurrentPopup();

			}
			if (ImGui::Button("New File"))
			{
				ImGui::OpenPopup("Create File");
				
			}
			if (ImGui::Button("Open"))
			{
				ImGuiFileDialog::Instance()->OpenDialog("OpenFile", "Open File", ".cpp, .c, .h, .hpp, .rs, .cs, .txt, .py, .js, .html, .sql, .jar, .bat, .shell, glsl, hlsl", "./ ");
			}
			ImGui::EndPopup();

		}
		ImGui::OpenPopup("Open/Create File");
	}
	
}

void Cling::App::CodeEditor()
{
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar);
#pragma region Menu
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save") && CurrentFilePath.length() > 2)
			{
				Save_file.open(CurrentFilePath);
				code = Texteditor.GetText();
				if (Save_file.is_open())
				{
					Save_file << code.data();
					Save_file.close();
				}

			}
			if (ImGui::MenuItem("Open"))
			{
				ImGuiFileDialog::Instance()->OpenDialog("SelectFile", "Select File", ".cpp, .c, .h, .hpp, .rs, .cs, .txt, .py, .js, .html, .sql, .jar, .bat, .shell, glsl, hlsl", "./ ");
			}
			// Maybe some other stuff here.
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			bool ro = Texteditor.IsReadOnly();

			if (ImGui::MenuItem("Undo", "Ctrl-Z", nullptr, !ro && Texteditor.CanUndo()))
			{
				Texteditor.Undo();
			}
			if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && Texteditor.CanRedo()))
			{
				Texteditor.Redo();
			}
			ImGui::Separator();

			if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, Texteditor.HasSelection()))
			{
				Texteditor.Copy();
			}
			if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && Texteditor.HasSelection()))
			{
				Texteditor.Cut();
			}
			if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && Texteditor.HasSelection()))
			{
				Texteditor.Delete();
			}
			if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
			{
				Texteditor.Paste();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Select all", nullptr, nullptr))
			{
				Texteditor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(Texteditor.GetTotalLines(), 0));
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Language"))
		{
			if (ImGui::MenuItem("C++"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
			}
			if (ImGui::MenuItem("C"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::C());
			}
			if (ImGui::MenuItem("Python"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Python());
			}
			if (ImGui::MenuItem("Lua"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
			}

			if (ImGui::MenuItem("GLSL"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
			}
			if (ImGui::MenuItem("HLSL"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::HLSL());
			}
			if (ImGui::MenuItem("SQL"))
			{
				Texteditor.SetLanguageDefinition(TextEditor::LanguageDefinition::SQL());
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Preferences"))
		{
			if (ImGui::MenuItem("Dark Mode"))
			{
				ImGui::Helper::DarkMode();
				Texteditor.SetPalette(Texteditor.GetDarkPalette());
			}
			if (ImGui::MenuItem("Light Mode"))
			{
				ImGui::Helper::LightMode();
				Texteditor.SetPalette(Texteditor.GetLightPalette());

			}
			if (ImGui::MenuItem("Retro Mode"))
			{
				ImGui::Helper::RetroMode();
				Texteditor.SetPalette(Texteditor.GetRetroBluePalette());
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::Text("Made With Opengl and imgui");
			// Maybe some other stuff here.
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::Button("Run"))
	{
		system(CurrentFilePath.c_str());
	}
	ImGui::SameLine();
	if (ImGui::Button("Save") && CurrentFilePath.length() > 2)
	{
		Save_file.open(CurrentFilePath);
		code = Texteditor.GetText();
		if (Save_file.is_open())
		{
			Save_file << code.data();
			Save_file.close();
		}
	}
	ImGui::SameLine();
	if (ImGui::BeginPopupModal("New File"))
	{
		if (ImGuiFileDialog::Instance()->Display("SelectFolder"))
		{
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				folderpath = ImGuiFileDialog::Instance()->GetCurrentPath();
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}
		ImGui::InputText("##FileName", &NewFileName);

		if (ImGui::Button("SelectFolder"))
		{
			ImGuiFileDialog::Instance()->OpenDialog("SelectFolder", "Select Folder", nullptr, ".\ ");
		}
		std::string temppath = folderpath + "\\" + NewFileName;
		ImGui::Text(temppath.c_str());


		if (ImGui::Button("Create") && folderpath.length() >= 3 && NewFileName.length() > 0)
		{
			std::ofstream file(folderpath + "\\" + NewFileName);
			CurrentFilePath = folderpath + "\\" + NewFileName;
			// action
			newFileOpen.open(CurrentFilePath, std::ios_base::in);
			code = "";
			if (newFileOpen.is_open()) {   //checking whether the file is open
				std::string g;
				while (getline(newFileOpen, g))
				{ //read data from file object and put it into string.
					code = code + g + "\n";
				}
				newFileOpen.close(); //close the file object.
			}
			Texteditor.SetText(code);
			NewFileName = "";
			folderpath = "";
			ImGui::CloseCurrentPopup();
		}
		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	if (ImGui::Button("New"))
	{
		ImGui::OpenPopup("New File");
	}
	ImGui::SameLine();
	if (ImGui::Button("Open"))
	{
		ImGuiFileDialog::Instance()->OpenDialog("SelectFile", "Select File", ".cpp, .c, .h, .hpp, .rs, .cs, .txt, .py, .js, .html, .sql, .jar, .bat, .shell", "./ ");
	}
	if (file_s.length() > 0)
	{
		ImGui::SameLine();
		ImGui::Text("Selected File - ");
		ImGui::SameLine();
		ImGui::Text(file_s.c_str());
	}
	ImGui::SameLine();
	ImGui::Text(Texteditor.GetLanguageDefinition().mName.c_str());
#pragma endregion
	Texteditor.Render("TextEditor");
	ImGui::End();
}
void Cling::App::Run()
{	
	TaskBar();
	CodeEditor();
}


