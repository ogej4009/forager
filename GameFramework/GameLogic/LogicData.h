#pragma once
#include <GameMath.h>

enum class RENDER_ORDER
{
	RO_LEVEL,
	RO_CURSOR,
	RO_MISC,
	RO_PLAYER,
	RO_PLAYER_SUB,
	RO_PLAYER_BULL,
	RO_DROPITEM,
	RO_ITEM,
	RO_MONSTER,
	RO_MON_BULL,
	RO_UI,
};

enum class COL_ORDER
{
	CO_LEVEL,
	CO_CURSOR,
	CO_MISC,
	CO_PLAYER,
	CO_PLAYER_SUB,
	CO_PLAYER_BULL,
	CO_DROPITEM,
	CO_ITEM,
	CO_MONSTER,
	CO_MON_BULL,
	CO_UI,
};

class LogicData
{
public:
	static const CVector ScreenSize;
};
