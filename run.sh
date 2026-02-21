#!/bin/bash

DEV_MODE=0

RED="\033[1;31m"
GREEN="\033[1;32m"
BLUE="\033[1;34m"
YELLOW="\033[1;33m"
NC="\033[0m"

print_error() {
    echo -e "${RED}✖ $1${NC}"
}

print_success() {
    echo -e "${GREEN}✔ $1${NC}"
}

print_msg() {
    echo -e "${BLUE}$1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

PROJECT_ROOT=$(git rev-parse --show-toplevel)
BUILD_DIR="$PROJECT_ROOT/build"
BUILD_SCRIPT="$PROJECT_ROOT/build.sh"
EXECUTABLE="$BUILD_DIR/Raycasting-in-Maze"

if [ "$DEV_MODE" == "1" ]; then
    print_warning "Development mode enabled. Rebuilding project..."
    echo ""
    rm -rf "$BUILD_DIR"
fi

if [ ! -f "$EXECUTABLE" ]; then
    print_warning "Executable not found. Building project first..."
    echo ""
    "$BUILD_SCRIPT"
    echo ""
fi

print_msg "Running $EXECUTABLE..."
"$EXECUTABLE"
