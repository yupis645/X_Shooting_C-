#ifndef AIRENEMYBASE_H
#define AIRENEMYBASE_H

#include "EnemyBase.h"

class AirEnemyBase : public EnemyBase {
public:
	int AnimUpdate(int UpdateInterval)override;

	void AppearPattern(float x_pos = -1);



};


class AirEnemyDummy : public AirEnemyBase
{
public:
	AirEnemyDummy() {}
	~AirEnemyDummy() = default;


	void Init() override {}
	int Create(std::shared_ptr<IPlayer> pl, int number, int typenumber = 0) override { return 0; }


	int Update(std::shared_ptr<IPlayer> pl) override{ return 0; }
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override { return 0; }


private:

};

#endif // AIRENEMYBASE_H
