#include "MenuItem.h"
#include "ServiceLocator.h"
#include "InputHandler.h"

MenuItem::MenuItem(const std::string& backgroundFilename,const int& x,const int& y) : _x(x), _y(y)
{
    _background = ServiceLocator::GetResourcesProvider()->AddSprite(backgroundFilename);
}

MenuItem::~MenuItem()
{
    _background->~ISprite();
}


void MenuItem::Update()
{
    _background->SetPos(_x,_y);

    for (std::map<std::string,ElementsBox*>::iterator itr = _list.begin();itr != _list.end();itr++) {
        itr->second->Update();
    }
}


void MenuItem::Draw()
{
    _background->Draw();

    for (std::map<std::string,ElementsBox*>::iterator itr = _list.begin();itr != _list.end();itr++) {
        itr->second->DrawElements();
    }
}


MenuItem::ElementsBox* MenuItem::AddElementsBox(const std::string& name,const int& x,const int& y,const sf::Vector2u& box,const sf::Vector2u& Elementsize,const int& spaceBetweenLine,const std::string& buttonBackground,const std::string& buttonHighlight)
{
        ElementsBox* newBox = new ElementsBox(this,x,y,box,Elementsize,spaceBetweenLine,buttonBackground);
        return (_list.insert(_list.end(),std::pair<std::string,ElementsBox*>(name,newBox)))->second;
}


const int& MenuItem::GetPosX() const { return _x; }
const int& MenuItem::GetPosY() const { return _y; }















//ElementsBox
MenuItem::ElementsBox::ElementsBox(MenuItem* menu,const int& x,const int& y,const sf::Vector2u& box,const sf::Vector2u& Elementsize,const int& spaceBetweenLine,const std::string& buttonBackgroundFilename)
: _x(x),_y(y),_box(box),_buttonBackgroundFilename(buttonBackgroundFilename),_Elementsize(Elementsize),_spaceBetweenLine(spaceBetweenLine),_menu(menu),_ElementsNumber(0)
{
    //Storing an sf::image of Element background for collision checking
    _buttonBackgroundCopy = new sf::Image;
    _buttonBackgroundCopy->loadFromFile("Texturepacks\\Default\\" + buttonBackgroundFilename);
}


MenuItem::ElementsBox::Element* MenuItem::ElementsBox::AddElement(const ElementType& type,const ElementFunction funct,const std::string& iconTextureFilename)
{
    _ElementsNumber++;

    Element* element = *(_list.insert(_list.end(),new Element(_ElementsNumber - 1,this,_Elementsize,_buttonBackgroundFilename)));
    element->SetElementUsage(new Element::UsageButton(element,_buttonBackgroundFilename));
    element->SetElementDisplay(new Element::DisplayIcon(element,iconTextureFilename));
    element->SetElementFunction(new Element::OpenMenu(element));

    return element;
}

MenuItem::ElementsBox::Element* MenuItem::ElementsBox::AddElement(const ElementType& type,const ElementFunction funct,const std::string& text,const std::string& fontFilename,const unsigned int& textSize,const int& red,const int& green,const int& blue,const int& alpha)
{
    _ElementsNumber++;

    Element* element = *(_list.insert(_list.end(),new Element(_ElementsNumber - 1,this,_Elementsize,_buttonBackgroundFilename)));
    element->SetElementUsage(new Element::UsageButton(element,_buttonBackgroundFilename));
    element->SetElementDisplay(new Element::DisplayText(element,text,fontFilename,textSize,red,green,blue));
    element->SetElementFunction(new Element::OpenMenu(element));

    return element;
}


void MenuItem::ElementsBox::DrawElements()
{
    for(std::list<Element*>::iterator itr = _list.begin();itr != _list.end();itr++) {
        (*itr)->Draw();
    }
}


int MenuItem::ElementsBox::GetPosX() const { return _menu->GetPosX() + _x; }
int MenuItem::ElementsBox::GetPosY() const { return _menu->GetPosY() + _y; }
int MenuItem::ElementsBox::GetWidth() const { return _box.x; }
int MenuItem::ElementsBox::GetHeight() const { return _box.y; }
const sf::Vector2u& MenuItem::ElementsBox::GetElementsize() const { return _Elementsize; }
const int& MenuItem::ElementsBox::GetSpaceBetweenLine() const { return _spaceBetweenLine; }
MenuItem* MenuItem::ElementsBox::GetMenuItem() const { return _menu; }
int MenuItem::ElementsBox::GetOpacity() const { return 1; }
const sf::Image* MenuItem::ElementsBox::GetButtonBackgroundCopy() const { return _buttonBackgroundCopy; }


void MenuItem::ElementsBox::Update()
{
    //Special "for" loop to prevent a crash when removing a Element from the list
    std::list<Element*>::iterator itr(_list.begin());
    std::list<Element*>::iterator itr2(_list.begin());

    for(std::list<Element*>::iterator itr = _list.begin();itr != _list.end();itr = itr2) {
        itr2++;

        (*itr)->Update();

        itr = itr2;
    }
}

//Private
void MenuItem::ElementsBox::UpdateElementsNumbers(const unsigned int& number)
{
    _ElementsNumber--;

    for(std::list<Element*>::iterator itr = _list.begin();itr != _list.end();itr++) {
        (*itr)->UpdateNumber(number);
    }
}


void MenuItem::ElementsBox::DeleteButton(Element* Element) {
    _list.remove(Element);
}













//Elements
MenuItem::ElementsBox::Element::Element(const int& number,ElementsBox* box,const sf::Vector2u& Elementsize,const std::string& backgroundTextureFilename) : _x(0),_y(0),_size(Elementsize),_box(box),_number(number),_speed(0),_maxSpeed(0),_opacity(0),_living(true)
{
    _background = ServiceLocator::GetResourcesProvider()->AddSprite(backgroundTextureFilename);
    _background->SetColor(255,255,255,0);
    _background->SetOrigin(_background->GetWidth()/2,_background->GetHeight()/2);
}


void MenuItem::ElementsBox::Element::Draw()
{
        _background->Draw();
        _elementDisplay->Draw();
        _elementUsage->Draw();
}


void MenuItem::ElementsBox::Element::Update()
{
    //Position
    float xtarget,ytarget;
    int ElementsPerLine;

    ElementsPerLine = std::floor(_box->GetWidth()/_box->GetElementsize().x);

    xtarget = std::round((_number%ElementsPerLine) * _box->GetWidth()/ElementsPerLine);
    ytarget = std::round(std::floor(_number/ElementsPerLine) * (_box->GetElementsize().y + _box->GetSpaceBetweenLine()) * _box->GetOpacity());

    if (_opacity != 0) {
        _speed = std::min(std::min(_maxSpeed,_speed + myfuncs::distance(_x,_y,xtarget,ytarget)/40),myfuncs::distance(_x,_y,xtarget,ytarget)/7);

        if (_x != xtarget || _y != ytarget) {
            if (_maxSpeed == 0) {
                _maxSpeed = myfuncs::distance(_x,_y,xtarget,ytarget)/10;
            }

            _x += myfuncs::lengthDirX(_speed,myfuncs::direction(_x,_y,xtarget,ytarget));
            _y += myfuncs::lengthDirY(_speed,myfuncs::direction(_x,_y,xtarget,ytarget));

            if (myfuncs::distance(_x,_y,xtarget,ytarget) < 1) {
                _x = xtarget;
                _y = ytarget;
            }

        } else {
            _maxSpeed = 0;
        }
    } else {
        _x = xtarget;
        _y = ytarget;
    }

    //Opacity
    if (_living == true) {
        _opacity = std::min(10,_opacity + 1);
    }

    //Death animation
    if (_living == false) {
        if (_opacity == 0) {
            _box->DeleteButton(this);
        }

        _opacity = std::max(0,_opacity - 1);
    }

    //Sprites update
    _background->SetPos(GetPosX(),GetPosY());
    _background->SetColor(255,255,255,255 * _opacity/10 * _box->GetOpacity());

    //Check if mouse is on the Element
    _isMouseOn = false;

    sf::Vector2f mouseVec((sf::Vector2f)sf::Mouse::getPosition(*(ServiceLocator::GetWindow())));

    if(_background->GetGlobalBounds().contains(mouseVec)) {
        sf::Vector2f vec(mouseVec - _background->GetPos() + _background->GetOrigin());

        if (_box->GetButtonBackgroundCopy()->getPixel(vec.x,vec.y).a == 255) {
            _isMouseOn = true;
        }
    }

    //Update additional objects
    _elementUsage->Update();
    _elementDisplay->Update();
}


float MenuItem::ElementsBox::Element::GetPosX() const { return _box->GetPosX() + _x; }
float MenuItem::ElementsBox::Element::GetPosY() const { return _box->GetPosY() + _y; }
int MenuItem::ElementsBox::Element::GetOpacity() const { return 255 * _opacity/10 * _box->GetOpacity(); }
MenuItem::ElementsBox::Element::IElementFunction* MenuItem::ElementsBox::Element::GetFunction() const { return _elementFunction; }

//Protected
void MenuItem::ElementsBox::Element::Kill()
{
    if (_living) {
        _living = false;

        _box->UpdateElementsNumbers(_number);
    }
}


//Private
const bool& MenuItem::ElementsBox::Element::IsMouseOn() const { return _isMouseOn; }

void MenuItem::ElementsBox::Element::UpdateNumber(const unsigned int& number)
{
    if (_number > number) {
        _number--;
    }
}

void MenuItem::ElementsBox::Element::SetElementUsage(IElementUsage* usage) {
    _elementUsage = usage;
}

void MenuItem::ElementsBox::Element::SetElementDisplay(IElementDisplay* display) {
    _elementDisplay = display;
}

void MenuItem::ElementsBox::Element::SetElementFunction(IElementFunction* funct) {
    _elementFunction = funct;
}














//Usages
//Button
MenuItem::ElementsBox::Element::UsageButton::UsageButton(Element* element,const std::string& textureFilename) : _element(element),_highlightA(0),_clickA(0) {
    //Creating the necessary sprites
    _highlight = ServiceLocator::GetResourcesProvider()->AddSprite(textureFilename);
    _highlight->SetOrigin(_highlight->GetWidth()/2,_highlight->GetHeight()/2);

    _click = ServiceLocator::GetResourcesProvider()->AddSprite(textureFilename);
    _click->SetOrigin(_click->GetWidth()/2,_click->GetHeight()/2);
}

void MenuItem::ElementsBox::Element::UsageButton::Update() {
    //Highlighting
    if (InputHandler::GetButtonState(sf::Mouse::Left) == InputHandler::None && _element->IsMouseOn()) {
        _clickedOn = true;
        _highlightA = std::min(10,_highlightA + 1);
    } else {
        _highlightA = std::max(0,_highlightA - 1);
    }

    //Ensure that click shadowing only appears while clicking on the button
    if (InputHandler::GetButtonState(sf::Mouse::Left) == InputHandler::None && !_element->IsMouseOn()) {
        _clickedOn = false;
    }

    //Click shadowing
    if (InputHandler::GetButtonState(sf::Mouse::Left) == InputHandler::Held && _clickedOn == true) {
        _clickA = std::min(10,_clickA + 1);
    } else {
        _clickA = std::max(0,_clickA - 1);
    }

    //Perform
    if (InputHandler::GetButtonState(sf::Mouse::Left) == InputHandler::Released && _clickedOn && _element->IsMouseOn()) {
        _element->GetFunction()->Perform();
    }

    //Updating sprites
    _highlight->SetPos(_element->GetPosX(),_element->GetPosY());
    _highlight->SetColor(255,255,255,_element->GetOpacity() * _highlightA/20);

    _click->SetPos(_element->GetPosX(),_element->GetPosY());
    _click->SetColor(0,0,0,_element->GetOpacity() * _clickA/20);
}

void MenuItem::ElementsBox::Element::UsageButton::Draw() {
    _highlight->Draw(ISprite::BlendAdd);
    _click->Draw();
}


//Display
//Icon
MenuItem::ElementsBox::Element::DisplayIcon::DisplayIcon(Element* element,const std::string& textureFilename) : _element(element) {
    _iconSprite = ServiceLocator::GetResourcesProvider()->AddSprite(textureFilename);
    _iconSprite->SetOrigin(_iconSprite->GetWidth()/2,_iconSprite->GetHeight()/2);
}

void MenuItem::ElementsBox::Element::DisplayIcon::Update() {
    //Sprites update
    _iconSprite->SetPos(_element->GetPosX(),_element->GetPosY());
    _iconSprite->SetColor(255,255,255,_element->GetOpacity());
}

void MenuItem::ElementsBox::Element::DisplayIcon::Draw() {
    _iconSprite->Draw();
}


//Text
MenuItem::ElementsBox::Element::DisplayText::DisplayText(Element* element,const std::string& text,const std::string& fontFilename,const unsigned int& textSize,const int& red,const int& green,const int& blue,const int& alpha) : _element(element) {
    _text = ServiceLocator::GetResourcesProvider()->AddText(fontFilename);
    _text->SetString(text);
    _text->SetCharacterSize(textSize);
    _text->SetFillColor(red,green,blue,alpha);
    _text->SetOrigin(_text->GetWidth(),_text->GetHeight());
}

void MenuItem::ElementsBox::Element::DisplayText::Update() {
    //Text update
    _text->SetPos(_element->GetPosX(),_element->GetPosY());
    _text->SetFillColor(255,255,255,_element->GetOpacity());
}

void MenuItem::ElementsBox::Element::DisplayText::Draw() {
    _text->Draw();
}


//Functions
//Open a menu
MenuItem::ElementsBox::Element::OpenMenu::OpenMenu(Element* element) : _element(element) {
}

void MenuItem::ElementsBox::Element::OpenMenu::Perform() {
    _element->Kill();
}
