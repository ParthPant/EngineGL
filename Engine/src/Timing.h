#pragma once

namespace Engine{

class FPSLimiter{
public:
    FPSLimiter(); 

    void init(float const targetfps);
    void begin();
    void end();

    void setTargetFPS(float const targetfps){_targetfps = targetfps;}
    float getFPS(){calculateFPS(); return _fps;};

    static float Deltatime;
private:
    float _targetfps;
    float _fps;
    float _frametime;
    unsigned int _startticks;

    void calculateFPS();
};

}
