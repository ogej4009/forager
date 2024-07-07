#pragma once
#include <LogicCom.h>
#include <GameCamera.h>

class GameCamera;
class MainCam : public LogicCom
{
private:
	S_Ptr<GameCamera> m_Cam;

public:
	void Init() override;
	void Update() override;
	void DebugRender() override;

public:
	MainCam();
	~MainCam();
};