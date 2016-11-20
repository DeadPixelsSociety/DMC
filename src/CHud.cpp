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

void CHud::update(sf::RenderWindow &window, sf::View viewPlayer, std::string infos)
{
	//
	
	m_text.setPosition(viewPlayer.getCenter().x - window.getSize().x / 2 + 5, viewPlayer.getCenter().y - window.getSize().y / 2 + 5);
	m_text.setString(infos);
}

void CHud::draw(sf::RenderWindow &window)
{
	//
	
	window.draw(m_text);
}
