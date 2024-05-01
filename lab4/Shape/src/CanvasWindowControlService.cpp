#include "../include/CanvasWindowControlService.h"
#include <SFML/Graphics.hpp>

CanvasWindowControlService::CanvasWindowControlService() = default;

void CanvasWindowControlService::DrawShapes(std::istream& input)
{
	m_shapeController.ReadShapes(input);
	auto shapes = m_shapeController.GetShapes();

	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 500), "My window");
	m_canvas = std::make_shared<CCanvas>(window);

	while (window->isOpen())
	{
		sf::Event event;
		while (
			window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();

		window->clear(sf::Color::White);

		for (auto const& shape : shapes)
		{
			shape->Draw(m_canvas);
		}
		window->display();
	}
}
