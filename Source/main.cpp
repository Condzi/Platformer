#include "Physic\PhysicEngine\PhysicEngine.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Platformer", sf::Style::Close);
	sf::Event event;
	PhysicEngine p;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.display();
	}
}