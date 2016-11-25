#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "inc/CLevel.hpp"
#include "inc/CPlayer.hpp"
#include "inc/CHud.hpp"

/*
--- TOUTDOUX ---

	[JEREMY] - Implementer le saut.
	
	[PAUL] - CLevel entierement fini ?
		   - Musique.
		   - Beurk -> player m_lastViewDep.

--- TOUTDOUX ---
*/

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pouet");	
	window.setFramerateLimit(60);
	
	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;
	sf::Vector2f wDim(wWidth, wHeight);

	CLevel lvl("1", wDim);
	
	CPlayer player(wDim, "Pouet");
	
	CHud hud("res/fonts/Hack-Regular.ttf", 15, sf::Vector2f(5, 5));
	
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	while (window.isOpen())
	{	
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
					switch (event.key.code)
					{
					 	case sf::Keyboard::Escape :
					 		window.close();
					 		break;
					 	case sf::Keyboard::T :
							hud.toggle();
							break;
						default : break;
					}
					break;
					
				default :
					break;
			}
		}

		// Set the direction of the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player.setDirectionH(Right);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			player.setDirectionH(Left);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			player.setDirectionV(Up);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.setDirectionV(Down);

		//---- UPDATE ----
		
		deltaTime = clock.restart();

		lvl.update(deltaTime, window, player);
	
		player.update(deltaTime, wDim, lvl.getLength(), lvl.getDepth());
	
		hud.update(deltaTime, window, player, lvl);

		//---- DRAWING ----
		
		window.clear(sf::Color::Black);
		
		lvl.draw(window, player);
		
		hud.draw(window);
		
		window.display();
	}

	return EXIT_SUCCESS;
}
