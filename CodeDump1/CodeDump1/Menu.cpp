#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window) {

	//Load menu image from file

	sf::Texture texture;
	texture.loadFromFile("images/mainmenu.png");
	sf::Sprite sprite(texture);

	//Setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.Top = 145;
	playButton.rect.Bottom = 380;
	playButton.rect.Left = 0;
	playButton.rect.Right = 1023;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.Top = 0;
	exitButton.rect.Bottom = 1023;
	exitButton.rect.Left = 383;
	exitButton.rect.Right = 560;
	exitButton.action = play;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();
	
	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
	
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it != _menuItems.end(); it++ ) {
		
		sf::Rect<int> menuItemRect = (*it).rect;

		if ( menuItemRect.Bottom > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.right > x ) {

}
