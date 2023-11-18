#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include<cstdlib>
#include <thread>
using namespace sf;
using namespace std;

int tam = 10;
int dir = 0;
int values[2][2] = { {1,2},{0,3} };
int f = 800;

RenderWindow window(VideoMode(50 * tam, 50 * tam), "Serpiente");

RectangleShape fondo(Vector2f(10.0f, 10.0f));
RectangleShape snake1(Vector2f(10.0f, 10.0f));
RectangleShape snake2(Vector2f(10.0f, 10.0f));

Clock reloj;
float timer = 0, delay = 0.1;
int a = 0;
class serpiente {
public:
	int x;
	int y;
};
serpiente s1[100];
serpiente s2[15];

void mov(int dir,serpiente *s) {
	for (int i{ 15 }; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}
	switch (dir) {
	case 0: s[0].y += 1;
		break;
	case 1: s[0].x -= 1;
		break;
	case 2: s[0].x += 1;
		break;
	case 3: s[0].y -= 1;
		break;
	}

	if (s[0].x > 50) s[0].x = 0;
	if (s[0].y > 50) s[0].y = 0;
	if (s[0].x < 0) s[0].x = 50;
	if (s[0].y < 0) s[0].y = 50;

}

void f1(serpiente * ser1) {
	srand(time(NULL));
	
	if (timer > delay) {
		timer = 0;
		mov(dir, ser1);
	}

	if (a % f == 0) {
		int it = rand() % 2;
		if (dir == 0 || dir == 3) {
			dir = values[0][it];
			f = rand() % 500 + 500;
		}
		else {
			dir = values[1][it];
			f = rand() % 500 + 500;
		}
	}


}

int main()
{
	thread t1;
	thread t2;
	
	fondo.setFillColor(Color::Blue);
	snake1.setFillColor(Color::Black);
	snake2.setFillColor(Color::Red);
	

	while (window.isOpen()) {
		float time = reloj.getElapsedTime().asSeconds();
		reloj.restart();
		timer += time;

		Event evnt;
		while (window.pollEvent(evnt)) {

			if (evnt.type == Event::Closed) {
				window.close();
			}
			break;
		}
		window.clear();

		t1 = thread(f1, s1);
		t2 = thread(f1, s2);
		t1.join();
		t2.join();
		//f1(s1, Color::Black);

		for (int i{ 0 }; i < 50; i++)
			for (int j{ 0 }; j < 50; j++) {
				fondo.setPosition(i * tam, j * tam);
				window.draw(fondo);
			}
		
		for (int i{ 0 }; i < 15; i++) {
			snake1.setPosition(s1[i].x * tam, s1[i].y * tam);
			window.draw(snake1);

		}
		for (int i{ 0 }; i < 15; i++) {
			snake2.setPosition(s2[i].x * tam, s2[i].y * tam);
			window.draw(snake2);

		}
		window.display();
		a++;
		//system("pause");
	}

	return 0;
}