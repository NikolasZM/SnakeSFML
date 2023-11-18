#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include<cstdlib>
using namespace sf;
using namespace std;

int tam = 10;

class serpiente {
public:
	int x;
	int y;
};
serpiente s[100];

void mov(int dir) {
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

int main()
{
	int dir = 0;
	int values[2][2] = { {1,2},{0,3} };
	int f = 500;
	RenderWindow window(VideoMode(50*tam, 50*tam), "Serpiente");
	RectangleShape snake(Vector2f(10.0f, 10.0f));
	RectangleShape fondo(Vector2f(10.0f, 10.0f));
	snake.setFillColor(Color::Blue);
	fondo.setFillColor(Color::White);

	Clock reloj;
	float timer = 0, delay = 0.1;
	int a = 0;
	srand(time(NULL));
	while(window.isOpen()) {
		float time = reloj.getElapsedTime().asSeconds();
		reloj.restart();
		timer += time;

		Event evnt;
		while (window.pollEvent(evnt)) {

			if (evnt.type == Event::Closed) {
				window.close();
			}

		}

		if (timer > delay) {
			timer = 0;
			mov(dir);
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

		cout << "dir = " << dir ;

		window.clear();
		for (int i{ 0 }; i < 50; i++) 
			for (int j{ 0 }; j < 50; j++) {
				fondo.setPosition(i*tam, j*tam);
				window.draw(fondo);
			}
		
		for (int i{ 0 }; i < 15; i++) {
			snake.setPosition(s[i].x * tam, s[i].y * tam);
			window.draw(snake);

		}

		window.display();
		a++;
	}

	return 0;
}