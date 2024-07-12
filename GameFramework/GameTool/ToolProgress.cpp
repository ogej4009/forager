#include "pch.h"
#include "ToolProgress.h"
#include <GameWin.h>
#include <GameDevice.h>
#include <GameScene.h>
#include <GameInput.h>
#include <GameTime.h>
#include "MapSceneCom.h"

void ToolProgress::Init()
{
	GameScene::CreateScene<CMapSceneCom>(L"MAP");
	GameScene::CreateScene(L"SCENE");
	GameScene::ChangeScene(L"MAP");
}

void ToolProgress::Update()
{
	GameTime::Update();
	GameInput::Update();
	GameScene::Progress();
}

ToolProgress::ToolProgress()
{
}

ToolProgress::~ToolProgress()
{
}
