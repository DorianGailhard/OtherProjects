#ifndef SFMLTEXT_H
#define SFMLTEXT_H

#include "PCH.h"
#include "IText.h"
#include "SFMLResourcesProvider.h"

class SFMLText : public IText
{
    public:
             SFMLText(SFMLResourcesProvider::SmartFont* font);
             ~SFMLText();

        void SetPos(const float& x,const float& y);
        void SetColor(const int& red,const int& green,const int& blue,const int& alpha);
        void Scale(const float& x,const float& y);
        void SetOrigin(const float& x,const float& y);
        void SetString(const std::string& text);
        void SetCharacterSize(const int& textSize);
        void SetFillColor(const unsigned int& red,const unsigned int& green,const unsigned int& blue,const unsigned int& alpha);

        float GetWidth() const;
        float GetHeight() const;
        sf::FloatRect GetGlobalBounds() const;

        const sf::Vector2f& GetPos() const;
        const sf::Vector2f& GetOrigin() const;

        void Draw(const BlendMode& mode = BlendNormal) const;

    protected:

    private:
        SFMLResourcesProvider::SmartFont* _font;
        sf::Text _text;
};

#endif // SFMLTEXT_H
