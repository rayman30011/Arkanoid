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

constexpr uint32_t MAP_WIDTH = 16;
constexpr uint32_t MAP_HEIDHT = 24;

constexpr uint32_t BLOCK_WIDTH = 16;
constexpr uint32_t BLOCK_HEIGHT = 16;

class Map
{
public:
	Map(std::string const& file_name);
	~Map();

	std::vector<Block>& getBlocks();
	bool is_collide_block(sf::FloatRect rect);
	void collide_block(sf::FloatRect rect);
	void onBlockDestroy(action fn) { _blockDestroyCallbacks.push_back(fn); }
	void loadMap();
private:
	Block createBlock(BlockType type);
	int getIndex(sf::Vector2u position);
	bool outBounds(sf::Vector2f position);

private:
	std::vector<Block> _blocks;
	std::vector<action> _blockDestroyCallbacks;
	std::string _fileName;
};

