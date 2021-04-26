#include "Timing.h"
#include "SDL_timer.h"

namespace Engine{

float FPSLimiter::Deltatime = 1/60.0f * 1000.0;

FPSLimiter::FPSLimiter()
{
}

void FPSLimiter::begin()
{
    _startticks = SDL_GetTicks();
}

void FPSLimiter::end()
{
    Deltatime = SDL_GetTicks() - _startticks;
    if (1000.0f / _targetfps > Deltatime)
       SDL_Delay(1000.0f/_targetfps - Deltatime);
}

void FPSLimiter::init(float const targetfps)
{
    setTargetFPS(targetfps);
}

void FPSLimiter::calculateFPS()
{
    static const int NUM_SAMPLES = 100;
    static float frame_times[NUM_SAMPLES];
    static float prev_tics = SDL_GetTicks();
    static int curr_frame = 0;

    float current_tics =  SDL_GetTicks();

    _frametime = current_tics - prev_tics;

    frame_times[curr_frame % NUM_SAMPLES] = _frametime;

    int count = curr_frame < NUM_SAMPLES ? curr_frame : NUM_SAMPLES;
    
    float frame_time_avg = 0;
    for (int i=0; i<count; i++)
        frame_time_avg += frame_times[i];

    frame_time_avg = count > 0 ? frame_time_avg/count : 0;
    _fps = frame_time_avg > 0 ? 1000.0f/frame_time_avg : 0;

    prev_tics = current_tics;
    curr_frame++;
}

}
