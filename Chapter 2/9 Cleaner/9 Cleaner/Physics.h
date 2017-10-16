/*
Just implements a simlpe delta_time variable
Not used at the moment.
*/
#pragma once

#include <SFML/System/Clock.hpp>

class Physics
{
public:
	static void			update_time();

	static sf::Clock&	delta_clock() { return m_delta_clock; }
	static int			delta_time()  { return static_cast<int>(m_delta_time.asMilliseconds()); }
private:
	static sf::Time		m_delta_time;
	static sf::Clock	m_delta_clock;
};