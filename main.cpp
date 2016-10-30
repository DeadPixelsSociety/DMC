#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "inc/CLevel.h"

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pouet");
	//window.setVerticalSyncEnabled(true);
	//window.setKeyRepeatEnabled(false);

	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;

	sf::Clock clock;
	
	sf::View view;
	view.reset(sf::FloatRect(0, 0, wWidth, wHeight));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	sf::Vector2f viewPos(wWidth / 2, wHeight / 2);

	CLevel *lvl = new CLevel("1");
	
	float moveSpeed = 1000.0f;
	
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
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			rect.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			rect.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
			
		//---- UPDATE ----
		
		if (rect.getPosition().x + 10 > wWidth / 2)
			viewPos.x = rect.getPosition().x + 10;
		else
			viewPos.x = wWidth / 2;
		
		view.setCenter(viewPos);
		
		lvl->update(clock.getElapsedTime().asSeconds(), wWidth, wHeight, moveSpeed);

		//---- DRAWING ----

		window.setView(view);
		
		window.clear(sf::Color::Black);
		
		lvl->draw(&window);

		window.draw(rect);
		
		window.display();
	}

	delete lvl;

	return EXIT_SUCCESS;
}
