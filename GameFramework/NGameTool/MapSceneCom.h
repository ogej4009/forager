#pragma once
#include <GameScene.h>

class CCam;
class CTileRender;
class CTileBRender;
class CImgRender;
class CTreeRender;
class CObjRender;
class CWRender;


class CMapSceneCom : public CGameScene::CSceneCom
{
public:


	CPTR<CCam> MapCam; // 카메라
	static CPTR<CTileRender> TR; // 타일1
	static CPTR<CTileBRender> TBR; // 타일B
	static CPTR<CTreeRender> TOR;
	static CPTR<CObjRender> OR;
	static CPTR<CWRender> WR;

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

