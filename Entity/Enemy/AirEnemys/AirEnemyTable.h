#ifndef AIRENEMYTABLE_H
#define AIRENEMYTABLE_H

#include <iostream>
#include "common.h"

class AirEnemyTable{
public :
    AirEnemyTable();

    
    ~AirEnemyTable() = default;
private:
    std::vector<std::vector<int>> enemyTable;
};

#endif //AIRENEMYTABLE_H

