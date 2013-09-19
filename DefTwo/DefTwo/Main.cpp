#include <SFML\Graphics.hpp>
#include <iostream>
 
using namespace sf;
 
bool intersects (const RectangleShape & rect1,const RectangleShape & rect2)
{
    FloatRect r1=rect1.getGlobalBounds();
    FloatRect r2=rect2.getGlobalBounds();
    return r1.intersects (r2);
}
 
int main()
{
    const int width = 640;
    const int height= 480;
    const int borderSize= 30;
 
    VideoMode videoMode(width, height);
    RenderWindow window(videoMode,"Rectangle Collision");
 
    RectangleShape top;
    RectangleShape left;
    RectangleShape right;
    RectangleShape bottom;
 
    top.setPosition(borderSize, 0);
    top.setSize(Vector2f(width-2*borderSize, borderSize));
 
    left.setPosition(0, 0);
    left.setSize(Vector2f(borderSize, height));
 
    right.setPosition(width-borderSize, 0);
    right.setSize(Vector2f(borderSize, height));
 
    bottom.setPosition(borderSize, height-borderSize);
    bottom.setSize(Vector2f(width-2*borderSize, borderSize));
 
    top.setFillColor(Color(100,100,100));
    top.setOutlineColor(Color::Blue);
    top.setOutlineThickness(3);
 
    left.setFillColor(Color(100,100,100));
    left.setOutlineColor(Color::Blue);
    left.setOutlineThickness(3);
 
    right.setFillColor(Color(100,100,100));
    right.setOutlineColor(Color::Blue);
    right.setOutlineThickness(3);
 
    bottom.setFillColor(Color(100,100,100));
    bottom.setOutlineColor(Color::Blue);
    bottom.setOutlineThickness(3);
 
    RectangleShape ball;
    ball.setPosition(width/2, height/2);
    ball.setSize(Vector2f(20, 20));
    ball.setFillColor(Color::Red);
    ball.setOutlineColor(Color::Yellow);
    ball.setOutlineThickness(1);
 
    Vector2f ballSpeed(0.1,0.1);
 
    while (window.isOpen())
    {
        window.clear(Color::White);
        window.draw(top);
        window.draw(bottom);
        window.draw(left);
        window.draw(right);
        window.draw(ball);
        window.display();
 
        Event event;
        while (window.pollEvent(event))
        {
            if ( (event.type == Event::Closed) ||
            ((event.type == Event::KeyPressed) && (event.key.code==Keyboard::Escape)) )
                window.close();
 
        }
 
        if (intersects(ball,top) || intersects(ball,bottom) )
        {
            ballSpeed.y=-ballSpeed.y;
        }
        if (intersects(ball,left) || intersects(ball,right))
        {
            ballSpeed.x=-ballSpeed.x;
        }
 
        ball.move(ballSpeed.x,ballSpeed.y);
    }
    return EXIT_SUCCESS;
}