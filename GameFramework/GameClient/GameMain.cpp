#include <list>
#include <GameWin.h>
#include <GameRef.h>
#include <GameDebug.h>
#include <GameString.h>
#include <GameDevice.h>
#include "FrameUpdater.h"

// bin >> Debug >> x64 >> Game~
// 출력디렉토리	$(SolutionDir)$(Platform)\$(Configuration)\	..\bin\$(Configuration)\$(PlatformTarget)\
// 중간디렉토리	$(Platform)\$(Configuration)\				..\bin\$(Configuration)\$(PlatformTarget)\$(ProjectName)\
// 대상이름 $(ProjectName)
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
	// 32비트에서는 static함수가 stdcall이 아니라 cdecl로 컴파일된다.
	GameWin::BaseLoop(FrameUpdater::Progress, FrameUpdater::Init);
}