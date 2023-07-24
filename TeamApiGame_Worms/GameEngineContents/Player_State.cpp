#include "Player.h"

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Player::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
}

void Player::MoveStart()
{

}
void Player::MoveUpdate(float _Delta)
{

}