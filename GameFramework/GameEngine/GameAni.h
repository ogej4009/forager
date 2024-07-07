#pragma once
#include "LogicCom.h"
#include <functional>

class GameSprRender;
class GameAni : public LogicCom
{
private:
	class GameAniData : public GameRef
	{
	public:
		friend GameAni;

	public:
		LogicCom* m_Parent;
		GameString m_AniName;
		bool m_bLoop;
		bool m_bEnd;
		GameString m_SpriteName;
		size_t m_Start;
		size_t m_End;
		size_t m_Cur;
		float m_InterTime; // 0.1
		float m_CurTime;

		// 맨 앞 SIZE_T 프레임
		std::map<size_t, std::list<std::function<void(LogicCom*)>>>::iterator FindMemberStartEventIter;
		std::map<size_t, std::list<std::function<void(LogicCom*)>>> m_StartEventList;
		std::map<size_t, std::list<std::function<void(LogicCom*)>>> m_EndMemberEventList;


	public:
		void Update();
		void Reset();

	public:
		GameAniData() {}
		~GameAniData() {}
	};


private:
	std::map<GameString, S_Ptr<GameAniData>>	 m_AllAni;

	GameAniData* m_CurAni;
	S_Ptr<GameSprRender> m_ImgRender;

public:
	bool IsCurAni(const GameString& _Name)
	{
		return m_CurAni->m_AniName == _Name;
	}

	bool IsCurAniEnd()
	{
		return m_CurAni->m_bEnd;
	}


public:
	void CreateAni(const GameString& _AniName, const GameString& _SpriteName, size_t _Start, size_t _End, float _Time, bool _Loop);
	void ChangeAni(const GameString& _AniName, size_t _StartIndex = -1);

	template<typename TYPE>
	void AddStartEvent(const GameString& _AniName, size_t _Frame, TYPE* _TypeObj, void(TYPE::* _Func)(LogicCom* _Func))
	{
		if (nullptr == _TypeObj || nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		GameAniData* FAni = FindAni(_AniName);

		std::map<size_t, std::list<std::function<void(LogicCom* _Func)>>>::iterator FAniIter = FAni->m_StartEventList.find(_Frame);

		if (FAni->m_StartEventList.end() == FAniIter)
		{
			FAni->m_StartEventList.insert(std::map<size_t, std::list<std::function<void(LogicCom*)>>>::value_type(_Frame, std::list<std::function<void(LogicCom*)>>()));
			FAniIter = FAni->m_StartEventList.find(_Frame);
		}

		FAniIter->second.push_back(std::bind(_Func, _TypeObj, std::placeholders::_1));
	}


	void AddStartEvent(const GameString& _AniName, size_t _Frame, void(*_Func)(LogicCom* _Func))
	{
		if (nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		GameAniData* FAni = FindAni(_AniName);

		std::map<size_t, std::list<std::function<void(LogicCom*)>>>::iterator FAniIter = FAni->m_StartEventList.find(_Frame);

		if (FAni->m_StartEventList.end() == FAniIter)
		{
			FAni->m_StartEventList.insert(std::map<size_t, std::list<std::function<void(LogicCom*)>>>::value_type(_Frame, std::list<std::function<void(LogicCom*)>>()));
			FAniIter = FAni->m_StartEventList.find(_Frame);
		}

		FAniIter->second.push_back(std::bind(_Func, std::placeholders::_1));

	}

	S_Ptr<GameAniData> FindAni(const GameString& _AniName);

public:
	void Init() override;
	void UpdateNext() override;

public:
	GameAni();
	~GameAni();
};

