![Build Passing](https://img.shields.io/wercker/ci/wercker/docs.svg)<br/>
# RG - Project for courses _Software Team Project 1/Software Engineering 1_ (BI-SP1/BI-SI1 2018)
Dive into the role of a dwarf that faces dangers in depths of dungeon that awaits to be explored.

![RG preview](https://i.imgur.com/MNx1RXu.png)

### Requirements
* sfml
* box2d
* lua (5.3)
* cmake (2.6 or higher)

Package names on ubuntu: libsfml-dev, libbox2d-dev, liblua5.3-dev, cmake

### Installation

1. Go to the &lt;root&gt; directory ( &lt;root&gt; means project root )
2. Run ``./setup.sh``
3. Go to the &lt;root&gt;/build directory
4. Run ``make game`

### How to run project
1. Go to the &lt;root&gt;/build directory
2. Run ``./game``

### Controls
You can move using arrow keys. Pause game with Escape and shoot with space bar. These key bindings can be changed in settings.

### Project architecture

Project uses MVC architecture and is divided into 5 main directories:
* Model         ( Game data and physical simulation (box2D) )
* Controller    ( Communication between Model and View )
* View          ( Game graphics (sfml) and user input )
* Util          ( Classes used across the application ex.: Logger, Observer, Subject... )
* NPC           ( Manages market, trading and non-combat NPC's. Basically part of the Model. )

We use observer pattern for fast communication between Model and View.<br/>
Lua is used for user scripting ( playing sound when is entity damaged ect. ) and default configuration of some game objects ( for example animations )

### Changelog

see [CHANGELOG](CHANGELOG.md)

### Results
Project was graded 50 out of 50 points obtainable.
