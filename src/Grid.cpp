#include <iostream>
#include <fstream>

#include "Grid.hpp"

/* --- PRIVATE FUNCTIONS --- */

bool Grid::init_std_texture() {
	texture = sf::Texture();
	if(!texture.loadFromFile(STD_TILESET_FILENAME))
		return false;

	if(CELL_SIZE < 28)
		texture.setSmooth(true);

	return true;
}

bool Grid::init_debug_texture() {
	texture = sf::Texture();
	if(!texture.loadFromFile(DEBUG_TILESET_FILENAME))
		return false;

	texture.setSmooth(true);
	return true;
}


bool Grid::init_texture() {
	if(DEBUG)
		return init_debug_texture();
	else
		return init_std_texture();
}


bool Grid::init_tileset_keys() {

	std::ifstream ifs(TILESET_KEYS_FILENAME);
	if(!ifs) {
		std::cout << "An error occured while opening " << TILESET_KEYS_FILENAME << ".\n";
		return false;
	}

	uint a;
	// The vector only stores the integers encountered
	while(ifs >> a)
		tilesetKeys.push_back((TileType) a);
		
	ifs.close();

	return true;
}


void Grid::init_vertices() {
	vertices.setPrimitiveType(sf::Quads);
	// Four vertices per tile
	vertices.resize(rows * cols * 4);

	for(std::size_t i = 0; i < rows; ++i)
		for(std::size_t j = 0; j < cols; ++j) {
			TileType tileKey = tilesetKeys[i * cols + j];
			
			// The background of a food tile is an empty (black) cell
			if(tileKey == TREAT_TILE || tileKey == PILL_TILE)
				tileKey = EMPTY_TILE;

			sf::Vertex* quad = &vertices[(i * cols + j) * 4];

			quad[0].position = sf::Vector2f(j * CELL_SIZE, i * CELL_SIZE);
			quad[1].position = sf::Vector2f((j + 1) * CELL_SIZE, i * CELL_SIZE);
			quad[2].position = sf::Vector2f((j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
			quad[3].position = sf::Vector2f(j * CELL_SIZE, (i + 1) * CELL_SIZE);

			// textureWidth = column index in tileset.png
			// textureHeight = row index in tileset.png
			uint textureColIndex = tileKey % IMAGES_NBR_PER_ROW;
			uint textureRowIndex = tileKey / IMAGES_NBR_PER_ROW;

			quad[0].texCoords = sf::Vector2f(textureColIndex * TILE_IMAGE_PX_SIZE, textureRowIndex * TILE_IMAGE_PX_SIZE);
			quad[1].texCoords = sf::Vector2f((textureColIndex + 1) * TILE_IMAGE_PX_SIZE, textureRowIndex * TILE_IMAGE_PX_SIZE);
			quad[2].texCoords = sf::Vector2f((textureColIndex + 1) * TILE_IMAGE_PX_SIZE, (textureRowIndex + 1) * TILE_IMAGE_PX_SIZE);
			quad[3].texCoords = sf::Vector2f(textureColIndex * TILE_IMAGE_PX_SIZE, (textureRowIndex + 1) * TILE_IMAGE_PX_SIZE);
		}
}


void Grid::init_map() {
	for(std::size_t i = 0; i < rows; ++i) {
		for(std::size_t j = 0; j < cols; ++j) {

			TileType tileKey = tilesetKeys[i * cols + j];

			Tile* newTile = new Tile(tileKey, i, j);

			map[i][j] = newTile;

			if(tileKey == TREAT_TILE || tileKey == PILL_TILE)
				// Adds a food tile in the map and in remainingFood
				remainingFood.push_back(newTile);
			
		}
			
	}
}


/* Tile* Grid::get_next_tile(c_int& i, c_int& j, c_int& dirX, c_int& dirY) {

	// Special case: pacman is not on a tile at the beginning
	if(i == -1 && j == -1) {
		if(dirX == -1)
			return &map[26][13];
		else if(dirX == 1)
			return &map[26][14];
		else
			return nullptr;
	}

	c_int iNextTile = i + dirY;
	c_int jNextTile = j + dirX;
	// Prevents signed and unsigned comparison
	c_int rows = this->rows;
	c_int cols = this->cols;

	//std::cout << "i, j: " << iNextTile << " " << jNextTile << "\n";

	if(iNextTile >= 0 && iNextTile < rows && jNextTile >= 0 && jNextTile < cols) {
		//std::cout << "i_n j_n" << iNextTile << " " << jNextTile << "\n";

		return &map[iNextTile][jNextTile];
	}
		
	return nullptr;
} */

/* --- PUBLIC FUNCTIONS --- */

// Constructors & Destructor


Grid::Grid() {

	// Does not handle potential errors !!! -> Exceptions ?
	if(!init_texture())
		std::cout << "Do something 'bout that.\n";
	if(!init_tileset_keys())
		std::cout << "Do something 'bout that.\n";

	init_vertices();
	init_map();
}

Grid::~Grid() {
	for(size_t i = 0; i < rows; ++i)
		for(size_t j = 0; j < cols; ++j)
			delete map[i][j];

}


Tile* Grid::get_tile_at(c_uint& i, c_uint& j) {
	return map[i][j];
}

void Grid::remove_food(c_uint& iFood, c_uint& jFood) {
	
	for(auto itr = remainingFood.begin(); itr != remainingFood.end(); ++itr) {
		// Find the food tile we want
		// Memory leaks or double free if I try to do this properly (using erase and delete)
		if((*itr)->rows == iFood && (*itr)->cols == jFood) {
			(*itr)->tileType = EMPTY_TILE;
			return;
		}
	}
}


void Grid::update() {

	// Modifier map en fonction de remainingFood entre autres


}


void Grid::render(sf::RenderTarget* target) {

	target->draw(vertices, &texture);

	for(auto &foodTile : remainingFood)
		if(foodTile->tileType == TREAT_TILE || foodTile->tileType == PILL_TILE)
			foodTile->render(target);
}