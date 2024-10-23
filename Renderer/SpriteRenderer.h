#ifndef RENDERER_H
#define RENDERER_H

class GameTexture;
class ResourceManager;


#include <iostream>

class SpriteRenderer {
public:
	SpriteRenderer(std::shared_ptr<ResourceManager> rm);

	enum class BomberType{
		bomber,
		airenemybomber
	};

	bool DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y) const;
	bool DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const;
	
	bool DrawBomberFromTopLeftPos(BomberType, int index, int x, int y) const;
	bool DrawBomberFromCenterPos(BomberType, int index, int x, int y) const;

	
	~SpriteRenderer() = default;

private:
	std::shared_ptr<GameTexture> bomber;
	std::shared_ptr<GameTexture> airenemybomber;
};

#endif // RENDERER_H

