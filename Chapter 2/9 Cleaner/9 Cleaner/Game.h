/*
- Game stores the playground (cleaning_area) and the
player (cleaner). 
- It also is responsible for the creation of the 
playground (area_factory_NAME() functions).
- Then it holds the game loop and the controlls.
*/

#pragma once


#include <SFML/Graphics.hpp>

#include "Area.h"
#include "Agent_Vacuum_Cleaner.h"

class Game : public sf::RenderWindow
{
public:
	Game(int width, int height, int rows, int columns, int obstacles)
		:
		sf::RenderWindow(sf::VideoMode(width, height), "Cleaner"),
		m_width				(width),
		m_height			(height),
		m_rows				(rows),
		m_columns			(columns),
		m_background		(sf::Vector2f (width, height)),
		m_cleaning_area		(area_factory_random_obstacles(width, height, rows, columns, obstacles)),
		m_cleaner			(0,
							 0, 
							 (m_cleaning_area.horizontal_tile_size() > m_cleaning_area.vertical_tile_size())? 
								m_cleaning_area.vertical_tile_size() / 6 : m_cleaning_area.horizontal_tile_size() / 6)
		//radius of m_cleaner is one sixth of the smaller tile side of the area
	{
		m_cleaner.x_speed() = m_cleaning_area.horizontal_tile_size();
		m_cleaner.y_speed() = m_cleaning_area.vertical_tile_size();
		place_on_rand_tile		(m_cleaner);
		m_background			.setFillColor(sf::Color::White);
	}

	void	 run();

	
private:
	

	Area&	area_factory_std(int width, int height, int row_count, int column_count);
	Area&	area_factory_random_obstacles(int width, int height, int row_count, int column_count, int obstacle_count);
	void	place_on_rand_tile(Agent_Vacuum_Cleaner& cleaner);

	const int			 m_width;
	const int			 m_height;
	const int			 m_rows;
	const int			 m_columns;
						 
	sf::RectangleShape	 m_background;
	Area				 m_cleaning_area;
	Agent_Vacuum_Cleaner m_cleaner;
};