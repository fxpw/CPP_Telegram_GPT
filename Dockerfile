# Use a base image with the desired Linux distribution and version
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages (CMake, g++, git)
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /vcpkg
RUN /vcpkg/bootstrap-vcpkg.sh
ENV PATH="/vcpkg:${PATH}"

# Copy the source code to the container
WORKDIR /app
COPY . /app

# Install vcpkg dependencies for your project
RUN mkdir -p build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake .. && \
    cmake --build . --config Release -j4

# Set the entry point for running your application
CMD ["./build/cpp_telegram_gpt"]
