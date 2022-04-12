#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main() {
	
	srand((unsigned)time(NULL));

	Application::EnableVisualStyles;
	Pr1MaksIntel::MainForm form;

	game = new Game(form.gameFrame->Width, form.gameFrame->Height, form.turnFrame->Width, form.turnFrame->Height);

	Application::Run(% form);

	delete game;

}

