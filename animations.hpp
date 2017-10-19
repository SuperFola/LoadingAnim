#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>

namespace sx
{

    namespace Colors
    {
        const sf::Color orange = sf::Color(250, 150, 50)
                      , purple = sf::Color(150, 50, 250);
    }

    class LoadingAnim
    {
    using ColorsUpdateFct = std::function<void(sf::Time, sf::Color&, sf::Color&)>;

    private:
        int kind;
        float max_size;
        float rotation;
        bool increasing;
        int outline_thickness;

        const float _lim = 2.0f;

        sf::Color fill_color;
        sf::Color outline_color;

        sf::CircleShape circ_shape;
        sf::RectangleShape rect_shape;
        sf::CircleShape poly_shape;

        ColorsUpdateFct colors_update;

    public:
        LoadingAnim(int k=0, float ms=50.0f, int s=8);
        void update(sf::Time&);
        void render(sf::RenderWindow&);
        void setFillColor(sf::Color);
        void setOutlineColor(sf::Color);
        void setColors(sf::Color, sf::Color);
        bool setKind(int);
        void setRotation(float);
        void registerColorUpdateFct(ColorsUpdateFct);

        static const int _MIN_K = 0
                  , CIRCLE = 0
                  , SQUARE = 1
                  , POLY = 2
                  , _MAX_K = 2;
    };

}  // namespace sx
