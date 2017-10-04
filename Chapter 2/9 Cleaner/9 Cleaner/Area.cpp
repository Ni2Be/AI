#include "Area.h"
#include <iostream>

Area::Area(int width, int height, int column_count, int row_count)
	:
	m_width			(width),
	m_height		(height),
	m_row_count		(row_count),
	m_column_count	(column_count)
{
	m_horizontal_tile_size	= width  / static_cast<float>(m_column_count);
	m_vertical_tile_size	= height / static_cast<float>(m_row_count);

	for (int h = 0; h < row_count; h++)
	{
		std::vector<Tile> row;
		for (int w = 0; w < column_count; w++)
		{
			row.push_back(Tile(
								m_horizontal_tile_size, 
								m_vertical_tile_size, 
								w * m_horizontal_tile_size, 
								h * m_vertical_tile_size, 
								true,
								(h * column_count) + w));
		}
		m_tiles.push_back(row);
	}
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
		this->setFillColor(dirty);
	else
		this->setFillColor(clean);
}
