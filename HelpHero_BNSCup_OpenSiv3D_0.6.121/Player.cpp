#include "stdafx.h"
#include "Player.h"
Player::Player()
{
	beforePos = pos;
}

void Player::Update()
{
	beforePos = pos;
	if (!KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない
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
	//pos.y += gravity;
	playerRect.x = pos.x;//移動反映
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
		pos = beforePos;
	}
}
