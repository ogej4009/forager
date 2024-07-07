#pragma once
#include <GameRef.h>
#include <map>
#include <list>

class GameRender;
class GameCamera;
class GameScene;
class GameRenderMgr final
{
	friend GameRender;
	friend GameCamera;
	friend GameScene;

private:
	GameScene* m_pScene;
	GameCamera* m_MainCam;
	std::map<unsigned int, S_Ptr<GameCamera>> m_AllCam;
	std::map<unsigned int, std::list<S_Ptr<GameRender>>> m_AllRender;
	std::list<S_Ptr<GameRender>>::iterator RStartIter;
	std::list<S_Ptr<GameRender>>::iterator REndIter;

public:
	GameCamera* MainCam()
	{
		return m_MainCam;
	}

public:
	std::map<unsigned int, std::list<S_Ptr<GameRender>>>::iterator GroupIter;

private:
	void PushCam(GameCamera* _Cam);
	void PushRender(GameRender* _Render);

private:
	void Render();
	void Release();

public:
	GameRenderMgr(GameScene* _pScene);
	~GameRenderMgr();
};

