#include "FrameUpdater.h"
#include <GameWin.h>
#include <GameDevice.h>
#include <GameInput.h>
#include <GameTime.h>
#include <GameDebug.h>
#include <GameScene.h>
#include "TitleScene.h"
#include "PlayScene.h"
//#include "EndScene.h"

FrameUpdater::FrameUpdater() {}
FrameUpdater::~FrameUpdater() {}

void FrameUpdater::Init()
{
	GameScene::CreateScene<TitleScene>(L"TITLE");
	GameScene::CreateScene<PlayScene>(L"PLAY");
	//GameScene::CreateScene<EndScene>(L"END");
	GameScene::ChangeScene(L"PLAY");
}

void FrameUpdater::Progress()
{
	GameTime::Update();
	GameInput::Update();
	GameScene::Progress();
}
