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
	BackLand,
	BackWave,
	Ground,
	Item,
	Player,
	Gauge,
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
	ShotHit,
	Flame,
	Item,
	UI,
	Mouse,
	BackEffect,
};

enum class WeaponEnum
{
	Bazooka,
	Uzi,
	HomingMissile,
	Sheep,
	Granade,
	Teleport,
	AirStrike,
	Girder,
	Donkey,
	HolyGranade,
	SuperSheep,
};