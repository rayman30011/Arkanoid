#pragma once
#include <string>
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

enum class BlockType
{
	None,
	Simple,
	OneLive,
	Immortal
};

struct BlockActionParams
{
	BlockType type;
	sf::Vector2f position;
};

struct Block {
	BlockType type;
	uint8_t lives;
	sf::FloatRect rect;
};

typedef std::function<void(BlockActionParams)> action;

constexpr uint32_t MAP_WIDTH = 15;
constexpr uint32_t MAP_HEIDHT = 12;

constexpr uint32_t BLOCK_WIDTH = 32;
constexpr uint32_t BLOCK_HEIGHT = 16;

class Map
{
public:
	Map(std::string const& file_name);
	~Map();

	std::vector<Block>& const get_blocks();
	bool is_collide_block(sf::FloatRect rect);
	void collide_block(sf::FloatRect rect);
	void onBlockDestroy(action fn) { _blockDestroyCallbacks.push_back(fn); }
private:
	Block create_block(BlockType type);
	int get_index(sf::Vector2u position);
	bool out_bounds(sf::Vector2f position);

private:
	std::vector<Block> _blocks;
	std::vector<action> _blockDestroyCallbacks;
};

