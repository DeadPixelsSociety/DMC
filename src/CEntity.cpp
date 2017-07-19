#include "../inc/CEntity.hpp"

CEntity::CEntity(float weight, sf::Vector2f position, sf::Vector2f size, std::string spritePath)
: m_weight(weight)
, m_eDirH(NoneH)
, m_eDirV(NoneV)
, m_isSpawned(false)
, m_size(size)
{
  m_animHandler = new CAnimationHandler(spritePath, size, position);
}

CEntity::~CEntity()
{
	// Free all the alocated memory.
	
	//delete m_pText;
	delete m_animHandler;
}

sf::Sprite *CEntity::getSprite()
{
  return m_animHandler->getSprite();
}

sf::Vector2f CEntity::getPosition()
{
	// Getter for the position.
	
	return getSprite()->getPosition();
}

void CEntity::setPosition(sf::Vector2f newPos)
{
	// Setter for the position from a vector.
	
	getSprite()->setPosition(newPos);
}

void CEntity::setPosition(float x, float y)
{
	// Setter for the position from two float.
	
	getSprite()->setPosition(x, y);
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

enum EDirectionHor CEntity::getDirectionH()
{
	// Getter for the horizontal direction.
	
	return m_eDirH;
}

void CEntity::setDirectionH(EDirectionHor newEDirH)
{
	// Setter for the horizontal direction.
	
	m_eDirH = newEDirH;
}

enum EDirectionVer CEntity::getDirectionV()
{
	// Getter for the vertical direction.
	
	return m_eDirV;
}

void CEntity::setDirectionV(EDirectionVer newEDirV)
{
	// Setter for the vertical direction.
	
	m_eDirV = newEDirV;
}

void CEntity::draw(sf::RenderWindow &window)
{
	// Draw the sprite of the entity.
	
	m_animHandler->draw(window);
}
