#include "stdafx.h"
#include "Robot.h"

Robot::Robot(P2World* _world)
{
	area = robotRect;
	world = _world;
	/*body = world->createRect(P2Dynamic, Vec2{pos.x + robotRect.w / 2,pos.y + robotRect.h / 2}, SizeF{robotRect.w, robotRect.h},
		P2Material{ .density = 1000, .restitution = 0.0, .friction = 1.0 }, P2Filter{ .categoryBits = 0 }).setAwake(false);*/
	timer.reset();

	texHandClose = Texture{ U"textures/HandClose.png" };
	texHandOpen = Texture{ U"textures/HandOpen.png" };
}

void Robot::Update()
{
	if (KeyShift.pressed() && ready) {//Shift中はロボットの操作　プレイヤーは動かない
		if (KeyA.pressed()) {
			pos.x -= speed * Scene::DeltaTime();
			//body.moveBy(Vec2(-speed * Scene::DeltaTime(), 0));
		}
		if (KeyD.pressed()) {
			pos.x += speed * Scene::DeltaTime();
			//body.moveBy(Vec2(speed * Scene::DeltaTime(), 0));
		}
		if (KeyEnter.down()) {
			ready = false;
			Beeps::GetBeep(U"ArmDown").playOneShot();
			timer.restart();
		}
	}

	if (!ready && !up) {
		pos.y += Scene::DeltaTime() * speed*4;
		//body.moveBy(Vec2(0, Scene::DeltaTime() * speed));
	}
	else if (up) {
		pos.y -= Scene::DeltaTime() * speed;
		body.setPos(Vec2{ robotRect.x + robotRect.w / 2,robotRect.y + robotRect.h });


		//body.moveBy(Vec2(0, Scene::DeltaTime() * -speed));
		if (body.getPos().y < -50) {
			ready = true;
			up = false;//フラグをリセット
			body.release();
		}
	}
	robotRect.x = pos.x;//反映
	robotRect.y = pos.y;
	area = robotRect;
	area.h += 750;
}

void Robot::Draw()
{
	if (KeyShift.pressed() && ready) {//掘削範囲
		area.draw(ColorF{ 1,0.2,0,0.5 });
	}
	robotRect.draw(ColorF{ 0.3,0.3,0.3 });//腕
	body.draw();
	if (up)
	{
		texHandClose.draw(Arg::center( body.getPos()));
	}
	else
	{
		texHandOpen.draw(Arg::center(area.center()));
	}
}

bool Robot::CheckGround(const P2Body ground)
{
	//robotRect.y + (robotRect.h / 2) >= ground->getPos().y
	
		if (ground.getPos().y - 140<robotRect.y && up==false)
		{
			up = true;
			Beeps::GetBeep(U"ArmCatch").playOneShot();
			Beeps::GetBeep(U"ArmUp").playOneShot();
			body = world->createRect(P2Dynamic, Vec2{ robotRect.x + robotRect.w / 2,robotRect.y + robotRect.h }, SizeF{ robotRect.w, 90 });
			body.setFixedRotation(true);
			return true;
			Print(body.getMass());
		}
	return false;
}

void Robot::SwingCamera(Camera2D* mCamera) {
	if (up) {
		mCamera->setCenter(Vec2(Scene::Center().x + Periodic::Triangle1_1(0.3), Scene::Center().y));
	}
}
