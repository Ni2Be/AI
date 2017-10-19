/*
class Area is a container that holds Tiles (class Tile also in Area.h) 
and allows to search for a Tile by coordinates. 
How an Area is build is part of the 
Game class and defined in an area_factory_NAME() function.

class Tile holds information if the tile is clean/dirty or 
an obstacle. 
It also knows how to draw itselfe by beeing an sfml recttangle 
shape, the color represents the information of the tile:
const sf::Color clean		= sf::Color::White;
const sf::Color dirty		= sf::Color::Red;
const sf::Color obstacle	= sf::Color::Black;
*/

#pragma once

//sfml
#include <SFML/Graphics.hpp>

//stl
#include <vector>

class Tile;

class Area
{
public:
	Area(int width, int height, int row_count, int column_count);

	//draws the tiles of the tiles vector to a window
	void draw_to_window(sf::RenderWindow *win);
	//returns the tile of the tiles vector that is on the coordinates
	Tile& get_tile_on_pos(float x, float y);

	//adds a row to the std::vector<Tile> m_tiles
	void add_row(std::vector<Tile> row);

	//returns one row of the tiles vector
	std::vector<Tile>& operator[](std::size_t index);


	float	width()					{ return m_width; };
	float	height()				{ return m_height; };
	int		row_count()				{ return m_row_count; };
	int		column_count()			{ return m_column_count; };
	float	horizontal_tile_size()	{ return m_horizontal_tile_size; };
	float	vertical_tile_size()	{ return m_vertical_tile_size; };
private:
	//returns the count of how often right fits fully into left
	//could possibly return the wrong number due to floating point inaccuracy
	int		float_modulo			(float left, float right);

	float							m_width;
	float							m_height;
	int								m_row_count;
	int								m_column_count;
	float							m_horizontal_tile_size;
	float							m_vertical_tile_size;
	std::vector<std::vector<Tile>>	m_tiles;
};



class Tile : public sf::RectangleShape
{
	const sf::Color clean		= sf::Color::White;
	const sf::Color dirty		= sf::Color::Red;
	const sf::Color obstacle	= sf::Color::Black;
public:
	Tile(float width, float height, float x_pos, float y_pos, bool is_dirty, bool is_obstacle, int number)
	:
	sf::RectangleShape(sf::Vector2f(width, height)),
	m_number(number),
	m_is_dirty(is_dirty),
	m_is_obstacle(is_obstacle)
	{
		update_color();

		this->setOutlineColor		(sf::Color::Black);
		this->setOutlineThickness	(-(width / 40));
		this->setPosition			(x_pos, y_pos);

	}

	//cleans up the tile, automatically calls update_color()
	void clean_up();
	//updates the color of the tile, needs to be called if 
	//a member is manually changed
	void update_color();

	//update_color() needs to be called after changing the value
	bool& is_dirty() { return m_is_dirty; };
	//update_color() needs to be called after changing the value
	bool& is_obstacle() { return m_is_obstacle; };

	int					m_number;

private:
	bool				m_is_dirty;
	bool				m_is_obstacle = false;
};
