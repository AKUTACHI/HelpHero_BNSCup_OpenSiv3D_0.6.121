#include "stdafx.h"
#include "Player.h"
Player::Player()
{

}

void Player::Update()
{
	if (!KeyShift.pressed()) {
		if (KeyW.down()) {
			gravity -= 10;
		}
		/*if (KeyS.pressed()) {
			pos.y += speed * Scene::DeltaTime();
		}*/
		if (KeyA.pressed()) {
			pos.x -= speed * Scene::DeltaTime();
		}
		if (KeyD.pressed()) {
			pos.x += speed * Scene::DeltaTime();
		}
	}
	pos.y += gravity;
	playerRect.x = pos.x;
	playerRect.y = pos.y;
	gravity += speed * Scene::DeltaTime();
}

void Player::Draw()
{
	playerRect.draw();
}

void Player::CheckGround(Foothold* foothold)
{
	if (playerRect.intersects(foothold->getRect())) {
		gravity = 0;
	}
}
