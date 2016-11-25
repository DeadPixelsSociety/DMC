#include "../inc/CPlayer.hpp"

CPlayer::CPlayer(sf::Vector2f wDim, std::string name)
: CCharacter(0.0f, sf::Vector2f(0, wDim.y - 20), sf::Vector2f(20, 20), "res/sprites/player.png", 0.0f, 100.0f, 0.0f, 0.0f)
, m_szName(name)
, m_view(sf::FloatRect(0, 0, wDim.x, wDim.y))
, m_isBlocked(false)
, m_lastViewDep(0.0f)
{

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

void CPlayer::updateView(float x, float y, sf::Vector2f wDim, float lvlLength)
{
	// Update the view the player with his movement.

	float coordX = getPosition().x + getSize().x / 2;
	static int accel = 30;
	int dist = (int) abs(coordX - m_view.getCenter().x);
	int velo = dist / accel;

	// Move or stop the scrolling when the player is either
	// at the start of the level or at the end.
	if (coordX  >= wDim.x / 2)
	{	
		if (coordX >= lvlLength - (wDim.x / 2))
		{
			// View reach end of the level.
			m_view.setCenter(lvlLength - (wDim.x / 2), wDim.y / 2);
		}
		else
		{
			// After a lock zone, the player is not always at the center
			// of the view, so we move it to correct that.
			if (dist > 1)
			{
				if (coordX > m_view.getCenter().x && x > 0) {
					m_view.move(velo, 0);
					m_lastViewDep = velo;
				} else if (coordX < m_view.getCenter().x && x < 0) {
					m_view.move(-velo, 0);
					m_lastViewDep = -velo;
				}
				accel = (accel > 1) ? accel - 1 : 10;
			}
			else
			{
				// Normal deplacement of the view.
				m_view.move(x, 0);
				m_lastViewDep = x;
			}
		}
	}
}

void CPlayer::update(sf::Time dt, sf::Vector2f wDim, float lvlLength, float lvlDepth)
{
	// Update the action of the player limited by the view.
	
	float x = 0.0f;
	float y = 0.0f;
	m_lastViewDep = 0.0f;
	
	switch (m_eDirH)
	{
		case Right : x = (getPosition().x < (getView().getCenter().x + (wDim.x / 2)) - getSize().x) ? m_velocity * dt.asSeconds() : 0.0f;
			break;
		case Left : x = (getPosition().x > (getView().getCenter().x - (wDim.x / 2))) ? -m_velocity * dt.asSeconds() : 0.0f;
			break;
		case NoneH : break;
	}
	
	switch (m_eDirV)
	{
		case Up : y = (getPosition().y > wDim.y - lvlDepth - getSize().y) ? -m_velocity * dt.asSeconds() : 0.0f;
			break;
		case Down : y = (getPosition().y < wDim.y - getSize().y) ? m_velocity * dt.asSeconds() : 0.0f;
			break;
		case NoneV : break;
	}
	
	if (x == 0.0f && y == 0.0f) return;
	
	if (!m_isBlocked) updateView(x, y, wDim, lvlLength);
	
	m_sprite.move(x, y);
}
