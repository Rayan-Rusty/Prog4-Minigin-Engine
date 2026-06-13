# Minigin Game Engine - DigDug Project 

## OverView


This project is built on top of a custom C++ game engine **Minigin**, used as part of my programming coursework.
The engine is designed with a component-based architecture (ecs-like system) and is used to run a remake of ***DigDug***

The game features tile-based movement, enemy AI behaviors , custom rendering pipeline and animations.



## Engine Architecture

### Component - based Design

The engine uses a ***Component over inheritance** approach:

- GameObjects behave as containers
- Behavior is implemented through `Component subclasses`
- Components communicate through events and observers as much as possible

This allows flexible gameplay systems without deep inheritance chains.


## Finite State Machine System 

Enemies and player behaviors are implemented using a **Finite state machine system** for example:

- Pookas have multiple states that go through the `PookaBehaviour`:
  - Normal
  - Ghost
  - Inflated
  - Dead

  
each state has its own Enter, update & exit.


### Observer/Event System

An event-driven system is used for gameplay interactions:

- Enemy hit detection
- Pump interactions
- Score updates

this causes less hard coupling between components or objects

### Rendering System:

The `SpriteComponent` can store little animations into structs that are then sent to the `rendererComponent`.
The rendering uses layers so that when we add objects to the scene we can sort it after wards.


#### Tilemap System (Aseprite Pipeline)

using bitmaps or hardcoded values into a txt file seemed rather not efficient to use with a game like DigDug,
so I used an indexed image and take the values out of it. that way I can place enemies, players, rocks or tiles wherever necessary.
This also makes it easy to layer it, find where players are and how much an enemy is worth.

### Input system
SUpports:

- Keyboard Input
- Gamepad Input
- Command-based input mapping


## Repository 

- https://github.com/Rayan-Rusty/Prog4-Minigin-Engine
