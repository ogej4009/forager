#include "GameWin.h"
#include "GameInput.h"
#include "GameTime.h"
//#include "GameSound.h"

std::map<std::wstring, WNDCLASSEXW> GameWin::m_ClassMap;
std::map<std::wstring, S_Ptr<GameWin>> GameWin::m_WinMap;
std::map<HWND, S_Ptr<GameWin>> GameWin::m_HWndMap;
S_Ptr<GameWin> GameWin::m_pMainWindow = nullptr;
HDC GameWin::m_MainDc;

LRESULT CALLBACK GameWin::MSGFUNC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		DestroyHGameWin(hWnd);
		// DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// int CGAMEWIN::BaseLoop(void(__stdcall *_GameFunc)())
// �Լ�ȣ���� ȣ���ڿ� �����ڸ� �����ϸ� �ȴ�.
// __stdcall ȣ���� ���� ȣ���� ���� ������ �ڱ��ڽ� // ��������.
// __cdecl ȣ���� ���� ȣ���� ���� ������ ȣ���� ��
// __thiscall �ɹ����� ���ο� this�� �ִ�. 

int GameWin::BaseLoop(void(__stdcall* _GameFunc)(), void(__stdcall* _InitFunc)())
{
	// MrGameSound::SoundInit();
	if (nullptr != _InitFunc)
	{
		_InitFunc();
	}

	MSG msg;

	while (0 != m_WinMap.size())
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			_GameFunc();
		}
	}

	return (int)msg.wParam;
}

GameWin::WinInit::WinInit()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = GameWin::MSGFUNC;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = 0;
	wcex.hIcon = 0;/*LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTAPI))*/;
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"DefaultWinClass";
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegWindowClass(wcex);

	// ���ο� ���� ����ְ�
	// szWindowClass�� ����ִ� �̸����� ��ϵȴ�.
	// USHORT S = RegisterClassExW(&wcex);
}

GameWin::WinInit::~WinInit() {}
GameWin::WinInit GameWin::Construct = GameWin::WinInit();

GameWin::GameWin(HWND _HWnd) : m_HWnd(_HWnd)
{
	m_DC = GetDC(_HWnd);
}

GameWin::GameWin()
{
}

GameWin::~GameWin()
{
	// DestroyWindow(m_HWnd);
}

void GameWin::DestroyHGameWin(HWND _HWnd)
{
	std::map<HWND, S_Ptr<GameWin>>::iterator FindIter = m_HWndMap.find(_HWnd);
	if (FindIter == m_HWndMap.end())
	{
		CodeEmbeddedErrorDetection;
	}

	std::map<std::wstring, S_Ptr<GameWin>>::iterator NameFindIter = m_WinMap.find(FindIter->second->GetWStrName());

	m_WinMap.erase(NameFindIter);
	m_HWndMap.erase(FindIter);

}

bool GameWin::IsRegClass(const wchar_t* _Name)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator FindIter = m_ClassMap.find(_Name);
	if (FindIter == m_ClassMap.end())
	{
		return false;
	}
	return true;
}

void GameWin::RegWindowClass(const WNDCLASSEXW& _wcex)
{
	// �̹� ��ϵ� Ŭ�������� ��Ʈ����
	if (true == IsRegClass(_wcex.lpszClassName))
	{
		CodeEmbeddedErrorDetection;
	}

	// ����� �����ϸ� ��Ʈ����.
	if (0 == RegisterClassExW(&_wcex))
	{
		CodeEmbeddedErrorDetection;
	}

	m_ClassMap.insert(std::map<std::wstring, WNDCLASSEXW>::value_type(_wcex.lpszClassName, _wcex));
}

S_Ptr<GameWin> GameWin::FindGameWin(const wchar_t* _WinName) {

	std::map<std::wstring, S_Ptr<GameWin>>::iterator FindIter = m_WinMap.find(_WinName);
	if (FindIter == m_WinMap.end())
	{
		return nullptr;
	}
	return FindIter->second;
}

S_Ptr<GameWin> GameWin::CreateGameWin(const wchar_t* _WinName, const wchar_t* _ClassName /*= L"DefaultWinClass"*/, bool _bShow /*= true*/)
{

	if (nullptr != FindGameWin(_WinName))
	{
		CodeEmbeddedErrorDetection;
	}

	if (false == IsRegClass(_ClassName))
	{
		CodeEmbeddedErrorDetection;
	}

	// WS_OVERLAPPEDWINDOW Ÿ��Ʋ�� ���� ��Ÿ�� �ɼ��� �־���.
	HWND hWnd = CreateWindowW(_ClassName, _WinName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, /*hInstance*/0, nullptr);

	if (0 == hWnd)
	{
		return FALSE;
	}

	GameWin* NewWin = new GameWin(hWnd);
	NewWin->m_Style = WS_OVERLAPPEDWINDOW;
	NewWin->SetCWTName(_WinName);
	m_WinMap.insert(std::map<std::wstring, GameWin*>::value_type(_WinName, NewWin));
	m_HWndMap.insert(std::map<HWND, GameWin*>::value_type(hWnd, NewWin));

	if (1 == m_WinMap.size())
	{
		m_pMainWindow = NewWin;
		m_MainDc = m_pMainWindow->WINHDC();
	}

	if (true == _bShow)
	{
		NewWin->Show();
	}

	return NewWin;
}

S_Ptr<GameWin> GameWin::AddGameWin(const wchar_t* _WinName, HWND _WinHWnd)
{
	if (nullptr != FindGameWin(_WinName))
	{
		//CodeEmbeddedErrorDetection;
		CodeEmbeddedErrorDetection;
	}

	// WS_OVERLAPPEDWINDOW Ÿ��Ʋ�� ���� ��Ÿ�� �ɼ��� �־���.
	HWND hWnd = _WinHWnd;

	if (0 == hWnd)
	{
		return FALSE;
	}

	GameWin* NewWin = new GameWin(hWnd);
	NewWin->m_Style = WS_OVERLAPPEDWINDOW;
	NewWin->SetCWTName(_WinName);
	RECT RC;
	GetWindowRect(_WinHWnd, &RC);
	NewWin->m_Size.x = (float)(RC.right - RC.left);
	NewWin->m_Size.y = (float)(RC.bottom - RC.top);

	m_WinMap.insert(std::map<std::wstring, GameWin*>::value_type(_WinName, NewWin));
	m_HWndMap.insert(std::map<HWND, GameWin*>::value_type(hWnd, NewWin));

	if (1 == m_WinMap.size())
	{
		m_pMainWindow = NewWin;
		m_MainDc = m_pMainWindow->WINHDC();
	}

	return NewWin;
}

void GameWin::Show()
{
	ShowWindow(m_HWnd, SW_SHOW);
}

CVector GameWin::MousePos()
{
	POINT Point;

	GetCursorPos(&Point);
	ScreenToClient(m_HWnd, &Point);

	CVector ReturnPos;

	ReturnPos.x = (float)Point.x;
	ReturnPos.y = (float)Point.y;

	return ReturnPos;
}

CVector GameWin::MousePos3D()
{
	CVector MPos = MousePos();
	MPos.x -= Size().HV().x;
	MPos.y -= Size().HV().y;
	MPos.y *= -1.0f;

	return MPos;
}

void GameWin::Size(CVector _Size)
{
	m_Size = _Size;

	// ũ�Ⱑ -> �ٿ� �װͱ��� ��ģ ����� 800 
	// �ɹ������� ��� PUBLIC�̸� �䷱������ ������ ����.
	RECT Rc = { 0, 0, m_Size.ix(), m_Size.iy() };
	// �� ������ ���� ��ģ ũ�⸦ �ش�.

	HMENU MenuCon = GetMenu(m_HWnd);

	if (nullptr == MenuCon)
	{
		AdjustWindowRect(&Rc, m_Style, FALSE);
	}
	else
	{
		AdjustWindowRect(&Rc, m_Style, TRUE);
	}

	int x = Rc.right - Rc.left;
	int y = Rc.bottom - Rc.top;


	SetWindowPos(m_HWnd, 0, 0, 0, Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOMOVE | SWP_NOZORDER);

}