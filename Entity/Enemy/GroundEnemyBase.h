#ifndef GROUNDENEMYBASE_H
#define GROUNDENEMYBASE_H

class IPlayer;

#include "EnemyBase.h"

class GroundEnemyBase : public EnemyBase {
public:
	int AnimUpdate(int UpdateInterval)override { return 0; }

	void AppearPattern(float x_pos = -1) {}

protected:

};


class GroundEnemyDummy : public GroundEnemyBase
{
public:
	GroundEnemyDummy() {}
	~GroundEnemyDummy() = default;


	void Init() override {}
	int Create(std::shared_ptr<IPlayer> pl, int number, int typenumber = 0) override { return 0; }


	int Update(std::shared_ptr<IPlayer> pl) override { return 0; }
	int UniqueUpdate(std::shared_ptr<IPlayer> pl) override { return 0; }


private:

};

#endif // GROUNDENEMYBASE_H