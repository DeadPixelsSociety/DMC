#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Clock.hpp>

#include "inc/CLevel.hpp"
#include "inc/CPlayer.hpp"
#include "inc/CHud.hpp"

/*
--- TOUTDOUX ---

	* QUAND FIN DE LOCK ZONE, SCROLLING BUG, DECALLAGE.

--- TOUTDOUX ---
*/

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pouet");
	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);
	//window.setKeyRepeatEnabled(false);
	
	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;
	sf::Vector2f wDim(wWidth, wHeight);

	CLevel lvl("1");
	
	CPlayer player(wDim, "Pouet");
	
	CHud hud("res/fonts/Hack-Regular.ttf", 15, sf::Vector2f(5, 5));
	
	sf::Clock clock;
	sf::Time frameTime;
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
						if (event.key.code == sf::Keyboard::Right) {
							player.setDirectionH(Right);
						} else if (event.key.code == sf::Keyboard::Left) {
							player.setDirectionH(Left);
						} else if (event.key.code == sf::Keyboard::Up) {
							player.setDirectionV(Up);
						} else if (event.key.code == sf::Keyboard::Down) {
							player.setDirectionV(Down);
						}
					}
					break;
						
				case sf::Event::KeyReleased :
					// Reset the direction of the player.
					switch (event.key.code)
					{
						case sf::Keyboard::Right : // fall throught
						case sf::Keyboard::Left :
							player.setDirectionH(NoneH);
							break;
						case sf::Keyboard::Up : // fall throught
						case sf::Keyboard::Down :
							player.setDirectionV(NoneV);
							break;
						default :
							break;
					}
					break;
					
				default :
					break;
			}
		}

		//---- UPDATE ----
		
		lvl.update(clock.getElapsedTime().asSeconds(), window, player);
		
		player.update(clock.getElapsedTime().asSeconds(), wDim, lvl.getLength(), lvl.getDepth());
		
		hud.update(window, frameTime, player, lvl);

		//---- DRAWING ----
		
		window.clear(sf::Color::Black);
		
		lvl.draw(window, player.getView());

		player.draw(window);
		
		hud.draw(window);
		
		window.display();
	}

	return EXIT_SUCCESS;
}
