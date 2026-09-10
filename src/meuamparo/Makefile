# Build do core e dos testes de host. Não depende do ESP-IDF: roda em qualquer Mac,
# Windows ou Linux com um compilador C11. É essa independência que permite medir a
# taxa de detecção de queda contra centenas de traces em segundos.

CC ?= cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Icore/include -Itest -O2 -g
LDLIBS = -lm

BUILD = build
FIRMWARE_DIR = firmware
IDF_VERSION ?= v5.5.5
IDF_DIR ?= $(HOME)/esp/esp-idf
WOKWI_DIR = simulator/wokwi
WOKWI_VERSION = 0.26.1
CORE_SRC = $(wildcard core/src/*.c)
TEST_SRC = $(wildcard test/test_*.c)
TEST_BIN = $(patsubst test/%.c,$(BUILD)/%,$(TEST_SRC))

.PHONY: help setup test firmware sim clean

# O help se monta sozinho a partir dos comentários "##" nos alvos: alvo novo sem
# descrição não aparece na lista, e descrição nenhuma fica desatualizada em silêncio.
help: ## Lista os alvos disponíveis
	@grep -E '^[a-zA-Z_-]+:.*?## ' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "  %-10s %s\n", $$1, $$2}'

# Um binário por arquivo de teste: cada teste tem seu próprio main e falha isolado.
test: $(TEST_BIN) ## Compila e roda os testes de host do core
	@for t in $(TEST_BIN); do echo "== $$t"; ./$$t || exit 1; done
	@echo "ok: todos os testes passaram"

$(BUILD)/%: test/%.c $(CORE_SRC) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< $(CORE_SRC) $(LDLIBS)

$(BUILD):
	@mkdir -p $(BUILD)

# Instala o que o firmware e o simulador precisam. Cada etapa checa antes de baixar,
# então rodar de novo é barato: serve para conferir a máquina do laboratório sem
# arriscar refazer um download de vários GB.
setup: ## Instala ESP-IDF e wokwi-cli, pulando o que já existe
	@if [ -d "$(IDF_DIR)/.git" ]; then \
		echo "ok: ESP-IDF já está em $(IDF_DIR)"; \
	else \
		echo ">> clonando ESP-IDF $(IDF_VERSION) em $(IDF_DIR) (alguns GB)"; \
		mkdir -p "$(dir $(IDF_DIR))"; \
		git clone -b $(IDF_VERSION) --depth 1 --recursive --shallow-submodules \
			https://github.com/espressif/esp-idf.git "$(IDF_DIR)"; \
	fi
	@if [ -d "$$HOME/.espressif/tools/xtensa-esp-elf" ] && \
	    [ -d "$$HOME/.espressif/tools/cmake" ] && \
	    [ -d "$$HOME/.espressif/tools/ninja" ]; then \
		echo "ok: toolchain do esp32s3 já instalada em ~/.espressif"; \
	else \
		echo ">> instalando toolchain do esp32s3 em ~/.espressif"; \
		"$(IDF_DIR)/install.sh" esp32s3; \
		python3 "$(IDF_DIR)/tools/idf_tools.py" install cmake ninja; \
	fi
	@if command -v wokwi-cli >/dev/null 2>&1; then \
		echo "ok: wokwi-cli já instalado"; \
	else \
		echo ">> instalando wokwi-cli $(WOKWI_VERSION) em ~/.wokwi/bin"; \
		curl -fsSL https://wokwi.com/ci/install.sh | sh -s -- $(WOKWI_VERSION); \
	fi
	@echo ""
	@echo "Falta carregar o ambiente do ESP-IDF na sua shell, a cada sessão:"
	@echo "  . $(IDF_DIR)/export.sh"
	@echo "E exportar o token do Wokwi (https://wokwi.com/dashboard/ci):"
	@echo "  export WOKWI_CLI_TOKEN=..."

# O ESP-IDF não vive neste Makefile: ele exige o export.sh da própria instalação
# para achar toolchain e Python. Aqui só checamos a presença e delegamos, para o
# erro sair legível em vez de "command not found" no meio de um build.
firmware: ## Compila o firmware ESP-IDF (precisa do export.sh do ESP-IDF carregado)
	@command -v idf.py >/dev/null 2>&1 || { \
		echo "idf.py não encontrado. Carregue o ambiente antes:"; \
		echo "  . $(IDF_DIR)/export.sh"; \
		echo "Se ainda não instalou, rode antes: make setup"; \
		exit 1; }
	@cd $(FIRMWARE_DIR) && idf.py build

# Roda o binário recém-compilado no Wokwi headless e falha se o LED não piscar:
# o --expect-text procura no serial a linha que o app_main imprime a cada troca.
sim: firmware ## Roda a demo no Wokwi headless sobre o binário compilado
	@command -v wokwi-cli >/dev/null 2>&1 || { \
		echo "wokwi-cli não encontrado. Instale com:"; \
		echo "  make setup"; \
		exit 1; }
	@[ -n "$$WOKWI_CLI_TOKEN" ] || { \
		echo "WOKWI_CLI_TOKEN não definido. Gere o token em https://wokwi.com/dashboard/ci"; \
		echo "e exporte na sua shell antes de rodar."; \
		exit 1; }
	@wokwi-cli --timeout 10000 --expect-text "led=1" $(WOKWI_DIR)

clean: ## Apaga os binários gerados em build/ e no firmware
	rm -rf $(BUILD) $(FIRMWARE_DIR)/build
