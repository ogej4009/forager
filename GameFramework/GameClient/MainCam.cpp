#include "MainCam.h"
#include <LogicData.h>
#include <GameInput.h>
#include <GameTransform.h>
#include "PlayScene.h"
#include "Hero.h"


MainCam::MainCam() {}
MainCam::~MainCam() {}

void MainCam::Init()
{
	m_Cam = AddCom<GameCamera>(10
		, (UINT)RENDER_ORDER::RO_LEVEL
		, (UINT)RENDER_ORDER::RO_PLAYER
		, (UINT)RENDER_ORDER::RO_MONSTER
		, (UINT)RENDER_ORDER::RO_ITEM
		, (UINT)RENDER_ORDER::RO_UI);
	m_Cam->Size(LogicData::ScreenSize);
}

void MainCam::Update()
{
	CVector Pos = PlayScene::g_Hero->Trans()->LPOS();
	Pos.z = -10;
	m_Cam->Trans()->LPOS(Pos);
}

void MainCam::DebugRender()
{
}