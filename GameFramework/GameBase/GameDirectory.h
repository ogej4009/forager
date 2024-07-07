#pragma once
#include "GameFile.h"
#include <vector>

class GameDirectory : public GamePath
{
public:
	// 파일 경로를 넣어줘도 파일은 제거해 버리고
	// 그 디렉토리로 자신의 패스를 세팅하게 한다.
	void PathSetting(const GameString& _Path);

	GameFile CreateGameFile(const GameString& _FileName);
	GameString CreateGameFilePath(const GameString& _FileName);

	// 그 디렉토리가 없다 CodeEmbeddedErrorDetection
	// Move(L"\\HiSuite"); 
	// C:\Users\JHK\Documents 
	// 실행후 //  C:\Users\JHK\Documents\HiSuite
	// 디렉토리간 이동만 가능하다.
	bool Move(const GameString& _Name);

	// 경로가 자기 부모 경로로 변경된다.
	// C:\Users\JHK\Documents\HiSuite
	// 실행후 // C:\Users\JHK\Documents
	void MoveParent();
	void MoveParent(const GameString& _Name);

	// 그 디렉토리 내부에 이 파일이 있는지 없는지 알아낸다.
	bool IsFile(const GameString& _FileName);

	// 그 디렉토리 내부에 있는 파일들의 목록을 모두 알아낸다.
	std::vector<GameFile> DirToAllFile();

	// *.*
	// *.png
	// *.txt
	std::vector<GameFile> DirToAllFile(const GameString& _Delimiter);

public:
	GameDirectory();
	~GameDirectory();
};