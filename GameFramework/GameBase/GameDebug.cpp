#include "GameDebug.h"
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

GameDebug::GameDebug(){}
GameDebug::~GameDebug(){}

void GameDebug::LeakCheckFunc()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1248);
}

void GameDebug::OpenConsole()
{
	if (0 != AllocConsole())
	{
		FILE* Out;
		FILE* In;
		freopen_s(&Out, "CONOUT$", "wt", stdout);
		freopen_s(&In, "CONIN$", "r", stdin);
		std::wcout.imbue(std::locale("kor"));
		std::wcout << L"CONSOLE OPEN" << std::endl;
	}
}