#!/usr/bin/env bash
set -euo pipefail
export DEBIAN_FRONTEND=noninteractive

# -------------------------------------------------------------
# APT setup
# -------------------------------------------------------------
apt-get update -y -qq
apt-get install -y -qq --no-install-recommends \
    software-properties-common \
    gnupg2 \
    ca-certificates

# Enable the "universe" repository (required for several dev packages)
add-apt-repository -y universe
apt-get update -y -qq

# -------------------------------------------------------------
# Core build tools (QTalk build environment)
# -------------------------------------------------------------
apt-get install -y -qq --no-install-recommends \
    appstream \
    binutils \
    build-essential \
    ccache \
    cmake \
    cppcheck \
    file \
    gdb \
    git \
    libfuse2 \
    fuse3 \
    libtool \
    locales \
    mold \
    ninja-build \
    patchelf \
    pipx \
    pkgconf \
    python3 \
    python3-pip \
    rsync \
    wget \
    zsync

# Install recent versions of CMake and Ninja via pipx
pipx ensurepath
pipx install cmake
pipx install ninja

# -------------------------------------------------------------
# Qt6 compile/runtime dependencies (for QTalk – Qt Quick/UI)
# Reference: https://doc.qt.io/qt-6/linux-requirements.html
# -------------------------------------------------------------
apt-get install -y -qq --no-install-recommends \
    libatspi2.0-dev \
    libfontconfig1-dev \
    libfreetype-dev \
    libgtk-3-dev \
    libsm-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxcb-cursor-dev \
    libxcb-glx0-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-present-dev \
    libxcb-randr0-dev \
    libxcb-render-util0-dev \
    libxcb-render0-dev \
    libxcb-shape0-dev \
    libxcb-shm0-dev \
    libxcb-sync-dev \
    libxcb-util-dev \
    libxcb-xfixes0-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libxcb1-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev \
    libxrender-dev \
    libunwind-dev

# -------------------------------------------------------------
# Misc (graphics / audio related, useful for desktop Qt apps)
# -------------------------------------------------------------
apt-get install -y -qq --no-install-recommends \
    libvulkan-dev \
    libpipewire-0.3-dev

# -------------------------------------------------------------
# Clean-up
# -------------------------------------------------------------
apt-get clean
rm -rf /var/lib/apt/lists/*
