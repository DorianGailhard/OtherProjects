#ifndef IResourcesProvider_H
#define IResourcesProvider_H

#include "PCH.h"
#include "ISprite.h"
#include "IText.h"

class IResourcesProvider
{
    public:
                            IResourcesProvider() : _resourceLifetime(500) {};
        virtual             ~IResourcesProvider() {};

        virtual ISprite*    AddSprite(const std::string& textureFilename) = 0;
        virtual IText*      AddText(const std::string& fontFilename) = 0;

        virtual void        DeleteSprite(ISprite* sprite) = 0;
        virtual void        DeleteText(IText* text) = 0;

        virtual void        UpdateResources() = 0;

        unsigned int        GetResourceLifetime() const { return _resourceLifetime; };

    protected:

    private:
        unsigned int _resourceLifetime;
};

#endif // IResourcesProvider_H
