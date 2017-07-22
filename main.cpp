#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "inc/CLevel.hpp"
#include "inc/CPlayer.hpp"
#include "inc/CHud.hpp"

/*
--- TOUTDOUX ---

	[JEREMY] - Implementer le saut.
	
	[PAUL] - Fix le bupbup
		   - CLevel entierement fini ?
		   - Musique.
		   - Beurk -> player m_lastViewDep.
		   - Possible simplifier reset direction player
		     ou besoins de l'info pour foes ou autre ?

--- TOUTDOUX ---
*/

void processEvent(sf::Event event, sf::RenderWindow &window, CPlayer &player, CHud &hud)
{
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
			
			case sf::Event::KeyReleased :
				// Reset the direction or action of the player
				switch (event.key.code)
				{
				 	case sf::Keyboard::Right :
				 	case sf::Keyboard::D :
				 	case sf::Keyboard::Left :
				 	case sf::Keyboard::Q :
				 		player.setDirectionH(DIR_NONEH);
				 		break;
				 	case sf::Keyboard::Up :
				 	case sf::Keyboard::Z :
				 	case sf::Keyboard::Down :
				 	case sf::Keyboard::S :
				 		player.setDirectionV(DIR_NONEV);
				 		break;
				 	case sf::Keyboard::Space :
				 	case sf::Keyboard::Slash :
				 	case sf::Keyboard::G :
				 	case sf::Keyboard::RControl :				 	
				 	  player.setAction(ACT_NONE);
				 	  break;
					default : break;
				}
				break;
			default :
				break;
		}
	}

	// Set the direction of the player.
	// Better reactivity with isKeyPressed()
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.setDirectionH(DIR_RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		player.setDirectionH(DIR_LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		player.setDirectionV(DIR_UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player.setDirectionV(DIR_DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
		player.setAction(ACT_JUMP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		player.setAction(ACT_ATTACK);
}

int main ()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "DMC");	
	window.setFramerateLimit(60);
	
	float wWidth = window.getSize().x;
	float wHeight = window.getSize().y;
	sf::Vector2f wDim(wWidth, wHeight);
	
	CPlayer player(wDim, "Pouet");
	
	CLevel lvl("1", wDim);
	CHud hud("res/fonts/Hack-Regular.ttf", 15, sf::Vector2f(5, 5));
	
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	
	sf::Event event;
	while (window.isOpen())
	{	
		//std::cout << player.getView().getCenter().x << " - " << player.getView().getCenter().y << std::endl;
	
		//---- EVENT ----

		processEvent(event, window, player, hud);

		//---- UPDATE ----
		
		deltaTime = clock.restart();

		lvl.update(deltaTime, window, player);
	
		hud.update(deltaTime, window, player, lvl);

		//---- DRAWING ----
		
		window.clear();
		
		lvl.draw(window, player);
		
		hud.draw(window);
		
		window.display();
	}

	return EXIT_SUCCESS;
}
