#pragma once
#include <list>
#include "GameComponent.h"
#include "GameDevice.h"

class GameRenderMgr;
class GameCamera : public GameComponent
{
	friend GameRenderMgr;

private:
	float	m_Near; 
	float	m_Far; 
	CVector	m_Size; 
	float	m_Fov; 

	CMatrix	m_MatView;
	CMatrix	m_MatProj;
	CMatrix	m_MatViewProj;

private:
	unsigned int m_Order; // 렌더 순서

	// 나는 플레이어(5) 몬스터(10), 지형(2)
	std::list<unsigned int> m_Group;

public:
	void Size(CVector _Size)
	{
		m_Size = _Size;
	}

	CVector Size()
	{
		return m_Size;
	}

	unsigned int Order() {
		return m_Order;
	}

public:
	void Init(unsigned int _Order);

	template<typename ... Rest>
	void Init(unsigned int _Order, Rest ... _Data)
	{
		Init(_Order);

		PushRenderGroup(_Data...);
	}

	template<typename ... Rest>
	void PushRenderGroup(unsigned int _Order, Rest ... _Data)
	{
		m_Group.push_back(_Order);
		PushRenderGroup(_Data...);
	}

	void PushRenderGroup(unsigned int _Order)
	{
		m_Group.push_back(_Order);
	}

public:
	CMatrix	MatView() {
		return m_MatView;
	}
	CMatrix	MatProj() {
		return m_MatProj;
	}
	CMatrix	MatViewProj() {
		return m_MatViewProj;
	}
	CVector	ScreenPos3DToWorldPos(const CVector& _ScreenPos);

public:
	void UpdateNext() override;

public:
	GameCamera();
	~GameCamera();
};

