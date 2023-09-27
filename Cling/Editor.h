#pragma once
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
		void Properties();
	public:
		void Init();
		void Run();
	};
}
