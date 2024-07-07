#include "TitleScene.h"
#include <LogicData.h>
#include <GameInput.h>
#include <GameActor.h>
#include <GameTransform.h>
#include <GameRender.h>
#include <GameCamera.h>
#include <GameCol.h>
#include <GameDirectory.h>
#include <GameSprRender.h>
#include <GameTexture.h>
#include <GameSprite.h>
#include <GameAni.h>
#include <GameFrameDebug.h>
#include <RenderTileBase.h>
#include <RenderTileSub.h>
#include <RenderTree.h>
#include <RenderMisc.h>
#include <RenderCW.h>
#include "Hero.h"
#include "MainCam.h"
#include "Backdrop.h"


TitleScene::TitleScene() {}
TitleScene::~TitleScene() {}

void TitleScene::Loading()
{
	GameInput::CreateKey(L"START", VK_SPACE);

	GameDirectory m_Dir;
	m_Dir.MoveParent(L"GameFramework");
	m_Dir.Move(L"Res");
	m_Dir.Move(L"Tex");

	GameTexture::Load(m_Dir.CreateGameFilePath(L"MainBackground.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"MainBackground.png"), 1, 1);
	
	GameTexture::Load(m_Dir.CreateGameFilePath(L"MainBackgroundr.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"MainBackgroundr.png"), 1, 1);
	
	GameTexture::Load(m_Dir.CreateGameFilePath(L"ForagerLogo.png"));
	GameSprite::Create(m_Dir.CreateGameFilePath(L"ForagerLogo.png"), 1, 1);

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		S_Ptr<MainCam> NewMainCam = NewActor->AddCom<MainCam>();
		NewActor->Trans()->LPOS({ 0.0f, 0.0f, -10.0f });
		S_Ptr<GameCamera> NewCam = NewActor->AddCom<GameCamera>(10
			, (UINT)RENDER_ORDER::RO_LEVEL
			, (UINT)RENDER_ORDER::RO_PLAYER
			, (UINT)RENDER_ORDER::RO_MONSTER
			, (UINT)RENDER_ORDER::RO_MISC);
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LSCALE({ 1024.0f,768.0f,0.0f });
		S_Ptr<Backdrop> NewBackdrop = NewActor->AddCom<Backdrop>();
		NewBackdrop->SetSprite(L"MainBackground.png");
		NewBackdrop->SetPos({ -1024.0f, 0.0f, 0.0f });
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LSCALE({ 1024.0f,768.0f,0.0f });
		S_Ptr<Backdrop> NewBackdrop = NewActor->AddCom<Backdrop>();
		NewBackdrop->SetSprite(L"MainBackgroundr.png");
		NewBackdrop->SetPos({ -12.0f, 0.0f, 0.0f });
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LSCALE({ 1024.0f, 768.0f, 0.0f });
		S_Ptr<Backdrop> NewBackdrop = NewActor->AddCom<Backdrop>();
		NewBackdrop->SetSprite(L"MainBackground.png");
		NewBackdrop->SetPos({ 1000.0f, 0.0f, 0.0f });
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		NewActor->Trans()->LSCALE({ 1024.0f, 768.0f, 0.0f });
		S_Ptr<Backdrop> NewBackdrop = NewActor->AddCom<Backdrop>();
		NewBackdrop->SetSprite(L"MainBackgroundr.png");
		NewBackdrop->SetPos({ 2012.0f, 0.0f, 0.0f });
	}

	{
		S_Ptr<GameActor> NewActor = CreateActor();
		S_Ptr<GameSprRender> NewRender = NewActor->AddCom<GameSprRender>();
		NewRender->Sprite(L"ForagerLogo.png");
		NewActor->Trans()->LSCALE({ 640.0f, 345.6f, 0.0f });
		NewActor->Trans()->LPOS({ 0.0f, 0.0f, -1.0f });
	}
}

void TitleScene::Update()
{
	if (true == GameInput::Press(L"START"))
	{
		GameScene::ChangeScene(L"PLAY");
	}
}

void TitleScene::DebugRender()
{
}