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


	size_t nbrFoe = levelFile["foe"].size();
	float type, spX, spY;
	for(size_t foe = 0; foe < nbrFoe; foe++)
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

	size_t size = m_pArrayFoes.size();
	for (size_t foe = 0; foe < size; foe++)
	{
		delete m_pArrayFoes[foe];
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

size_t *CLevel::foesInScreen()
{
	// Si position de foe dans view
	// mettre index du foe dans res
	
	// Dynamic obligé ?
	
	return 0;
}

void CLevel::update(float dt, sf::Vector2f wDim, float moveSpeed)
{
	// Gestion des foes
	/*
		- Comment determiner qels foes sont dans la vue courante. (view ?)
		  Pour chacun de ces foes, appeller leur update() (ou fonction ia, puis update())
		  
		  (De même si arme / obstacle implantés.)
	*/
	
	// Delete tous les foes qui sont à gauche de la view ?	
	
	size_t size = m_pArrayFoes.size();
	for (size_t rect = 0; rect < size; rect++)
	{
		m_pArrayFoes[rect]->update(dt, wDim.x, moveSpeed);
	}
}

void CLevel::draw(sf::RenderWindow *window, sf::View *viewPlayer)
{
	// Draw all the drawable entitys inside the level.
	
	// Drawing of the 3 sprites of the level with parallaxe effect.
	sf::View view;
	view.reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	
	sf::Vector2f viewPos((viewPlayer->getCenter().x + m_pTBack->getSize().x) * 0.15, viewPlayer->getCenter().y);
	view.setCenter(viewPos);
	window->setView(view);
	window->draw(m_background);
	
	viewPos.x = (viewPlayer->getCenter().x + m_pTFore->getSize().x) * 0.35;
	view.setCenter(viewPos);
	window->setView(view);
	window->draw(m_foreground);

	// Reset the view to default so the path sprite
	// is draw at the speed of the player.	
	window->setView(*viewPlayer);
	window->draw(m_path);

	// Draw all other entity.
	size_t size = m_pArrayFoes.size();
	for (size_t rect = 0; rect < size; rect++)
	{
		m_pArrayFoes[rect]->draw(window);
	}
}
