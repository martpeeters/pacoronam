#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

using std::string;

typedef const int c_int;
typedef unsigned int uint;
typedef const unsigned int c_uint;
typedef const double c_double;
typedef const float c_float;
typedef const string c_string;
typedef const bool c_bool;

static c_uint CELL_SIZE = 27;
static c_uint GRID_COLS = 28;
static c_uint GRID_ROWS = 36;

static c_bool DEBUG = false; 
static c_string TILESET_KEYS_FILENAME = "assets/tileset_keys.txt";
static c_string STD_TILESET_FILENAME = "assets/tileset.png";
static c_string DEBUG_TILESET_FILENAME = "assets/debug_tileset.png";
static c_string FONT_FILENAME = "assets/font.ttf";

static c_uint FPS = 60;
static c_double REF_SPEED = (5.f * CELL_SIZE) / FPS;

static c_uint TILE_IMAGE_PX_SIZE = 64;
static c_uint IMAGES_NBR_PER_ROW = 5;

enum TileType 	{
					VOID_TILE = -1, EMPTY_TILE, FULL_WALL, LEFT_WALL, TOP_WALL, RIGHT_WALL,
					BOTTOM_WALL, TOP_LEFT_WALL, TOP_RIGHT_WALL, BOTTOM_RIGHT_WALL,
					BOTTOM_LEFT_WALL, TRI_TOP_LEFT_WALL, TRI_TOP_RIGHT_WALL,
					TRI_BOTTOM_RIGHT_WALL, TRI_BOTTOM_LEFT_WALL, DOOR_TILE, 
					TREAT_TILE, PILL_TILE
				};

typedef const TileType c_TileType;

#endif // !CONSTANTS_HPP