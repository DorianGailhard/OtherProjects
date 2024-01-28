#ifndef SFMLSPRITE_H
#define SFMLSPRITE_H

#include "PCH.h"
#include "ISprite.h"
#include "SFMLResourcesProvider.h"

class SFMLSprite : public ISprite
{
    public:
             SFMLSprite(SFMLResourcesProvider::SmartTexture* texture);
             ~SFMLSprite();

        void SetPos(const float& x,const float& y);
        void SetColor(const int& red,const int& green,const int& blue,const int& alpha);
        void Scale(const float& x,const float& y);
        void SetOrigin(const float& x,const float& y);

        float GetWidth() const;
        float GetHeight() const;
        sf::FloatRect GetGlobalBounds() const;

        const sf::Vector2f& GetPos() const;
        const sf::Vector2f& GetOrigin() const;

        void Draw(const BlendMode& mode = BlendNormal) const;

    protected:

    private:
        SFMLResourcesProvider::SmartTexture* _texture;
        sf::Sprite _sprite;
};

#endif // SFMLSPRITE_H
