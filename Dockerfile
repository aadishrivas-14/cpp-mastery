# C++ Mastery TDD Development Environment
FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Kolkata

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    gcc-12 \
    g++-12 \
    clang-15 \
    clang-tidy-15 \
    clang-format-15 \
    libgtest-dev \
    libgmock-dev \
    gcov \
    lcov \
    cppcheck \
    valgrind \
    sqlite3 \
    libsqlite3-dev \
    postgresql-client \
    libpq-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    nlohmann-json3-dev \
    git \
    vim \
    curl \
    wget \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Set up modern C++ compiler as default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100 \
    && update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-15 100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-15 100

# Build and install Google Test
RUN cd /usr/src/gtest \
    && cmake . \
    && make \
    && cp lib/*.a /usr/lib \
    && cd /usr/src/gmock \
    && cmake . \
    && make \
    && cp lib/*.a /usr/lib

# Set up workspace
WORKDIR /workspace

# Set up shell environment
RUN echo 'alias ll="ls -la"' >> /etc/bash.bashrc

# Install Python packages for development
RUN pip3 install pre-commit

# Expose common ports
EXPOSE 8080 5432 6379

# Set default command
CMD ["/bin/bash"]
