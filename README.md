# CryptsEdge

A 2D dark fantasy side-scroller built from scratch in C++ and SFML.

## Tech Stack
- C++20
- SFML 3.1.0
- MinGW/GCC 15.2.0
- Windows / VS Code

## Build
```bash
g++ -std=c++20 main.cpp src/entities/Player/Player.cpp src/core/Room/Room.cpp src/environment/Torch/Torch.cpp src/entities/Enemy/Enemy.cpp src/entities/Enemy/Slime.cpp -IC:/SFML-3.1.0/include -LC:/SFML-3.1.0/lib -lsfml-graphics -lsfml-window -lsfml-system -o rooster.exe
```

## What's Implemented
- Player movement, jumping, and dual melee attacks (J/K)
- Full animation state machine — Idle, Run, Attack, Jump, Fall, Hurt, Dead
- Invincibility frames after taking damage
- Slime enemy with chase AI and 30-frame animation
- Hitbox-based combat — player attack hitbox, enemy body hitbox
- Per-hit stun system preventing multi-hit in a single swing
- Torch environment animations
- Room tilemap rendering

## Key Problems Solved
- **White rectangle bug** — SFML sprites hold a texture reference that breaks on vector resize. Fixed using `std::unique_ptr` to keep objects stable on the heap.
- **Animation state stomping** — `handleInput()` was overriding states like Hurt every frame. Fixed by guarding state changes with condition checks.
- **Multi-hit per swing** — attack hitbox overlap fired every frame while attacking. Fixed using stun state as a damage gate.
- **Sprite flip offset** — negative x scale flips around origin causing visual jump. Fixed by setting origin to sprite center and offsetting position when facing left.

## Screenshots

### Idle Position

<img width="1917" height="1077" alt="Gameplay01" src="https://github.com/user-attachments/assets/846988b3-1e59-49e1-aa50-0fabd097d994" />

### Player attacking enemy

<img width="1456" height="818" alt="Gameplay02" src="https://github.com/user-attachments/assets/60d9a5e2-bbfb-4e58-a197-f2d3ff885a93" />

## Planned
- 10 rooms with progressive enemy difficulty
- Skeleton and NightBorne enemies
- Minotaur and Hooded Knight mini-bosses
- Blue Wizard final boss with 2 phases
- Room transition system
