#pragma once
#include "GameString.h"
#include <assert.h>
#include <Windows.h>

class GamePath
{
public:
	static GameString PathToFileName(const wchar_t* _Path)
	{
		std::wstring m_FileName = _Path;
		size_t LastFolderIndex = m_FileName.find_last_of(L"\\");
		m_FileName = m_FileName.replace(0, LastFolderIndex + 1, L"");
		return m_FileName;
	}

	static bool IsExist(const wchar_t* _Path)
	{
		if (0 != _waccess_s(_Path, 0))
		{
			return false;
		}
		return true;
	}

	static bool IsDir(const wchar_t* _Path)
	{
		int Result = GetFileAttributesW(_Path);

		if (-1 == Result)
		{
			return false;
		}

		if (0 == (FILE_ATTRIBUTE_DIRECTORY & Result))
		{
			return false;
		}
		return true;
	}

protected:
	GameString m_Path;

public:
	const std::wstring FullPath() const
	{
		return m_Path;
	}

public:
	void PathSetting(const char* _Path);
	void PathSetting(const wchar_t* _Path);

public:
	GamePath();
	~GamePath();
};

