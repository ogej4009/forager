#include "GameTime.h"

GameTime::CGameTimer GameTime::m_MainTimer;

GameTime::GameTime() {}
GameTime::~GameTime() {}
GameTime::CGameTimer::CGameTimer() { Reset();}
GameTime::CGameTimer::~CGameTimer() {}

float GameTime::CGameTimer::Update()
{
	QueryPerformanceCounter(&m_CurCPUCount);

	// 8byte 
	m_dDeltaTime = ((double)(m_CurCPUCount.QuadPart - m_PrevCPUCount.QuadPart)) / ((double)m_CPUCount.QuadPart);
	m_fDeltaTime = (float)m_dDeltaTime;

	m_PrevCPUCount = m_CurCPUCount;

	return m_fDeltaTime;
}

void GameTime::CGameTimer::Reset()
{
	QueryPerformanceFrequency(&m_CPUCount);
	QueryPerformanceCounter(&m_CurCPUCount);
	QueryPerformanceCounter(&m_PrevCPUCount);
}