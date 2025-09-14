#!/bin/bash
set -e

IMAGE_TAG="$(basename "$PWD")-dev:latest"
WORKSPACE_DIR="/workspaces/gridtest"

echo "Starting an interactive shell as user 'vscode' in the '$IMAGE_TAG' container..."

declare -a PODMAN_ARGS

PODMAN_ARGS+=(
    -it --rm
    --userns=keep-id
    --user vscode
    -v "$(pwd):${WORKSPACE_DIR}:z"
    -v "/tmp/.X11-unix:/tmp/.X11-unix:ro"
    -v "${XAUTHORITY}:/home/vscode/.Xauthority:ro,z"
    -e "DISPLAY=${DISPLAY}"
    -e "XAUTHORITY=/home/vscode/.Xauthority"
    --ipc=host
)

SSH_DIR="${HOME}/.ssh"
if [ -d "$SSH_DIR" ]; then
    echo "Host .ssh directory found. Forwarding..."
    PODMAN_ARGS+=( -v "${SSH_DIR}:/home/vscode/.ssh:ro,z" )
fi

GITCONFIG_PATH="${HOME}/.gitconfig"
if [ -f "$GITCONFIG_PATH" ]; then
    echo "Host .gitconfig found. Forwarding..."
    PODMAN_ARGS+=( -v "${GITCONFIG_PATH}:/home/vscode/.gitconfig:ro,z" )
else
    echo "Warning: Host .gitconfig not found. You may need to configure git inside the container."
fi

if [ -n "$SSH_AUTH_SOCK" ]; then
    echo "SSH agent socket found. Forwarding..."
    PODMAN_ARGS+=(
        -v "${SSH_AUTH_SOCK}:${SSH_AUTH_SOCK}"
        -e "SSH_AUTH_SOCK=${SSH_AUTH_SOCK}"
    )
else
    echo "Warning: SSH_AUTH_SOCK is not set. SSH agent forwarding will be disabled."
fi

podman run "${PODMAN_ARGS[@]}" "$IMAGE_TAG" /bin/bash
