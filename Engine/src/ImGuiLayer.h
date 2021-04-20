#pragma once

#include "Layers.h"

namespace Engine{

class ImGuiLayer : public Layer{
public:
    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onImGuiRender() override;

    virtual void imGuiBegin();
    virtual void imGuiEnd();

    virtual void onEvent(Event &e) override;
private:
    bool _blockevents = true;
};

}
