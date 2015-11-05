#include <SFML\Graphics.hpp>
#include "map.h"
#include "view.h"

using namespace sf;

class Player {
private: float x, y=0;
public:
	float w, h, dx, dy, speed = 0;
	int dir = 0;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String f, int X, int Y, float W, float H) {
		file = f;
		w = W;
		h = H;
		image.loadFromFile("images/" + file);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(w, h, w, h));
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;	//вправо
		case 1: dx = -speed; dy = 0; break;	//влево
		case 2: dx = 0; dy = speed; break;	//вниз
		case 3: dx = 0; dy = -speed; break;	//вверх
		default: dx = 0; dy = 0;
		}

		x += dx*time;
		y += dy*time;

		speed = 0;
		sprite.setPosition(x, y);
	}
	float getPlayerCoordinateX() {
		return x;
	}
	float getPlayerCoordinateY() {
		return y;
	}
};

int main()
{
	RenderWindow window(VideoMode(640, 480), "SFML works!");
	view.reset(FloatRect(0, 0, 640, 480));

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p("hero.png",250,250,96.0,96.0);

	Clock clock;
	float currentFrame = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dir = 1;
			p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
			getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dir = 0;
			p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
			getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			p.dir = 3;
			p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 288, 96, 96));
			getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			p.dir = 2;
			p.speed = 0.1;
			currentFrame += 0.005 * time;
			if (currentFrame > 3)
				currentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
			getPlayerCoordinatesForView(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}

		p.update(time);
		viewMap(time);
		window.setView(view);
		changeView();
		window.clear();

		for (int i = 0; i < HEIGHT_MAP;i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')
				s_map.setTextureRect(IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')
				s_map.setTextureRect(IntRect(32, 0, 32, 32));
			if (TileMap[i][j] == '0')
				s_map.setTextureRect(IntRect(64, 0, 32, 32));

			s_map.setPosition(j * 32, i * 32);

			window.draw(s_map);
		}

		window.draw(p.sprite);
		window.display();
	}

	return 0;
}