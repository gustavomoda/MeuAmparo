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

.PHONY: help setup test firmware sim sim-queda sim-cancelada sim-botao sim-pulo web clean

# O help se monta sozinho a partir dos comentários "##" nos alvos: alvo novo sem
# descrição não aparece na lista, e descrição nenhuma fica desatualizada em silêncio.
help: ## Lista os alvos disponíveis
	@grep -E '^[a-zA-Z_-]+:.*?## ' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "  %-14s %s\n", $$1, $$2}'

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
	@echo "Falta o token do Wokwi. Gere em https://wokwi.com/dashboard/ci e salve:"
	@echo "  mkdir -p ~/.config/wokwi && pbpaste > $(WOKWI_TOKEN_FILE)"

# O ESP-IDF exige o export.sh da própria instalação para achar toolchain e Python.
# Se a shell ainda não carregou, o alvo carrega sozinho. O venv é escolhido entre os
# que já existem em ~/.espressif: quando o Homebrew troca a versão do python3, o
# export.sh procura um venv que não existe e falha, mesmo com tudo instalado.
IDF_ENV = command -v idf.py >/dev/null 2>&1 || { \
	[ -f "$(IDF_DIR)/export.sh" ] || { echo "ESP-IDF não encontrado em $(IDF_DIR). Rode: make setup"; exit 1; }; \
	[ -n "$$IDF_PYTHON_ENV_PATH" ] || \
		export IDF_PYTHON_ENV_PATH="$$(ls -d $$HOME/.espressif/python_env/idf*_env 2>/dev/null | tail -1)"; \
	. "$(IDF_DIR)/export.sh" >/dev/null 2>&1 || { echo "falha ao carregar $(IDF_DIR)/export.sh"; exit 1; }; \
}

firmware: ## Compila o firmware ESP-IDF (carrega o ambiente sozinho)
	@$(IDF_ENV); cd $(FIRMWARE_DIR) && idf.py build

# O token de CI do Wokwi vem da variável WOKWI_CLI_TOKEN ou do arquivo
# ~/.config/wokwi/token, fora do repositório. O arquivo aceita só o token ou a
# linha "export WOKWI_CLI_TOKEN=..." colada inteira.
WOKWI_TOKEN_FILE ?= $(HOME)/.config/wokwi/token
WOKWI_TOKEN = [ -n "$$WOKWI_CLI_TOKEN" ] || \
	export WOKWI_CLI_TOKEN="$$(sed -E 's/^export +//; s/^WOKWI_CLI_TOKEN=//; s/[\"'"'"' ]//g' \
		"$(WOKWI_TOKEN_FILE)" 2>/dev/null | tr -d '\r\n')"; \
	[ -n "$$WOKWI_CLI_TOKEN" ] || { \
		echo "Token do Wokwi não encontrado. Gere em https://wokwi.com/dashboard/ci e salve:"; \
		echo "  mkdir -p ~/.config/wokwi && pbpaste > $(WOKWI_TOKEN_FILE)"; \
		exit 1; }

# Cada cenário em simulator/wokwi/scenarios/ é um teste de integração: mexe no MPU6050
# e no botão pela automação do Wokwi e espera pela linha certa no serial. O primeiro
# cenário que falhar para tudo, com o log dele na tela.
SCENARIOS = $(wildcard $(WOKWI_DIR)/scenarios/*.yaml)

sim: firmware ## Roda todos os cenários do Wokwi headless (queda, botão, pulo...)
	@command -v wokwi-cli >/dev/null 2>&1 || { \
		echo "wokwi-cli não encontrado. Instale com:"; \
		echo "  make setup"; \
		exit 1; }
	@$(WOKWI_TOKEN); \
	for s in $(SCENARIOS); do \
		echo "== $$s"; \
		wokwi-cli --quiet --timeout 40000 --scenario scenarios/$$(basename $$s) $(WOKWI_DIR) || exit 1; \
	done
	@echo "ok: todos os cenários passaram"

# Um cenário por vez, com o serial inteiro na tela: é o que se mostra na apresentação.
# Sem --quiet, o wokwi-cli também imprime cada passo do cenário ([Queda...] delay 300ms),
# o que deixa ver o sensor sendo mexido e a resposta do firmware logo abaixo.
define run_scenario
	@command -v wokwi-cli >/dev/null 2>&1 || { echo "wokwi-cli não encontrado. Rode: make setup"; exit 1; }
	@$(WOKWI_TOKEN); \
	wokwi-cli --timeout 40000 --scenario scenarios/$(1).yaml $(WOKWI_DIR)
endef

sim-queda: firmware ## Cenário: queda, janela de 10 s e alerta com posição
	$(call run_scenario,queda)

sim-cancelada: firmware ## Cenário: queda cancelada pelo botão dentro da janela
	$(call run_scenario,queda-cancelada)

sim-botao: firmware ## Cenário: pedido de ajuda pelo botão
	$(call run_scenario,botao)

sim-pulo: firmware ## Cenário: pulo, que não pode gerar alerta
	$(call run_scenario,pulo)

# O wokwi.com aceita upload de firmware, mas prefere um .bin único com bootloader,
# tabela de partição e aplicação juntos. O alvo gera esse arquivo e diz o que fazer
# com ele: é o caminho para ver o circuito e mexer no botão e nos sliders com o mouse.
WEB_BIN = $(FIRMWARE_DIR)/build/meuamparo-wokwi.bin

web: firmware ## Gera o .bin para rodar no wokwi.com e mostra o passo a passo
	@$(IDF_ENV); cd $(FIRMWARE_DIR) && idf.py merge-bin -o meuamparo-wokwi.bin >/dev/null
	@echo ""
	@echo "Binário pronto: $(CURDIR)/$(WEB_BIN)"
	@echo ""
	@echo "1. Abra https://wokwi.com/projects/new/esp32-s3"
	@echo "2. Na aba diagram.json, troque o conteúdo pelo de $(WOKWI_DIR)/diagram.json"
	@echo "3. Clique no editor de código, aperte F1 e escolha"
	@echo "   'Upload Firmware and Start Simulation...'"
	@echo "4. Selecione o arquivo acima"
	@echo ""
	@echo "Para simular uma queda à mão: clique no MPU6050 e leve accelZ a 0,1 por um"
	@echo "instante, depois a 4, depois 0 com accelX em 1. O botão vermelho é o de ajuda."

clean: ## Apaga os binários gerados em build/ e no firmware
	rm -rf $(BUILD) $(FIRMWARE_DIR)/build
