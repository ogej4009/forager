#include <list>
#include <GameWin.h>
#include <GameRef.h>
#include <GameDebug.h>
#include <GameString.h>
#include <GameDevice.h>
#include "FrameUpdater.h"

// bin >> Debug >> x64 >> Game~
// ��µ��丮	$(SolutionDir)$(Platform)\$(Configuration)\	..\bin\$(Configuration)\$(PlatformTarget)\
// �߰����丮	$(Platform)\$(Configuration)\				..\bin\$(Configuration)\$(PlatformTarget)\$(ProjectName)\
// ����̸� $(ProjectName)
// FMOD

#pragma comment(lib, "GameBase.lib")
#pragma comment(lib, "GameEngine.lib")
#pragma comment(lib, "GameLogic.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameDebug::LeakCheckFunc();
	//_CrtSetBreakAlloc(1248);
	//new int(0); 

	S_Ptr<GameWin> NewWin = GameWin::CreateGameWin(L"GameWin");
	NewWin->Size({ 1024, 768 });
	GameDevice::CreateDevice(NewWin);
	// 32��Ʈ������ static�Լ��� stdcall�� �ƴ϶� cdecl�� �����ϵȴ�.
	GameWin::BaseLoop(FrameUpdater::Progress, FrameUpdater::Init);
}