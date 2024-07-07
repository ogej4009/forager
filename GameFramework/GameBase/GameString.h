#pragma once
#include <string>
#include <atlstr.h>
#include <vector>

class GameString
{
public:
	std::wstring m_Str;

public: 
	class CGamePathData
	{
	public:
		wchar_t ArrDiv[256];
		wchar_t ArrDir[256];
		wchar_t ArrFile[256];
		wchar_t ArrExt[256];
		wchar_t ArrFullFile[256];

	public:
		bool IsExt(const GameString& _Ext);
	};

	CGamePathData  PathData() const
	{
		CGamePathData  Data;
		_wsplitpath_s(m_Str.c_str(), Data.ArrDiv, Data.ArrDir, Data.ArrFile, Data.ArrExt);
		swprintf_s(Data.ArrFullFile, L"%s%s", Data.ArrFile, Data.ArrExt);
		return Data;
	}

public:
	size_t Size() const
	{
		return m_Str.size();
	}

	void Resize(const size_t _Size)
	{
		m_Str.resize(_Size);
		return;
	}

	GameString GetCutText(const size_t& _Start, const size_t& _End);

	const wchar_t& operator [](size_t _Count) const
	{
		return m_Str[_Count];
	}

	operator std::wstring() const
	{
		return m_Str;
	}

	operator std::string() const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	operator const wchar_t* () const
	{
		return m_Str.c_str();
	}

	const wchar_t* StrPtr() const
	{
		return m_Str.c_str();
	}

	GameString operator+(const GameString& _Other)
	{
		GameString Result = m_Str + _Other.m_Str;
		return Result;
	}

	GameString& operator+=(const GameString& _Other)
	{
		m_Str += _Other.m_Str;
		return *this;
	}

	GameString& operator=(const GameString& _Other)
	{
		m_Str = _Other.m_Str;

		return *this;
	}

	operator const char* () const
	{
		return CW2A(m_Str.c_str()).m_psz;
	}

	bool operator>(const  wchar_t* _Other) const { return m_Str > _Other; }
	bool operator<(const  wchar_t* _Other) const { return m_Str < _Other; }
	bool operator>=(const wchar_t* _Other) const { return m_Str >= _Other; }
	bool operator<=(const wchar_t* _Other) const { return m_Str <= _Other; }
	bool operator==(const wchar_t* _Other) const { return m_Str == _Other; }
	bool operator!=(const wchar_t* _Other) const { return m_Str != _Other; }

	bool operator>(const  std::wstring _Other) const { return m_Str > _Other; }
	bool operator<(const  std::wstring _Other) const { return m_Str < _Other; }
	bool operator>=(const std::wstring _Other) const { return m_Str >= _Other; }
	bool operator<=(const std::wstring _Other) const { return m_Str <= _Other; }
	bool operator==(const std::wstring _Other) const { return m_Str == _Other; }
	bool operator!=(const std::wstring _Other) const { return m_Str != _Other; }

	bool operator>(const  std::wstring& _Other)  const { return m_Str > _Other; }
	bool operator<(const  std::wstring& _Other)  const { return m_Str < _Other; }
	bool operator>=(const std::wstring& _Other)  const { return m_Str >= _Other; }
	bool operator<=(const std::wstring& _Other)  const { return m_Str <= _Other; }
	bool operator==(const std::wstring& _Other)  const { return m_Str == _Other; }
	bool operator!=(const std::wstring& _Other)  const { return m_Str != _Other; }

	bool operator>(const GameString& _Other)  const { return m_Str > _Other.m_Str; }
	bool operator<(const GameString& _Other) const { return m_Str < _Other.m_Str; }
	bool operator>=(const GameString& _Other) const { return m_Str >= _Other.m_Str; }
	bool operator<=(const GameString& _Other) const { return m_Str <= _Other.m_Str; }
	bool operator==(const GameString& _Other) const { return m_Str == _Other.m_Str; }
	bool operator!=(const GameString& _Other) const { return m_Str != _Other.m_Str; }

	bool IsContains(const wchar_t* _Find);
	size_t Find(const wchar_t* _Find);
	std::vector<size_t> FindToCount(const wchar_t* _Find);
	void Change(const wchar_t* _Prev, const wchar_t* _Next);
	bool ChangeToFirstOne(const wchar_t* _Prev, const wchar_t* _Next);

	template<typename ...Rest>
	void ChangeToAll(const wchar_t* _Next, Rest ... Arg)
	{
		ChangePush(_Next, Arg...);
	}

private:
	template<typename ...Rest>
	void ChangePush(const wchar_t* _Next, const wchar_t* _Prev, Rest ... Arg)
	{
		Change(_Prev, _Next);
		ChangePush(_Next, Arg...);
	}

	void ChangePush(const wchar_t* _Next) {}

public:
	void Create(const wchar_t* _Format, ...);

public:
	GameString();
	GameString(const wchar_t* _Str);
	GameString(const char* _Str);
	GameString(const std::wstring& _Str);
	GameString(const std::string& _Str);
	~GameString();
};