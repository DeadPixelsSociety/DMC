#include "../inc/CMovement.hpp"

CMovement::CMovement(std::vector<sf::Rect<int>> newFrames)
{
  m_frames = newFrames;
  m_current = 0;
}

CMovement::~CMovement()
{

}

void CMovement::nextFrame(sf::Sprite *toChange)
{
  if (m_current == m_frames.size()) {
    m_current = 0;
  }

  toChange->setTextureRect(m_frames[m_current]);
  m_current++;
}
