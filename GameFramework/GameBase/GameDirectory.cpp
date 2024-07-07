#include "GameDirectory.h"
#include <io.h>
#include <atlstr.h>
#include "GameMacro.h"

GameDirectory::GameDirectory()
{
	wchar_t ArrSize[1024];
	if (0 == GetCurrentDirectoryW(1024, ArrSize))
	{
		CodeEmbeddedErrorDetection;
	}
	GameString Path = ArrSize;
	PathSetting(Path);
}

GameDirectory::~GameDirectory()
{
}

bool GameDirectory::IsFile(const GameString& _FileName)
{
	GameString FindPath = m_Path;
	FindPath += L"\\";
	FindPath += _FileName;
	return GamePath::IsExist(FindPath);
}

std::vector<GameFile> GameDirectory::DirToAllFile()
{
	return DirToAllFile(L"*.*");
}

std::vector<GameFile> GameDirectory::DirToAllFile(const GameString& _Delimiter)
{
	std::vector<GameFile> ReturnList;
	std::wstring FindPath = m_Path + L"\\" + _Delimiter;
	_wfinddata_t fd;
	std::wstring Check;

	intptr_t handle = _wfindfirst(FindPath.c_str(), &fd);	// 가장 첫파일을 찾아준다.
	do
	{
		Check = L".";
		if (fd.name == Check)
		{
			continue;
		}

		Check = L"..";
		if (fd.name == Check)
		{
			continue;
		}

		GameFile NewFile;
		NewFile.PathSetting(m_Path + L"\\" + fd.name);
		// 복사생성자.
		ReturnList.push_back(NewFile);
	} while (0 == _wfindnext(handle, &fd));

	_findclose(handle);
	return ReturnList;
}

bool GameDirectory::Move(const GameString& _Name)
{
	GameString MovePath = m_Path;
	MovePath += L"\\";
	MovePath += _Name;

	if (false == IsDir(MovePath))
	{
		assert(false);
		return false;
	}
	m_Path = MovePath;

	return true;
}

void GameDirectory::MoveParent()
{
	GameString FileName = L"\\";
	FileName += m_Path.PathData().ArrFile;
	m_Path.Change(FileName, L"");
}

void GameDirectory::MoveParent(const GameString& _Name)
{
	GameString Data = _Name;
	GameString LeftDir = m_Path.PathData().ArrFile;
	if (LeftDir != Data)
	{
		MoveParent();
		MoveParent(_Name);
	}
}

void GameDirectory::PathSetting(const GameString& _Path)
{
	if (0 != (FILE_ATTRIBUTE_DIRECTORY & GetFileAttributesW(_Path)))
	{
		m_Path = _Path;
		return;
	}

	m_Path = _Path;
	MoveParent();
}

GameFile GameDirectory::CreateGameFile(const GameString& _FileName)
{
	std::wstring CreatePath = CreateGameFilePath(_FileName);
	GameFile NewFile;
	NewFile.Open(CreatePath.c_str(), L"wb");
	NewFile.Close();
	return GameFile(NewFile);
}

GameString GameDirectory::CreateGameFilePath(const GameString& _FileName)
{
	return m_Path + L"\\" + _FileName;
}

