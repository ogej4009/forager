#pragma once
#include "GameVirtualFunc.h"
#include <GameName.h>
#include <list>


class GameTransform;
class GameComponent;
class GameScene;
class GameActor final : public GameVirtualFunc, public GameName
{
public:
	friend GameScene;

private:
	bool m_IsFind;
	GameScene* m_pScene;

public:
	GameScene* Scene()
	{
		return m_pScene;
	}

public:
	void ChangeScene(GameString& _Name);

private:
	GameTransform* m_pTrans;
	std::list<S_Ptr<GameComponent>> m_AllCom;

public:
	GameTransform* Trans()
	{
		return m_pTrans;
	}

public:
	template<typename TYPE>
	S_Ptr<TYPE> GetCom()
	{
		const type_info* TInfo = &typeid(TYPE);
		for (auto& Value : m_AllCom)
		{
			if (true == Value->Check(TInfo))
			{
				return Value;
			}
		}

		return nullptr;
	}


	template<class T, typename ...ARG>
	S_Ptr<T> AddCom(ARG ... _Data)
	{
		T* NewCom = new T();
		const type_info* TInfo = &typeid(T);
		NewCom->TypeSetting(TInfo);
		NewCom->m_pActor = this;
		NewCom->Init(_Data ...);
		m_AllCom.push_back(NewCom);
		return NewCom;
	}


public:
	void UpdatePrev();
	void Update();
	void UpdateNext();
	void DebugRender();


public:
	GameActor();
	~GameActor();
};

