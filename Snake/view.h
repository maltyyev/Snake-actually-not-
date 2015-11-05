#include <SFML\Graphics.hpp>
using namespace sf;

View view;

void getPlayerCoordinatesForView(float x, float y)
{
	if (x < 320) x = 320;
	if (x > 960) x = 960;
	if (y < 240) y = 240;
	if (y > 560) y = 560;

	view.setCenter(x, y);
}

void viewMap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::D))
		view.move(0.1*time, 0);
	if (Keyboard::isKeyPressed(Keyboard::A))
		view.move(-0.1*time, 0);
	if (Keyboard::isKeyPressed(Keyboard::S))
		view.move(0, 0.1*time);
	if (Keyboard::isKeyPressed(Keyboard::W))
		view.move(0, -0.1*time);
}

void changeView()
{
	if (Keyboard::isKeyPressed(Keyboard::U))
	{
		view.zoom(1.0100f);
	}
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		view.rotate(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		view.setSize(640, 480);
	}
	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		view.setSize(540, 320);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		view.setViewport(FloatRect(0, 0, 0.5f, 1));
	}
}