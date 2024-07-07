#include "GameTransform.h"
#include "GameActor.h"
#include "GameCamera.h"

GameTransform::GameTransform() :
	WorldFunc(&GameTransform::CalWorld),
	m_LScale(CVector::ONE),
	m_LRot(CVector::ZERO),
	m_LPos(CVector::ZERO),
	m_pParent(nullptr)
{
}

GameTransform::~GameTransform()
{
}

void GameTransform::QSetting()
{
	m_LRotQ = m_LRot;
	m_WRotQ = m_WRot;

	// 이함수는 오일러 값이 세팅됐다는 가정하에 오일러 값을 쿼터니온으로 변형시키는 함수
	m_LRotQ.EulerToQ();
	m_WRotQ.EulerToQ();
}

void GameTransform::Update()
{
	DebugCheck();

	m_MatScale.Scale(m_LScale);

	m_MatRotX.RotXDeg(m_LRot.x);
	m_MatRotY.RotYDeg(m_LRot.y);
	m_MatRotZ.RotZDeg(m_LRot.z);
	m_MatRot = m_MatRotX * m_MatRotY * m_MatRotZ;

	m_MatPos.Pos(m_LPos);
	(this->*WorldFunc)();
	QSetting();
	// m_WScale = ;

}

void GameTransform::CalWorld()
{
	m_LW = m_MatScale * m_MatRot * m_MatPos;
	m_WW = m_LW;

	m_WRot = m_LRot;
	m_WScale = m_LScale;
	m_WPos = m_WW.ArrVec[3];
}

void GameTransform::CalParentWorld()
{
	m_LW = m_MatScale * m_MatRot * m_MatPos;
	m_WW = m_LW * m_pParent->m_WW;

	m_WRot = m_pParent->WROT() + m_LRot;
	m_WScale = m_pParent->WSCALE() * m_LScale;
	m_WPos = m_WW.ArrVec[3];
}


void GameTransform::Init()
{
	if (nullptr != Actor()->GetCom<GameTransform>())
	{
		CodeEmbeddedErrorDetection;
	}

}

void GameTransform::CalTransData(GameCamera* _Cam) {

	m_TransData.W = m_WW;
	m_TransData.V = _Cam->MatView();
	m_TransData.P = _Cam->MatProj();
	m_TransData.WV = m_TransData.W * m_TransData.V;
	m_TransData.VP = _Cam->MatViewProj();
	m_TransData.WVP = m_TransData.W * m_TransData.V * m_TransData.P;

	m_TransData.AllTP();
}