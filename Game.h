#pragma once
#include  "SFML/Graphics.hpp"
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>

class Game
{
	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;
		sf::Font font;

		// Entities
		std::vector<sf::Text> enemies;
		sf::Text enemy;
		sf::RectangleShape line;

		// Stats
		sf::Text pointsText;
		sf::Text lifesText;

		// Functions
		void initVariables();
		void initWindow();
		void initEnemies();
		void initStats();
		void clearGame();

	public:
		Game();
		virtual ~Game();
		void pollEvents();
		void update();
		void render();

		void spawnEnemies();
		void updateEnemies();
		void updateStats();
		void renderStats();
		void renderEnemies();
		
		// Logic
		int points;
		int lifes;
		int rand_index;
		int maxEnemies;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		std::vector<std::string> chars;

		const bool running() const;

};