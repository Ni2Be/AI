/*
Cleaner exercise:
To get an overview of the code i recommend
starting in Game.h read the comments, 
then go to Area.h and finally to
Agent_Vacuum_Cleaner.h

Tried different kinds of cleaner agents.
Only the random agent is left, to see the others
look into the git history. But they are only
usable in an environment without ostacles.
And I comment and clean-up my code only every
milestone so it will look a little crappy.

Physics.h is not used at the moment.

To be executed the sfml .dll s must be in the same 
folder as the .exe, they are gitignored so you need
to use the ones from the folder:
AI/libs/SFML-2.4.2/bin/ *

license:
You can use this code for anything you want.
The only restrictions are the ones from the sfml library
(but there are none, bottem of this page)
*/

#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	Game cleaner_game(800, 800, 4, 4, 0);
	cleaner_game.run();

	return 0;
}


/*
License for the used sfml library:

SFML (Simple and Fast Multimedia Library) - Copyright (c) Laurent Gomila

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. If you use this software in a product,
an acknowledgment in the product documentation would be appreciated but is
not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.
*/