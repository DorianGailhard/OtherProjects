#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "PCH.h"
#include "MenuItem.h"

class ObjectManager
{
    public:
                 ObjectManager();
        virtual ~ObjectManager();

        void     RegisterMenuItem(const std::string& name,MenuItem* item);
        void     UpdateMenuItems();
        void     DrawMenuItems();

    protected:

    private:
        std::map<std::string, MenuItem*> _menuItemsList;
};

#endif // OBJECTMANAGER_H
