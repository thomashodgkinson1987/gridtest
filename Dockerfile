# Use the latest official Fedora image as our base environment.
FROM fedora:latest

# Add metadata to the image to describe its purpose.
LABEL author="Thomas Hodgkinson"
LABEL description="Development environment for the GridTest project."

# Create a generic, non-root user. The tool will take care of the rest.
# The UID/GID of 1000 are just placeholders.
RUN groupadd -g 1000 vscode && \
    useradd -u 1000 -g 1000 -m -s /bin/bash vscode

# Give this user passwordless sudo rights for convenience.
USER root
RUN usermod -aG wheel vscode && \
    echo '%wheel ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers

    
# Install all dependencies, upgrade the system, and clean up in a single layer.
# The --mount cache ensures that re-running this layer is fast, as packages
# are cached on the host and do not need to be re-downloaded.
RUN --mount=type=cache,target=/var/cache/dnf \
    dnf install -y \
    git \
    gcc \
    gcc-c++ \
    mingw64-gcc \
    mingw64-gcc-c++ \
    gdb \
    cmake \
    mesa-libGL-devel \
    libX11-devel \
    libXrandr-devel \
    libXi-devel \
    libXcursor-devel \
    libXfixes-devel \
    alsa-lib-devel \
    libXinerama-devel \
    libXxf86vm-devel \
    vim \
    neovim && \
    dnf upgrade -y && \
    dnf clean all

# Switch back to the generic user as the default.
USER vscode
WORKDIR /workspaces/gridtest
CMD ["/bin/bash"]
