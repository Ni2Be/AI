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

Tile& Area::get_tile_on_pos(int x, int y)
{
	for (int h = 0; h < m_row_count; h++)
	{
		for (int w = 0; w < m_column_count; w++)
		{
			if (   (x >= m_tiles[h][w].getPosition().x) 
				&& (x <= m_tiles[h][w].getPosition().x + m_horizontal_tile_size)
				&& (y >= m_tiles[h][w].getPosition().y)
				&& (y <= m_tiles[h][w].getPosition().y + m_vertical_tile_size))
			{
				return m_tiles[h][w];
			}
		}
	}
}

void Area::add_row(std::vector<Tile> row)
{
	this->m_tiles.push_back(row);
}

std::vector<Tile>& Area::operator[](std::size_t index)
{
	return this->m_tiles[index];
}

void Tile::clean_up()
{
	this->m_is_dirty	= false;
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

//not working
//void Tile::draw(sf::RenderTarget &target, sf::RenderStates states)
//{
//	update_color();
//	this->draw(target, states);
//}
