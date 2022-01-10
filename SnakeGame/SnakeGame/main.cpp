//Happy Gaming
//Part of comment are quoted from the "Documentation of SFML 2.5.1"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <time.h>

/*
* Test window
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Hello world");

	sf::Event event;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}
	}

	return 0;
}*/


using namespace sf;

int N = 30, M = 20;
int size = 16; //the size of images is 16*16 pixels
int w = size * N; //w is the width of the window
int h = size * M; //h is the height of the window

int dir, num = 4; // 4 is the inital length of the snake
int keylog[9999], counter=0;
struct Snake
{
    int x, y; //coordinates. Note that the origin of the coordinate system is at the top left corner of the window
}  s[100]; //The maximum length of the snake is 100 units

struct Fruit
{
    int x, y;
} f;

void Tick()
{
    //snake moving forward
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }

    //Change the direction
    //if (log[counter-1] == 1)
    if (dir == 0) s[0].y += 1;//down
    if (dir == 1) s[0].x -= 1;//left
    if (dir == 2) s[0].x += 1;//right
    if (dir == 3) s[0].y -= 1;//up

    //Cheak if the snake eat a fruit, if yes, then add one unit of length of it and reset the position of the fruit
    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++; f.x = rand() % N; f.y = rand() % M;
    }

    //let the snake comes out at the opposite side of wherever it "hits" a wall
    if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y)  num = i; //bug, if you go back, the length of the snake would bug
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    Texture t1, t2;
    t1.loadFromFile("images/white.png"); //white square
    t2.loadFromFile("images/red.png");  //red square

    //construct the sprite from a sub-rectangle of a source texture
    Sprite sprite1(t1);
    Sprite sprite2(t2);

    //initialize a timer
    Clock clock;
    float timer = 0, delay = 0.1;

    //The inital position of the fruit
    f.x = 10;
    f.y = 10;

    //create the window
    while (window.isOpen())
    {
        //start the timer,then wait every delay(0.1) second to call the Tick function
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //The close buttom, to close the window:
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        //detect keyboard input
        //int currentDir=5;
        if (Keyboard::isKeyPressed(Keyboard::Left)) { dir = 1; counter++; }
        if (Keyboard::isKeyPressed(Keyboard::Right)) { dir = 2; counter++; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;
        
        keylog[counter] = dir;
        if (timer > delay) { timer = 0; Tick();}
        
        window.clear();

        ////// draw and redraw ///////
      
        //fill the window with white squares
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        //draw the snake
        for (int i = 0; i < num; i++)
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);
        }
        
        //draw the fruit
        sprite2.setPosition(f.x * size, f.y * size);  window.draw(sprite2);

        window.display();
    }

    for (int i = 0; i < 10; i++) {
        std::cout << keylog[i]<<std::endl;
    }

    return 0;
}

