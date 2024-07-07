#pragma once
#include <GameRef.h>

class GameVirtualFunc : public GameRef
{
private:
	bool m_Active;
	bool m_Death;

public:
	virtual bool IsDeath() { return m_Death; }
	virtual bool IsUpdate() { return true == m_Active && false == m_Death; }
	virtual bool IsOn() { return m_Active; }
	virtual void Death() { m_Death = true; }
	virtual void On() { m_Active = true; }
	virtual void Off() { m_Active = false; }

public:
	GameVirtualFunc();
	~GameVirtualFunc();
};