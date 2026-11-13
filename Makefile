# ============================================================================
# RCRE-LEARN: 10-Week C Systems Engineering & Interactive Journey
# ============================================================================

CC ?= clang
CFLAGS ?= -std=c2x -Wall -Wextra -Wpedantic -O2 -Iinclude
SANFLAGS ?= -fsanitize=address,undefined -g -O1

WEEKS = 01 02 03 04 05 06 07 08 09 10
BIN_DIR = bin
BUILD_DIR = build

.PHONY: help prep all clean test san serve sync-blog

prep:
	@chmod +x scripts/prep.sh 2>/dev/null || true
	@bash scripts/prep.sh

all: $(BIN_DIR) $(BUILD_DIR)
	@echo "==> Building all curriculum suites..."
	@$(MAKE) build-all

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

build-all: $(BIN_DIR)
	@$(CC) $(CFLAGS) curriculum/week01_lockers/test.c -o $(BIN_DIR)/test_w01
	@$(CC) $(CFLAGS) curriculum/week02_whiteboard/test.c -o $(BIN_DIR)/test_w02
	@$(CC) $(CFLAGS) curriculum/week03_mosaic/test.c -o $(BIN_DIR)/test_w03
	@$(CC) $(CFLAGS) curriculum/week04_pencils/test.c -o $(BIN_DIR)/test_w04
	@$(CC) $(CFLAGS) curriculum/week05_stencil/test.c -o $(BIN_DIR)/test_w05
	@$(CC) $(CFLAGS) curriculum/week06_simd/test.c -o $(BIN_DIR)/test_w06
	@$(CC) $(CFLAGS) curriculum/week07_stream/test.c -o $(BIN_DIR)/test_w07
	@$(CC) $(CFLAGS) curriculum/week08_dispatcher/test.c -o $(BIN_DIR)/test_w08
	@$(CC) $(CFLAGS) curriculum/week09_intelligence/test.c -o $(BIN_DIR)/test_w09
	@$(CC) $(CFLAGS) curriculum/week10_portal/test.c -o $(BIN_DIR)/test_w10
	@echo "==> All 10 suites compiled cleanly!"

test: build-all
	@echo "============================================================"
	@echo "  RCRE-LEARN: Running 10-Week Verification Battery"
	@echo "============================================================"
	@$(BIN_DIR)/test_w01
	@$(BIN_DIR)/test_w02
	@$(BIN_DIR)/test_w03
	@$(BIN_DIR)/test_w04
	@$(BIN_DIR)/test_w05
	@$(BIN_DIR)/test_w06
	@$(BIN_DIR)/test_w07
	@$(BIN_DIR)/test_w08
	@$(BIN_DIR)/test_w09
	@$(BIN_DIR)/test_w10
	@echo "============================================================"
	@echo "  ALL 10 WEEKS PASSED VERIFICATION WITH ZERO ERRORS!"
	@echo "============================================================"

san: $(BIN_DIR)
	@echo "==> Compiling with AddressSanitizer + UndefinedBehaviorSanitizer..."
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week01_lockers/test.c -o $(BIN_DIR)/test_w01_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week02_whiteboard/test.c -o $(BIN_DIR)/test_w02_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week03_mosaic/test.c -o $(BIN_DIR)/test_w03_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week04_pencils/test.c -o $(BIN_DIR)/test_w04_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week05_stencil/test.c -o $(BIN_DIR)/test_w05_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week06_simd/test.c -o $(BIN_DIR)/test_w06_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week07_stream/test.c -o $(BIN_DIR)/test_w07_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week08_dispatcher/test.c -o $(BIN_DIR)/test_w08_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week09_intelligence/test.c -o $(BIN_DIR)/test_w09_san
	@$(CC) $(CFLAGS) $(SANFLAGS) curriculum/week10_portal/test.c -o $(BIN_DIR)/test_w10_san
	@echo "==> Running Sanitizer checks..."
	@$(BIN_DIR)/test_w01_san
	@$(BIN_DIR)/test_w02_san
	@$(BIN_DIR)/test_w03_san
	@$(BIN_DIR)/test_w04_san
	@$(BIN_DIR)/test_w05_san
	@$(BIN_DIR)/test_w06_san
	@$(BIN_DIR)/test_w07_san
	@$(BIN_DIR)/test_w08_san
	@$(BIN_DIR)/test_w09_san
	@$(BIN_DIR)/test_w10_san
	@echo "==> SANITIZERS CLEAN: 0 leaks, 0 out-of-bounds, 0 undefined behaviors."

serve:
	@echo "==> Serving rcre-learn web app at http://localhost:8000"
	@cd web && python3 -m http.server 8000

sync-blog:
	@echo "==> Syncing rcre-learn web app to Hugo blog static directory..."
	@mkdir -p ../personal-blog/blog/receps_blog/static/rcre-learn
	@cp web/index.html ../personal-blog/blog/receps_blog/static/rcre-learn/index.html
	@echo "==> Synced! Run 'make deploy' in apps/personal-blog to publish to erolrecep.github.io."

clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR)
	@echo "==> Cleaned build artifacts."

help:
	@echo "RCRE-LEARN targets:"
	@echo "  make prep  - Detect OS/Arch/Bitness and prepare build environment"
	@echo "  make all   - Compile all 10 weekly test binaries"
	@echo "  make test  - Run tests for weeks 1 through 10"
	@echo "  make san   - Run tests under Clang ASan + UBSan sanitizers"
	@echo "  make serve - Launch the interactive web app locally (port 8000)"
	@echo "  make clean - Delete binaries"
