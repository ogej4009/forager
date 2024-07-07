#include "GameRenderMgr.h"
#include <GameTFunc.h>
#include "GameCamera.h"
#include "GameRender.h"
#include "GameDevice.h"
#include "GameTexture.h"
#include "GameSampler.h"
#include "GameScene.h"
#include "GameFrameDebug.h"

GameRenderMgr::GameRenderMgr(GameScene* _pScene)
	: m_pScene(_pScene)
	, m_MainCam(nullptr)
{
}

GameRenderMgr::~GameRenderMgr()
{
}

void GameRenderMgr::PushCam(GameCamera* _Cam)
{
	if (nullptr == _Cam)
	{
		CodeEmbeddedErrorDetection;
	}

	m_AllCam.insert(std::map<unsigned int, S_Ptr<GameCamera>>::value_type(_Cam->Order(), _Cam));

	if (nullptr == m_MainCam)
	{
		m_MainCam = _Cam;
	}
}

void GameRenderMgr::PushRender(GameRender* _Render)
{
	std::map<unsigned int, std::list<S_Ptr<GameRender>>>::iterator FindIter = m_AllRender.find(_Render->m_Order);

	if (m_AllRender.end() == FindIter)
	{
		m_AllRender.insert(std::map<unsigned int, std::list<S_Ptr<GameRender>>>::value_type(_Render->m_Order, std::list<S_Ptr<GameRender>>()));
		FindIter = m_AllRender.find(_Render->m_Order);
	}
	FindIter->second.push_back(_Render);
}

void GameRenderMgr::Render()
{
	GameDevice::gMainDevice()->RenderBegin();
	// 세팅의 순서는 아무런 상관없다.
	GameDevice::gMainDevice()->DEFVIEWPORTSET();
	GameDevice::gMainDevice()->DEFRENDERTARGETSET();
	for (std::pair<const unsigned int, S_Ptr<GameCamera>>& Item : m_AllCam)
	{
		for (unsigned int Value : Item.second->m_Group)
		{
			GroupIter = m_AllRender.find(Value);

			if (GroupIter == m_AllRender.end())
			{
				continue;
			}

			for (auto& Renderer : GroupIter->second)
			{
				Renderer->RenderUpdate(Item.second);
				Renderer->Render(Item.second);
			}
		}
	}

	m_pScene->DebugRender();

	GameFrameDebug::DebugRender();

	GameDevice::gMainDevice()->RenderEnd();
}

void GameRenderMgr::Release()
{
	for (auto& _Var : m_AllRender)
	{
		RStartIter = _Var.second.begin();
		REndIter = _Var.second.end();

		for (; RStartIter != REndIter;)
		{
			if (false == (*RStartIter)->IsDeath())
			{
				++RStartIter;
				continue;
			}

			RStartIter = _Var.second.erase(RStartIter);
		}

	}
}

