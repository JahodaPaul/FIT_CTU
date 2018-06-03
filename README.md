![TeamCity CodeBetter](https://img.shields.io/teamcity/codebetter/bt428.svg)<br/>
# RG - Project for courses _Software Team Project 1/Software Engineering 1_ (BI-SP1/BI-SI1 2018)
In this game you dive into the role of the dwarf that faces dangers in depths of dungeon that awaits to be explored.

## Compiling from source

### Requirements
* sfml
* box2d
* lua (5.3)
* cmake (2.6 or higher)

Package names on ubuntu: libsfml-dev, libbox2d-dev, liblua5.3-dev, cmake

1. Go to the &lt;root&gt; directory ( &lt;root&gt; means project root )
2. Run ``./setup.sh``
3. Go to the &lt;root&gt;/build directory
4. Run ``make game``
3. Run ``./game``

## Instalation

You can use debian package witch will comes with all necessary files and dependencies.

## Project architecture

Project uses MVC architecture and is divided int 4 main folders:
* Model         ( game data and physical simulation (box2D) )
* Controller    ( communication between Model and View )
* View          ( game graphics (sfml) and user input 
* Util          ( There stored classes used across all project ex.: Logger, Observer, Subject... )
* NPC           ( Basically part of Model, NPC manages market and trading data )

We use observer pattern for fast communication between model and View.
Lua is used for user scripting ( playing sound on entity hurt... ) and default configuration of some game objects ( for example animations )

## Changelog

see [CHANGELOG](CHANGELOG.md)

## Results
This project was awarded X out of 50 points.
