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
	FrountWave,
	Player,
	Weapon,
	UI,

	Mouse,
};

enum class CollisionOrder
{
	PlayerBody,
	UI,
	Mouse,
	Boom,
};