#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Code Dump");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch(event.type){

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape){
					cout << "the escape key was pressed"    << endl;
					cout << "control:" << event.key.control << endl;
					cout << "alt:"     << event.key.alt     << endl;
					cout << "shift:"   << event.key.shift   << endl;
					cout << "system:"  << event.key.system  << endl;
				}
				break;

			case sf::Event::MouseMoved:
				cout << "new mouse x: " << event.mouseMove.x << endl;
				cout << "new mouse y: " << event.mouseMove.y << endl;
				break;

			case sf::Event::MouseEntered:
				cout << "the mouse cursor has entered the window" << endl;
				break;

			case sf::Event::MouseLeft:
				cout << "the mouse cursor has left the window" << endl;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right){
					cout << "the right button was pressed"     << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
				}

				if (event.mouseButton.button == sf::Mouse::Left){
					cout << "the left button was pressed"     << endl;
					cout << "mouse x: " << event.mouseButton.x << endl;
					cout << "mouse y: " << event.mouseButton.y << endl;
				}
				break;

			default:
				break;

			}
        }

        window.display();
    }

    return 0;
}