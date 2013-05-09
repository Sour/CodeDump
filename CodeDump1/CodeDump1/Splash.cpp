#include "stdafx.h"
#include "Splash.h"

void Splash::Show(sf::RenderWindow & renderWindow) {

	sf::Texture texture;
	if(texture.loadFromFile("Image/Splash.png") != true) {
		std::cout << "Failed to load Image." << std::endl;
		return;
	}

	sf::Sprite sprite(texture);
	
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;

	while(true) {

		while(renderWindow.pollEvent(event)) {

			if(event.type == sf::Event::EventType::KeyPressed 
				|| event.type == sf::Event::EventType::MouseButtonPressed 
				|| event.type == sf::Event::EventType::Closed ) {

					return;
			}
		}
	}
}