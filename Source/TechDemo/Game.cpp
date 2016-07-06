#include "Game.hpp"

void Game::draw()
{
	m_window.clear(sf::Color::Green);
	m_window.draw(test_player);
	m_window.display();
}

void Game::handleEvents()
{
	if (m_event.type == sf::Event::Closed)
		m_window.close();
}

void Game::update(const float & deltaTime)
{
	if (m_textureManager != nullptr)
		m_textureManager->Update();
	if (m_physicEngine != nullptr)
		m_physicEngine->Update(deltaTime);
	
	test_player.Update();
}

void Game::initPhysicEngine()
{
	if (m_physicEngine == nullptr)
		m_physicEngine = new PhysicEngine;
	else
	{
		delete m_physicEngine;
		m_physicEngine = nullptr;
		initPhysicEngine();
		return;
	}

	//Add all rigidbodies etc here...
	m_physicEngine->AddRigidbody(test_player.GetRigidbody());
	m_physicEngine->AddCollider(test_player.GetBoxCollider());
}

void Game::initTextureManager()
{
	if (m_textureManager == nullptr)
		m_textureManager = new TextureManager;
	else
	{
		delete m_textureManager;
		m_textureManager = nullptr;
		initTextureManager();
		return;
	}

	//load and add all textures here...

	m_textureManager->AddPath("Data/Textures/ball.png");
	
	//...
	m_textureManager->ReloadTextures();
}

Game::Game(uint16_t winX, uint16_t winY, uint8_t fpsLimit)
{
	m_window.create(sf::VideoMode(winX, winY), "TechDemo 1", sf::Style::Close);
	m_window.setFramerateLimit(fpsLimit);

	//somwhere here add method to init GameObjects (Player etc)
	m_physicEngine = nullptr;
	m_textureManager = nullptr;

	initPhysicEngine();
	initTextureManager();
	//..
	test_player.SetTexture(m_textureManager->GetTexture("Data/Textures/ball.png"));
	test_player.SetTextureManagerPointer(m_textureManager);
	
}

Game::~Game()
{
	delete m_physicEngine;
	delete m_textureManager;
}

void Game::Run()
{
	sf::Clock deltaTime;
	
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(m_event))
		{
			handleEvents();
		}

		update(deltaTime.getElapsedTime().asSeconds());
		draw();
	}
}
