#include "../inc/CHud.hpp"

CHud::CHud(std::string fontPath, float charSize, sf::Vector2f posText)
: m_visible(true)
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

void CHud::toggle()
{
	// Indicate if the hud is visible or not.
	
	m_visible = !m_visible;
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

std::string CHud::printDirection(CEntity &entity)
{
	// Print the direction of an entity.
	
	std::string direction;
	
	switch (entity.getDirectionH())
	{
		case Right : direction += "[Right - ";
			break;
		case Left : direction += "[Left - ";
			break;
		case NoneH : direction += "[NoneH - ";
	}
	
	switch (entity.getDirectionV())
	{
		case Up : direction += "Up]";
			break;
		case Down : direction += "Down]";
			break;
		case NoneV : direction += "NoneV]";
	}

	return "Direction : " + direction;
}

void CHud::update(sf::Time frameTime, sf::RenderWindow &window, CPlayer &player, CLevel &lvl)
{
	// Update the the informations to display.
	
	if (!m_visible) return;
	
	m_text.setPosition(player.getView().getCenter().x - window.getSize().x / 2 + 5, player.getView().getCenter().y - window.getSize().y / 2 + 5);
	m_text.setString(printFps(frameTime)
					 + " | " + printNbrFoesInScreen(window.getSize(), player.getView().getCenter(), lvl)
					 + " | " + printNextLockZone(lvl.getLockZones())
					 + " | " + printPosition(player)
					 + "\n" + printDirection(player));
}

void CHud::draw(sf::RenderWindow &window)
{
	// Display the informations to the screen.
	
	if (m_visible) window.draw(m_text);
}
