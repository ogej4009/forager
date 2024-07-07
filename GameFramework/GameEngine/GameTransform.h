#pragma once
#include <GameTime.h>
#include "GameDevice.h"
#include "GameComponent.h"
#include "GameCamera.h"

class GameCamera;
class GameTransform : public GameComponent
{
private:
	GameTransform* m_pParent;

private:
	CVector	m_LScale;
	CVector	m_LRotQ;
	CVector	m_LRot;
	CVector	m_LPos;

	CVector	m_WScale;
	CVector	m_WRotQ;
	CVector	m_WRot;
	CVector	m_WPos;

	CMatrix	m_MatScale;
	CMatrix	m_MatRotX;
	CMatrix	m_MatRotY;
	CMatrix	m_MatRotZ;
	CMatrix	m_MatRot;
	CMatrix	m_MatPos;
	CMatrix	m_LW;
	CMatrix	m_WW;


	void (GameTransform::* WorldFunc)();

protected:
	CTransformData m_TransData;

public:
	const CMatrix& CREFWW()
	{
		return m_WW;
	}

	void LMOVETOTIMESPEED(CVector _Value, float _Speed)
	{
		LMOVE(_Value * GameTime::DeltaTime() * _Speed);
	}

	void LMOVETOTIME(CVector _Value)
	{
		LMOVE(_Value * GameTime::DeltaTime());
	}

	void LMOVE(CVector _Value)
	{
		m_LPos += _Value;
	}

	void LPOS(CVector _Value)
	{
		m_LPos = _Value;
	}

	CVector LPOS()
	{
		return m_LPos;
	}

	void LSCALE(CVector _Value)
	{
		m_LScale = _Value;
	}

	CVector LSCALE()
	{
		return m_LScale;
	}

	void LROT(CVector _Value)
	{
		m_LRot = _Value;
	}

	CVector LROT()
	{
		return m_LRot;
	}

	//// World
	void WPOS(CVector _Value)
	{
		if (nullptr == m_pParent)
		{
			m_WPos = _Value;
			m_LPos = _Value;
			return;
		}

		CVector PScale = m_pParent->WSCALE();
		CVector PPos = _Value - m_pParent->WPOS();

		m_WPos = _Value;
		m_LPos = {
			PScale.x != 0.0f ? PPos.x / PScale.x : PPos.x,
			PScale.y != 0.0f ? PPos.y / PScale.y : PPos.y,
			PScale.z != 0.0f ? PPos.z / PScale.z : PPos.z
		};

	}

	CVector LQ()
	{
		return m_LRotQ;
	}

	CVector WQ()
	{
		return m_WRotQ;
	}

	CVector WPOS()
	{
		return m_WPos;
	}

	void WSCALE(CVector _Value)
	{
		if (nullptr == m_pParent)
		{
			m_WScale = _Value;
			m_LScale = _Value;
			return;
		}

		CVector PScale = m_pParent->WSCALE();

		// 5 5
		// 1 1 
		m_WScale = _Value;
		m_LScale = {
			PScale.x != 0.0f ? _Value.x / PScale.x : _Value.x,
			PScale.y != 0.0f ? _Value.y / PScale.y : _Value.y,
			PScale.z != 0.0f ? _Value.z / PScale.z : _Value.z
		};
	}

	CVector WSCALE()
	{
		return m_WScale;
	}

	void WROT(CVector _Value)
	{
		if (nullptr == m_pParent)
		{
			m_WRot = _Value;
			m_LRot = _Value;
			return;
		}

		CVector PRot = m_pParent->WROT();

		m_WRot = _Value;
		m_LRot = {
			_Value.x - PRot.x,
			_Value.y - PRot.y,
			_Value.z - PRot.z,
		};
		QSetting();
	}

	CVector WROT()
	{
		return m_WRot;
	}

	CVector WFORWARD()
	{
		return m_WW.ArrVec[2].Normal3DReturn();
	}

	CVector WBACK()
	{
		return -WFORWARD();
	}

	CVector WRIGHT()
	{
		return m_WW.ArrVec[0].Normal3DReturn();
	}

	CVector WLEFT()
	{
		return -WRIGHT();
	}

	CVector WUP()
	{
		return m_WW.ArrVec[1].Normal3DReturn();
	}

	CVector WDOWN()
	{
		return -WUP();
	}

	void ScaleXMinus()
	{
		if (0 < m_LScale.x)
		{
			m_LScale.x = -m_LScale.x;
		}
	}

	void ScaleXPlus()
	{
		if (0 > m_LScale.x)
		{
			m_LScale.x = m_LScale.x * -1.0f;
		}
	}

	void LROTZ(float _Value)
	{
		m_LRot.z += _Value;
	}

public:
	void Parent(GameTransform* _pParent)
	{
		// 부모 자식관계를 해제하겠다. 
		if (nullptr == _pParent)
		{
			if (nullptr != m_pParent)
			{
				// 원래 부모가 있었다. 그럼 떼어내는 작업을 해야 한다.
			}
			else
			{
				WorldFunc = &GameTransform::CalWorld;
				return;
			}
		}

		m_pParent = _pParent;

		WorldFunc = &GameTransform::CalParentWorld;
	}

	GameTransform* Parent()
	{
		return m_pParent;
	}

public:
	void Init();
	void CalTransData(GameCamera* _Cam);

private:
	void CalWorld();
	void CalParentWorld();
	void QSetting();

public:
	void Update() override;

public:
	GameTransform();
	~GameTransform();
};

