#!/usr/bin/env bash

# Qt SDK setup script

set -euo pipefail

QT_VERSION="${QT_VERSION:-6.8.0}"
QT_PATH="${QT_PATH:-/opt/Qt}"
QT_HOST="${QT_HOST:-linux}"
QT_TARGET="${QT_TARGET:-desktop}"
QT_ARCH="${QT_ARCH:-linux_gcc_64}"
QT_ARCH_DIR="${QT_ARCH_DIR:-gcc_64}"
QT_ROOT_DIR="${QT_ROOT_DIR:-${QT_PATH}/${QT_VERSION}/${QT_ARCH_DIR}}"

QT_MODULES="${QT_MODULES:-qtdeclarative qtquickcontrols2 qtshadertools qtimageformats qt5compat qtmultimedia}"

echo "QT_VERSION      = ${QT_VERSION}"
echo "QT_PATH         = ${QT_PATH}"
echo "QT_HOST         = ${QT_HOST}"
echo "QT_TARGET       = ${QT_TARGET}"
echo "QT_ARCH         = ${QT_ARCH}"
echo "QT_ARCH_DIR     = ${QT_ARCH_DIR}"
echo "QT_ROOT_DIR     = ${QT_ROOT_DIR}"
echo "QT_MODULES      = ${QT_MODULES}"

# -------------------------------------------------------------
# Install Python + pipx (for aqtinstall, cmake, ninja)
# -------------------------------------------------------------
apt-get update -y --quiet
apt-get install -y --quiet --no-install-recommends \
    python3 \
    python3-pip \
    pipx

# Make sure pipx bin path is available
pipx ensurepath
export PATH="$(python3 -m site --user-base)/bin:${PATH}"

# Install aqtinstall + build tools via pipx
pipx install aqtinstall
pipx install cmake
pipx install ninja

# -------------------------------------------------------------
# Install Qt using aqtinstall
# -------------------------------------------------------------
aqt install-qt "${QT_HOST}" "${QT_TARGET}" "${QT_VERSION}" "${QT_ARCH}" \
    -O "${QT_PATH}" \
    -m ${QT_MODULES}

# Resolve QT_ROOT_DIR to an absolute path
QT_ROOT_DIR="$(readlink -e "${QT_ROOT_DIR}")"
export QT_ROOT_DIR

# -------------------------------------------------------------
# Environment for QTalk build
# -------------------------------------------------------------
export PATH="${QT_ROOT_DIR}/bin:${PATH}"
export PKG_CONFIG_PATH="${QT_ROOT_DIR}/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
export LD_LIBRARY_PATH="${QT_ROOT_DIR}/lib:${LD_LIBRARY_PATH:-}"
export QT_PLUGIN_PATH="$(readlink -e "${QT_ROOT_DIR}/plugins")"
export QML2_IMPORT_PATH="$(readlink -e "${QT_ROOT_DIR}/qml")"
export CMAKE_PREFIX_PATH="${QT_ROOT_DIR}:${CMAKE_PREFIX_PATH:-}"

echo "QT_ROOT_DIR      = ${QT_ROOT_DIR}"
echo "PATH             = ${PATH}"
echo "PKG_CONFIG_PATH  = ${PKG_CONFIG_PATH}"
echo "LD_LIBRARY_PATH  = ${LD_LIBRARY_PATH}"
echo "QT_PLUGIN_PATH   = ${QT_PLUGIN_PATH}"
echo "QML2_IMPORT_PATH = ${QML2_IMPORT_PATH}"
echo "CMAKE_PREFIX_PATH= ${CMAKE_PREFIX_PATH}"
