#pragma once
#include <GameScene.h>


class Hero;
class RenderTileBase;
class PlayScene : public GameScene::CSceneCom
{
public:
	S_Ptr<GameCamera> m_Cam;
	S_Ptr<GameCamera> m_UICam;
	S_Ptr<GameActor> m_CursorActor;
	S_Ptr<GameActor> m_InvenActor;
	static S_Ptr<Hero> g_Hero;
	static S_Ptr<RenderTileBase> g_GroundTile;

public:
	static bool g_IsUIOn;

public:
	void Loading() override;
	void Update() override;
	void DebugRender() override;

public:
	PlayScene();
	~PlayScene();
};

