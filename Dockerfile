# C++ Mastery TDD Development Environment
FROM ubuntu:22.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Kolkata

# Install system dependencies
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    cmake \
    ninja-build \
    pkg-config \
    # Compilers
    gcc-12 \
    g++-12 \
    clang-15 \
    clang-tidy-15 \
    # Testing frameworks
    libgtest-dev \
    libgmock-dev \
    # Code coverage
    gcov \
    lcov \
    # Static analysis
    cppcheck \
    valgrind \
    # Databases
    sqlite3 \
    libsqlite3-dev \
    postgresql-client \
    libpq-dev \
    # Networking
    libcurl4-openssl-dev \
    libssl-dev \
    # JSON processing
    nlohmann-json3-dev \
    # Performance tools
    libbenchmark-dev \
    # Development tools
    git \
    vim \
    nano \
    htop \
    tree \
    curl \
    wget \
    # Python for scripts
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

# Set up modern C++ compiler as default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-15 100

# Install vcpkg for package management
RUN git clone https://github.com/Microsoft/vcpkg.git /opt/vcpkg \
    && /opt/vcpkg/bootstrap-vcpkg.sh \
    && ln -s /opt/vcpkg/vcpkg /usr/local/bin/vcpkg

# Install Catch2 (latest version)
RUN cd /tmp \
    && git clone https://github.com/catchorg/Catch2.git \
    && cd Catch2 \
    && cmake -Bbuild -H. -DBUILD_TESTING=OFF \
    && cmake --build build/ --target install

# Install Google Benchmark
RUN cd /tmp \
    && git clone https://github.com/google/benchmark.git \
    && cd benchmark \
    && cmake -E make_directory "build" \
    && cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../ \
    && cmake --build "build" --config Release --target install

# Create development user
RUN useradd -m -s /bin/bash developer \
    && usermod -aG sudo developer \
    && echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Set up workspace
WORKDIR /workspace
RUN chown developer:developer /workspace

# Switch to developer user
USER developer

# Set up shell environment
RUN echo 'export PATH="/opt/vcpkg:$PATH"' >> ~/.bashrc \
    && echo 'export VCPKG_ROOT="/opt/vcpkg"' >> ~/.bashrc \
    && echo 'alias ll="ls -la"' >> ~/.bashrc \
    && echo 'alias la="ls -A"' >> ~/.bashrc \
    && echo 'alias l="ls -CF"' >> ~/.bashrc

# Install Python packages for development
RUN pip3 install --user \
    conan \
    pre-commit \
    cppcheck-codequality

# Expose common ports
EXPOSE 8080 5432 3306

# Set default command
CMD ["/bin/bash"]
