#pragma once
#include "GameComponent.h"
#include "GameScene.h"
#include "GameActor.h"

class GameTransform;
class LogicCom : public GameComponent
{
public:
	template<typename TYPE>
	S_Ptr<TYPE> GetCom()
	{
		return Actor()->GetCom<TYPE>();
	}

	template<class TYPE, typename ...ARG>
	S_Ptr<TYPE> AddCom(ARG ... _Data)
	{
		return Actor()->AddCom<TYPE>(_Data...);;
	}

	S_Ptr<GameActor> CreateActor(const GameString& _Name)
	{
		return Actor()->Scene()->CreateActor(_Name);
	}

	S_Ptr<GameActor> CreateActor()
	{
		return Actor()->Scene()->CreateActor();
	}

public:
	LogicCom();
	~LogicCom();
};

