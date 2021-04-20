#include "Layers.h"
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

LayerStack::LayerStack()
    :_inserter(_layerstack.begin())
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
    _layerstack.emplace(_inserter, l);
}

void LayerStack::pop(Layer *l)
{
    auto it = std::find(_layerstack.begin(), _layerstack.end(), l);
    if (it != _layerstack.end())
    {
        _layerstack.erase(it);
        l->onDetach();
        _inserter--;
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
