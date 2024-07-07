#include "Item.h"



Item::Item()
	: ItemCount(0)
{
}

Item::~Item()
{
	//for (auto& Item : ItemList)
	//{
	//	Item->Death();
	//}
	ItemList.clear();
}

void Item::Load()
{
}

void Item::Init()
{
	AddItemList(0, L"sprStone.png", L"StoneDrop.png", L"StonDrop", 14, 0.06f); // 0에서 14까지
	AddItemList(1, L"sprIronOre.png", L"IronDrop.png", L"IronDrop", 19, 0.06f); // 0에서 19까지
	AddItemList(2, L"sprGoldOre.png", L"GoldOreDrop.png", L"GoldOreDrop", 19, 0.06f); // 0에서 19까지
	AddItemList(3, L"sprFossil.png", L"FossilDrop.png", L"FossilDrop", 19, 0.06f); // 0에서 19까지
	AddItemList(4, L"sprWood.png", L"WoodDrop.png", L"WoodDrop", 19, 0.06f); // 0에서 19까지
}

void Item::Update()
{
}

void Item::DebugRender()
{
}