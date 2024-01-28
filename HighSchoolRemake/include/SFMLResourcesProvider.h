#ifndef SFMLResourcesProvider_H
#define SFMLResourcesProvider_H

#include "PCH.h"
#include "IResourcesProvider.h"

class SFMLResourcesProvider : public IResourcesProvider
{
    public:
                    SFMLResourcesProvider();
                    ~SFMLResourcesProvider();

        ISprite*    AddSprite(const std::string& textureFilename);
        IText*      AddText(const std::string& fontFilename);

        void        DeleteSprite(ISprite* sprite);
        void        DeleteText(IText* text);

        void        UpdateResources();

        //A basic container of a texture, handling its lifetime
        struct SmartTexture {
            public:
                                    SmartTexture(const std::string& filename,SFMLResourcesProvider* provider);
                virtual             ~SmartTexture();

                const sf::Texture&  GetTexture();
                const unsigned int& GetNumber() const;
                void                DecreaseNumber();

            protected:

            private:
                void                Update();
                void                DeleteTexture();

                SFMLResourcesProvider* _provider;
                sf::Texture        _texture;
                unsigned int       _number; //Number of instances using this texture
                unsigned int       _cooldown; //Cooldown before deletion
                const std::string  _filename; //Filename for the desired file (for deletion)

            friend class SFMLResourcesProvider;
        };

        //A basic container of a font, handling its lifetime
        struct SmartFont {
            public:
                                    SmartFont(const std::string& filename,SFMLResourcesProvider* provider);
                virtual             ~SmartFont();

                const sf::Font&     GetFont();
                const unsigned int& GetNumber() const;
                void                DecreaseNumber();

            protected:

            private:
                void                Update();
                void                DeleteFont();

                SFMLResourcesProvider* _provider;
                sf::Font           _font;
                unsigned int       _number; //Number of instances using this texture
                unsigned int       _cooldown; //Cooldown before deletion
                const std::string  _filename; //Filename for the desired file (for deletion)

            friend class SFMLResourcesProvider;
        };

    protected:
        void          DeleteTexture(const std::string& filename);
        void          DeleteFont(const std::string& filename);

    private:
        std::map<std::string,SmartTexture*> _texture;
        std::map<std::string,SmartFont*>    _font;

        std::list<ISprite*>                 _sprite;
        std::list<IText*>                   _text;

        SmartTexture* GetTexture(const std::string& filename);
        SmartFont*    GetFont(const std::string& filename);

    friend SmartTexture;
    friend SmartFont;
};

#endif // SFMLResourcesProvider_H
