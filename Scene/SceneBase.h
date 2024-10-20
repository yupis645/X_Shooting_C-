#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "ResourceManager.h"

class SceneBase {
public:
    SceneBase() : init(true), state(0){}
    virtual ~SceneBase() = default; // I—¹ˆ—

    virtual int Init() {        // ‰Šú‰»
        init = true; 
        state = 0;
        return 0; 
    };  
    virtual int Update() = 0;    // XVˆ—
    virtual int Draw() = 0;      // •`‰æˆ—


protected:
    bool init;
    int state;
};


#endif // SCENEBASE_H