
// TIPS: ヘッダーファイルの名前が変わった
#include "lib/framework.hpp"

enum WindowSize {
  WIDTH  = 512,
  HEIGHT = 512,
};

class Player{
	Vec2f pos = Vec2f::Zero();
	Vec2f size = Vec2f(256,128);
	Vec2f scale = Vec2f::Ones();
	Vec2f origin = size.array()*.5f;
	Vec2f speed = Vec2f(10, 10);
	const Vec2f SUPREMUM = Vec2f(WindowSize::WIDTH *.5f - origin.x(),WindowSize::HEIGHT*.5f - origin.y());
	const Vec2f INFIMUM = Vec2f(-WindowSize::WIDTH *.5f + origin.x(), -WindowSize::HEIGHT*.5f + origin.y());
	Texture texture = Texture("res/player_img.png");
	float rotate = .0f;
	Color color = Color::white;

public:
	void Update(AppEnv& env){
		if(env.isPressKey('W')){
			pos.y() += speed.y();
			pos.y() = std::min(pos.y(), SUPREMUM.y());
		}
		if (env.isPressKey('S')){
			pos.y() += -speed.y();
			pos.y() = std::max(pos.y(), INFIMUM.y());
		}
		if (env.isPressKey('D')){
			scale.x() = 1;
			pos.x() += speed.x();
			pos.x() = std::min(pos.x(), SUPREMUM.x());
		}
		if (env.isPressKey('A')){
			scale.x() = -1;
			pos.x() += -speed.x();
			pos.x() = std::max(pos.x(), INFIMUM.x());
		}
	}

	void Draw(){
		drawTextureBox(pos.x(), pos.y(), size.x(), size.y(),
			0, 0, texture.width(), 128, 
			texture, color,
			rotate,scale,origin);
	}
};

int main() {
  AppEnv env(WIDTH, HEIGHT);
  env.bgColor(Color::white);

  Player player;

  while (env.isOpen()) {
	player.Update(env);

    env.begin();

	player.Draw();

    env.end();
  }
}
