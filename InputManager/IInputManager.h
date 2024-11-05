#ifndef IINPUTMANAGER_H
#define IINPUTMANAGER_H

class IInputManager {
public:
    virtual ~IInputManager() = default;       //デストラクタ

    enum class InputFlag {
        left = 1 << 0,	 // 0001
        right = 1 << 1,	 // 0010
        up = 1 << 2,	 // 0100
        down = 1 << 3,   // 1000
        select = 1 << 4, // 0001 0000
        cancel = 1 << 5, // 0010 0000
        shot = 1 << 6,   // 0100 0000
        bom = 1 << 7,	 // 1000 0000
        pose = 1 << 8,	 // 0001 0000 0000
        reset = 1 << 9,  // 0010 0000 0000
        esc = 1 << 10	 // 0100 0000 0000
    }; 
    enum class InputMode {
      pushdown,
      pushup,
      press,
      toggle
    };
    //動きに関する関数
    virtual void GetKeySetup() = 0;
    virtual int InputReception() = 0;
    virtual Vector2 Dirctionkeyinput(InputMode flag) = 0;
    virtual Vector2 DirctionkeyinputAxis(float x_value,float y_value,float maxspeed) = 0;
    virtual void left() = 0;
    virtual void right() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void  select() = 0;
    virtual void  cancel() = 0;

    virtual void  shot() = 0;
    virtual void  bom() = 0;
    virtual void  pose() = 0;

    virtual void  esc() = 0;

    virtual void SetFlag(InputFlag flag, InputMode mode) = 0;

    virtual void ClearFlag(InputFlag flag, InputMode mode) = 0;
    virtual void ToggleFlag(InputFlag flag) = 0;
    virtual bool IsFlagSet(InputFlag flag, InputMode mode) const = 0;
    virtual void ClearAll() = 0;
    virtual int GetFlags(InputMode mode) const = 0;

    virtual void SetActive(bool ac) = 0;
    virtual bool Active()const = 0;
    virtual void SetGamemode(int mode) = 0;
    virtual int Gamemode()const = 0;
    virtual Vector2 GetAxis()const =0;

};

#endif // IINPUTMANAGER_H