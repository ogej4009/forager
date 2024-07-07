#include "GameScene.h"
#include <GameTFunc.h>
#include "GameActor.h"
#include "GameTransform.h"


std::map<GameString, S_Ptr<GameScene>> GameScene::m_AllMap;

S_Ptr<GameScene> GameScene::m_CurScene = nullptr;
S_Ptr<GameScene> GameScene::m_NextScene = nullptr;

GameScene::GameScene()
	: m_IsLoading(false)
	, RENDERMGR(this)
{
}

GameScene::~GameScene()
{
}

S_Ptr<GameActor> GameScene::CSceneCom::CreateActor(const GameString& _Name)
{
	return m_pScene->CreateActor(_Name);
}

S_Ptr<GameActor> GameScene::CSceneCom::FindActor(const GameString& _Name)
{
	return m_pScene->FindActor(_Name);
}

S_Ptr<GameScene> GameScene::FindScene(const GameString& _Name)
{
	return GameTFunc::MapFindPointer(m_AllMap, _Name);
}

S_Ptr<GameScene> GameScene::CreateScene(const GameString& _Name)
{
	GameScene* NewScene = new GameScene();
	NewScene->SetCGStrName(_Name);
	m_AllMap.insert(std::map<GameString, S_Ptr<GameScene>>::value_type(NewScene->GetCGStrName(), NewScene));

	return NewScene;
}

void GameScene::ChangeScene(const GameString& _Name)
{
	m_NextScene = FindScene(_Name);
}

void GameScene::Progress()
{
	if (nullptr != m_NextScene)
	{
		if (false == m_NextScene->m_IsLoading)
		{
			m_NextScene->Loading();
		}

		if (nullptr != m_CurScene)
		{
			m_CurScene->ChangeEnd(m_NextScene);
		}

		m_NextScene->ChangeEnd(m_CurScene);
		m_CurScene = m_NextScene;
	}

	m_CurScene->UpdatePrev();
	m_CurScene->Update();
	m_CurScene->UpdateNext();
	m_CurScene->Collision();
	m_CurScene->Render();
	m_CurScene->Release();
}


void GameScene::ChangeEnd(GameScene* _pNextScene)
{
	for (auto& Item : m_AllSceneCom)
	{
		Item->ChangeEnd(_pNextScene);
	}
}

void GameScene::ChangeStart(GameScene* _pPrevScene)
{
	for (auto& Item : m_AllSceneCom)
	{
		Item->ChangeStart(_pPrevScene);
	}
}

void GameScene::Loading()
{
	for (auto& Item : m_AllSceneCom)
	{
		Item->Loading();
	}
	m_IsLoading = true;
}

S_Ptr<GameActor> GameScene::CreateActor(const GameString& _Name)
{
	GameActor* NewActor = new GameActor();
	NewActor->m_pScene = this;
	NewActor->m_pTrans = NewActor->AddCom<GameTransform>();

	if (_Name != L"")
	{
		NewActor->m_IsFind = true;
		NewActor->SetCGStrName(_Name);
		m_FindActor.insert(std::map<GameString, S_Ptr<GameActor>>::value_type(_Name, NewActor));
	}

	m_AllActor.push_back(NewActor);

	return NewActor;
}

S_Ptr<GameActor> GameScene::FindActor(const GameString& _Name)
{
	return GameTFunc::MapFindPointer(m_FindActor, _Name);
}

void GameScene::UpdatePrev()
{
	for (auto& Actor : m_AllActor)
	{
		Actor->UpdatePrev();
	}
}

void GameScene::Update()
{
	for (auto& Item : m_AllSceneCom)
	{
		Item->Update();
	}

	for (auto& Actor : m_AllActor)
	{
		Actor->Update();
	}
}

void GameScene::UpdateNext()
{
	for (auto& Actor : m_AllActor)
	{
		Actor->UpdateNext();
	}
}

void GameScene::Render()
{
	RENDERMGR.Render();
}

void GameScene::Collision()
{
	COLMGR.Collision();
}

void GameScene::DebugRender()
{
	for (auto& Item : m_AllSceneCom)
	{
		Item->DebugRender();
	}

	for (auto& Actor : m_AllActor)
	{
		if (false == Actor->IsUpdate())
		{
			continue;
		}

		Actor->DebugRender();
	}
}

void GameScene::Release()
{
	COLMGR.Release();
	RENDERMGR.Release();

	m_StartIter = m_AllActor.begin();
	m_EndIter = m_AllActor.end();

	for (; m_StartIter != m_EndIter; )
	{
		if (false == (*m_StartIter)->IsDeath())
		{
			++m_StartIter;
			continue;
		}

		m_StartIter = m_AllActor.erase(m_StartIter);
	}

}