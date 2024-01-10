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

    sf::Texture texture;
    texture.loadFromFile("res/Haha.png");

    sf::Cube cube;
    cube.setTexture(texture);

    sf::Cube cube2;
    cube2.setColor(sf::Color::Green);
    cube2.setScale({.2, .2, .2});
    sf::Cube cube3;
    cube3.setColor(sf::Color::Blue);
    cube3.setScale({.2, .2, .2});
    sf::Cube cube4;
    cube4.setColor(sf::Color::Red);
    cube4.setScale({.2, .2, .2});

    cube2.setPosition(cube.getPosition() + (cube.getUp()) );
    cube3.setPosition(cube.getPosition() + (-cube.getForward()) );
    cube4.setPosition(cube.getPosition() + (cube.getRight()) );

    sf::Clock dtClock;
    float deltaTime = 0;
    bool running = true;
    while (running){
        deltaTime = dtClock.restart().asSeconds();
    
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

        window.clear();

        window.draw(cube);
        window.draw(cube2);
        window.draw(cube3);
        window.draw(cube4);

        window.display();
    }



    return 0;
}