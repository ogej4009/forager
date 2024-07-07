#pragma once
#include "GameRender.h"

class GameFrameDebug
{
	friend class GameDevice;
	friend class GameRenderMgr;

private:
	class DEBUGDRAWINFO
	{
	public:
		GameCamera* m_Cam;
		GameTransform* m_Trans;
		CVector Color;
		GameRenderData* RD;
	};

	class DEBUGFONTINFO
	{
	public:
		GameString _Text;
		float _Size;
		CVector _Pos;
		CVector _Color;
	};

	static size_t m_DrawFontCount;
	static size_t m_DrawCount;
	static std::vector<DEBUGDRAWINFO> m_Info;
	static std::vector<DEBUGFONTINFO> m_FontInfo;

private:
	static void Init();
	static void DebugRender();

private:
	static CTransformData		 m_DebugTransData;
	static CVector			m_DebugColor;
	static S_Ptr<GameRenderData> RectRenderData;

public:
	static void Draw2DRect(GameTransform* _Trans, CVector _Color = CVector::RED);
	static void Draw2DRect(GameCamera* _Cam, GameTransform* _Trans, CVector _Color = CVector::RED);
	static void Draw2DFont(const GameString& _Text, const float& _Size, const CVector& _Pos, const CVector& _Color);

private:
	GameFrameDebug();
	~GameFrameDebug();
};

