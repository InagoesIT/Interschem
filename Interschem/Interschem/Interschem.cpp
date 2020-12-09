#include <SFML/Graphics.hpp>

int main()
{
	//to check if SFML is configured correctly
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

	sf::Event event;

	while (window.isOpen()) 
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

	return 0;
}