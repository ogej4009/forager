#pragma once
#include <GameScene.h>

class GameCamera;
class RenderTileBase;
class RenderTileSub;
class RenderTree;
class RenderMisc;
class RenderCW;


class CMapSceneCom : public GameScene::CSceneCom
{
public:


	S_Ptr<GameCamera> MapCam; // 카메라
	static S_Ptr<RenderTileBase> R_T; // 타일1
	static S_Ptr<RenderTileSub> R_TS; // 타일B
	static S_Ptr<RenderTree> R_TREE;
	static S_Ptr<RenderMisc> R_MISC;
	static S_Ptr<RenderCW> R_CW;

	static int m_TileSetIdx;



public:
	void Loading() override;
	void Update() override;
	void DebugRender() override;

	void CraeteTileSet(unsigned int _Idx);



public:
	CMapSceneCom();
	~CMapSceneCom();
};

