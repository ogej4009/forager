#pragma once
#include <Windows.h>

class GameTime
{
private:
	class CGameTimer
	{
	public:
		friend GameTime;

	private:
		LARGE_INTEGER m_CPUCount; 
		LARGE_INTEGER m_CurCPUCount; 
		LARGE_INTEGER m_PrevCPUCount; 
		double m_dDeltaTime;
		float m_fDeltaTime;

	public:
		float Update();
		void Reset();

	private:
		CGameTimer();
		~CGameTimer();
	};

private:
	static CGameTimer m_MainTimer;

public:
	static void Reset()
	{
		m_MainTimer.Reset();
	}

	static float Update()
	{
		return m_MainTimer.Update();
	}

	static float DeltaTime()
	{
		return m_MainTimer.m_fDeltaTime;
	}

private:
	GameTime();
	~GameTime();
};