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

BUILD_DIR="$PROJECT_ROOT/build"
PACKAGE_FILE="$PROJECT_ROOT/packages.txt"

print_msg "Starting the cleaning process..."
print_msg "removing build directory and installed packages..."

echo ""

if [ -d "$BUILD_DIR" ]; then
    print_msg "Cleaning build directory $BUILD_DIR ..."
    rm -rf "$BUILD_DIR"
    if [ $? -eq 0 ]; then
        print_success "Build directory cleaned successfully."
    else
        print_error "Failed to clean build directory. Do it manually."
    fi
else
    print_warning "No build directory found at $BUILD_DIR, Nothing to clean."
fi

echo ""

PACKAGES=()
while IFS= read -r package; do
    if ! dpkg -s "$package" &> /dev/null; then
        print_warning "Package $package is not installed. Skipping."
    else
        PACKAGES+=("$package")
        print_msg "Package $package will be removed."
    fi
done < "$PACKAGE_FILE"

if [ ${#PACKAGES[@]} -ne 0 ]; then
    print_msg "Removing packages..."
    sudo apt remove -y "${PACKAGES[@]}" -qq &> /dev/null
    if [ $? -eq 0 ]; then
        print_success "Packages removed successfully."
    else
        print_error "Failed to remove some packages. Do it manually."
    fi
else
    print_warning "No packages to remove."
fi

echo ""

print_success "Cleaning process completed."
