#include "SFMLSprite.h"
#include "ServiceLocator.h"

SFMLSprite::SFMLSprite(SFMLResourcesProvider::SmartTexture* texture)
{
    _texture = texture;
    _sprite.setTexture(texture->GetTexture());
}

SFMLSprite::~SFMLSprite()
{
    _texture->DecreaseNumber();
}

void SFMLSprite::SetPos(const float& x,const float& y)
{
    _sprite.setPosition(x,y);
}

void SFMLSprite::SetColor(const int& red,const int& green,const int& blue,const int& alpha)
{
    _sprite.setColor(sf::Color(red,green,blue,alpha));
}

void SFMLSprite::Scale(const float& x,const float& y)
{
    _sprite.scale(x,y);
}

void SFMLSprite::SetOrigin(const float& x,const float& y)
{
    _sprite.setOrigin(x,y);
}

float SFMLSprite::GetWidth() const
{
    return _sprite.getLocalBounds().width;
}

float SFMLSprite::GetHeight() const
{
    return _sprite.getLocalBounds().height;
}

sf::FloatRect SFMLSprite::GetGlobalBounds() const
{
    return _sprite.getGlobalBounds();
}

const sf::Vector2f& SFMLSprite::GetPos() const
{
    return _sprite.getPosition();
}

const sf::Vector2f& SFMLSprite::GetOrigin() const
{
    return _sprite.getOrigin();
}

void SFMLSprite::Draw(const BlendMode& mode) const
{
    switch (mode) {
        case BlendNormal : ServiceLocator::GetWindow()->draw(_sprite); break;
        case BlendAdd : ServiceLocator::GetWindow()->draw(_sprite,sf::BlendAdd); break;
   }
}
