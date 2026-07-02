FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    pkg-config \
    libssl-dev \
    libhiredis-dev \
    wget \
    curl \
    zip \
    unzip \
    tar

WORKDIR /opt

RUN git clone https://github.com/microsoft/vcpkg.git

WORKDIR /opt/vcpkg

RUN ./bootstrap-vcpkg.sh

WORKDIR /app

COPY . .

RUN /opt/vcpkg/vcpkg install

RUN cmake \
    -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake

RUN cmake --build build -j

EXPOSE 8080

CMD ["./build/DistributedRateLimiter"]