#!/bin/bash
set -e

IMAGE_TAG="$(basename "$PWD")-dev:latest"
WORKSPACE_DIR="/workspaces/gridtest"

if [ "$#" -eq 0 ]; then exit 1; fi

declare -a PODMAN_ARGS

PODMAN_ARGS+=(
    --rm
    --userns=keep-id
    --user vscode # <-- ADDED
    -v "$(pwd):${WORKSPACE_DIR}:z"
    -v "/tmp/.X11-unix:/tmp/.X11-unix:ro"
    -v "${XAUTHORITY}:/home/vscode/.Xauthority:ro,z"
    -e "DISPLAY=${DISPLAY}"
    -e "XAUTHORITY=/home/vscode/.Xauthority"
    --ipc=host
)

SSH_DIR="${HOME}/.ssh"
if [ -d "$SSH_DIR" ]; then
    PODMAN_ARGS+=( -v "${SSH_DIR}:/home/vscode/.ssh:ro,z" )
fi

GITCONFIG_PATH="${HOME}/.gitconfig"
if [ -f "$GITCONFIG_PATH" ]; then
    PODMAN_ARGS+=( -v "${GITCONFIG_PATH}:/home/vscode/.gitconfig:ro,z" )
fi

if [ -n "$SSH_AUTH_SOCK" ]; then
    PODMAN_ARGS+=(
        -v "${SSH_AUTH_SOCK}:${SSH_AUTH_SOCK}"
        -e "SSH_AUTH_SOCK=${SSH_AUTH_SOCK}"
    )
fi

podman run "${PODMAN_ARGS[@]}" "$IMAGE_TAG" "$@"
