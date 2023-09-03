#include <SFML/Graphics.hpp>


using namespace sf;
int gridSize = 20;
class Snake {
	public:
		Snake();
		void move();
		void grow();
		void update();
		void render(sf::RenderWindow& window);
		sf::Vector2f getDirection() const;  
		void setDirection(const sf::Vector2f& newDirection);  
		bool isCollidingWithFood(const sf::Vector2f& foodPosition);
	private:
		std::vector<sf::RectangleShape> segments;
		sf::Vector2f direction;
};
sf::Vector2f Snake::getDirection() const {
	return direction;
}

void Snake::setDirection(const sf::Vector2f& newDirection) {
	direction = newDirection;
}
Snake::Snake() {
	int gridSize = 20;
	int rows = 800 / gridSize;
	int columns = 600 / gridSize;
	sf::RectangleShape head(sf::Vector2f(gridSize, gridSize));
	head.setPosition((rows / 2) * gridSize, (columns / 2) * gridSize);
	segments.push_back(head);
}
void Snake::move() {
	int gridSize = 20;
	if (segments.empty()) {
		return;
	}

	sf::Vector2f headPosition = segments.front().getPosition();
	headPosition.x += direction.x * gridSize;
	headPosition.y += direction.y * gridSize;

	sf::RectangleShape newHead(sf::Vector2f(gridSize, gridSize));
	newHead.setPosition(headPosition);

	segments.insert(segments.begin(), newHead);
	segments.pop_back();
}
void Snake::grow() {}
void Snake::update() {}
void Snake::render(sf::RenderWindow& window) {
	for (const sf::RectangleShape& segment : segments) {
		window.draw(segment);
	}
}
class Apple {
	public:
		Apple(int maxWidth, int maxHeight);
		void respawn(int maxWidth, int maxHeight);
		sf::Vector2f getPosition() const;
		 void render(sf::RenderWindow& window);


	private:
		sf::RectangleShape appleShape;
		sf::Vector2f position;
};

Apple::Apple(int maxWidth, int maxHeight ) {
	
	appleShape.setSize(sf::Vector2f(gridSize, gridSize));
	appleShape.setFillColor(sf::Color::Red);
	respawn(maxWidth, maxHeight);
}
void Apple::render(sf::RenderWindow& window) {
    window.draw(appleShape);
}

void Apple::respawn(int maxWidth, int maxHeight) {
	int x = rand() % (maxWidth / gridSize) * gridSize;
	int y = rand() % (maxHeight / gridSize) * gridSize;

	position = sf::Vector2f(x, y);
	appleShape.setPosition(position);
}

sf::Vector2f Apple::getPosition() const {
	return position;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Game");
	window.setFramerateLimit(10);
	Snake snake;
	Apple apple(800, 600);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up && snake.getDirection() != sf::Vector2f(0, 1)) {
					snake.setDirection(sf::Vector2f(0, -1));
				} else if (event.key.code == sf::Keyboard::Down && snake.getDirection() != sf::Vector2f(0, -1)) {
					snake.setDirection(sf::Vector2f(0, 1));
				} else if (event.key.code == sf::Keyboard::Left && snake.getDirection() != sf::Vector2f(1, 0)) {
					snake.setDirection(sf::Vector2f(-1, 0));
				} else if (event.key.code == sf::Keyboard::Right && snake.getDirection() != sf::Vector2f(-1, 0)) {
					snake.setDirection(sf::Vector2f(1, 0));
				}
				else if (event.type == sf::Event::Closed) {
					window.close();}
			}

		}

		snake.move();
		snake.update();
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
		snake.render(window);
		apple.render(window);
		window.display();
	}

	return 0;
}
