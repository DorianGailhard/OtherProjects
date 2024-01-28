#include "ServiceLocator.h"

ServiceLocator::ServiceLocator()
{

}

ServiceLocator::~ServiceLocator()
{
    //dtor
}

//Return a pointer to the differents services
IResourcesProvider* ServiceLocator::GetResourcesProvider()
{
    return _resourcesProvider;
}

ObjectManager* ServiceLocator::GetObjectManager()
{
    return _objectManager;
}

sf::RenderWindow* ServiceLocator::GetWindow()
{
    return _window;
}

//Registration of differents services
void ServiceLocator::RegisterServiceLocator(IResourcesProvider* provider)
{
    _resourcesProvider = provider;
}

void ServiceLocator::RegisterServiceLocator(ObjectManager* manager)
{
    _objectManager = manager;
}

void ServiceLocator::RegisterServiceLocator(sf::RenderWindow* window)
{
    _window = window;
}

IResourcesProvider* ServiceLocator::_resourcesProvider = NULL;
ObjectManager* ServiceLocator::_objectManager = NULL;
sf::RenderWindow* ServiceLocator::_window = NULL;
