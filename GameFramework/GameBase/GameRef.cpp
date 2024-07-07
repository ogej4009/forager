#include "GameRef.h"
#include <memory>

GameRef::GameRef() : m_RefCount(0), m_bDebug(false)
{
}

GameRef::~GameRef()
{
}

void GameRef::PlusRef()
{
	++this->m_RefCount;
}

void GameRef::MinusRef()
{
	--this->m_RefCount;

	if (0 >= m_RefCount)
	{
		delete this;
	}
}