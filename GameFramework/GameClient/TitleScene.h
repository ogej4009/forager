#pragma once
#include <GameScene.h>
#include <GameMath.h>

class TitleScene : public GameScene::CSceneCom
{
public:
	void Loading() override;
	void Update() override;
	void DebugRender() override;

public:
	TitleScene();
	~TitleScene();
};