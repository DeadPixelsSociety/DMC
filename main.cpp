#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "inc/CLevel.h"

// REVOIR DIMENSION ET CALCUL PATH.PNG !!!!!!!!!!!!!!!!!!!!!!
// TJRS LE CALCULER DU .PNG OU LE METTRE EN BRUT DANS .YAML ?

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pouet");
	//window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);
	//window.setKeyRepeatEnabled(false);

	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;

	sf::Clock clock;
	
	// Set the view of the player.
	sf::View view;
	view.reset(sf::FloatRect(0, 0, wWidth, wHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPos(wWidth / 2, wHeight / 2);

	CLevel *lvl = new CLevel("1");
	
	float moveSpeed = 10000.0f;
	
	// Set the pseudo player.
	sf::RectangleShape rect(sf::Vector2f(20, 20));
	rect.setPosition(0, wHeight - 20);
	rect.setFillColor(sf::Color::Black);
	
	while (window.isOpen())
	{
	
		clock.restart();
	
		//---- EVENT ----
	
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed :		
					window.close();
					break;
					
				case sf::Event::KeyPressed :		
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					break;
					
				default :
					break;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rect.getPosition().x < lvl->getLength() - 20)
			rect.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rect.getPosition().x >= 0)
			rect.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rect.getPosition().y > wHeight - 84 - 20) // 84 est que .getDepth() devrais retourner.
			rect.move(0, (-moveSpeed / 3) * clock.getElapsedTime().asSeconds());
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rect.getPosition().y <= wHeight - 20)
			rect.move(0, (moveSpeed / 3) * clock.getElapsedTime().asSeconds());
			
		//---- UPDATE ----
		
		// Move or stop the scrolling when the player is either
		// at the start of the level or at the end.
		if (rect.getPosition().x + 10 > wWidth / 2)
		{	
			viewPos.x = rect.getPosition().x + 10;
			
			if (rect.getPosition().x + 10 > lvl->getLength() - (wWidth / 2))
			{
				viewPos.x = lvl->getLength() - (wWidth / 2);
			}
		}
		else
		{
			viewPos.x = wWidth / 2;
		}
		
		view.setCenter(viewPos);
		
		//lvl->update(clock.getElapsedTime().asSeconds(), sf::Vector2f(wWidth, wHeight), moveSpeed);

		//---- DRAWING ----

		window.setView(view);
		
		window.clear(sf::Color::Black);
		
		lvl->draw(&window, &view);

		window.draw(rect);
		
		window.display();
	}

	delete lvl;

	return EXIT_SUCCESS;
}
