#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

bool isCollide(Sprite s1, Sprite s2);

void main(void)
{
	RenderWindow app(VideoMode(520, 450), "Arkanoid");
	app.setFramerateLimit(60);

	// �ؽ��� load
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");

	// image ��ġ
	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 400);
	sBall.setPosition(300, 300);

	Sprite block[1000];
	int n = 0;
	for(int i=1; i<=10; i++)
		for(int j=0; j<=10; j++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}
	// ���� �߻簢��
	float dx = 6.0f, dy = 5.0f;


	while(app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

		// ���� ������ �浹�ϸ� ������ ���ְ�, ���� ������ �ݴ��
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

		// ���� boundary ����
		Vector2f b = sBall.getPosition();
		if (b.x < 0 || b.x > 520)
			dx = -dx;
		if (b.y < 0 || b.y > 450)
			dy = -dy;


		app.clear();
		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);

		app.display();
	}
}

// �簢�浹
bool isCollide(Sprite s1, Sprite s2)
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
