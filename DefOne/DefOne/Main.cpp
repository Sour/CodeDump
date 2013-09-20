#include "stdafx.h"

float clamp(float value, float min, float max)
{
	if(value < min)
		return min;

	if(value > max)
		return max;

	return value;
}

bool cirToRect ( const RectangleShape &rect, const CircleShape &circle)
{
	FloatRect r = rect.getGlobalBounds();
	FloatRect b = circle.getGlobalBounds();
	return r.intersects(b);
}
bool ballToTopOnly( const RectangleShape &rect, const CircleShape &circle)
{
	FloatRect r = rect.getGlobalBounds();
	FloatRect b = circle.getGlobalBounds();


	float left,right,center;

	left = r.left;
	right = r.left + r.width;
	center = b.left + b.width / 2;

	if(center > left && center < right)
	{
		if(r.top<b.top + b.height && b.top < r.top + r.height / 2)
		{
			return true;
		}
	}
	return false;
}

class Game
{
private:
	const static int width = 640;
	const static int height = 480;
	const static int borderSize = 10;

	const static int MAX_FRAMERATE = 60;
	const static int MAX_FRAMESKIP = 10;

	const static int moveDistance = 20;
	const static int maxScore = 8;

	RenderWindow _mainWindow;

	RectangleShape grid[8];

	RectangleShape top;
	RectangleShape left;
	RectangleShape right;

	RectangleShape player;

	CircleShape ball;

	Font font;
	Text won;

	Texture ballTexture,paddle,brick,brickLow;

	enum gameState {Initializing, Waiting, Paused, Playing, Exiting, Won};

	gameState _gameState;

	Vector2f ballSpeed;

	Event event;

	Time elapsed;
	Int32 updateTime;


public:
	Game(){};

	int manageTime()
	{
		Clock clock, frameClock;
		while (_mainWindow.isOpen())
		{
			const Int64 frameTime = 1000000/MAX_FRAMERATE;
			Time t = clock.getElapsedTime();
			Int64 nextFrameTime = t.asMicroseconds() + frameTime;


			int loops = 0;
			while (t.asMicroseconds() < nextFrameTime && loops < MAX_FRAMESKIP)
			{
				elapsed = frameClock.restart();
				systemEvents();
				updateObjects();
				t = clock.getElapsedTime();
				loops++;
			}
			display();
		}
		return EXIT_SUCCESS;
	}

	bool initGame()
	{
		if(!font.loadFromFile("Walkway_Black.ttf"))
			return false;

		if (!ballTexture.loadFromFile("ballBlue.png"))
			return false;

		if (!paddle.loadFromFile("paddle.png"))
			return false;

		if (!brick.loadFromFile("brickGrey.png"))
			return false;

		if (!brickLow.loadFromFile("brickRed.png"))
			return false;


		_mainWindow.create(VideoMode(width,height,32),"Breakout v2");
		_mainWindow.setFramerateLimit(MAX_FRAMERATE);
		_mainWindow.setVerticalSyncEnabled(true);

		top.setPosition(0,0);
		top.setSize(Vector2f(width,borderSize));
		top.setFillColor(Color::White);

		left.setPosition(0,0);
		left.setSize(Vector2f(borderSize,height));
		left.setFillColor(Color::White);

		right.setPosition(width-borderSize,0);
		right.setSize(Vector2f(borderSize,height));
		right.setFillColor(Color::White);

		player.setSize(Vector2f(60, 10));
		player.setPosition((width / 2) - (player.getGlobalBounds().width / 2), height - 30);
		player.setTexture(&paddle);

		ball.setRadius(10);
		ball.setFillColor(Color::White);
		ball.setPosition(Vector2f(
			(player.getGlobalBounds().left + player.getGlobalBounds().width/2) - ball.getRadius(), 
			(player.getGlobalBounds().top - ball.getGlobalBounds().height -1)
			)); 
		ball.setTexture(&ballTexture);

		won.setString("You Won!");
		won.setPosition(won.getGlobalBounds().width / 2 - width / 2,height/2);
		won.setColor(Color::White);
		won.setCharacterSize(24);
		won.setFont(font);

		ballSpeed = Vector2f(-1,-1);

		_gameState = Playing;	
		createGrid();
		return true;
	}

	void createGrid()
	{
		for(int i=0;i<8;i++)
		{
			if(i != 0)
			{
				grid[i].setSize(Vector2f(66.0f,20.0f));
				grid[i].setTexture(&brick);
				grid[i].setPosition(
					grid[i-1].getGlobalBounds().left + grid[i-1].getGlobalBounds().width + 10 ,
					top.getGlobalBounds().top + top.getGlobalBounds().height + 10
					);
			}else{
				grid[i].setSize(Vector2f(66.0f,20.0f));
				grid[i].setTexture(&brick);
				grid[i].setPosition(
					left.getGlobalBounds().left + left.getGlobalBounds().width + 10 ,
					top.getGlobalBounds().top + top.getGlobalBounds().height + 10
					);
			}
		}
		manageTime();
	}

	void systemEvents()
	{
		while (_mainWindow.pollEvent(event))
		{
			if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				_mainWindow.close();
			}else if((event.type == Event::KeyPressed) && (_gameState == Waiting))
			{
				_gameState = Playing;
			}
		}
	}

	void updateObjects()
	{
			updatePlayer();
			updateBall();
			checkCollisions();
			checkScore();
	}


	void updatePlayer()
	{
		FloatRect p = player.getGlobalBounds();

		if(Keyboard::isKeyPressed(Keyboard::A))
			if(clamp(p.left,borderSize,width - borderSize) == p.left)
				player.move(-moveDistance * elapsed.asMilliseconds() / 40,0);

		if(Keyboard::isKeyPressed(Keyboard::D))
			if(clamp(p.left + p.width,borderSize,width - borderSize) == p.left + p.width)
				player.move(moveDistance * elapsed.asMilliseconds() / 40,0);
	}

	void updateBall()
	{
		ball.move(
			ballSpeed.x * elapsed.asMilliseconds() / 7,
			ballSpeed.y * elapsed.asMilliseconds() / 7
			);
	}

	void checkCollisions()
	{
		if(ballToTopOnly(player,ball))
		{
			FloatRect p = player.getGlobalBounds();
			FloatRect b = ball.getGlobalBounds();
			if(
				b.top - b.height >= p.top - 1 && 
				(b.left + b.width / 2) > p.left || 
				(b.left + b.width / 2) < p.left + p.width
				)
			{
				float speed = sqrtf((ballSpeed.x * ballSpeed.x) + (ballSpeed.y * ballSpeed.y));
				float angle = ((b.left + b.width / 2) - (p.left + p.width / 2))*1.5f ;

				ballSpeed.x = sinf(angle*(PI/180)) * speed;
				ballSpeed.y = -abs(cosf(angle*(PI/180)) * speed);
				cout<<"SPEED: "<<speed<<" ANGLE: "<<angle<<" X: "<<ballSpeed.x<<" Y: "<<ballSpeed.y<<endl<<endl;

				ballSpeed.x *= 1.02f;
				ballSpeed.y *= 1.02f;


				ball.setPosition(b.left,p.top - b.height - 1);
				updateBall();
			}

		}

		if(cirToRect(top,ball))
		{
			ballSpeed.y = -ballSpeed.y;
			updateBall();
		}
		if(cirToRect(left,ball) || cirToRect(right,ball))
		{
			ballSpeed.x = -ballSpeed.x;
			updateBall();
		}
		for(int i=0;i<8;i++)
		{
			if(cirToRect(grid[i],ball))
			{
				if(grid[i].getTexture() == &brick)
				{
					grid[i].setTexture(&brickLow);
					ballSpeed.y *=-1;
					updateBall();
				}
				else
				{
					grid[i].setPosition(Vector2f(-100,-100));
				}
			}
		}
	}

	void checkScore()
	{
		unsigned int score = 0;
		for(int i=0;i<8;i++)
		{
			if(grid[i].getPosition() == Vector2f(-100,-100))
			{
				score++;
			}
		}
		if(score == maxScore)
			_gameState = Won;
	}

	void display()
	{
		switch(_gameState)
		{
		case Playing:
			_mainWindow.clear();
			_mainWindow.draw(top);
			_mainWindow.draw(left);
			_mainWindow.draw(right);
			_mainWindow.draw(player);
			_mainWindow.draw(ball);
			for each (RectangleShape rect in grid)
				_mainWindow.draw(rect);

			break;

		case Won:
			_mainWindow.clear();
			_mainWindow.draw(won);
			_mainWindow.display();
			break;
		}
		_mainWindow.display();
	}
};

int main()
{
	Game game;
	return game.initGame();
}