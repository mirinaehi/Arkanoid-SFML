#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
using namespace sf;

#define GAME_OVER -1

inline bool isCollide(Sprite s1, Sprite s2);

int main(void)
{
	srand(time(nullptr));
	RenderWindow app(VideoMode(520, 700), "Arkanoid");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");

	Sprite sBackground(t2, IntRect(0, 0, 520, 700)), sBall(t3), sPaddle(t4);
	
	sPaddle.setPosition(300, 610);
	sBall.setPosition(300, 600);

	Sprite block[1000];
	int n = 0;
	for(int i=1; i<=10; i++)
		for(int j=0; j<=10; j++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}

	float dx = 6.0f, dy = 5.0f;


	while(app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

		sBall.move(dx, 0);
		for (int i = 0; i < n; i++) {
			if (isCollide(sBall, block[i])) {
				block[i].setPosition(-100, 0);
				dx = -dx;
			}
		}

		sBall.move(0, dy);
		for (int i = 0; i < n; i++) {
			if (isCollide(sBall, block[i])) {
				block[i].setPosition(-100, 0);
				dy = -dy;
			}
		}

		Vector2f b = sBall.getPosition();
		if (b.y > 700)
			return GAME_OVER;
		if (b.x < 0 || b.x > 520)
			dx = -dx;
		if (b.y < 0)
			dy = -dy;

		if (Keyboard::isKeyPressed(Keyboard::Right))
			sPaddle.move(6.0f, 0.0f);
		if (Keyboard::isKeyPressed(Keyboard::Left))
			sPaddle.move(-6.0f, 0.0f);
		if (isCollide(sPaddle, sBall))
			dy = -(rand() % 5 + 2);


		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);

		app.display();
	}
	return 0;
}

inline bool isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}