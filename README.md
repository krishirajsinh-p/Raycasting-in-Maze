# Raycasting in Maze

A 3D maze exploration game built using raycasting techniques in C++ with SDL2. This project demonstrates the classic raycasting algorithm similar to early first-person games like Wolfenstein 3D.

## Features

- **Procedurally Generated Mazes**: Each maze is randomly generated for a unique experience
- **3D Raycasting Rendering**: Converts 2D maze data into a 3D first-person perspective
- **Smooth Movement**: Fluid player movement and rotation controls
- **Real-time Rendering**: Efficient SDL2-based graphics rendering
- **Configurable Settings**: Easy-to-modify game parameters (FOV, speed, screen resolution)

## Prerequisites

The project automatically installs dependencies, but you'll need:

- **Operating System**: Linux (tested on Debian/Ubuntu-based distributions)
- **Git**: For project management
- **Sudo privileges**: For installing packages

### Dependencies (auto-installed)

- `build-essential`: C++ compiler and build tools
- `libsdl2-dev`: SDL2 development libraries
- `cmake`: Build system generator

## Building the Project

The project includes automated build scripts for easy setup.

### Quick Build

```bash
./build.sh
```

This script will:
1. Check for required packages
2. Install any missing dependencies
3. Create a build directory
4. Compile the project using CMake and Make
5. Generate the executable in `build/Raycasting-in-Maze`

## Running the Game

After building, run the game with:

```bash
./run.sh
```

The `run.sh` script will:
- Check if the executable exists
- Build the project if needed
- Launch the game

### Development Mode

To force a rebuild before running, edit `run.sh` and set:
```bash
DEV_MODE=1
```

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit game |

## Project Structure

```
Raycasting-in-Maze/
├── include/
│   ├── Config.hpp      # Game configuration constants
│   ├── Game.hpp        # Main game loop and logic
│   ├── Maze.hpp        # Maze generation and management
│   ├── Player.hpp      # Player movement and state
│   └── Renderer.hpp    # Raycasting rendering engine
├── src/
│   ├── main.cpp        # Entry point
│   ├── Game.cpp        # Game implementation
│   ├── Maze.cpp        # Maze generation algorithm
│   ├── Player.cpp      # Player controller
│   └── Renderer.cpp    # Rendering implementation
├── build.sh            # Automated build script
├── run.sh              # Automated run script
├── clean.sh            # Cleanup script
├── packages.txt        # Required system packages
└── CMakeLists.txt      # CMake configuration
```

## How It Works

### Raycasting Algorithm

The project implements a raycasting engine that:
1. Casts rays from the player's position through each screen column
2. Calculates ray-wall intersections using DDA (Digital Differential Analysis)
3. Computes wall distances to determine wall heights
4. Renders vertical lines with appropriate heights to create 3D perspective

### Maze Generation

Uses a randomized algorithm to generate perfect mazes (mazes with exactly one path between any two points).

## Cleaning Up

To remove build artifacts and uninstall dependencies:

```bash
./clean.sh
```

This will:
- Remove the `build/` directory
- Uninstall packages listed in `packages.txt`

**Note**: Use with caution if you have other projects using the same dependencies.

## Configuration

Edit [include/Config.hpp](include/Config.hpp) to customize:

- **Maze Size**: `MAZE_WIDTH` and `MAZE_HEIGHT` (default: 20x20)
- **Movement Speed**: `MOVE_SPEED` (default: 0.05)
- **Rotation Speed**: `ROTATE_SPEED` (default: 0.05)
- **Field of View**: `FOV` (default: 0.66)
- **Screen Resolution**: `SCREEN_WIDTH` and `SCREEN_HEIGHT` (default: 1920x1080)
- **Key Bindings**: Customize control keys

After modifying configuration, rebuild the project:
```bash
./build.sh
```

## Building Manually

If you prefer manual building:

```bash
# Install dependencies
sudo apt update
sudo apt install build-essential libsdl2-dev cmake

# Create build directory
mkdir -p build && cd build

# Configure with CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compile
make -j$(nproc)

# Run
./Raycasting-in-Maze
```

## Troubleshooting

### Build Fails
- Ensure all dependencies are installed: `sudo apt install build-essential libsdl2-dev cmake`
- Check that you're in the project root directory
- Try cleaning and rebuilding: `./clean.sh && ./build.sh`

### Black Screen
- Check that SDL2 is properly initialized
- Verify screen resolution settings in `Config.hpp` match your display

### Performance Issues
- Reduce `SCREEN_WIDTH` and `SCREEN_HEIGHT` in `Config.hpp`
- Ensure you're building in Release mode (default in `build.sh`)
