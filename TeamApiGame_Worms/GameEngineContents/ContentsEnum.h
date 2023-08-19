#pragma once

enum class UpdateOrder
{
	Map,
	Player,
};

enum class RenderOrder
{
	BackGround,
	BackGroundEffect,
	BackWave,
	Ground,
	Item,
	Player,
	CrossHair,
	Weapon,
	FrontWave,
	Effect,
	UI,

	Mouse,
};

enum class CollisionOrder
{
	PlayerBody,
	Weapon,
	Bomb,
	Item,
	UI,
	Mouse,
};