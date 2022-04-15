#Work in progress on this branch

This branch aim to provide an other way to compile the project using cmake
For now it works on windows only with mingw, do not forget to set the Qt5_DIR 
for exemple here is why i type: cmake .. -G "MinGW Makefiles" -Qt5_DIR="C:\Qt\5.15.2\mingw81_32\lib\cmake\Qt5"


# BezierCurveAndPatch

This is a small program to visualise bezier curves, and bezier patches written in C++ using OpenGL and QT5.
It provide a small GUI to allow the user to interact with the scenes and changes some visual effects. 

## How to compile it?

For now the project is using Visual Studio which mean that if you want to compile it, you should also have visual studio installed on your computer alongside
with his QT extention.

## dependencies

This project use GLM (include within the project) and QT5.

## How does it works?

You can use your mouse to rotate around the scene.

You can also zoom in and out with the scrolling button.

All the other interactions can be done directly by using the GUI.

# some illustrations!
![](https://github.com/AntoineLafon/BezierCurveAndPatch/blob/main/Images/BezierCurve1.png)
![](https://github.com/AntoineLafon/BezierCurveAndPatch/blob/main/Images/BezierCurve2.png)
![](https://github.com/AntoineLafon/BezierCurveAndPatch/blob/main/Images/BezierPatch1.png)
![](https://github.com/AntoineLafon/BezierCurveAndPatch/blob/main/Images/BezierPatch2.png)
![](https://github.com/AntoineLafon/BezierCurveAndPatch/blob/main/Images/animation.gif)
