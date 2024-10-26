#ifndef DEBUGTEXTURE_H
#define DEBUGTEXTURE_H

class ResourceManager;
class SpriteRenderer;
class Vector2;

#include <iostream>
#include "types.h"

class DebugTexture {
public:
	DebugTexture(std::shared_ptr<ResourceManager> rm, std::shared_ptr<SpriteRenderer>sr):render(sr),resource(rm) {}
	enum class DebugSelectDraw
	{
		Unique,
		Airenemy,
		GroundEnemy,
		Boss,
		MapChip
	};


	void DebugScreenDrawTexture(DebugSelectDraw draw);
	
	void UniqueTextureDraw();
	void AirEnemyTextureDraw();
	void GroundEnemyTextureDraw();
	void BossTextureDraw();
	void MapChipTextureDraw();


	

	~DebugTexture() = default;

private :
	std::shared_ptr<ResourceManager> resource;
	std::shared_ptr<SpriteRenderer> render;

	void DebugDrawRupe(TextureType type, Vector2 pos);
};

#endif	//DEBUGTEXTURE_H