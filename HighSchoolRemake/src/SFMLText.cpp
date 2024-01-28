#include "SFMLText.h"
#include "ServiceLocator.h"

SFMLText::SFMLText(SFMLResourcesProvider::SmartFont* font)
{
    _font = font;
    _text.setFont(font->GetFont());
}

SFMLText::~SFMLText()
{
    _font->DecreaseNumber();
}

void SFMLText::SetPos(const float& x,const float& y)
{
    _text.setPosition(x,y);
}

void SFMLText::SetColor(const int& red,const int& green,const int& blue,const int& alpha)
{
    _text.setFillColor(sf::Color(red,green,blue,alpha));
}

void SFMLText::Scale(const float& x,const float& y)
{
    _text.scale(x,y);
}

void SFMLText::SetOrigin(const float& x,const float& y)
{
    _text.setOrigin(x,y);
}

void SFMLText::SetString(const std::string& text)
{
    _text.setString(text);
}

void SFMLText::SetCharacterSize(const int& textSize)
{
    _text.setCharacterSize(textSize);
}

void SFMLText::SetFillColor(const unsigned int& red, const unsigned int& green, const unsigned int& blue, const unsigned int& alpha)
{
    _text.setFillColor(sf::Color(red,green,blue,alpha));
}

float SFMLText::GetWidth() const
{
    return _text.getLocalBounds().width;
}

float SFMLText::GetHeight() const
{
    return _text.getLocalBounds().height;
}

sf::FloatRect SFMLText::GetGlobalBounds() const
{
    return _text.getGlobalBounds();
}

const sf::Vector2f& SFMLText::GetPos() const
{
    return _text.getPosition();
}

const sf::Vector2f& SFMLText::GetOrigin() const
{
    return _text.getOrigin();
}

void SFMLText::Draw(const BlendMode& mode) const
{
    switch (mode) {
        case BlendNormal : ServiceLocator::GetWindow()->draw(_text); break;
        case BlendAdd : ServiceLocator::GetWindow()->draw(_text,sf::BlendAdd); break;
   }
}
