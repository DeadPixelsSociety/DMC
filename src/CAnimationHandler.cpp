#include "../inc/CAnimationHandler.hpp"

CAnimationHandler::CAnimationHandler(std::string resPath, sf::Vector2f size, sf::Vector2f position)
{
  m_resourcePath = resPath;
  
	m_pTexture = new sf::Texture();	
	if (!m_pTexture->loadFromFile(m_resourcePath)) {
		std::cerr << "[!] Can't load the sprite : " + m_resourcePath << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_sprite = new sf::Sprite();
	m_sprite->setPosition(position);
	m_sprite->setTexture(*m_pTexture);
	
	m_sprite->setTextureRect(sf::Rect<int>(position.x, position.y, size.x, size.y));
	
	m_acc = 0.0f;
	
  for (size_t i = 0; i < ALL_MOVEMENTS; ++i) {
    m_movements[i] = NULL;
  }
}

CAnimationHandler::~CAnimationHandler()
{

  for (size_t i = 0; i < ALL_MOVEMENTS; ++i) {
    if (m_movements[i] != NULL) {
      delete m_movements[i];
    }
  }

  delete m_pTexture;
  delete m_sprite;
}

sf::Sprite *CAnimationHandler::getSprite()
{
  return m_sprite;
}

void CAnimationHandler::addMovement(EMovements movement, std::vector<sf::Rect<int>> newMovement)
{
  m_movements[movement] = new CMovement(newMovement);
}

void CAnimationHandler::update(sf::Time dt, EMovements movement)
{
  // 0.1f to have a nice display of the animation.
  if (m_acc > 0.1f) {
    m_acc = 0.0f;
    m_movements[movement]->nextFrame(m_sprite);
  } else {
    m_acc += dt.asSeconds();
  }
}

void CAnimationHandler::draw(sf::RenderWindow &window)
{
  window.draw(*m_sprite);
}
