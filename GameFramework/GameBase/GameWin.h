#pragma once
#include "GameName.h"
#include "GameRef.h"
#include "GameString.h"
#include "GameMath.h"
#include "GameMacro.h"
#include <windows.h>
#include <map>
#include <string>


class GameWin : public GameRef, public GameName
{
private:
	class WinInit
	{
	public:
		WinInit();
		~WinInit();
	};

	static WinInit Construct;

private:
	static std::map<std::wstring, WNDCLASSEXW> m_ClassMap;
	static std::map<std::wstring, S_Ptr<GameWin>> m_WinMap;
	static std::map<HWND, S_Ptr<GameWin>> m_HWndMap;
	static S_Ptr<GameWin> m_pMainWindow;
	static HDC m_MainDc;

public: 
	static S_Ptr<GameWin> MainWindow()
	{
		return m_pMainWindow;
	}

	static HDC MainHDC()
	{
		return m_MainDc;
	}

private:
	static void DestroyHGameWin(HWND _HWnd);

public:
	static LRESULT __stdcall MSGFUNC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static bool IsRegClass(const wchar_t* _Name);
	static void RegWindowClass(const WNDCLASSEXW& _wcex);
	static S_Ptr<GameWin> FindGameWin(const wchar_t* _WinName);
	static S_Ptr<GameWin> CreateGameWin(const wchar_t* _WinName, 
		const wchar_t* _ClassName = L"DefaultWinClass", 
		bool _bShow = true);
	static S_Ptr<GameWin> AddGameWin(const wchar_t* _WinName, HWND _WinHWnd);
	static int BaseLoop(void(__stdcall* _GameFunc)(), void(__stdcall* _InitFunc)() = nullptr);

private:
	HWND m_HWnd;
	HDC m_DC;
	int m_Style;
	CVector m_Size;

public:
	HWND WINHWND()
	{
		return m_HWnd;
	}

	HDC WINHDC()
	{
		return m_DC;
	}

public:
	void Show();
	CVector MousePos();
	CVector MousePos3D();

public:
	CVector Size() { return m_Size; }
	CVector SizeH() { return m_Size.HV(); }
	void Size(CVector _Size);

protected:
	GameWin(HWND _HWnd);
	GameWin();
	virtual ~GameWin();

};

