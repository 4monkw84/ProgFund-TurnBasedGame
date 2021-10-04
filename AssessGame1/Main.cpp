#include <iostream>
#include <limits>
#include <vector>
#include <thread>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "character.h"
#include "gameController.h"
#include "menuSystem.h"

int main() {
	srand((unsigned int)time(NULL));
	game::game();
}