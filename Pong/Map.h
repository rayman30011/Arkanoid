#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

enum class BlockType {
	None,
	Simple,
	OneLive,
	Immortal
};

struct Block {
	BlockType type;
	uint8_t lives;
	sf::IntRect rect;
};

constexpr uint32_t MAP_WIDTH = 15;
constexpr uint32_t MAP_HEIDHT = 12;

constexpr uint32_t BLOCK_WIDTH = 32;
constexpr uint32_t BLOCK_HEIDHT = 16;

class Map
{
public:
	Map(std::string const& file_name);
	~Map();

	std::vector<Block*>& const get_blocks();
	bool is_collide_block(sf::IntRect rect);
	void collide_block(sf::IntRect rect);
private:
	Block* create_block(BlockType type);
	int get_index(sf::Vector2u position);
	bool out_bounds(sf::Vector2f position);

private:
	std::vector<Block*> _blocks;
};

