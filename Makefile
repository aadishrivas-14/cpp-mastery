.PHONY: help setup build test clean format lint check coverage docker-up docker-down docker-shell

help:
	@echo "C++ Mastery Development Commands"
	@echo "================================="
	@echo "setup          - Setup development environment"
	@echo "build          - Build all projects"
	@echo "test           - Run all tests"
	@echo "clean          - Clean build artifacts"
	@echo "format         - Format all code"
	@echo "lint           - Run linters"
	@echo "check          - Run all quality checks"
	@echo "coverage       - Generate coverage report"
	@echo "docker-up      - Start Docker services"
	@echo "docker-down    - Stop Docker services"
	@echo "docker-shell   - Enter development container"

setup:
	@bash setup-dev-env.sh

build:
	@docker-compose run --rm cpp-dev bash -c "cd /workspace && \
		for week in week-{1,2,3,4}; do \
			if [ -f $$week/CMakeLists.txt ]; then \
				cd $$week && mkdir -p build && cd build && \
				cmake .. -GNinja && ninja && cd ../..; \
			fi; \
		done"

test:
	@docker-compose run --rm test-runner

clean:
	@find . -type d -name build -exec rm -rf {} + 2>/dev/null || true
	@rm -rf coverage-html 2>/dev/null || true

format:
	@echo "Formatting C++ files..."
	@find week-* -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | xargs clang-format -i
	@echo "Done!"

lint:
	@echo "Running clang-tidy..."
	@find week-* -name "*.cpp" | xargs -I {} clang-tidy {} -- -std=c++20 -Iinclude
	@echo "Running cppcheck..."
	@cppcheck --project=compile_commands.json 2>&1 | grep -v "Checking" || true

check: format lint
	@echo "Running pre-commit hooks..."
	@pre-commit run --all-files || true

coverage:
	@docker-compose run --rm coverage

docker-up:
	@docker-compose up -d

docker-down:
	@docker-compose down

docker-shell:
	@docker-compose run --rm cpp-dev
