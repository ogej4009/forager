#pragma once
#include <GameRef.h>
#include <map>
#include <list>

class GameScene;
class GameCol;
class GameColManager
{
public:
	friend GameCol;
	friend GameScene;

private:
	std::map<unsigned int, std::list<unsigned int>> m_AllLink;

	std::map<unsigned int, std::list<S_Ptr<GameCol>>>::iterator SrcIter;
	std::map<unsigned int, std::list<S_Ptr<GameCol>>>::iterator DestIter;

	std::list<S_Ptr<GameCol>>::iterator CStartIter;
	std::list<S_Ptr<GameCol>>::iterator CEndIter;
	std::map<unsigned int, std::list<S_Ptr<GameCol>>> m_AllCol;

private:
	void OtherCol(std::list<S_Ptr<GameCol>>& _Left, std::list <S_Ptr<GameCol>>& _Right);

	void PushCol(GameCol* _Col);

	void Release();

	void Collision();

public:
	void Link(unsigned int _Src, unsigned int _Dest);

public:
	GameColManager();
	~GameColManager();
};

