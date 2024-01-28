#ifndef MENUITEM_H
#define MENUITEM_H

#include "PCH.h"
#include "IResourcesProvider.h"

//Base classes
class MenuItem
{
    public:
                    MenuItem(const std::string& backgroundFilename,const int& x,const int& y);
        virtual     ~MenuItem();

        void        Update();
        void        Draw();

        const int&  GetPosX() const;
        const int&  GetPosY() const;

    protected:

    private:
        std::string   _textureFilename;
        ISprite*      _background;
        int           _x;
        int           _y;

    public:
        //Basic container of Elements
        struct ElementsBox {
            public:
                enum ElementType { Basic,Button };
                enum ElementFunction { OpenMenu };

                                    ElementsBox(MenuItem* menu,const int& x,const int& y,const sf::Vector2u& box,const sf::Vector2u& Elementsize,const int& spaceBetweenLine,const std::string& buttonBackgroundFilename);

                void                DrawElements();

                int                 GetPosX() const;
                int                 GetPosY() const;
                int                 GetWidth() const;
                int                 GetHeight() const;
                const sf::Vector2u& GetElementsize() const;

                const int&          GetSpaceBetweenLine() const;

                MenuItem*           GetMenuItem() const;

                int                 GetOpacity() const;

                const sf::Image*    GetButtonBackgroundCopy() const;

                void                Update();

                //Basic Element
                struct Element {
                    public:
                                        Element(const int& number,ElementsBox* box,const sf::Vector2u& Elementsize,const std::string& backgroundTextureFilename);

                        void            Draw();

                        void            Update();

                        const bool&     IsMouseOn() const;

                        float           GetPosX() const;
                        float           GetPosY() const;

                        int             GetOpacity() const;

                        //Types of usage for the element (Button, SelectableButton, ...)
                        //Standard interface
                        struct IElementUsage {
                            public:
                                virtual void Update() = 0;
                                virtual void Draw() = 0;
                        };

                        //Basic button
                        struct UsageButton : public IElementUsage {
                            public:
                                        UsageButton(Element* element,const std::string& textureFilename);
                                void    Update();
                                void    Draw();

                            private:
                                Element*        _element;
                                ISprite*        _highlight;
                                ISprite*        _click;
                                bool            _clickedOn;
                                int             _highlightA;
                                int             _clickA;
                        };

                        //What is displayed on the element
                        //Standard interface
                        struct IElementDisplay {
                            public:
                                virtual void Update() = 0;
                                virtual void Draw() = 0;
                        };

                        //Basic button
                        struct DisplayIcon : public IElementDisplay {
                            public:
                                        DisplayIcon(Element* element,const std::string& textureFilename);
                                void    Update();
                                void    Draw();

                            private:
                                ISprite*        _iconSprite;
                                Element*        _element;
                        };

                        //Basic button
                        struct DisplayText : public IElementDisplay {
                            public:
                                        DisplayText(Element* element,const std::string& text,const std::string& fontFilename,const unsigned int& textSize,const int& red,const int& green,const int& blue,const int& alpha = 255);
                                void    Update();
                                void    Draw();

                            private:
                                IText*              _text;
                                Element*            _element;
                        };

                        //What the element do
                        //Standard interface
                        struct IElementFunction {
                            public:
                                virtual void Perform() = 0;
                        };

                        //Open a menu
                        struct OpenMenu : public IElementFunction {
                            public:
                                     OpenMenu(Element* element);
                                void Perform();

                            private:
                                Element* _element;
                        };

                    protected:
                        void              Kill();
                        IElementFunction* GetFunction() const;


                    private:
                        void        UpdateNumber(const unsigned int& number);
                        void        SetElementUsage(IElementUsage* usage);
                        void        SetElementDisplay(IElementDisplay* display);
                        void        SetElementFunction(IElementFunction* funct);

                        float               _x;
                        float               _y;
                        ISprite*            _background;
                        sf::Vector2u        _size;
                        ElementsBox*        _box;
                        unsigned int        _number;
                        float               _speed;
                        float               _maxSpeed;
                        int                 _opacity;
                        bool                _living;
                        bool                _isMouseOn;
                        IElementUsage*      _elementUsage;
                        IElementDisplay*    _elementDisplay;
                        IElementFunction*   _elementFunction;

                    friend ElementsBox;
                };

                Element* AddElement(const ElementType& type,const ElementFunction funct,const std::string& iconTextureFilename);
                Element* AddElement(const ElementType& type,const ElementFunction funct,const std::string& text,const std::string& fontFilename,const unsigned int& textSize,const int& red,const int& green,const int& blue,const int& alpha = 255);

            protected:

            private:
                void    UpdateElementsNumbers(const unsigned int& number);
                void    DeleteButton(Element* Element);

                std::list<Element*> _list;
                int                 _x;
                int                 _y;
                sf::Vector2u        _box;
                ISprite*            _background;
                std::string         _buttonBackgroundFilename;
                sf::Vector2u        _Elementsize;
                int                 _spaceBetweenLine;
                MenuItem*           _menu;
                sf::Image*          _buttonBackgroundCopy;
                unsigned int        _ElementsNumber;
        };

    //Here because it needs the declaration of ElementsBox
    ElementsBox* AddElementsBox(const std::string& name,const int& x,const int& y,const sf::Vector2u& box,const sf::Vector2u& Elementsize,const int& spaceBetweenLine,const std::string& buttonBackground,const std::string& buttonHighlight = "");

    private:
        std::map<std::string, ElementsBox*>  _list;
};


#endif // MENUITEM_H
