#include "../inc/CLevel.h"

CLevel::CLevel(std::string _num)
{

	/*
		SUPPRIMER LES OBJETS (YAML::Node, les textures, ...) ?
	*/

	std::string name("res/levels/level");
	std::string ext(".yaml");
	
	YAML::Node levelFile = YAML::LoadFile(name + _num + ext);
	
	if (levelFile.IsNull())
	{
		std::cerr << "[!] Can't open " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}
	
	m_szName = levelFile["name"].as<std::string>();
	
	size_t sizeLock = levelFile["lock"].size();
	for(size_t zone = 0; zone < sizeLock; zone++)
	{
		m_lockZones.push_back(levelFile["lock"][zone].as<float>());
	}


	size_t nbrFoes = levelFile["foe"].size();
	float type, spX, spY;
	for(size_t foe = 0; foe < nbrFoes; foe++)
	{
		type = levelFile["foe"][foe]["type"].as<float>();
		spX = levelFile["foe"][foe]["spawnPos"]["x"].as<float>();
		spY = levelFile["foe"][foe]["spawnPos"]["y"].as<float>();
		
		m_pArrayFoes.push_back(new CRectangle(type, spX, spY));
	}
	
	m_pTPath = new sf::Texture();
	if (!m_pTPath->loadFromFile(levelFile["path"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the path picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_path.setTexture(*m_pTPath);
	
	m_pTFore = new sf::Texture();
	if (!m_pTFore->loadFromFile(levelFile["foreground"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the foreground picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_foreground.setTexture(*m_pTFore);
	
	m_pTBack = new sf::Texture();	
	if (!m_pTBack->loadFromFile(levelFile["background"].as<std::string>()))
	{
		std::cerr << "[!] Can't load the background picture of : " + name + _num + ext << std::endl;
		exit(EXIT_FAILURE);
	}	
	m_background.setTexture(*m_pTBack);
	
	m_length = m_pTPath->getSize().x;
	m_depth = m_pTPath->getSize().y;
	
	// music ?
	
	m_difficulty = levelFile["difficulty"].as<float>();	
}

CLevel::~CLevel()
{
	// Free all the alocate memory for the level.
	
	delete m_pTBack;
	delete m_pTPath;
	delete m_pTFore;

	for (auto foe : m_pArrayFoes)
	{
		delete foe;
	}
}

float CLevel::getLength(void)
{
	// Getter for the length of the level.
	
	return m_length;
}

float CLevel::getDepth(void)
{
	// Getter for the depth of the level.
	
	return m_depth;
}

void CLevel::foesInScreen(sf::RenderWindow &window, sf::View &viewPlayer, std::vector<size_t> *foesVisibles)
{
	// Fill a vector with indexs of all the foes visibled in the view.
	
	size_t xPosLeftView = viewPlayer.getCenter().x - window.getSize().x / 2;
	size_t xPosRightView = viewPlayer.getCenter().x + window.getSize().x / 2;
	size_t rightCorner = 0;
	size_t leftCorner = 0;
	
	size_t size = m_pArrayFoes.size();
	for (size_t foe = 0; foe < size; foe++)
	{
		rightCorner = m_pArrayFoes[foe]->getPosition().x + m_pArrayFoes[foe]->getSize().x;
		leftCorner = m_pArrayFoes[foe]->getPosition().x;
		
		if ((rightCorner > xPosLeftView && rightCorner < xPosRightView) ||
			(leftCorner > xPosLeftView && leftCorner < xPosRightView))
		{
			foesVisibles->push_back(foe);
		}
	}
}

void  CLevel::printNbrEntity(sf::RenderWindow &window, sf::View &viewPlayer)
{
	// Print the number of entity in the current view.
	
	sf::Font font;
	if (!font.loadFromFile("res/fonts/sansation.ttf")) {}
	sf::Text foe; foe.setFont(font); foe.setCharacterSize(12); foe.setStyle(sf::Text::Bold); foe.setColor(sf::Color::Black);
	
	std::vector<size_t> foesVisibles;
	foesInScreen(window, viewPlayer, &foesVisibles);
	
	foe.setString("Entity : " + std::to_string(foesVisibles.size()));
	foe.setPosition(viewPlayer.getCenter().x - window.getSize().x / 2 + 75, viewPlayer.getCenter().y - window.getSize().y / 2 + 5);
	window.draw(foe);
}

void CLevel::update(float dt, sf::Vector2f wDim)
{
	// Gestion des foes
	/*
		- Comment determiner qels foes sont dans la vue courante. (view ?)
		  Pour chacun de ces foes, appeller leur update() (ou fonction ia, puis update())
		  
		  (De même si arme / obstacle implantés.)
	*/
	
	// Delete tous les foes qui sont à gauche de la view ?	
	
	for (auto foe : m_pArrayFoes)
	{
		foe->update(dt, wDim.x);
	}
}

void CLevel::draw(sf::RenderWindow &window, sf::View &viewPlayer)
{
	// Draw all the drawable entitys inside the level.
	
	// Drawing of the 3 sprites of the level with parallaxe effect.
	sf::View viewParallaxe(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	
	viewParallaxe.move(viewPlayer.getCenter().x * 0.15f, 0);
	window.setView(viewParallaxe);
	window.draw(m_background);
	
	viewParallaxe.move(viewPlayer.getCenter().x * 0.35f, 0);
	window.setView(viewParallaxe);
	window.draw(m_foreground);

	// Reset the view to default so the path sprite
	// is draw at the speed of the player.	
	window.setView(viewPlayer);
	window.draw(m_path);

	//printNbrEntity(window, viewPlayer);

	// Draw only the entity in the view.
	std::vector<size_t> foesVisibles;
	foesInScreen(window, viewPlayer, &foesVisibles);
	for (auto index : foesVisibles)
	{
		m_pArrayFoes[index]->draw(window);
	}
}
