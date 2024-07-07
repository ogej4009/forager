#pragma once
#include <map>
#include <list>
#include <GameString.h>
#include <GameRef.h>
#include <GameName.h>
#include "GameRenderMgr.h"
#include "GameColManager.h"

class GameActor;
class GameScene final : public GameRef, public GameName
{
	friend GameRenderMgr;

private:
	static std::map<GameString, S_Ptr<GameScene>> m_AllMap;

public:
	static GameScene* CurScene()
	{
		return m_CurScene;
	}

private:
	static S_Ptr<GameScene> m_CurScene;
	static S_Ptr<GameScene> m_NextScene;

public:
	class CSceneCom : public GameRef
	{
	public:
		friend GameScene;

	private:
		GameScene* m_pScene;

	public:
		GameScene* Scene()
		{
			return m_pScene;
		}

	public:
		S_Ptr<GameActor> CreateActor(const GameString& _Name = L"");
		S_Ptr<GameActor> FindActor(const GameString& _Name);

		virtual void Loading() {} // 씬을 시작할 때 처음 한번 실행해주는 함수
		virtual void ChangeEnd(GameScene* _NextScene) {}
		virtual void ChangeStart(GameScene* _NextScene) {}
		virtual void Update() {}
		virtual void UpdateAfter() {}
		virtual void DebugRender() {}
	};

public:
	static S_Ptr<GameScene> FindScene(const GameString& _Name);
	static S_Ptr<GameScene> CreateScene(const GameString& _Name);

	template<typename T, typename ... Rest>
	static S_Ptr<GameScene> CreateScene(const GameString& _Name)
	{
		S_Ptr<GameScene> NewScene = CreateScene(_Name);
		NewScene->AddCom<T>();
		return NewScene;
	}

	static void ChangeScene(const GameString& _Name);

	static void Progress();

	static S_Ptr<GameScene> GetCurScene()
	{
		return m_CurScene;
	}

private:
	bool m_IsLoading;

	std::list<S_Ptr<CSceneCom>> m_AllSceneCom;

public:
	template<typename T>
	void AddCom()
	{
		T* NewCom = new T();
		NewCom->m_pScene = this;
		m_AllSceneCom.push_back(NewCom);
	}

private:
	void ChangeEnd(GameScene* _pNextScene);
	void ChangeStart(GameScene* _pPrevScene);

public:
	void Loading();

public:
	std::list<S_Ptr<GameActor>> m_AllActor;
	std::list<S_Ptr<GameActor>>::iterator m_StartIter;
	std::list<S_Ptr<GameActor>>::iterator m_EndIter;

	std::map<GameString, S_Ptr<GameActor>> m_FindActor;

public:
	S_Ptr<GameActor> CreateActor(const GameString& _Name = L"");
	S_Ptr<GameActor> FindActor(const GameString& _Name);

public:
	void UpdatePrev();
	void Update();
	void UpdateNext();
	void Render();
	void Collision();
	void DebugRender();
	void Release();

public:
	GameRenderMgr RENDERMGR;
	GameColManager COLMGR;

public:
	GameScene();
	~GameScene();
};