#pragma once

#include "Events/Events.hpp"
#include <string>
#include <vector>

namespace Engine{

class Layer{
public:
    Layer(std::string const &name);
    ~Layer();

    virtual void onEvent(Event &e);
    virtual void onUpdate();
    virtual void onAttach();
    virtual void onDetach();

    std::string getName(){return _name;}

protected:
    std::string _name;
};

class LayerStack{
public:
    LayerStack();
    ~LayerStack();

    void push(Layer* l);
    void pop(Layer* l);
    void popOverlay(Layer* l);
    void addOverlay(Layer* l);

    void onUpdate();
    void onEvent(Event &e);

    std::vector<Layer*>::iterator begin() {return _layerstack.begin();}
    std::vector<Layer*>::iterator end() {return _layerstack.end();}
    std::vector<Layer*>::reverse_iterator rbegin() {return _layerstack.rbegin();}
    std::vector<Layer*>::reverse_iterator rend() {return _layerstack.rend();}

    std::vector<Layer*>::const_iterator begin() const { return _layerstack.begin(); }
    std::vector<Layer*>::const_iterator end()	const { return _layerstack.end(); }
    std::vector<Layer*>::const_reverse_iterator rbegin() const { return _layerstack.rbegin(); }
    std::vector<Layer*>::const_reverse_iterator rend() const { return _layerstack.rend(); }

private:
    std::vector<Layer*> _layerstack;
    std::vector<Layer*>::iterator _inserter;
};

}
