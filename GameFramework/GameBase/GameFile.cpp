#include <assert.h>
#include <atlstr.h>
#include "GameFile.h"

GameFile::GameFile(const wchar_t* _Path, const wchar_t* _Mode) : m_pFile(nullptr)
{
	Open(_Path, _Mode);
}

GameFile::GameFile(const GameFile& _Other)
{
	Copy(_Other);
}

GameFile::GameFile() : m_pFile(nullptr)
{
}

GameFile::~GameFile()
{
	Close();
}

void GameFile::PathSetting(const GameString& _Path)
{
	m_Path = _Path;
}

bool GameFile::Open()
{
	return Open(m_Path, m_OpenMode.c_str());
}

bool GameFile::Open(const wchar_t* _Path, const wchar_t* _Mode)
{
	PathSetting(_Path);
	m_OpenMode = _Mode;
	_wfopen_s(&m_pFile, m_Path, m_OpenMode.c_str());

	if (nullptr == m_pFile)
	{
		assert(false);
		return false;
	}

	return true;
}

void GameFile::Close()
{
	if (nullptr != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}

void GameFile::Copy(const GameFile& _Other)
{
	PathSetting(_Other.m_Path);
	m_pFile = _Other.m_pFile;
}