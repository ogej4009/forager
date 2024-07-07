#include "GameCamera.h"

#include "GameActor.h"
#include "GameScene.h"
#include "GameTransform.h"

GameCamera::GameCamera()
	: m_Near(0.1f), m_Far(10000.0f), m_Size(GameWin::MainWindow()->Size()), m_Fov(60.0f)
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Init(unsigned int _Order)
{
	m_Order = _Order;

	if (nullptr == Actor()->GetCom<GameTransform>())
	{
		CodeEmbeddedErrorDetection;
	}

	if (nullptr != Actor()->GetCom<GameCamera>())
	{
		CodeEmbeddedErrorDetection;
	}

	if (nullptr == Actor()->Scene())
	{
		CodeEmbeddedErrorDetection;
	}

	Actor()->Scene()->RENDERMGR.PushCam(this);
}

void GameCamera::UpdateNext()
{
	// trans���� ������Ʈ �ǰ� ���� �ϰ� �ϱ� ���ؼ� ���⼭ �ߴ�.
	m_MatView.VIEWTOLH(Trans()->LPOS(), Trans()->WFORWARD(), Trans()->WUP());
	// H3DMProj.PERSLHDEG(H3DFov, H3DWidth, H3DHeight, H3DNear, H3DFar);

	m_MatProj.ORTHLH(m_Size, m_Near, m_Far);
}

CVector GameCamera::ScreenPos3DToWorldPos(const CVector& _ScreenPos)
{
	// m_Size �������� ����� �ʿ��ϴ�.
	// m_Size ���� ������ ȭ���� ���� ������

	CVector WinScale = GameWin::MainWindow()->Size();
	// ������ ���� 0,0
	// 1280 720
	// 16, 9

	CVector ConPos;
	ConPos.x = _ScreenPos.x * m_Size.x / WinScale.x;
	ConPos.y = _ScreenPos.y * m_Size.y / WinScale.y;
	ConPos += Trans()->WPOS();
	return ConPos;
}