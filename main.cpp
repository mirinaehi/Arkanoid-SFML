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

	// 텍스쳐 load
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");

	// image 배치
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
	// 공의 발사각도
	float dx = 6.0f, dy = 5.0f;


	while(app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

		// 공이 벽돌과 충돌하면 벽돌을 없애고, 공의 방향은 반대로
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

		// 공의 boundary 설정
		Vector2f b = sBall.getPosition();
		if (b.y > 700)
			return GAME_OVER;
		if (b.x < 0 || b.x > 520)
			dx = -dx;
		if (b.y < 0)
			dy = -dy;

		// paddle 움직이고, 공과의 충돌처리
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

// 사각충돌
inline bool isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

//int main()
//{
//    srand(time(0));
//
//    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
//    app.setFramerateLimit(60);
//
//    Texture t1,t2,t3,t4;
//    t1.loadFromFile("images/block01.png");
//    t2.loadFromFile("images/background.jpg");
//    t3.loadFromFile("images/ball.png");
//    t4.loadFromFile("images/paddle.png");
//
//    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
//    sPaddle.setPosition(300,440);
//
//    Sprite block[1000];
//
//    int n=0;
//    for (int i=1;i<=10;i++)
//    for (int j=1;j<=10;j++)
//      {
//         block[n].setTexture(t1);
//         block[n].setPosition(i*43,j*20);
//         n++;
//      }
//
//    float dx=6, dy=5;
//    float x=300, y=300;
//
//    while (app.isOpen())
//    {
//       Event e;
//       while (app.pollEvent(e))
//       {
//         if (e.type == Event::Closed)
//             app.close();
//       }
//
//    x+=dx;
//    for (int i=0;i<n;i++)
//        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
//             {block[i].setPosition(-100,0); dx=-dx;}
//
//    y+=dy;
//    for (int i=0;i<n;i++)
//        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
//             {block[i].setPosition(-100,0); dy=-dy;}
//
//    if (x<0 || x>520)  dx=-dx;
//    if (y<0 || y>450)  dy=-dy;
//
//    if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6,0);
//    if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6,0);
//
//    if ( FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds()) ) dy=-(rand()%5+2);
//
//    sBall.setPosition(x,y);
//
//    app.clear();
//    app.draw(sBackground);
//    app.draw(sBall);
//    app.draw(sPaddle);
//
//    for (int i=0;i<n;i++)
//     app.draw(block[i]);
//
//    app.display();
//    }
//
//  return 0;
//}
