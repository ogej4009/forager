#include "GameString.h"

bool GameString::CGamePathData::IsExt(const GameString& _Ext)
{
	GameString Str = ArrExt;
	return Str == _Ext;
}

GameString::GameString() {}
GameString::GameString(const wchar_t* _Str) : m_Str(_Str) {}
GameString::GameString(const char* _Str) : m_Str(CA2W(_Str).m_psz) {}
GameString::GameString(const std::wstring& _Str) : m_Str(_Str) {}
GameString::GameString(const std::string& _Str) : m_Str(CA2W(_Str.c_str()).m_psz) {}
GameString::~GameString() {}

bool GameString::IsContains(const wchar_t* _Find) 
{
	size_t Result = m_Str.find(_Find);

	if (Result == -1)
	{
		return false;
	}

	return true;
}

size_t GameString::Find(const wchar_t* _Find)
{
	return  m_Str.find(_Find);
}

std::vector<size_t> GameString::FindToCount(const wchar_t* _Find)
{
	size_t Check = 0;

	GameString Text = _Find;

	std::vector<size_t> SizeArr;

	while (true)
	{
		Check = m_Str.find(_Find, Check);

		if (std::wstring::npos == Check)
		{
			break;
		}

		SizeArr.push_back(Check);
		Check += Text.Size();
	}

	return SizeArr;
}

void GameString::Change(const wchar_t* _Prev, const wchar_t* _Next)
{
	std::wstring Prev = _Prev;

	while (true)
	{
		size_t Result = m_Str.find(Prev);

		if (Result == -1)
		{
			break;
		}

		m_Str.replace(Result, Prev.size(), _Next);
	}
}

bool GameString::ChangeToFirstOne(const wchar_t* _Prev, const wchar_t* _Next)
{
	std::wstring Prev = _Prev;

	size_t Result = m_Str.find(Prev);

	if (Result == -1)
	{
		return false;
	}

	m_Str.replace(Result, Prev.size(), _Next);

	return true;
}

void GameString::Create(const wchar_t* _Format, ...) {}

GameString GameString::GetCutText(const size_t& _Start, const size_t& _End)
{
	size_t TextCutSize = _End - _Start + 1;
	std::wstring Cut;
	Cut.resize(TextCutSize);
	wmemcpy_s(&Cut[0], TextCutSize, &m_Str[_Start], TextCutSize);
	return Cut;
}