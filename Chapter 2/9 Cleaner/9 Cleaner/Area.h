/*
Area is a container that holds Tiles and allows to search for
a Tile by coordinates. How an Area is build is part of the 
Game class and defined in an area_factory_TYPE function.

Tile holds information if the tile is clean/dirty or 
an obstacle. It also knows how to draw itselfe by beeing
an sfml recttangle shape, the color represents the information
of the tile:
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

	void draw_to_window(sf::RenderWindow *win);
	Tile& get_tile_on_pos(int x, int y);

	//adds a row to the std::vector<Tile> m_tiles
	void add_row(std::vector<Tile> row);


	std::vector<Tile>& operator[](std::size_t index);


	int		width()					{ return m_width; };
	int		height()				{ return m_height; };
	int		row_count()				{ return m_row_count; };
	int		column_count()			{ return m_column_count; };
	float	horizontal_tile_size()	{ return m_horizontal_tile_size; };
	float	vertical_tile_size()	{ return m_vertical_tile_size; };
private:
	int								m_width;
	int								m_height;
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

	void clean_up();
	void update_color();

	bool& is_dirty() { return m_is_dirty; };
	bool& is_obstacle() { return m_is_obstacle; };

	int					m_number;

	//would be nice
	//void draw(sf::RenderTarget &target, sf::RenderStates states);
private:
	bool				m_is_dirty;
	bool				m_is_obstacle = false;
};
