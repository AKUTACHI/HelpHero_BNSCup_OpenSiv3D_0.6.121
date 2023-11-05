#include "stdafx.h"

#include "Common.h"
#include "Player.h"
Player::Player(P2World* _world)
{
	beforePos = pos;
	playerRect.x = pos.x;
	playerRect.y = pos.y;
	world = _world;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + playerRect.w / 2,pos.y + playerRect.h / 2 }, SizeF{ playerRect.w, playerRect.h });//RectとP2Bodyの位置を合わせてる、後で変えるかも
	body.setFixedRotation(false);
	texPlayer.emplace(0, Texture{ U"textures/Hero0.png" });
	texPlayer.emplace(1, Texture{ U"textures/Hero1.png" });
	texPlayer.emplace(2, Texture{ U"textures/Hero2.png" });
	texPlayer.emplace(3, Texture{ U"textures/Hero3.png" });
}

void Player::Update()
{
	dir = 0;
	beforePos = pos;
	if (!KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない
		
		if (KeyW.down() && abs(body.getVelocity().y)<=0.01) {//取りあえずｙ速度がほぼ0の状態でジャンプ可能に
			gravity -= 10;//ジャンプ
			body.applyLinearImpulse(Vec2(0,-200));
		}
		if (KeyA.pressed()) {
			beforePos.x -= speed * Scene::DeltaTime();
			body.applyLinearImpulse(Vec2(-speed * Scene::DeltaTime(), 0));
			dir = -1;
		}
		else 
		if (KeyD.pressed()) {
			beforePos.x += speed * Scene::DeltaTime();
			body.applyLinearImpulse(Vec2(speed * Scene::DeltaTime(), 0));
			dir = 1;
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

	if (dir != 0)
	{
		lastDir = dir;
	}
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
	//Print << pos;
	//playerRect.draw();
	//body.draw();
	if (body.getVelocity().length() < 0.2)
	{
		playerRect(texPlayer[0].mirrored(lastDir < 0)).draw();
	}
	else
	{
		int32 frame = Periodic::Sawtooth0_1(1s) * 4;
		playerRect(texPlayer[frame].mirrored(lastDir < 0)).draw();
	}

}

void Player::CheckGround()
{

	gravity = 0;
	pos = beforePos;

}
