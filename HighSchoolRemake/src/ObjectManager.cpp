#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
    //ctor
}

ObjectManager::~ObjectManager()
{
    //dtor
}

//Register a MenuItem object to the map
void ObjectManager::RegisterMenuItem(const std::string& name,MenuItem* item)
{
    _menuItemsList.insert(_menuItemsList.end(),std::pair<std::string, MenuItem*>(name,item));
}

//Update interface
void ObjectManager::UpdateMenuItems()
{
    for (std::map<std::string, MenuItem*>::iterator itr = _menuItemsList.begin();itr != _menuItemsList.end();itr++) {
        itr->second->Update();
    }
}

//Draw interface
void ObjectManager::DrawMenuItems()
{
    for (std::map<std::string, MenuItem*>::iterator itr = _menuItemsList.begin();itr != _menuItemsList.end();itr++) {
        itr->second->Draw();
    }
}
