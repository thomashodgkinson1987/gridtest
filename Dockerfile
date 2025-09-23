FROM docker.io/library/fedora:42 AS base

LABEL author="Thomas Hodgkinson"
LABEL description="CI/CD environment for the GridTest project."

USER root

RUN groupadd -g 1000 vscode && \
    useradd -u 1000 -g 1000 -m -s /bin/bash vscode

RUN usermod -aG wheel vscode && \
    echo '%wheel ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers

RUN --mount=type=cache,target=/var/cache/dnf \
    dnf install -y \
    git-2.51.0-2.fc42 \
    gcc-15.2.1-1.fc42 \
    gcc-c++-15.2.1-1.fc42 \
    mingw64-gcc-14.2.1-4.fc42 \
    mingw64-gcc-c++-14.2.1-4.fc42 \
    gdb-16.3-1.fc42 \
    cmake-3.31.6-2.fc42 \
    mesa-libGL-devel-25.1.9-1.fc42 \
    libX11-devel-1.8.12-1.fc42 \
    libXrandr-devel-1.5.4-5.fc42 \
    libXi-devel-1.8.2-2.fc42 \
    libXcursor-devel-1.2.3-2.fc42 \
    libXfixes-devel-6.0.1-5.fc42 \
    alsa-lib-devel-1.2.14-3.fc42 \
    libXinerama-devel-1.1.5-8.fc42 \
    libXxf86vm-devel-1.1.6-2.fc42 && \
    dnf clean all

WORKDIR /workspaces/gridtest

USER vscode
CMD ["/bin/bash"]

FROM base AS dev

LABEL author="Thomas Hodgkinson"
LABEL description="Development environment for the GridTest project."

USER root

RUN --mount=type=cache,target=/var/cache/dnf \
    dnf upgrade -y && \
    dnf copr enable -y rivenirvana/lazygit && \
    dnf install -y \
    vim-enhanced \
    neovim \
    micro \
    lazygit && \
    dnf clean all

WORKDIR /workspaces/gridtest

USER vscode
CMD ["/bin/bash"]
