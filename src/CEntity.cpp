#include "../inc/CEntity.hpp"

CEntity::CEntity(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath)
: m_weight(weight)
, m_eDirH(NoneH)
, m_eDirV(NoneV)
, m_isSpawned(false)
, m_size(size)
{
	m_pText = new sf::Texture();
	if (!m_pText->loadFromFile(spritePath, sf::Rect<int>(0, 0, m_size.x, m_size.y)))
	{
		std::cerr << "[!] Can't load the sprite : " + spritePath << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_sprite.setTexture(*m_pText);
	m_sprite.setPosition(position);
}

CEntity::~CEntity()
{
	// Free all the alocated memory.
	
	delete m_pText;
}

sf::Vector2f CEntity::getPosition()
{
	// Getter for the position.
	
	return m_sprite.getPosition();
}

void CEntity::setPosition(sf::Vector2f newPos)
{
	// Setter for the position from a vector.
	
	m_sprite.setPosition(newPos);
}

void CEntity::setPosition(float x, float y)
{
	// Setter for the position from two float.
	
	m_sprite.setPosition(x, y);
}

float CEntity::getWeight()
{
	// Getter for the weight
	
	return m_weight;
}

void CEntity::setWeight(float newWeight)
{
	// Setter for the weight
	
	m_weight = newWeight;
}

sf::Vector2f CEntity::getSize(void)
{
	// Getter the size of the sprite.
	
	return m_size;
}

void CEntity::setDirectionH(EDirectionHor newEDirH)
{
	//
	
	m_eDirH = newEDirH;
}

void CEntity::setDirectionV(EDirectionVer newEDirV)
{
	//
	
	m_eDirV = newEDirV;
}

void CEntity::draw(sf::RenderWindow &window)
{
	// Draw the sprite of the entity
	
	window.draw(m_sprite);
}

void CEntity::printDir()
{
	//
	
	std::string direction;
	
	switch (m_eDirH)
	{
		case Right : direction += "[Right - ";
			break;
		case Left : direction += "[Left - ";
			break;
		case NoneH : direction += "[NoneH - ";
	}
	
	switch (m_eDirV)
	{
		case Up : direction += "Up]";
			break;
		case Down : direction += "Down]";
			break;
		case NoneV : direction += "NoneV]";
	}

	std::cout << direction << std::endl;
}