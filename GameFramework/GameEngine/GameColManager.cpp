#include "GameColManager.h"
#include "GameCol.h"

GameColManager::GameColManager()
{
}


GameColManager::~GameColManager()
{
}

void GameColManager::Collision()
{
	for (auto& DestList : m_AllLink)
	{
		SrcIter = m_AllCol.find(DestList.first);
		std::list<S_Ptr<GameCol>>& SrcColList = SrcIter->second;

		if (0 >= SrcColList.size())
		{
			continue;
		}

		for (auto& DestOrder : DestList.second)
		{
			DestIter = m_AllCol.find(DestOrder);

			std::list<S_Ptr<GameCol>>& DestColList = DestIter->second;

			if (0 >= DestColList.size())
			{
				continue;
			}

			if (DestList.first == DestOrder)
			{
				// 같은 그룹
				int a = 0;
			}
			else
			{
				// 다른 그룹
				OtherCol(SrcColList, DestColList);
			}

		}
	}


}

void GameColManager::OtherCol(std::list<S_Ptr<GameCol>>& _Left, std::list <S_Ptr<GameCol>>& _Right)
{
	for (auto& LeftCol : _Left)
	{
		for (auto& RightCol : _Right)
		{
			LeftCol->Collision(RightCol);
		}
	}

}


void GameColManager::PushCol(GameCol* _Col)
{
	std::map<unsigned int, std::list<S_Ptr<GameCol>>>::iterator FindIter
		= m_AllCol.find(_Col->m_Order);

	if (m_AllCol.end() == FindIter)
	{
		// 없다면 만든다.
		m_AllCol.insert(std::map<unsigned int, std::list<S_Ptr<GameCol>>>::value_type(_Col->m_Order, std::list<S_Ptr<GameCol>>()));
		FindIter = m_AllCol.find(_Col->m_Order);
	}
	FindIter->second.push_back(_Col);

}

void GameColManager::Link(unsigned int _Src, unsigned int _Dest)
{
	std::map<unsigned int, std::list<unsigned int>>::iterator FindIter
		= m_AllLink.find(_Src);

	if (m_AllLink.end() == FindIter)
	{
		// 없다면 만든다.
		m_AllLink.insert(std::map<unsigned int, std::list<unsigned int>>::value_type(_Src, std::list<unsigned int>()));
		FindIter = m_AllLink.find(_Src);
	}

	FindIter->second.push_back(_Dest);
}

void GameColManager::Release()
{
	for (auto& _Var : m_AllCol)
	{
		CStartIter = _Var.second.begin();
		CEndIter = _Var.second.end();

		for (; CStartIter != CEndIter;)
		{
			if (false == (*CStartIter)->IsDeath())
			{
				++CStartIter;
				continue;
			}
			(*CStartIter)->Release();

			CStartIter = _Var.second.erase(CStartIter);
		}

	}
}