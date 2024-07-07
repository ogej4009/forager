#include "GameActor.h"
#include "GameComponent.h"


GameActor::GameActor() {}
GameActor::~GameActor() {}

void GameActor::UpdatePrev()
{
	for (auto& Actor : m_AllCom)
	{
		Actor->UpdatePrev();
	}
}

void GameActor::Update()
{
	for (auto& Actor : m_AllCom)
	{
		Actor->Update();
	}
}

void GameActor::UpdateNext()
{
	for (auto& Actor : m_AllCom)
	{
		Actor->UpdateNext();
	}
}

void GameActor::DebugRender()
{
	for (auto& Com : m_AllCom)
	{
		Com->DebugRender();
	}
}

void GameActor::ChangeScene(GameString& _Name)
{
}

