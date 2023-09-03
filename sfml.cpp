#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		int gridSize = 20;  
		int rows = window.getSize().y / gridSize;
		int columns = window.getSize().x / gridSize;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				sf::RectangleShape cell(sf::Vector2f(gridSize, gridSize));
				cell.setPosition(j * gridSize, i * gridSize);
				cell.setFillColor(sf::Color::Transparent);  
				cell.setOutlineColor(sf::Color::White); 
				cell.setOutlineThickness(1.0f);  
				window.draw(cell);
			}
		}
		window.display();
	}

	return 0;
}
