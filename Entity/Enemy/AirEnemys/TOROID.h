#ifndef TOROID_H
#define TOROID_H

#include "AirEnemyBase.h"
#include "Player.h"
#include "BulletManager.h"

class TOROID : public AirEnemyBase 
{
public:
	TOROID(std::shared_ptr<IPlayer> pl, std::shared_ptr<IBulletManager> bm):player_(pl),bulletmanager_(bm) {}
	~TOROID(){}


	int Init() override;
	int Create(int number, int typenumber = 0) override;
	int ActionUpdate(int framecount) override;
	int UniqueUpdate(int framecount) override;

	int ActionPattern01();
	int ActionPattern02(int framecount);
	int ActionPattern03(int framecount);

	int tiypeaction();

protected:
	std::shared_ptr<IPlayer> player_;
	std::shared_ptr<IBulletManager> bulletmanager_;;
};


#endif // TOROID_H