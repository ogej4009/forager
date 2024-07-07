#pragma once
#include <crtdbg.h>

class GameDebug
{
public:
	static void LeakCheckFunc();
	static void OpenConsole();

private:
	GameDebug();
	~GameDebug();
};