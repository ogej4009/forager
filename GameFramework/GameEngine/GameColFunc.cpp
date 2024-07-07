
#include "GameCol.h"
#include "GameActor.h"
#include "GameScene.h"
#include "GameColManager.h"


template<typename LEFT, typename RIGHT>
bool ColCheckTemplate(GameCol::COLDATA* _Left, GameCol::COLDATA* _Right)
{
	return ((LEFT*)_Left)->DATA.Intersects(((RIGHT*)_Right)->DATA);
}

void GameCol::COLAABBBOX::DataUpdate(GameTransform* _DataSetting)
{
	DATA.Center = _DataSetting->WPOS();
	DATA.Extents = _DataSetting->WSCALE().ABS();
}

bool GameCol::COLAABBBOX::ColCheck(COLDATA* _Other)
{
	switch (_Other->Type)
	{
	case GameCol::AABBRECT:
		return ColCheckTemplate<COLAABBBOX, COLAABBBOX>(this, _Other);
	case GameCol::OBBRECT:
		return ColCheckTemplate<COLAABBBOX, COLOBBBOX>(this, _Other);
	case GameCol::CIRCLE:
		return ColCheckTemplate<COLAABBBOX, COLCIRCLE>(this, _Other);
	default:
		break;
	}
	return false;
}

void GameCol::COLOBBBOX::DataUpdate(GameTransform* _DataSetting)
{
	DATA.Center = _DataSetting->WPOS();
	DATA.Extents = _DataSetting->WSCALE().ABS().HV();
	DATA.Orientation = _DataSetting->WQ();
}

bool GameCol::COLOBBBOX::ColCheck(COLDATA* _Other)
{
	switch (_Other->Type)
	{
	case GameCol::AABBRECT:
		return ColCheckTemplate<COLOBBBOX, COLAABBBOX>(this, _Other);
	case GameCol::OBBRECT:
		return ColCheckTemplate<COLOBBBOX, COLOBBBOX>(this, _Other);
	case GameCol::CIRCLE:
		return ColCheckTemplate<COLOBBBOX, COLCIRCLE>(this, _Other);
	default:
		break;
	}
	return false;
}

void GameCol::COLCIRCLE::DataUpdate(GameTransform* _DataSetting)
{
}

bool GameCol::COLCIRCLE::ColCheck(COLDATA* _Other)
{
	switch (_Other->Type)
	{
	case GameCol::AABBRECT:
		return ColCheckTemplate<COLCIRCLE, COLAABBBOX>(this, _Other);
	case GameCol::OBBRECT:
		return ColCheckTemplate<COLCIRCLE, COLOBBBOX>(this, _Other);
	case GameCol::CIRCLE:
		return ColCheckTemplate<COLCIRCLE, COLCIRCLE>(this, _Other);
	default:
		break;
	}
	return false;
}
