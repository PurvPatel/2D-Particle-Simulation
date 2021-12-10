# Welcome to Particle Simulation

## Usage
- Run 'make' on linux terminal or a mingw64 (get msys2) terminal if on windows.

## Menu

- Adding a particle:
Press 'a' and a particle will be added at the cursor location, make sure to place the cursor inside the window.

- Deleting a particle:
Press 'd' and the particle closest to your cursor position will be deleted.

- Reset simulation:
Press 'r' to reset the entire simulation.

- Pause/Play simulation:
Press space to pause/play the simulation.

- Generate an attractive force:
Press/hold the left mouse button to generate an attractive force around the cursor position.

- Generate a repelling force:
Press/hold the right mouse button to generate a repelling force around the cursor position.

- Increase/Decrease the attracting/repelling range:
Use '+' to increase, or '-' to decrease the range of the forces.

- Increase/Decrease the speeds of particles:
Use 'UP_ARROW_KEY' to increase, or 'DOWN_ARROW_KEY' to decrease the speeds of particles.

- Simulate Gravity:
Press 'g' to toggle gravity on and off.


## Extra Features

- Improved physics: Particles have acceleration and velocity to provide more realistic movements when acted upon by forces.
- Bounded Particles: Particles will bounce off of the window borders instead of going off of them.
- Gravity Mode: Gravity can be toggled on and off.

## Helpful Tips and Notes
- Attraction and repulsion are forces so you will be able to see particles orbit around attracting forces and be bounced away from repelling forces.
- Since these are forces, their affects on particle speeds will be present a bit after the forces fade away.
- There is a artifical decay programmed into the particles to stimulate air friction to eventually slow down and stop the particles.
- You can still interact through attracting and repelling forces even when gravity is enabled.
- Particles are bounded by the window and will bounce off the edges to provide a better simulation.

## Author
- Purv Patel
