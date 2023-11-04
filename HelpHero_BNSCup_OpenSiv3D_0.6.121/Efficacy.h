#pragma once
class Efficacy
{

	Vec2 komaMax;//コマ数
	Vec2 komaNow;//コマ数
	Vec2 komaSize;//コマサイズ
	Vec2 pos;//座標
	Texture effect;//テクスチャ
	bool isValid = false;//有効かどうか

	Timer timer;

	double count=0;
public:
	Efficacy();
	Efficacy(Vec2 _pos, Texture _effect, Vec2 _komaSize, Vec2 _koma);

	//座標、画像、コマサイズ、コマ数
	void set(Vec2 _pos, Texture _effect,Vec2 _komaSize,Vec2 _koma);
	//バラけるタイプ
	//中心座標、
	void set(Vec2 _center);

	void Update();

	void Draw();

	bool IsValid() { return isValid; }
};
