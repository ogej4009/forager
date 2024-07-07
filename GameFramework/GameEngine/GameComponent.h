
#pragma once
#include "GameActor.h"
#include "GameVirtualFunc.h"
#include <GameName.h>
#include <GameRTTI.h>
#include <list>

class GameTransform;
class GameComponent : public GameVirtualFunc, public GameName, public GameRTTI
{
	friend GameActor;

private:
	GameActor* m_pActor;

public:
	GameActor* Actor()
	{
		return m_pActor;
	}

	GameTransform* Trans()
	{
		return m_pActor->Trans();
	}

public:
	bool IsDeath() override
	{
		return Actor()->IsDeath() || GameVirtualFunc::IsDeath();
	}

	bool IsUpdate() override
	{
		return Actor()->IsUpdate() && GameVirtualFunc::IsUpdate();
	}

	bool IsOn() override
	{
		return Actor()->IsOn() && GameVirtualFunc::IsOn();
	}

public:
	virtual void Init();

public:
	virtual void UpdatePrev() {}
	virtual void Update() {}
	virtual void UpdateNext() {}
	virtual void DebugRender() {}

public:
	GameComponent();
	~GameComponent();
};
