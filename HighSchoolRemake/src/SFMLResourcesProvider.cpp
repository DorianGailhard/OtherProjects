#include "SFMLResourcesProvider.h"
#include "ServiceLocator.h"
#include "SFMLSprite.h"
#include "SFMLText.h"

SFMLResourcesProvider::SFMLResourcesProvider()
{
    //ctor
}

SFMLResourcesProvider::~SFMLResourcesProvider()
{
    //dtor
}


//Add a sprite
ISprite* SFMLResourcesProvider::AddSprite(const std::string& textureFilename)
{
    ISprite* sprite = new SFMLSprite(GetTexture(textureFilename));
    _sprite.insert(_sprite.end(),sprite);

    return sprite;
}

//Delete a sprite
void SFMLResourcesProvider::DeleteSprite(ISprite* sprite)
{
    _sprite.remove(sprite);
}

//Add a text area
IText* SFMLResourcesProvider::AddText(const std::string& fontFilename)
{
    IText* text = new SFMLText(GetFont(fontFilename));
    _text.insert(_text.end(),text);

    return text;
}

//Delete a text area
void SFMLResourcesProvider::DeleteText(IText* text)
{
    _text.remove(text);
}

//Update stored resources (cooldown before deletion)
void SFMLResourcesProvider::UpdateResources()
{
    for (std::map<std::string,SmartTexture*>::iterator itr = _texture.begin();itr != _texture.end();itr++) {
        itr->second->Update();
    }

    for (std::map<std::string,SmartFont*>::iterator itr = _font.begin();itr != _font.end();itr++) {
        itr->second->Update();
    }
}



//Private
//Return a pointer to the selected texture (contained inside a "SmartTexture" handling its lifetime)
SFMLResourcesProvider::SmartTexture* SFMLResourcesProvider::GetTexture(const std::string& filename)
{
    std::map<std::string,SmartTexture*>::iterator itr = _texture.find(filename);

        if(itr == _texture.end()) {
            SmartTexture* texture = new SmartTexture(filename,this);
            _texture.insert(_texture.end(),std::pair<std::string,SmartTexture*>(filename,texture));

            return texture;
        } else {
            return itr->second;
        }
}

//Does what its name implies
void SFMLResourcesProvider::DeleteTexture(const std::string& filename)
{
        std::map<std::string,SmartTexture*>::iterator itr = _texture.find(filename);

        if(itr == _texture.end()) {
            std::cout << "Couldn't delete \"" << filename + "\" : no such texture found." << std::endl;
        } else {
            _texture.erase(itr);
            std::cout << "Texture \""<< filename + "\" deleted." << std::endl;
        }
}


//Return a pointer to the selected font (contained inside a "SmartFont" handling its lifetime)
SFMLResourcesProvider::SmartFont* SFMLResourcesProvider::GetFont(const std::string& filename)
{
    std::map<std::string,SmartFont*>::iterator itr = _font.find(filename);

        if(itr == _font.end()) {
            SmartFont* font = new SmartFont(filename,this);
            _font.insert(_font.end(),std::pair<std::string,SmartFont*>(filename,font));

            return font;
        } else {
            return itr->second;
        }
}

//Does what its name implies
void SFMLResourcesProvider::DeleteFont(const std::string& filename)
{
        std::map<std::string,SmartFont*>::iterator itr = _font.find(filename);

        if(itr == _font.end()) {
            std::cout << "Couldn't delete \"" << filename + "\" : no such font found." << std::endl;
        } else {
            _font.erase(itr);
            std::cout << "Font \""<< filename + "\" deleted." << std::endl;
        }
}


//SmartTexture
//Public
SFMLResourcesProvider::SmartTexture::SmartTexture(const std::string& filename,SFMLResourcesProvider* provider) : _provider(provider),_number(0),_cooldown(-1),_filename(filename)
{
    if(!_texture.loadFromFile("Texturepacks\\Default\\" + filename))
    {
        std::cout << "Couldn't load \""<< filename + "\" : no such texture found." << std::endl;
        return;
    }

    std::cout << "Texture \"" << filename << "\" loaded." << std::endl;
}

SFMLResourcesProvider::SmartTexture::~SmartTexture()
{
    //dtor
}

//Return pointer to the stored texture
const sf::Texture& SFMLResourcesProvider::SmartTexture::GetTexture()
{
    //Because one more instance uses it, increases the counter by one
    _number += 1;

    return _texture;
}

//Return the number of instances using the stored texture
const unsigned int& SFMLResourcesProvider::SmartTexture::GetNumber() const
{
    return _number;
}

//In case an object does not use this texture anymore, decreases its counter by one
void SFMLResourcesProvider::SmartTexture::DecreaseNumber()
{
    _number -= 1;
}

//Private
//Delete the texture when it is not used anymore
void SFMLResourcesProvider::SmartTexture::Update()
{
    if (_number == 0) {
        _cooldown += 1;
    }

    if (_cooldown == ServiceLocator::GetResourcesProvider()->GetResourceLifetime()) {
        DeleteTexture();
    }
}

//Delete this object
void SFMLResourcesProvider::SmartTexture::DeleteTexture()
{
        _provider->DeleteTexture(_filename);
        this->~SmartTexture();
}



//SmartFont
//Public
SFMLResourcesProvider::SmartFont::SmartFont(const std::string& filename,SFMLResourcesProvider* provider) : _provider(provider),_number(0),_cooldown(-1),_filename(filename)
{
    if(!_font.loadFromFile("Texturepacks\\Default\\Fonts\\" + filename))
    {
        std::cout << "Couldn't load \""<< filename + "\" : no such font found." << std::endl;
        return;
    }

    std::cout << "Font \"" << filename << "\" loaded." << std::endl;
}

SFMLResourcesProvider::SmartFont::~SmartFont()
{
    //dtor
}

//Return pointer to the stored texture
const sf::Font& SFMLResourcesProvider::SmartFont::GetFont()
{
    //Because one more instance uses it, increases the counter by one
    _number += 1;

    return _font;
}

//Return the number of instances using the stored texture
const unsigned int& SFMLResourcesProvider::SmartFont::GetNumber() const
{
    return _number;
}

//In case an object does not use this texture anymore, decreases its counter by one
void SFMLResourcesProvider::SmartFont::DecreaseNumber()
{
    _number -= 1;
}

//Private
//Delete the texture when it is not used anymore
void SFMLResourcesProvider::SmartFont::Update()
{
    if (_number == 0) {
        _cooldown += 1;
    }

    if (_cooldown == ServiceLocator::GetResourcesProvider()->GetResourceLifetime()) {
        DeleteFont();
    }
}

//Delete this object
void SFMLResourcesProvider::SmartFont::DeleteFont()
{
        _provider->DeleteFont(_filename);
        this->~SmartFont();
}
