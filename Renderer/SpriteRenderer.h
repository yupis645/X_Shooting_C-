#ifndef RENDERER_H
#define RENDERER_H

#include "GameTexture.h"

	class SpriteRenderer {
	public:
		void DrawFromTopLeftPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y) const;
		void DrawFromCenterPos(const std::shared_ptr<const GameTexture>& texture, int index, int x, int y, int pic_size) const;
	};

#endif // RENDERER_H

