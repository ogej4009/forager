#include "GameCol.h"

#include "GameActor.h"
#include "GameScene.h"
#include "GameColManager.h"
#include "GameFrameDebug.h"
#include <DirectXCollision.h>
#include <DirectXCollision.inl>

bool GameCol::Debug;

GameCol::GameCol() {}
GameCol::~GameCol() {}

void GameCol::Init(COLTYPE _Type, unsigned int _Order/* = 0*/)
{
	m_Order = _Order;

	if (nullptr == Actor()->Scene())
	{
		CodeEmbeddedErrorDetection;
	}

	DebugOn();

	// �������� Ʈ������ �θ�� ���� �ȴ�?
	// ������ Ʈ���� ���� �ȴ�.
	Parent(Actor()->Trans());
	Type(_Type);
	Actor()->Scene()->COLMGR.PushCol(this);
}

void GameCol::Collision(GameCol* _Col)
{
	if (true == ColCheck(_Col))
	{
		if (m_OtherCol.end() == m_OtherCol.find(_Col))
		{
			// Enter
			int a = 0;


			m_OtherCol.insert(_Col);
			_Col->m_OtherCol.insert(this);

			for (auto& _Item : m_EnterMemberEventList)
			{
				_Item(this, _Col);
			}
		}
		else
		{
			for (auto& _Item : m_StayMemberEventList)
			{
				_Item(this, _Col);
			}
		}

		// �浹�� ���� ����� �ְ� ������?

	}
	else
	{
		if (m_OtherCol.end() != m_OtherCol.find(_Col))
		{
			for (auto& _Item : m_ExitMemberEventList)
			{
				_Item(this, _Col);
			}
			// Exit
			m_OtherCol.erase(_Col);
			_Col->m_OtherCol.erase(this);
		}
	}

}

bool GameCol::ColCheck(GameCol* _Col)
{
	// Ʈ������ ������ ����� ������ ������Ʈ �ϰ� �ϴ°� ���ڴ�.

	pData->DataUpdate(this);
	_Col->pData->DataUpdate(_Col);

	return pData->ColCheck(_Col->pData);
}

void GameCol::Type(COLTYPE _Type)
{
	switch (_Type)
	{
	case GameCol::AABBRECT:
		pData = new COLAABBBOX();
		pData->Type = AABBRECT;
		break;
	case GameCol::OBBRECT:
		pData = new COLOBBBOX();
		pData->Type = OBBRECT;
		break;
	case GameCol::CIRCLE:
		pData = new COLCIRCLE();
		pData->Type = CIRCLE;
		break;
	default:
		break;
	}

}

void GameCol::DebugRender()
{
	if (Debug)
	{
		GameFrameDebug::Draw2DRect(this);
	}

}

void GameCol::Release()
{
	for (auto& _Item : m_OtherCol)
	{
		_Item->m_OtherCol.erase(this);
	}


}