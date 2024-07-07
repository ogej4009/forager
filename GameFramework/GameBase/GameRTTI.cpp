#include "GameRTTI.h"

GameRTTI::GameRTTI() { m_TypeInfo = nullptr; }
GameRTTI::~GameRTTI() {}

void GameRTTI::TypeSetting()
{
	m_TypeInfo = &typeid(*this);
}