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
	Ground,
	Player,
	Weapon,
	Effect,
	UI,

	Mouse,
};

enum class CollisionOrder
{
	PlayerBody,
	UI,
	Mouse,
	Bomb,
};