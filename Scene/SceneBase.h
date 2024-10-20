#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "ResourceManager.h"

class SceneBase {
public:
    SceneBase() : init(true), state(0){}
    virtual ~SceneBase() = default; // �I������

    virtual int Init() {        // ������
        init = true; 
        state = 0;
        return 0; 
    };  
    virtual int Update() = 0;    // �X�V����
    virtual int Draw() = 0;      // �`�揈��


protected:
    bool init;
    int state;
};


#endif // SCENEBASE_H