#include "Layers.h"
#include "Log.h"
#include <algorithm>

namespace Engine{
    
Layer::Layer(std::string const &name)
    :_name(name)
{ 
}

Layer::~Layer()
{ 
}

void Layer::onEvent(Event &e)
{
}

void Layer::onUpdate()
{
}

void Layer::onAttach()
{
}

void Layer::onDetach()
{
}

void Layer::onImGuiRender()
{
}

LayerStack::LayerStack()
    :_insertindex(0)
{
}

LayerStack::~LayerStack()
{
    for(auto *l : _layerstack)
        delete(l);

    _layerstack.clear();
}

void LayerStack::push(Layer *l)
{
    _layerstack.emplace(_layerstack.begin()+_insertindex, l);
    _insertindex++;
}

void LayerStack::pop(Layer *l)
{
    auto it = std::find(_layerstack.begin(), _layerstack.end(), l);
    if (it != _layerstack.end())
    {
        _layerstack.erase(it);
        l->onDetach();
        _insertindex--;
    }
}

void LayerStack::addOverlay(Layer *l)
{
    _layerstack.emplace_back(l);
}

void LayerStack::popOverlay(Layer *l)
{
    auto it = std::find(_layerstack.begin(), _layerstack.end(), l);
    if (it != _layerstack.end())
    {
        _layerstack.erase(it);
    }
}

}
