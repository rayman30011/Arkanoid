#include "MapRenderer.h"

MapRenderer::MapRenderer(Map* map)
{
	_map = map;
	_image = new sf::Image();
	_image->loadFromFile("resources/blocks.png");
	_texture = new sf::Texture();
	_texture->loadFromImage(*_image);
	_sprite = new sf::Sprite();
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(0, 0, BLOCK_WIDTH / 2, BLOCK_HEIDHT / 2));
	_sprite->setScale(2.f, 2.f);
}

void MapRenderer::render(sf::RenderTarget& target)
{
	auto blocks = _map->get_blocks();
	for (auto block : blocks) 
	{
		_sprite->setPosition(sf::Vector2f(block->rect.left, block->rect.top));
		renderBlock(*block);
		target.draw(*_sprite);
	}
}

void MapRenderer::renderBlock(Block& block)
{
	_sprite->setColor(sf::Color::White);
	_sprite->setTextureRect(sf::IntRect(0, 0, BLOCK_WIDTH / 2, BLOCK_HEIDHT / 2));
	if (block.type != BlockType::Immortal)
	{
		if (block.lives > 2)
			_sprite->setColor(sf::Color::Red);

		if (block.lives > 1)
			_sprite->setColor(sf::Color::Yellow);
	}
	else
	{
		_sprite->setTextureRect(sf::IntRect(BLOCK_WIDTH / 2, 0, BLOCK_WIDTH / 2, BLOCK_HEIDHT / 2));
	}
}
