#include "../inc/CHud.hpp"

CHud::CHud(std::string fontPath, float charSize, sf::Vector2f posText)
: m_visible(true)
{
	if (!m_font.loadFromFile(fontPath))	{
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
	
	if (!lockZones.empty()) {
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
		case DIR_RIGHT :
      direction = "[Right - ";
			break;
		case DIR_LEFT :
      direction = "[Left - ";
			break;
		case DIR_NONEH :
      direction = "[NoneH - ";
      break;
	}
	
	switch (entity.getDirectionV())
	{
		case DIR_UP :
      direction += "Up]";
			break;
		case DIR_DOWN :
      direction += "Down]";
			break;
		case DIR_NONEV :
      direction += "NoneV]";
      break;
	}

	return "Direction : " + direction;
}

std::string CHud::printAction(CEntity &entity)
{
  // Print the action of an entity
  
  std::string action;
  
  switch (entity.getAction())
  {
    case ACT_JUMP :
      action = "[Jump]";
      break;
    case ACT_ATTACK :
      action = "[Attack]";
      break;
    case ACT_NONE :
      action = "[None]";
      break;
  }
  
  return "Action : " + action;
}

std::string CHud::printDist(CPlayer &player)
{
	// Print the distance between the x of the center of the view and the x of the center of the player.
	
	float coordX = player.getPosition().x + player.getSize().x / 2;
	int dist = (int) abs(coordX - player.getView().getCenter().x);
	
	return "Dist : " + std::to_string(dist);
}

void CHud::update(sf::Time frameTime, sf::RenderWindow &window, CPlayer &player, CLevel &lvl)
{
	// Update the the informations to display.
	
	if (!m_visible) return;
	
	m_text.setPosition(player.getView().getCenter().x - window.getSize().x / 2 + 5, player.getView().getCenter().y - window.getSize().y / 2 + 5);
	m_text.setString(printFps(frameTime)
					 + " | " + printNbrFoesInScreen(window.getSize(), player.getView().getCenter(), lvl)
					 + " | " + printNextLockZone(lvl.getLockZones())
					 + "\n" + printPosition(player)
					 + " | " + printDist(player)
					 + "\n" + printDirection(player)
					 + " | " + printAction(player));
}

void CHud::draw(sf::RenderWindow &window)
{
	// Display the informations to the screen.
	
	if (m_visible) window.draw(m_text);
}
