#include <SFML/Graphics.hpp>

#include "animations.hpp"

#define SIN(f, t, i) (std::sin(f * t + i) * 127.0f + 128.0f)
#define COS(f, t, i) (std::cos(f * t + i) * 127.0f + 128.0f)

int main()
{
    sf::RenderWindow window(sf::VideoMode(480, 480), "Animations");
    sx::LoadingAnim loam(sx::LoadingAnim::POLY, 96.0f, 10);
    sf::Time elapsed;
    sf::Clock clock;

    window.setFramerateLimit(60);

    loam.registerColorUpdateFct([](sf::Time elapsed, sf::Color& fc, sf::Color& oc){
                                float freq = 0.7f;

                                fc.r = SIN(freq, elapsed.asSeconds(), 0.0f);
                                fc.g = SIN(freq, elapsed.asSeconds(), 2.0f);
                                fc.b = SIN(freq, elapsed.asSeconds(), 4.0f);

                                oc.r = COS(freq, elapsed.asSeconds(), 0.0f);
                                oc.g = COS(freq, elapsed.asSeconds(), 2.0f);
                                oc.b = COS(freq, elapsed.asSeconds(), 4.0f);
                                });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::C)
                    loam.setKind(sx::LoadingAnim::CIRCLE);
                else if (event.key.code == sf::Keyboard::S)
                {
                    loam.setKind(sx::LoadingAnim::SQUARE);
                    loam.setRotation(1.0f);
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    loam.setKind(sx::LoadingAnim::POLY);
                    loam.setRotation(1.0f);
                }
            }
        }

        // update
        sf::Time dt = clock.restart();
        elapsed += dt;
        loam.update(elapsed);

        // render
        window.clear();
        loam.render(window);
        window.display();
    }

    return 0;
}
