#ifndef RENDERER_H
#define RENDERER_H

class GameTexture;
class ResourceManager;
class Vector2;


class SpriteRenderer {
public:
	SpriteRenderer(std::shared_ptr<ResourceManager> rm);

	enum class BomberType{
		bomber,
		airenemybomber
	};

	bool DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y) const;
	bool DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>& texture, int index, Vector2 pos) const;

	bool DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const;
	bool DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, Vector2 pos, int pic_size) const;
	
	bool DrawBomberFromTopLeftPos(BomberType, int index, int x, int y) const;
	bool DrawBomberFromTopLeftPos(BomberType, int index, Vector2 pos) const;

	bool DrawBomberFromCenterPos(BomberType, int index, int x, int y) const;
	bool DrawBomberFromCenterPos(BomberType, int index, Vector2 pos) const;

	
	~SpriteRenderer() = default;

private:
	std::shared_ptr<GameTexture> bomber;
	std::shared_ptr<GameTexture> airenemybomber;
};

#endif // RENDERER_H

