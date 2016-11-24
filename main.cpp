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

--- TOUTDOUX ---
*/

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pouet");
	window.setFramerateLimit(61);
	
	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;
	sf::Vector2f wDim(wWidth, wHeight);

	CLevel lvl("1");
	
	CPlayer player(wDim, "Pouet");
	
	CHud hud("res/fonts/Hack-Regular.ttf", 15, sf::Vector2f(5, 5));
	
	sf::Clock clock;
	sf::Time frameTime;
	float dt;
	while (window.isOpen())
	{
		frameTime = clock.restart();
	
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
					{
						window.close();
					}
					else {
						// Set the direction of the player
						switch (event.key.code) {
							case sf::Keyboard::Right :
								player.setDirectionH(Right);
								break;
							case sf::Keyboard::Left :
								player.setDirectionH(Left);
								break;
							case sf::Keyboard::Up :
								player.setDirectionV(Up);
								break;
							case sf::Keyboard::Down :
								player.setDirectionV(Down);
								break;
							default: break;
						}
					}
					break;
						
				case sf::Event::KeyReleased :
					// Reset the direction of the player.
					switch (event.key.code)
					{
						case sf::Keyboard::Right : // fall through
						case sf::Keyboard::Left :
							player.setDirectionH(NoneH);
							break;
						case sf::Keyboard::Up : // fall through
						case sf::Keyboard::Down :
							player.setDirectionV(NoneV);
							break;
						default : break;
					}
					break;
					
				default :
					break;
			}
		}

		//---- UPDATE ----
		
		dt = clock.getElapsedTime().asSeconds();
		
		lvl.update(dt, window, player);
		
		player.update(dt, wDim, lvl.getLength(), lvl.getDepth());
		
		hud.update(window, frameTime, player, lvl);

		//---- DRAWING ----
		
		window.clear(sf::Color::Black);
		
		lvl.draw(window, player);
		
		hud.draw(window);
		
		window.display();
	}

	return EXIT_SUCCESS;
}
