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
	Item,
	UI,
	Mouse,
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