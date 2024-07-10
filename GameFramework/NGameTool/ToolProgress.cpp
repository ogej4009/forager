#include "pch.h"
#include "ToolProgress.h"

#include <GameWin.h>
#include <GameDevice.h>
#include <GameScene.h>
#include <GameInput.h>
#include <GameTime.h>
#include "MapSceneCom.h"



CToolProgress::CToolProgress()
{
}

CToolProgress::~CToolProgress()
{
}



void CToolProgress::Init()
{
	CGameScene::CreateScene<CMapSceneCom>(L"MAP");
	CGameScene::CreateScene(L"SCENE");
	CGameScene::ChangeScene(L"MAP");
}

void CToolProgress::Progress()
{
	CGameTime::Update();
	CGameInput::Update();
	CGameScene::Progress();
}

