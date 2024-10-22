#ifndef SCENEBASE_H
#define SCENEBASE_H

#include "Geometry.h"

class SceneBase {
public:
    SceneBase() : isinit(false), state(0), framecount(0), cursor({ 0, 0 }) {}
    virtual ~SceneBase() = default; // 終了処理


    virtual int Init() 
    {
        isinit = false;
        state = 0;
        framecount = 0;
        cursor = Vector2::zero;

        return 0;
    };
    virtual int Update() = 0;
    virtual int Draw() = 0;

    void FrameCountUpdate(int value) {
        framecount += value;
        if (framecount > 10000) framecount = 0;
    }

    void framecountReset() { framecount = 0; }
    int Getframecount() const { return framecount; }

    Vector2 Getcarsor()const { return cursor; }
    void movecarsor(float x_value,float y_value, float min, float max) 
    { 
        cursor.x = carsorclamp(cursor.x + x_value, min, max);
        cursor.y = carsorclamp(cursor.y + y_value, min, max);
    }

    float carsorclamp(float value, float min, float max) {
        if (value < min) { return max; }
        else if (value > max) { return min; }

        return value;
    }

    void SetIsinit(bool is) { isinit = is; }
    bool GetIsinit() { return isinit; }

protected:
    bool isinit;
    int state;
    int framecount;
    Vector2 cursor ;		//カーソルの位置
};

#endif // SCENEBASE_H
