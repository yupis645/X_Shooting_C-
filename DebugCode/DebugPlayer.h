#ifndef DEBUGPLAYER_H
#define DEBUGPLAYER_H


#include <iostream>
#include "conioex.h"
#include "IPlayer.h"

class DebugPlayer{
public :
	DebugPlayer(std::shared_ptr<IPlayer> pl):player_(pl) {}
	~DebugPlayer() = default;

	void DrawPos(bool is)
	{
		if (is) {
			DrawRect(player_->GetHitbox().left, player_->GetHitbox().top, player_->GetHitbox().right, player_->GetHitbox().bottom, DWRGB(255, 0, 0), true);								//ìñÇΩÇËîªíË
			DrawRect((int)player_->GetPosition().x - 1, (int)player_->GetPosition().y - 1, (int)player_->GetPosition().x + 1, (int)player_->GetPosition().y + 1, DWRGB(255, 255, 255), true);	//íÜêSì_
			//DrawRect(_p.sight_hitbox.left, _p.sight_hitbox.top, _p.sight_hitbox.right, _p.sight_hitbox.bottom, DWRGB(0, 255, 255), false);	//ìñÇΩÇËîªíË

		}
	}

	void DrawHitbox() {

	}

	std::shared_ptr<IPlayer> player_;
};

#endif //DEBUGPLAYER_H
