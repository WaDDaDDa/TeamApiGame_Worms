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
	Player,
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
	UI,
	Mouse,
};