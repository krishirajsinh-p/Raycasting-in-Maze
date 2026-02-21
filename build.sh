#!/bin/bash

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
PACKAGE_FILE="$PROJECT_ROOT/packages.txt"
BUILD_DIR="$PROJECT_ROOT/build"
EXECUTABLE="$BUILD_DIR/Raycasting-in-Maze"

print_msg "Starting build process..."
echo ""

if [ ! -f "$PACKAGE_FILE" ]; then
    print_error "Package file $PACKAGE_FILE not found!"
    exit 1
fi

print_msg "Checking required packages..."

MISSING_PACKAGES=()

while IFS= read -r package; do
    if ! dpkg -s "$package" &> /dev/null; then
        print_warning "Package $package is not installed."
        MISSING_PACKAGES+=("$package")
    else
        print_success "Package $package is already installed. Skipping."
    fi
done < "$PACKAGE_FILE"

if [ ${#MISSING_PACKAGES[@]} -ne 0 ]; then
    print_msg "Installing missing packages..."
    sudo apt update -qq &> /dev/null
    sudo apt install -y "${MISSING_PACKAGES[@]}" -qq &> /dev/null
    print_success "Dependencies installed."
else
    print_success "All dependencies are installed."
fi

echo ""

print_msg "Building in $BUILD_DIR now..."

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=Release .. &> /dev/null
make -j$(nproc) &> /dev/null

if [ ! -f "$EXECUTABLE" ]; then
    print_error "Build failed."
    exit 1
else
    print_success "Build succeeded."
fi
