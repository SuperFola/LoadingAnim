#include "animations.hpp"

namespace sx
{

    LoadingAnim::LoadingAnim(int k, float ms, int s) :
        kind(k)
        , max_size(ms)
        , sides(s)
        , rotation(0.0f)
        , outline_thickness(10)
        , fill_color(Colors::purple)
        , outline_color(Colors::orange)
        , circ_shape(ms)
        , rect_shape(sf::Vector2f(ms * 2.0f, ms * 2.0f))
        , poly_shape(ms, s)
    {
        this->increasing = false;

        this->circ_shape.setOutlineThickness(this->outline_thickness);
        this->circ_shape.setFillColor(this->fill_color);
        this->circ_shape.setOutlineColor(this->outline_color);
        this->circ_shape.setOrigin(this->max_size / 2.0f, this->max_size / 2.0f);

        this->rect_shape.setOutlineThickness(this->outline_thickness);
        this->rect_shape.setFillColor(this->fill_color);
        this->rect_shape.setOutlineColor(this->outline_color);
        this->rect_shape.setOrigin(this->max_size, this->max_size);

        this->poly_shape.setOutlineThickness(this->outline_thickness);
        this->poly_shape.setFillColor(this->fill_color);
        this->poly_shape.setOutlineColor(this->outline_color);
        this->poly_shape.setOrigin(this->max_size / 2.0f, this->max_size / 2.0f);

        this->colors_update = [](sf::Time elapsed, sf::Color& fc, sf::Color& oc){};
    }

    void LoadingAnim::update(sf::Time& elapsed)
    {
        this->colors_update(elapsed, this->fill_color, this->outline_color);
        this->setColors(this->fill_color, this->outline_color);

        if (this->increasing)
            this->outline_thickness++;
        else
            this->outline_thickness--;

        switch (this->kind)
        {
        case LoadingAnim::CIRCLE:
            this->circ_shape.setOutlineThickness(this->outline_thickness);
            this->circ_shape.setRadius(this->max_size - this->outline_thickness);
            this->circ_shape.setOrigin(
                                       this->circ_shape.getRadius() / 2.0f - this->outline_thickness / 2.0f
                                       , this->circ_shape.getRadius() / 2.0f - this->outline_thickness / 2.0f
                                       );
            break;

        case LoadingAnim::SQUARE:
            this->rect_shape.setOutlineThickness(this->outline_thickness);
            this->rect_shape.setSize(sf::Vector2f(
                                                  (this->max_size - this->outline_thickness) * 2.0f
                                                  , (this->max_size - this->outline_thickness) * 2.0f));
            this->rect_shape.setOrigin(
                                       this->rect_shape.getSize().x / 2.0f
                                       , this->rect_shape.getSize().y / 2.0f
                                       );
            this->rect_shape.rotate(this->rotation);
            break;

        case LoadingAnim::POLY:
            this->poly_shape.setOutlineThickness(this->outline_thickness);
            this->poly_shape.setRadius(this->max_size - this->outline_thickness);
            this->poly_shape.setOrigin(
                                       this->poly_shape.getRadius() / 2.0f - this->outline_thickness / 2.0f
                                       , this->poly_shape.getRadius() / 2.0f - this->outline_thickness / 2.0f
                                       );
            this->poly_shape.rotate(this->rotation);
            break;

        default:
            break;
        }

        if (this->increasing && this->outline_thickness == this->max_size - this->_lim)
            this->increasing = false;
        else if (!this->increasing && this->outline_thickness == this->_lim)
            this->increasing = true;
    }

    void LoadingAnim::render(sf::RenderWindow& window)
    {
        switch (this->kind)
        {
        case LoadingAnim::CIRCLE:
            this->circ_shape.setPosition(
                                         window.getSize().x / 2.0f - this->max_size / 2.0f
                                         , window.getSize().y / 2.0f - this->max_size / 2.0f
                                         );
            window.draw(this->circ_shape);
            break;

        case LoadingAnim::SQUARE:
            this->rect_shape.setPosition(
                                         window.getSize().x / 2.0f
                                         , window.getSize().y / 2.0f
                                         );
            window.draw(this->rect_shape);
            break;

        case LoadingAnim::POLY:
            this->poly_shape.setPosition(
                                         window.getSize().x / 2.0f - this->max_size / 2.0f
                                         , window.getSize().y / 2.0f - this->max_size / 2.0f
                                         );
            window.draw(this->poly_shape);
            break;

        default:
            break;
        }
    }

    void LoadingAnim::setFillColor(sf::Color fc)
    {
        this->fill_color = fc;

        switch (this->kind)
        {
        case LoadingAnim::CIRCLE:
            this->circ_shape.setFillColor(this->fill_color);
            break;

        case LoadingAnim::SQUARE:
            this->rect_shape.setFillColor(this->fill_color);
            break;

        case LoadingAnim::POLY:
            this->poly_shape.setFillColor(this->fill_color);
            break;

        default:
            break;
        }
    }

    void LoadingAnim::setOutlineColor(sf::Color oc)
    {
        this->outline_color = oc;

        switch (this->kind)
        {
        case LoadingAnim::CIRCLE:
            this->circ_shape.setOutlineColor(this->outline_color);
            break;

        case LoadingAnim::SQUARE:
            this->rect_shape.setOutlineColor(this->outline_color);
            break;

        case LoadingAnim::POLY:
            this->poly_shape.setOutlineColor(this->outline_color);
            break;

        default:
            break;
        }
    }

    void LoadingAnim::setColors(sf::Color fc, sf::Color oc)
    {
        this->setFillColor(fc);
        this->setOutlineColor(oc);
    }

    bool LoadingAnim::setKind(int k)
    {
        if (LoadingAnim::_MIN_K <= k && k <= LoadingAnim::_MAX_K)
        {
            this->kind = k;
            return true;
        }
        return false;
    }

    void LoadingAnim::setRotation(float r)
    {
        this->rotation = r;
    }

    void LoadingAnim::registerColorUpdateFct(ColorsUpdateFct cuf)
    {
        this->colors_update = cuf;
    }

}  // namespace sx
