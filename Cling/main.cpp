#pragma region Includes
#pragma region Imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#pragma endregion
#pragma region GLFW and GLAD
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#pragma endregion
#pragma region Extra
#include <iostream>
#include "Editor.h"
#pragma endregion
#pragma endregion

Cling::App app;
int main()
{
#pragma region Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Cling", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#pragma endregion
	
#pragma region Initialize Imgui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::Helper::DarkMode();
	auto fancyFont = io.Fonts->AddFontFromFileTTF(
		"./Data/Font/Montserrat-Regular.ttf", 20);
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 100");
#pragma endregion

	
	app.Init();
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
#pragma region Clear, Imgui Frame, PushFont and Docking
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGui::DockSpaceOverViewport();
		ImGui::PushFont(fancyFont);
#pragma endregion

		app.Run();

#pragma region Render, Pop, Swap, Poll
		ImGui::PopFont();
		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
#pragma endregion
	}
#pragma region Destroy

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
#pragma endregion
	return 0;
}