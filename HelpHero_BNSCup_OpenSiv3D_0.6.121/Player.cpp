#include "stdafx.h"
#include "Player.h"
Player::Player()
{
	beforePos = pos;
	playerRect.x = pos.x;
	playerRect.y = pos.y;
}

void Player::Update()
{
	beforePos = pos;
	if (!KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない
		if (KeyW.down()) {
			gravity -= 10;//ジャンプ
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
	playerRect.x = pos.x;
	playerRect.y = pos.y;
	//pos.y += gravity;//ジャンプと落下の反映　一旦オフにしてる
	gravity += speed * Scene::DeltaTime();//落下
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
