#pragma once
class Buff {
private:
    float duration;
    float timrer = 0.0f;
public:
    virtual void Enter()=0;
    virtual void ReCalc()=0;
    virtual void Update()=0;
    virtual void Exit()=0;

};

