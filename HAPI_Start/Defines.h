#pragma once

/*
	This class includes the main headers used in this project
*/

#include <HAPI_lib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <memory>

using namespace HAPISPACE;
using namespace std;

// Details about the application
#define targetFPS 144
#define updatedelay	80.0f
#define screenWidth 1600
#define screenHeight 900

// Details about the simulation world
#define GameBoundaryLeft -1000;
#define GameBoundaryRight 1000;
#define GameBoundaryTop -1000;
#define GameBoundaryBottom 1000;

// File paths
#define characterStatsMainFilePath "Data\\_Characters\\"
#define soundMainFilePath "Data\\_Sound\\"
#define spriteMainFilePath "Data\\_Sprites\\"
#define levelMainFilePath "Data\\_Level\\"

