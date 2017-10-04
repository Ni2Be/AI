#pragma once

//sfml
#include <SFML/Graphics.hpp>


//stl
#include <vector>

class Tile;

class Area
{
public:
	Area(int width, int height, int column_count, int row_count);

	void draw_to_window(sf::RenderWindow *win);
	Tile& get_tile_on_pos(int x, int y);


	//not used at the moment
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
	const sf::Color clean = sf::Color::White;
	const sf::Color dirty = sf::Color::Red;
public:
	Tile(float width, float height, float x_pos, float y_pos, bool is_dirty, int number)
	:
	sf::RectangleShape(sf::Vector2f(width, height)),
	m_number(number),
	m_is_dirty(is_dirty)
	{
		this->setFillColor			(dirty);
		this->setOutlineColor		(sf::Color::Black);
		this->setOutlineThickness	(-(width / 40));
		this->setPosition			(x_pos, y_pos);

	}

	void clean_up();
	void update_color();

	bool is_dirty() { return m_is_dirty; };

	int					m_number;
private:
	bool				m_is_dirty;
};
