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
			gravity = -10;//ジャンプ
		}
		/*if (KeyS.pressed()) {
			pos.y += speed * Scene::DeltaTime();
		}*/
		if (KeyA.pressed()) {
			beforePos.x -= speed * Scene::DeltaTime();
		}
		if (KeyD.pressed()) {
			beforePos.x += speed * Scene::DeltaTime();
		}
	}
	
	//pos.y += gravity;//ジャンプと落下の反映　一旦オフにしてる
	gravity += speed * Scene::DeltaTime();//落下
	beforePos.y += gravity;
}

void Player::DecisionMave() {

	pos = beforePos;

	playerRect.x = pos.x;
	playerRect.y = pos.y;
}

void Player::Draw()
{
	Print << pos;
	playerRect.draw();
}

void Player::CheckGround()
{

	gravity = 0;
	beforePos.y = pos.y;

}
