#pragma once

class Victim//ちなみにvictimが被災者の英語らしい
{
	P2World* world;
	P2Body body;
	Player* player;
	Vec2 pos = { 1100,450 };
	bool carry = false;//運ばれてる
	Rect victimRect = { 1100,450,80,80 };
public:
	Victim(P2World* _world, Player* _player);
	void Update();
	void Draw();

	void carry_move(Vec2 _player); //掴まれている時ロボットに追従する
	void carry_flip() { carry = !carry; }//掴まれているかの反転

	Vec2 getPos() { return pos; }
	Rect getRect() { return victimRect; }

	Texture texVictim;
};

