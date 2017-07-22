#include "../inc/CPlayer.hpp"

CPlayer::CPlayer(sf::Vector2f wDim, std::string name)
: CCharacter(0.0f, sf::Vector2f(0, wDim.y - 36), sf::Vector2f(30, 38), "res/sprites/animPlayer.png", 0.0f, 150.0f, 0.0f, 0.0f)
, m_szName(name)
, m_view(sf::Rect<float>(0, 0, wDim.x, wDim.y))
, m_isBlocked(false)
, m_lastViewDep(0.0f)
{
  
  getSprite()->setPosition(getPosition());

  std::vector<sf::Rect<int>> none;
  none.push_back(sf::Rect<int>(0, 0, 30, 38));
  none.push_back(sf::Rect<int>(30, 0, 30, 38));
  none.push_back(sf::Rect<int>(60, 0, 30, 38));

  std::vector<sf::Rect<int>> right;
  right.push_back(sf::Rect<int>(0, 38, 30, 38));
  right.push_back(sf::Rect<int>(30, 38, 30, 38));
  right.push_back(sf::Rect<int>(60, 38, 30, 38));

  std::vector<sf::Rect<int>> left;
  left.push_back(sf::Rect<int>(0, 76, 30, 38));
  left.push_back(sf::Rect<int>(30, 76, 30, 38));
  left.push_back(sf::Rect<int>(60, 76, 30, 38));
  
  m_animHandler->addMovement(MOV_NONE, none);
  m_animHandler->addMovement(MOV_RIGHT, right);
  m_animHandler->addMovement(MOV_LEFT, left);
}

CPlayer::~CPlayer()
{
}

sf::View CPlayer::getView()
{
	// Getter for the view.
	
	return m_view;
}

sf::Vector2f CPlayer::getViewPos()
{
	// Getter for the position of the view.
	
	return m_view.getCenter();
}

bool CPlayer::getIsBlocked()
{
	// Indicate if the view of the player his lock or not.
	
	return m_isBlocked;
}

void CPlayer::setIsBlocked(bool newBlocked)
{
	// Setter to lock or unlock the view of the player.
	
	m_isBlocked = newBlocked;
}

float CPlayer::getLastViewDep()
{
	// Getter for the value of the last deplacement.
	
	return m_lastViewDep;
}

void CPlayer::updateView(float x, float y, sf::Vector2u wDim, float lvlLength)
{
	// Update the view the player with his movement.

	float player_x = getPosition().x + getSize().x / 2;
	
	//std::cout << "BEFORE: player=" << player_x << ", view=" << m_view.getCenter().x << ", x=" << x << ", lastViewDep=" << m_lastViewDep << "\n";

	// Start of the level.
	if (player_x > wDim.x / 2 && player_x < lvlLength - (wDim.x / 2)) {

    m_view.move(x, 0);
    	
    // View not centered
    if (player_x != getView().getCenter().x) {
      m_view.setCenter(player_x, wDim.y / 2);
    } else {
      m_lastViewDep = x;
    }
	}
	
	//std::cout << "AFTER : player=" << (getPosition().x + getSize().x / 2) << ", view=" << m_view.getCenter().x << ", lastViewDep=" << m_lastViewDep << "\n\n";
}

void CPlayer::update(sf::Time dt, sf::Vector2u wDim, float lvlLength, float lvlDepth)
{
	// Update the action of the player limited by the view.
	
	float x = 0.0f;
	float y = 0.0f;
	float h_limit;
	float v_limit;
	
	m_lastViewDep = 0.0f;

  switch (m_eAction)
  {
    case ACT_JUMP : break;
    case ACT_ATTACK : break;
    case ACT_NONE : break;
  }

	switch (m_eDirH)
	{
		case DIR_RIGHT :
		  m_animHandler->update(dt, MOV_RIGHT);
		  // Block the player to the right extremity of the view.
		  h_limit = getView().getCenter().x + (wDim.x / 2);
		  if (getPosition().x < h_limit - getSize().x) {
		    x = m_velocity * dt.asSeconds();
		  }
			break;
		case DIR_LEFT :
      m_animHandler->update(dt, MOV_LEFT);
		  // Block the player to the left extremity of the view.
		  h_limit = getView().getCenter().x - (wDim.x / 2);
		  if (getPosition().x > h_limit) {
		    x = -m_velocity * dt.asSeconds();
		  }
			break;
		case DIR_NONEH : break;
	}
	
	switch (m_eDirV)
	{
		case DIR_UP :
		  // Block the player to the top extremity of the path.
		  v_limit = wDim.y - lvlDepth - getSize().y;
		  if (getPosition().y > v_limit) {
		    y = -m_velocity * dt.asSeconds();
		  }
			break;
		case DIR_DOWN :
		  // Block the player to the bottom extremity of the path.
		  v_limit = wDim.y - getSize().y;
		  if (getPosition().y < v_limit) {
		    y = m_velocity * dt.asSeconds();
		  }
			break;
		case DIR_NONEV : break;
	}
	
	
	if (x == 0.0f && y == 0.0f) {
    m_animHandler->update(dt, MOV_NONE);
	} else {
    getSprite()->move(x, y);
    if (!m_isBlocked) updateView(x, y, wDim, lvlLength);
  }
}
