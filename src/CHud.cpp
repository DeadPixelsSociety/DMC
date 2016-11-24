#include "../inc/CHud.hpp"

CHud::CHud(std::string fontPath, float charSize, sf::Vector2f posText)
{
	if (!m_font.loadFromFile(fontPath))
	{
		std::cerr << "[!] Can't load the font." << std::endl;
	}
	
	m_text.setFont(m_font);
	m_text.setCharacterSize(charSize);
	m_text.setStyle(sf::Text::Bold);
	m_text.setColor(sf::Color::Black);
	m_text.setPosition(posText);
}

CHud::~CHud()
{

}

std::string CHud::printFps(sf::Time frameTime)
{
	// Print the fps of the game.
	
	return "Fps : " + std::to_string((int) (1 / (frameTime.asSeconds())));	
}

std::string CHud::printPosition(CPlayer &player)
{
	// Print the position of the player.
	
	return "Position : (" + std::to_string((int) player.getPosition().x) + ", " + std::to_string((int) player.getPosition().y) + ")";
}

std::string CHud::printNbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, CLevel &lvl)
{
	// Print the number of foes in the screen.
	
	std::vector<size_t> foesVisibles;
	lvl.foesInScreen(wDim, centerView, &foesVisibles);
	
	return "Foe : " + std::to_string(foesVisibles.size());
}

std::string CHud::printNextLockZone(std::queue<float> lockZones)
{
	// Print the x coordonate of the next lock zone.
	
	std::string lockZone("None");
	
	if (!lockZones.empty())
	{
		lockZone = std::to_string((int) lockZones.front());
	}
	
	return "Next Lock Zone : " + lockZone;
}

void CHud::update(sf::RenderWindow &window, sf::Time frameTime, CPlayer &player, CLevel &lvl)
{
	// Update the the informations to display.
	
	m_text.setPosition(player.getView().getCenter().x - window.getSize().x / 2 + 5, player.getView().getCenter().y - window.getSize().y / 2 + 5);
	m_text.setString(printFps(frameTime)
					 + " | " + printNbrFoesInScreen(window.getSize(), player.getView().getCenter(), lvl)
					 + " | " + printNextLockZone(lvl.getLockZones())
					 + " | " + printPosition(player));
}

void CHud::draw(sf::RenderWindow &window)
{
	// Display the informations to the screen.
	
	window.draw(m_text);
}
