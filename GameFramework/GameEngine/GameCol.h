#pragma once
#include "GameTransform.h"
#include <functional>
#include <unordered_map>
#include <unordered_set>

class GameColManager;
class GameCol :	public GameTransform
{
public:
	enum COLTYPE
	{
		AABBRECT,
		OBBRECT,
		CIRCLE,
	};

private:
	class COLDATA : public GameRef
	{
	public:
		COLTYPE Type;
	public:
		virtual void DataUpdate(GameTransform* _DataSetting) = 0;
		virtual bool ColCheck(COLDATA* _Other) = 0;
	};

	class COLAABBBOX : public COLDATA
	{
	public:
		void DataUpdate(GameTransform* _DataSetting) override;
		bool ColCheck(COLDATA* _Other) override;

	public:
		DirectX::BoundingBox DATA;
	};


	class COLOBBBOX : public COLDATA
	{
	public:
		void DataUpdate(GameTransform* _DataSetting) override;
		bool ColCheck(COLDATA* _Other) override;
	public:
		DirectX::BoundingOrientedBox DATA;
	};

	class COLCIRCLE : public COLDATA
	{
	public:
		void DataUpdate(GameTransform* _DataSetting) override;
		bool ColCheck(COLDATA* _Other) override;

	public:
		DirectX::BoundingSphere DATA;
	};

	//template<typename Left, typename Right>
	//bool ColCheckTemplate(const Left& _Left, const Right& _Right)
	//{
	//	return _Left.Intersects(_Right);
	//}



public:
	friend GameColManager;

public:
	static bool Debug;


private:
	int m_Order;
	S_Ptr<COLDATA> pData;

private:
	std::unordered_set<GameCol*> m_OtherCol;


	static std::unordered_map<const type_info*, std::unordered_map<const type_info*, void()>> m_Func;

	void Collision(GameCol* _Col);
	bool ColCheck(GameCol* _Col);
	void DebugRender() override;
	void Release();

public:
	virtual void Init(COLTYPE _Type, unsigned int _Order = 0);
	void Type(COLTYPE _Type);
	int GetOrder()
	{
		return m_Order;
	}



private:

	std::list<std::function<void(GameCol* _This, GameCol* _Other)>> m_EnterMemberEventList;
	std::list<std::function<void(GameCol* _This, GameCol* _Other)>> m_StayMemberEventList;
	std::list<std::function<void(GameCol* _This, GameCol* _Other)>> m_ExitMemberEventList;

public:
	template<typename TYPE>
	void AddEnterEvent(TYPE* _TypeObj, void(TYPE::* _Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _TypeObj || nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_EnterMemberEventList.push_back(std::bind(_Func, _TypeObj, std::placeholders::_1, std::placeholders::_2));
	}

	void AddEnterEvent(void(*_Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_EnterMemberEventList.push_back(std::bind(_Func, std::placeholders::_1, std::placeholders::_2));
	}

	template<typename TYPE>
	void AddExitEvent(TYPE* _TypeObj, void(TYPE::* _Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _TypeObj || nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_ExitMemberEventList.push_back(std::bind(_Func, _TypeObj, std::placeholders::_1, std::placeholders::_2));
	}

	void AddExitEvent(void(*_Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_ExitMemberEventList.push_back(std::bind(_Func, std::placeholders::_1, std::placeholders::_2));
	}

	template<typename TYPE>
	void AddStayEvent(TYPE* _TypeObj, void(TYPE::* _Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _TypeObj || nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_StayMemberEventList.push_back(std::bind(_Func, _TypeObj, std::placeholders::_1, std::placeholders::_2));
	}

	void AddStayEvent(void(*_Func)(GameCol* _This, GameCol* _Other))
	{
		if (nullptr == _Func)
		{
			CodeEmbeddedErrorDetection;
		}

		m_StayMemberEventList.push_back(std::bind(_Func, std::placeholders::_1, std::placeholders::_2));
	}



public:
	GameCol();
	~GameCol();
};
