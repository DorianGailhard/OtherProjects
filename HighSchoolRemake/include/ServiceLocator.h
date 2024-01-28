#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include "PCH.h"
#include "IResourcesProvider.h"
#include "ObjectManager.h"

class ServiceLocator
{
    public:
                                        ServiceLocator();
        virtual                         ~ServiceLocator();

        static IResourcesProvider*      GetResourcesProvider();
        static ObjectManager*           GetObjectManager();
        static sf::RenderWindow*        GetWindow();

        static void                     RegisterServiceLocator(IResourcesProvider* provider);
        static void                     RegisterServiceLocator(ObjectManager* manager);
        static void                     RegisterServiceLocator(sf::RenderWindow* window);

    protected:

    private:
        static IResourcesProvider*  _resourcesProvider;
        static ObjectManager*       _objectManager;
        static sf::RenderWindow*    _window;
};


#endif // SERVICELOCATOR_H
