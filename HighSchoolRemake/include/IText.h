#ifndef ITEXT_H
#define ITEXT_H


class IText
{
    public:
        enum BlendMode { BlendNormal,BlendAdd };

        IText() {};

        virtual void SetPos(const float& x,const float& y) = 0;
        virtual void SetColor(const int& red,const int& green,const int& blue,const int& alpha) = 0;
        virtual void Scale(const float& x,const float& y) = 0;
        virtual void SetOrigin(const float& x,const float& y) = 0;
        virtual void SetString(const std::string& text) = 0;
        virtual void SetCharacterSize(const int& textSize) = 0;
        virtual void SetFillColor(const unsigned int& red,const unsigned int& green,const unsigned int& blue,const unsigned int& alpha) = 0;

        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual sf::FloatRect GetGlobalBounds() const = 0;

        virtual const sf::Vector2f& GetPos() const = 0;
        virtual const sf::Vector2f& GetOrigin() const = 0;

        virtual void Draw(const BlendMode& mode = BlendNormal) const = 0;

    protected:

    private:
};

#endif // ITEXT_H
