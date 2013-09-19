#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <math.h>

#define PI 3.1415926

using namespace sf;
using namespace std;



bool rectToRect ( const RectangleShape &rect1, const RectangleShape &rect2)
{
	FloatRect r1 = rect1.getGlobalBounds();
	FloatRect r2 = rect2.getGlobalBounds();
	return r1.intersects(r2);
}

Vector2f clamp(RectangleShape obj, RectangleShape top)
{
	switch(rectToRect(obj,top))
	{
	case true:
		return Vector2f(obj.getPosition().x,16);
		break;
	case false:
		return Vector2f(obj.getPosition().x,402);
		break;
	}
}

bool cirToRect ( const RectangleShape &rect, const CircleShape &circle)
{
	FloatRect r = rect.getGlobalBounds();
	FloatRect b = circle.getGlobalBounds();
	return r.intersects(b);
}

class Game
{
private:
	static const int width = 640;
	static const int height = 480;
	static const int borderSize = 12;

	static const int FRAMES_PER_SECOND = 60;
	static const int MAX_FRAMESKIP = 10;

	static const int moveDistance = 20;

	RenderWindow window;
	Font font;

	RectangleShape top;
	RectangleShape bottom;
	RectangleShape left;
	RectangleShape right;
	RectangleShape split;

	CircleShape ball;

	Vector2f ballSpeed;

	RectangleShape player1;
	RectangleShape player2;

	Text score;
	Text showFps;
	Text playerOneWin;
	Text playerTwoWin;

	Time time;
	Int32 updateTime;

	unsigned int playerOneScore, playerTwoScore;

	enum states {WAITING, PLAYING, PLAYER_ONE, PLAYER_TWO};

	int gameState;

public:
	Game(){};

	bool init()
	{
		VideoMode videoMode(width, height);
		window.create(videoMode,"Pong v2");
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(FRAMES_PER_SECOND);

		if(!font.loadFromFile("Walkway_Black.ttf"))
			return false;

		setup();
		return true;
	}

	int exec()
	{
		Clock renderClock, updateClock;

		while (window.isOpen())
		{
			Time time = renderClock.getElapsedTime();
			float fps = 1000000/time.asMicroseconds();
			stringstream s;
			s << fps <<" fps";
			showFps.setString(s.str());
			renderClock.restart();

			const Int64 frameTime = 1000000/FRAMES_PER_SECOND;
			Clock c;
			Time t = c.getElapsedTime();
			Int64 nextFrameTime = t.asMicroseconds() + frameTime;

			int loops = 0;
			while (t.asMicroseconds() < nextFrameTime && loops < MAX_FRAMESKIP)
			{
				systemEvents();
				updateTime = updateClock.restart().asMilliseconds();
				t = c.getElapsedTime();

				updateObjects();

				loops++;

			}
			display();
		}
		return EXIT_SUCCESS;
	}
private:
	void systemEvents()
	{
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			{
				window.close();
			}else if((event.type == Event::KeyPressed) && (gameState == WAITING))
			{
				gameState = PLAYING;
			}
		}
	}

	void updateObjects()
	{
		if(gameState != PLAYING)
			return;

		updatePlayer1();
		updatePlayer2();
		checkCollisions();
		updateBall();
		checkScores();
	}

	void setup()
	{
		ball.setOrigin(Vector2f(6.5f,6.5f));

		player1.setPosition(borderSize * 2, height/2);
		player1.setSize(Vector2f(12,60));
		player1.setFillColor(Color::White);
		player1.setOutlineColor(Color(100,100,100));
		player1.setOutlineThickness(2);

		player2.setPosition(width - borderSize * 2, height/2);
		player2.setSize(Vector2f(12,60));
		player2.setFillColor(Color::White);
		player2.setOutlineColor(Color(100,100,100));
		player2.setOutlineThickness(2);

		top.setPosition(0,0);
		top.setSize(Vector2f(width,borderSize));
		top.setFillColor(Color::White);

		bottom.setPosition(0,height-borderSize);
		bottom.setSize(Vector2f(width,borderSize));
		bottom.setFillColor(Color::White);

		left.setPosition(0,0);
		left.setSize(Vector2f(borderSize,height));
		left.setFillColor(Color::White);

		right.setPosition(width-borderSize,0);
		right.setSize(Vector2f(borderSize,height));
		right.setFillColor(Color::White);

		score.setString("0   0");
		score.setFont(font);
		score.setCharacterSize(30);
		score.setPosition(Vector2f(width/2-score.getGlobalBounds().width/2,borderSize*2));
		score.setColor(Color::White);

		showFps.setString("0");
		showFps.setFont(font);
		showFps.setCharacterSize(30);
		showFps.setPosition(Vector2f(borderSize*2,borderSize*2));
		showFps.setColor(Color::White);

		playerOneWin.setString("Player 1 Wins!");
		playerOneWin.setFont(font);
		playerOneWin.setCharacterSize(60);
		playerOneWin.setPosition(Vector2f(width / 2 - (playerOneWin.getGlobalBounds().width / 2), height / 2 - (playerOneWin.getGlobalBounds().height / 2)));
		playerOneWin.setColor(Color::White);

		playerTwoWin.setString("Player 2 Wins!");
		playerTwoWin.setFont(font);
		playerTwoWin.setCharacterSize(60);
		playerTwoWin.setPosition(Vector2f(width / 2 - (playerOneWin.getGlobalBounds().width / 2), height / 2 - (playerOneWin.getGlobalBounds().height / 2)));
		playerTwoWin.setColor(Color::White);

		ball.setPosition(width/2,height/2);
		ball.setRadius(borderSize);
		ball.setFillColor(Color(100,100,100));

		split.setOrigin(3,0);
		split.setPosition(width/2,0);
		split.setSize(Vector2f(3,height));
		split.setFillColor(Color::White);

		Vector2f ballSpeed(8,8);
		unsigned int pScore = 0, aScore=0;

		resetGame1();
		playerOneScore = 0;
		playerTwoScore = 0;
		gameState = WAITING;
	}

	void display()
	{
		window.clear();
		switch(gameState)
		{
		case WAITING:
			window.draw(top);
			window.draw(bottom);
			window.draw(left);
			window.draw(right);
			window.draw(split);
			break;
		case PLAYING:
			window.draw(top);
			window.draw(bottom);
			window.draw(left);
			window.draw(right);
			window.draw(split);
			window.draw(score);
			window.draw(showFps);
			window.draw(ball);
			window.draw(player1);
			window.draw(player2);
			break;
		case PLAYER_ONE:
			window.draw(playerOneWin);
			break;
		case PLAYER_TWO:
			window.draw(playerTwoWin);
			break;
		}
		window.display();
	}

	void updatePlayer1()
	{
		if (Keyboard::isKeyPressed(Keyboard::Up))
			player1.move(0, -moveDistance * updateTime / 50.0);
		else
			if (Keyboard::isKeyPressed(Keyboard::Down))
				player1.move(0,  moveDistance * updateTime / 50.0);
	}

	void updatePlayer2()
	{
		if (ball.getPosition().y < player2.getPosition().y)
			player2.move(0, -moveDistance * updateTime / 50.0);
		else if(ball.getPosition().y + ball.getRadius() > player2.getPosition().y + player2.getSize().y)
			player2.move(0,  moveDistance * updateTime / 50.0);
	}

	void updateBall()
	{
		ball.move(ballSpeed.x*updateTime,ballSpeed.y*updateTime);
	}

	void checkCollisions()
	{

		if(rectToRect(player1, bottom) || rectToRect(player1, top))
		{
			player1.setPosition(clamp(player1,top));
		}

		if(rectToRect(player2, bottom) || rectToRect(player2, top))
		{
			player2.setPosition(clamp(player2,top));
		}

		if(cirToRect(top, ball))
		{
			ball.move(0,1);
			ballSpeed.y *= -1;
		}

		if(cirToRect(bottom, ball))
		{
			ball.move(0,-1);
			ballSpeed.y *= -1;
		}

		if(cirToRect(player1, ball))
		{
			FloatRect p = player1.getGlobalBounds();
            FloatRect b = ball.getGlobalBounds();

			Vector2f o = Vector2f(p.left + p.width / 2, p.top + p.height / 2);
			Vector2f om = Vector2f(b.left + b.width / 2 - o.x, b.top + b.height / 2 - o.y);

			om.x /= p.width;
			om.y /= p.height;

			float angle = atan2(om.y, om.x);
			if( abs(angle) > PI/2 )
			{
				ballSpeed.x = abs(ballSpeed.x);
                ballSpeed.y = (b.top + b.height / 2 - p.top - p.height / 2) / 100;

                ball.move(5,0);

                ballSpeed.x*=1.02f;
                ballSpeed.y*=1.02f;  
			}
		}

		if(cirToRect(player2, ball))
		{
			FloatRect p = player2.getGlobalBounds();
            FloatRect b = ball.getGlobalBounds();

			Vector2f o = Vector2f(p.left + p.width / 2, p.top + p.height / 2);
			Vector2f om = Vector2f(b.left + b.width / 2 - o.x, b.top + b.height / 2 - o.y);

			om.x /= p.width;
			om.y /= p.height;

			float angle = atan2(om.y, om.x);
			if( abs(angle) > PI/2 )
			{
				ballSpeed.x = -abs(ballSpeed.x);
                ballSpeed.y = (b.top + b.height / 2 - p.top - p.height / 2) / 100;

                ball.move(-5,0);

                ballSpeed.x*=1.02f;
                ballSpeed.y*=1.02f;  
			}
		}

		if(cirToRect(left,ball))
		{
			playerTwoScore++;
			stringstream s;
			s << playerOneScore << "   " << playerTwoScore;
			score.setString(s.str());
			score.setPosition(width / 2 - score.getGlobalBounds().width / 2, 40);
			resetGame2();
		}

		if(cirToRect(right,ball))
		{
			playerOneScore++;
			stringstream s;
			s << playerOneScore << "   " << playerTwoScore;
			score.setString(s.str());
			score.setPosition(width / 2 - score.getGlobalBounds().width / 2, 40);
			resetGame1();
		}



	}

	void checkScores()
	{
		if (playerOneScore >=11 && playerOneScore >= playerTwoScore +2)
			gameState=PLAYER_ONE;
		if (playerTwoScore >=11 && playerTwoScore >= playerOneScore +2)
			gameState=PLAYER_TWO;
	}

	void resetGame1()
	{
		FloatRect p = player1.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		ball.setPosition(p.left + p.width + 10, height / 2);
		ballSpeed.x = 0.3f;
		ballSpeed.y = 0.3f;
	}

	void resetGame2()
	{
		FloatRect p = player2.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();
		ball.setPosition(p.left - b.width - 5, height / 2);
		ballSpeed.x = -0.3f;
		ballSpeed.y = 0.3f;
	}
};

int main()
{
	Game game;
	if (!game.init())
		return EXIT_FAILURE;
	return game.exec();
}