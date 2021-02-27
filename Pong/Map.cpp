#include "Map.h"
#include <fstream>

Map::Map(std::string const& fileName) : _fileName(fileName)
{
	
}

Map::~Map()
{
	
}

std::vector<Block>& Map::getBlocks()
{
	return _blocks;
}

bool Map::is_collide_block(sf::FloatRect rect)
{
	for (auto& block : _blocks) {
		if (block.rect.intersects(rect))
			return true;
	}

	return false;
}

void Map::collide_block(sf::FloatRect rect)
{
	for (auto it = _blocks.begin(); it != _blocks.end();)
	{
		Block& block = *it;
		if (block.rect.intersects(rect)) 
		{
			block.lives--;
			if (block.lives < 1)
			{
				it = _blocks.erase(it);
				for (auto& callback : _blockDestroyCallbacks)
				{
					const BlockActionParams params = { block.type, sf::Vector2f(block.rect.left, block.rect.top) };
					callback(params);
				}
				continue;
			}
		}
		++it;
	}
}

bool Map::outBounds(sf::Vector2f position) {
	return position.x < 0 || position.x > MAP_WIDTH || position.y < 0 || position.y > MAP_HEIDHT;
}

int Map::getIndex(sf::Vector2u position) {
	return MAP_WIDTH * position.y + position.x;
}

void Map::loadMap()
{
	std::ifstream file(_fileName);
	if (file.is_open())
	{
		std::string line;
		int y = 0;
		const int xOffset = MAP_WIDTH * BLOCK_WIDTH / 2;
		while (getline(file, line))
		{
			for (int i = 0; i < MAP_WIDTH; i++)
			{
				char a = line[i];
				int tmp = atoi(&a);
				const auto type = static_cast<BlockType>(tmp);
				if (type == BlockType::None)
					continue;

				auto block = createBlock(type);
				block.rect.top = y * BLOCK_HEIGHT / 2;
				block.rect.left = i * BLOCK_WIDTH;

				_blocks.push_back(block);
			}
			y++;
		}
	}
	file.close();
}

Block Map::createBlock(BlockType type)
{
	Block block;
	block.type = type;
	block.rect.height = BLOCK_HEIGHT;
	block.rect.width = BLOCK_WIDTH;
	block.lives = 1;

	switch (type)
	{
	case BlockType::None:
		break;
	case BlockType::Simple:
		block.lives = 1;
		break;
	case BlockType::OneLive:
		block.lives = 2;
		break;
	case BlockType::Immortal:
		block.lives = UCHAR_MAX;
		break;
	}

	return block;
}
