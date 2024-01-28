#ifndef ISPRITE_H
#define ISPRITE_H


class ISprite
{
    public:
        enum BlendMode { BlendNormal,BlendAdd };

        ISprite() {};

        virtual void SetPos(const float& x,const float& y) = 0;
        virtual void SetColor(const int& red,const int& green,const int& blue,const int& alpha) = 0;
        virtual void Scale(const float& x,const float& y) = 0;
        virtual void SetOrigin(const float& x,const float& y) = 0;

        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
        virtual sf::FloatRect GetGlobalBounds() const = 0;

        virtual const sf::Vector2f& GetPos() const = 0;
        virtual const sf::Vector2f& GetOrigin() const = 0;

        virtual void Draw(const BlendMode& mode = BlendNormal) const = 0;

    protected:

    private:
};

#endif // ISPRITE_H
