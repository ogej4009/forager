#pragma once
#include <GameMath.h>
#include <GameRes.h>
#include <FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

class GameFont : public GameRes<GameFont>
{
public:
	static bool Create(const GameString& _FontName)
	{
		GameFont* NewRes = CreateRes(_FontName);
		return NewRes->CreateGameFont(_FontName);
	}

private:
	static IFW1Factory* m_pFontFactory;
	IFW1FontWrapper* m_pFontWrapper;

public:
	bool CreateGameFont(const GameString& _FontName);
	void DrawUI(const GameString& _Text, float _Size, CVector _Pos, CVector _Color, FW1_TEXT_FLAG _Flag = FW1_TOP);

public:
	GameFont();
	~GameFont();
};

