#include "GameAni.h"

#include "GameSprRender.h"
#include <GameTime.h>
#include <GameTFunc.h>


void GameAni::GameAniData::Reset()
{
	m_Cur = m_Start;
	m_CurTime = m_InterTime;
	m_bEnd = false;
}

void GameAni::GameAniData::Update()
{
	// 프레임당 이벤트도 만듭시다.
	// 0.1
	m_CurTime -= GameTime::DeltaTime();

	if (0 >= m_CurTime)
	{
		++m_Cur;

		FindMemberStartEventIter = m_StartEventList.find(m_Cur);

		if (FindMemberStartEventIter != m_StartEventList.end())
		{
			for (auto& _Var : FindMemberStartEventIter->second)
			{
				_Var(m_Parent);
			}
		}

		m_CurTime = m_InterTime;

		if (true == m_bLoop)
		{
			if (m_End < m_Cur)
			{
				m_Cur = m_Start;
			}
		}
		else {
			if (m_End < m_Cur)
			{
				m_bEnd = true;
				// 루프가 아니다.
				--m_Cur;
			}
		}
	}
}


GameAni::GameAni() {}
GameAni::~GameAni() {}

void GameAni::Init()
{
	m_ImgRender = Actor()->GetCom<GameSprRender>();
	if (nullptr == m_ImgRender)
	{
		CodeEmbeddedErrorDetection;
	}
}

S_Ptr<GameAni::GameAniData> GameAni::FindAni(const GameString& _AniName)
{
	return GameTFunc::MapFindPointer(m_AllAni, _AniName);
}

void GameAni::ChangeAni(const GameString& _AniName, size_t _StartIndex)
{
	m_CurAni = FindAni(_AniName);
	m_CurAni->Reset();
	if (-1 != _StartIndex)
	{
		m_CurAni->m_Cur = _StartIndex;
	}
	if (nullptr == m_CurAni)
	{
		CodeEmbeddedErrorDetection;
	}
}

void GameAni::CreateAni(const GameString& _AniName, const GameString& _SpriteName, size_t _Start, size_t _End, float _Time, bool _Loop)
{
	// 같은 이름이 있다면 미리 잘라.
	if (nullptr != FindAni(_AniName))
	{
		CodeEmbeddedErrorDetection;
	}

	GameAniData* NewAni = new GameAniData();
	NewAni->m_AniName = _AniName;
	NewAni->m_SpriteName = _SpriteName;
	NewAni->m_InterTime = _Time;
	NewAni->m_Start = _Start;
	NewAni->m_End = _End;
	NewAni->m_bLoop = _Loop;
	NewAni->m_bEnd = false;
	NewAni->m_Parent = this;

	m_AllAni.insert(std::map<GameString, S_Ptr<GameAniData>>::value_type(_AniName, NewAni));

}

void GameAni::UpdateNext()
{
	m_CurAni->Update();

	m_ImgRender->Index(m_CurAni->m_Cur);
	m_ImgRender->Sprite(m_CurAni->m_SpriteName);
}