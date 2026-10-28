# Atalho da raiz: repassa tudo para src/meuamparo, onde mora o código. Existe para que
# `make sim` funcione logo depois do clone, sem precisar saber a estrutura de pastas.
CODE_DIR = src/meuamparo

.PHONY: help setup test firmware sim sim-queda sim-cancelada sim-botao sim-pulo web clean

help: ## Lista os alvos disponíveis
	@grep -E '^[a-zA-Z_-]+:.*?## ' $(CODE_DIR)/Makefile \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "  %-14s %s\n", $$1, $$2}'

setup test firmware sim sim-queda sim-cancelada sim-botao sim-pulo web clean:
	@$(MAKE) --no-print-directory -C $(CODE_DIR) $@
