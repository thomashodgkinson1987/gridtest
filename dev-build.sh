#!/bin/bash
set -e

# Use the project's directory name to create a unique and predictable image tag.
# This avoids conflicts with other projects.
IMAGE_TAG="$(basename "$PWD")-dev:latest"

echo "Building the '$IMAGE_TAG' container image..."

# We no longer need --build-arg for user info.
# The user mapping is handled dynamically at runtime.
podman build \
    -t "$IMAGE_TAG" \
    -f Dockerfile \
    .

echo "Build complete! Image '$IMAGE_TAG' is ready."
