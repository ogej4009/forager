#pragma once
#include "GameString.h"
#include "GameName.h"
#include "GameRef.h"
#include <map>

template<typename T>
class GameRes : public GameName, public GameRef
{
public:
	friend T; // 본인을 상속받는 클래스만 friend

private:
	static std::map<GameString, S_Ptr<T>> m_ResMap;

protected:
	static void AddRes(const GameString& _Name, T* _Res)
	{
		_Res->SetCGStrName(_Name);
		AddRes(_Res);
	}

	static void AddRes(T* _Res)
	{
		if (nullptr != Find(_Res->GetCGStrName())) { CodeEmbeddedErrorDetection; }
		m_ResMap.insert(std::map<GameString, S_Ptr<T>>::value_type(_Res->GetCGStrName(), _Res));
	}

	static T* CreateRes(const GameString& _Name)
	{
		if (nullptr != Find(_Name)) { CodeEmbeddedErrorDetection; }
		T* NewRes = new T();
		NewRes->SetCGStrName(_Name);
		AddRes(NewRes);
		return NewRes;
	}

public:
	static S_Ptr<T> Find(const wchar_t* _Name)
	{
		typename std::map<GameString, S_Ptr<T>>::iterator FindIter = m_ResMap.find(_Name);

		if (m_ResMap.end() == FindIter)
		{
			return nullptr;
		}

		return FindIter->second;
	}

private:
	GameString m_Path;

public:
	GameString Path() { return m_Path; }

protected:
	GameRes() {}
	virtual ~GameRes() {}
};

template<typename T>
std::map<GameString, S_Ptr<T>> GameRes<T>::m_ResMap;