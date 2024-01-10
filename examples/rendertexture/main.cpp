#include <SFML/Graphics.hpp>
#include <SFML3D/SFML3D.hpp>

int main()
{

    sf::RenderWindow3D window(sf::VideoMode(1080, 1080), "Game");
    window.setFramerateLimit(120);

    float camSpeed = 2.5;
    float camRot = 60;
    sf::View3D& camera = window.getView3D();
    camera.setOrigin({0, 0, 3});
    camera.setPosition({0, 0, 0});

    sf::RenderTexture3D renderTexture;
    renderTexture.create(500,500);

    sf::Plane plane;
    plane.setTexture(renderTexture.getTexture());

    sf::Clock dtClock;
    float deltaTime = 0;
    float runtime = 0;
    bool running = true;
    while (running){
        deltaTime = dtClock.restart().asSeconds();
        runtime += deltaTime;
    
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) running = false;
        }

        float forward = sf::Keyboard::isKeyPressed(sf::Keyboard::S)-sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        float right = sf::Keyboard::isKeyPressed(sf::Keyboard::D)-sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        float up = sf::Keyboard::isKeyPressed(sf::Keyboard::E)-sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

        camera.rotate({forward*deltaTime*camRot, right*deltaTime*camRot, 0});
        camera.setOrigin({0, 0, camera.getOrigin().z + up*deltaTime*camSpeed});

        renderTexture.clear({50, 50, 50});

        sf::CircleShape circle(20);
        circle.setOrigin(20, 20);
        circle.setFillColor({255, 0, 100});
        circle.setPosition( sf::Vector2f{250, 250} + sf::Vector2f{cosf(runtime)*100, sinf(runtime)*100} );
        renderTexture.draw(circle);

        renderTexture.display();

        window.clear();

        window.draw(plane);

        window.display();
    }



    return 0;
}