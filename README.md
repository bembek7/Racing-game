# Racing Game Overview

This is a simple racing game developed with Unreal Engine 5.

[![Alt text](https://img.youtube.com/vi/NMupr8zrmLA/0.jpg)](https://youtu.be/NMupr8zrmLA)

## Game Modes

1. **Qualifications**
   - The player drives one lap as fast as possible.

2. **Race**
   - Similar to qualifications, but the player chooses the number of laps to race. Future development will allow this mode to be played with AI and/or other players.

3. **Survival**
   - The player tries to drive as far as possible within a limited time. Each checkpoint adds a certain amount of time.

## Features

- **Checkpoints System**
  - The player must go through all the checkpoints for the lap to count.

- **Three Different Player Cameras**
  - Players can switch between three different camera views.

- **Destruction System**
  - Collisions damage the car's livery, and destroyed parts fall off the car.

- **Changing Car Look**
  - Players can choose from a few different textures for their car. However, the four provided textures are not properly mapped, possibly due to incorrect placement.

- **Vehicles Starting Positions Placement**
  - Vehicles start at randomized positions from a set of possible starting places.

- **Input Options**
  - The car can be controlled using a keyboard or a controller.

## Possible Further Development

- Add AI and online/offline multiplayer.
- Make more parts destructible.
- Make destruction affect gameplay, not just be visual.
- Implement a pause menu.
- Add more race parameters.
- Allow the player some control over the camera, and add scene capture to wing mirrors.

I think most of these changes, thanks to how the code is organized and the ease of adding and widening functionalities, should be fairly easy to implement. They would already be in place if I had more time.
