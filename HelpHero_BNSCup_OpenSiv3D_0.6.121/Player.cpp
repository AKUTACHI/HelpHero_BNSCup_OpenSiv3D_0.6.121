#include "stdafx.h"
#include "Player.h"
Player::Player(P2World* _world)
{
	beforePos = pos;
	playerRect.x = pos.x;
	playerRect.y = pos.y;
	world = _world;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + playerRect.w / 2,pos.y + playerRect.h / 2 }, SizeF{ playerRect.w, playerRect.h });//RectとP2Bodyの位置を合わせてる、後で変えるかも
	body.setFixedRotation(false);
}

void Player::Update()
{
	beforePos = pos;
	if (!KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない

		
		if (KeyW.down() && abs(body.getVelocity().y)<=0.01) {//取りあえずｙ速度がほぼ0の状態でジャンプ可能に
			gravity -= 10;//ジャンプ
			body.applyLinearImpulse(Vec2(0,-200));
		}
		if (KeyA.pressed()) {
			beforePos.x -= speed * Scene::DeltaTime();
			body.applyLinearImpulse(Vec2(-speed * Scene::DeltaTime(), 0));
		}
		else 
		if (KeyD.pressed()) {
			beforePos.x += speed * Scene::DeltaTime();
			body.applyLinearImpulse(Vec2(speed * Scene::DeltaTime(), 0));
		}
		else {
			body.setVelocity(Vec2(0, body.getVelocity().y));//停止
		}
	}
	else {
		body.setVelocity(Vec2(0,body.getVelocity().y));
	}

	if (body.getVelocity().x < -400)body.setVelocity(Vec2(-400, body.getVelocity().y));//速度制限
	if (body.getVelocity().x > 400)body.setVelocity(Vec2(400, body.getVelocity().y));

	//pos.y += gravity;//ジャンプと落下の反映　一旦オフにしてる
	gravity += speed * Scene::DeltaTime();//落下
	beforePos.y += gravity;
}

void Player::DecisionMave() {

	pos = beforePos;
	playerRect.x = pos.x;
	playerRect.y = pos.y;
	playerRect.pos.x = body.getPos().x - playerRect.w / 2;
	playerRect.pos.y = body.getPos().y - playerRect.h / 2;
}

void Player::Draw()
{
	Print << pos;
	playerRect.draw();
	body.draw();
}

void Player::CheckGround()
{

	gravity = 0;
	beforePos.y = pos.y;

}
