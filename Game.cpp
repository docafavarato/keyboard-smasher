#include "Game.h"
#include <vector>
#include <iostream>

void Game::initVariables() {
	this->window = nullptr;
	this->points = 0;
	this->lifes = 5;
	this->maxEnemies = 10;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->chars = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	this->font.loadFromFile("sweetssmile.ttf");
}

// Inits
void Game::initWindow() 
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Keyboard Smasher", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setFont(font);
	this->enemy.setCharacterSize(80);
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setOutlineThickness(5.f);

	this->line.setFillColor(sf::Color::White);
	this->line.setSize(sf::Vector2f(800.f, 1.f));
	this->line.setPosition(sf::Vector2f(0.f, 500.f));
}

void Game::initStats()
{
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(50);
	this->pointsText.setPosition(sf::Vector2f(10.f, 0));

	this->lifesText.setFont(this->font);
	this->lifesText.setCharacterSize(40);
	this->lifesText.setPosition(sf::Vector2f(650.f, 0));
}

void Game::pollEvents() 
{
	while (this->window->pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::Closed) 
		{
			this->window->close();
		}

		if (this->ev.type == sf::Event::TextEntered)
		{
			for (int i = 0; i < this->enemies.size(); i++)
			{
				if (enemies[i].getString() == static_cast<char>(std::toupper(ev.text.unicode)))
				{
					this->enemies.erase(this->enemies.begin() + i);
					this->points++;
				}
			}
		}

	}
}

// Spawns
void Game::spawnEnemies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)),
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().y - 200)))
	);

	this->enemy.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

	this->enemies.push_back(this->enemy);
}

// Updates
void Game::clearGame()
{
	this->window->clear();
	this->enemies.clear();
	this->points = 0;
}

void Game::updateStats()
{
	if (this->lifes == 0) {
		this->clearGame();
	}

	this->pointsText.setString("Points: " + std::to_string(this->points));
	this->lifesText.setString("Lifes: " + std::to_string(this->lifes));
}

void Game::updateEnemies()
{
	int rand_index = rand() % chars.size();
	
	this->enemy.setString(this->chars[rand_index]);

	if (this->enemies.size() < this->maxEnemies) 
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) 
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else 
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	for (int i = 0; i < this->enemies.size(); i++) 
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 1.f);

		if (this->enemies[i].getPosition().y > 500.f)
		{
			deleted = true;
			this->lifes--;
		}

		if (deleted) 
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}

}

void Game::update() 
{
	this->pollEvents();
	this->updateEnemies();
	this->updateStats();
}

// Renders
void Game::renderStats()
{
	this->window->draw(this->pointsText);
	this->window->draw(this->lifesText);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}

	this->window->draw(this->line);
}

void Game::render() 
{
	this->window->clear();

	this->renderEnemies();
	this->renderStats();

	this->window->display();
}

Game::Game() 
{
	this->initVariables();
	this->initEnemies();
	this->initStats();
	this->initWindow();
}

Game::~Game() 
{
	delete this->window;
}

const bool Game::running() const 
{
	return this->window->isOpen();
}