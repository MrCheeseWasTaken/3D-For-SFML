# 3D-For-SFML

```Disclaimer: The current state of the project is in early stage of development and therefore I do not recommend to use in projects```

This a small 3D library I made using SFML 2.6 and Opengl
I made this library to learn about 3D and therefore there will be some bugs

The library was inspired by SFML so it uses many of bits of SFML

# Usage
1) Download the release
2) Drag all the includes to your include folder, same with the libs
3) Drag the dll file inside bin into the build directory of your project

# Building
If you clone this project an run Cmake it *should* just compile, but compilation has always been my weak point so I may not have set it up incorrectly

as for the examples:
1) create a SFML3D folder inside your lib directory, then you have to build the project once first, 
2) then inside the build directory and inside the SFML3D folder that should have created, drag the .dll.a into your lib/SFML3D folder and drag .dll file into your build directory
3) Then in the Cmakelists.txt, near the bottom, change the FALSE's of the if statements to TRUE for each example you want to compile

# Simple Tutorial

You can include the library as so
```cpp
#include <SFML3D/SFML3D.hpp>
```
before doing **anything**, please create a RenderWindow3D as this will setup opengl for 3D.

(Note) RenderWindow3D and RenderTarget3D inherit from their 2D counterparts so they can still be used to draw 2D stuff. They are also initialised in the same way
You will also have to create a bool variable that will be used for the main loop as window.isOpen() will cause some errors when closing the window

```cpp
#include <SFML/Graphics.hpp>
#include <SFML3D/SFML3D.hpp>

int main(){

  sf::RenderWindow3D window(sf::VideoMode(1080, 1080), "Game");

  bool running = true;
  while(running){

     sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed) running = false;
      }

    window.clear();

    //draw stuff

    window.display();

  }

  return 0;

}

## Simple Shapes

The library has simple shapes you can create, they are Cube, Cylinder, Plane and SingleSidePlane

Cubes example
```cpp
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

```
