#pragma once

enum class UpdateOrder
{
	Map,
	Player,
};

enum class RenderOrder
{
	BackGround,
	Ground,
	Player,
	Weapon,
	UI,
};

enum class CollisionOrder
{
	PlayerBody,
	UI,
};