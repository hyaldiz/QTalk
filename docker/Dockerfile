FROM debian:trixie

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    build-essential \
    gcc g++ \
    cmake \
    git \
    pkg-config \
    qt6-base-dev \
    qt6-declarative-dev \
    libqt6core6 \
    libqt6gui6 \
    libqt6widgets6 \
    libqt6qml6 \
    libqt6qmlmodels6 \
    libqt6quick6 \
    libqt6quickcontrols2-6 \
    libqt6quickwidgets6 \
    libqt6network6 \
    libqt6dbus6 \
    libqt6test6 \
    libgl1 \
    libglx0 \
    libopengl0 \
    libegl1 \
    libx11-6 \
    libxcb1 \
    libxkbcommon0 \
    libfontconfig1 \
    libfreetype6 \
    mesa-utils \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m builder
USER builder
WORKDIR /home/builder/project
CMD ["/bin/bash"]


