#include "../inc/CHud.hpp"

CHud::CHud(std::string fontPath, float charSize, sf::Vector2f posText)
{
	if (!m_font.loadFromFile(fontPath))
	{
	
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
	//
	
	return "Fps : " + std::to_string((int) (1 / (frameTime.asSeconds())));	
}

std::string CHud::printPosition(CPlayer &player)
{
	//
	
	return "Position : (" + std::to_string((int) player.getPosition().x) + ", " + std::to_string((int) player.getPosition().y) + ")";
}

std::string CHud::printNbrFoesInScreen(sf::Vector2u wDim, sf::Vector2f centerView, CLevel &lvl)
{
	//
	
	std::vector<size_t> foesVisibles;
	lvl.foesInScreen(wDim, centerView, &foesVisibles);
	
	return "Entity : " + std::to_string(foesVisibles.size());
}

std::string CHud::printNextLockZone(std::queue<float> lockZones)
{
	//
	
	std::string lockZone("None");
	
	if (!lockZones.empty())
	{
		lockZone = std::to_string((int) lockZones.front());
	}
	
	return "Next Lock Zone : " + lockZone;
}

void CHud::update(sf::RenderWindow &window, sf::Time frameTime, CPlayer &player, CLevel &lvl)
{
	//
	
	m_text.setPosition(player.getView().getCenter().x - window.getSize().x / 2 + 5, player.getView().getCenter().y - window.getSize().y / 2 + 5);
	m_text.setString(printFps(frameTime)
					 + " | " + printNbrFoesInScreen(window.getSize(), player.getView().getCenter(), lvl)
					 + " | " + printNextLockZone(lvl.getLockZones())
					 + " | " + printPosition(player));
}

void CHud::draw(sf::RenderWindow &window)
{
	//
	
	window.draw(m_text);
}
