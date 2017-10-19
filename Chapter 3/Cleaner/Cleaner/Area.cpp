#include "Area.h"
#include <iostream>

Area::Area(int width, int height, int row_count, int column_count)
	:
	m_width			(width),
	m_height		(height),
	m_row_count		(row_count),
	m_column_count	(column_count)
{
	m_horizontal_tile_size = width / static_cast<float>(column_count);
	m_vertical_tile_size   = height / static_cast<float>(row_count);
}

void Area::draw_to_window(sf::RenderWindow *win)
{
	for each (auto vec in m_tiles)
	{
		for each (auto tile in vec)
		{
			win->draw(tile);
		}
	}
}

int	Area::float_modulo(float left, float right)
{
	int mod = 0;
	while (left - right >= 0)
	{
		left = left - right;
		mod++;
	}
	return mod;
}

Tile& Area::get_tile_on_pos(float x, float y)
{
	int column  = float_modulo(x, m_horizontal_tile_size);
	int row		= float_modulo(y, m_vertical_tile_size);

	return m_tiles[row][column];
}

void Area::add_row(std::vector<Tile> row)
{
	this->m_tiles.push_back(row);
}

std::vector<Tile>& Area::operator[](std::size_t index)
{
	return this->m_tiles[index];
}

std::vector<Tile>& Area::operator[](std::size_t index) const
{
	return this->m_tiles[index];
}


void Tile::clean_up()
{
	this->is_dirty()	= false;
	this->update_color	();
}

void Tile::update_color()
{
	if (this->m_is_dirty)
	{
		this->setFillColor(dirty);
	}
	else
	{
		this->setFillColor(clean);
	}
	if (this->m_is_obstacle)
	{
		this->setFillColor(obstacle);
	}
}
