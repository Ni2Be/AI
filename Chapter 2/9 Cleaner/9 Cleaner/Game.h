#pragma once

#include <random>

#include <SFML/Graphics.hpp>

#include "Area.h"
#include "Agent_Vacuum_Cleaner.h"

class Game : public sf::RenderWindow
{
public:
	Game(int width, int height, int columns, int rows)
		:
		sf::RenderWindow(sf::VideoMode(width, height), "Cleaner"),
		m_width				(width),
		m_height			(height),
		m_rows				(rows),
		m_columns			(columns),
		m_background		(sf::Vector2f (width, height)),
		m_cleaning_area		(width, height, columns, rows),
		m_cleaner			((width  / columns) / 2, 
							 (height / rows) / 2, 
							 ((height / rows) / 6 > (width / columns) / 6)? (width / columns) / 6 : (height / rows) / 6)
	{
		std::random_device					rd;
		std::uniform_int_distribution<int>	dist_h(1, rows - 1);
		std::uniform_int_distribution<int>	dist_v(1, columns - 1);
		m_cleaner.setPosition(dist_h(rd) * (width / columns) + ((width / columns) / 2), dist_v(rd) * (height / rows) + ((height / rows) / 2));


		m_background			.setFillColor(sf::Color::White);
	}

	void run();

private:
	const int			 m_width;
	const int			 m_height;
	const int			 m_rows;
	const int			 m_columns;
						 
	sf::RectangleShape	 m_background;
	Area				 m_cleaning_area;
	Agent_Vacuum_Cleaner m_cleaner;
};