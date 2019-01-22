Tanks Game
==========

Tanks is a project for controlling Arduino based game devices and use them in a game. All applications in this project have been written on C++, with some Qt libs and OpenCV libs. This project contains 3 applications:

tanks_client:
=============
This is a GUI application allows to:
* Control remote game device,based on Arduino platform. It handles input from gamepad and send it to the tanks_server;
* Shows game statistic from game server.
* Handles video-camera output from Arduino device.

tanks_game:
=============

This apllications sets the rules of the game for devices and handles the game statistic from different devices.


tanks_server:
=============
* Manages the input information from client;
* Convert all input to signals for different parts of Arduino device;
* Send *game actions* to tanks_game.