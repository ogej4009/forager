#pragma once
#include "GameFile.h"
#include <vector>

class GameDirectory : public GamePath
{
public:
	// ���� ��θ� �־��൵ ������ ������ ������
	// �� ���丮�� �ڽ��� �н��� �����ϰ� �Ѵ�.
	void PathSetting(const GameString& _Path);

	GameFile CreateGameFile(const GameString& _FileName);
	GameString CreateGameFilePath(const GameString& _FileName);

	// �� ���丮�� ���� CodeEmbeddedErrorDetection
	// Move(L"\\HiSuite"); 
	// C:\Users\JHK\Documents 
	// ������ //  C:\Users\JHK\Documents\HiSuite
	// ���丮�� �̵��� �����ϴ�.
	bool Move(const GameString& _Name);

	// ��ΰ� �ڱ� �θ� ��η� ����ȴ�.
	// C:\Users\JHK\Documents\HiSuite
	// ������ // C:\Users\JHK\Documents
	void MoveParent();
	void MoveParent(const GameString& _Name);

	// �� ���丮 ���ο� �� ������ �ִ��� ������ �˾Ƴ���.
	bool IsFile(const GameString& _FileName);

	// �� ���丮 ���ο� �ִ� ���ϵ��� ����� ��� �˾Ƴ���.
	std::vector<GameFile> DirToAllFile();

	// *.*
	// *.png
	// *.txt
	std::vector<GameFile> DirToAllFile(const GameString& _Delimiter);

public:
	GameDirectory();
	~GameDirectory();
};