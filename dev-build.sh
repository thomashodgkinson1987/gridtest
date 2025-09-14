#!/bin/bash
set -e

IMAGE_TAG="$(basename "$PWD")-dev:latest"

echo "Building the '$IMAGE_TAG' container image..."

podman build \
    -t "$IMAGE_TAG" \
    -f Dockerfile \
    .

echo "Build complete! Image '$IMAGE_TAG' is ready."
