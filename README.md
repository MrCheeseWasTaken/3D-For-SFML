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
If you clone this project an run Cmake it *should* just compile, but compilation has always been my week point so I may not have set it up correctly

as for the examples, create a SFML3D folder inside your lib directory, then you have to build the project once first, then inside the build directory and inside the SFML3D folder that should have created, drag the .dll.a into your lib/SFML3D folder. Then in the Cmakelists.txt, near the bottom, change the FALSE's of the if statements to TRUE for each example you want to compile


