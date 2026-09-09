# Código

Trabalho de código acontece em `src/meuamparo/`. A regra que organiza tudo é a fronteira entre as
pastas, explicada com o porquê em `src/meuamparo/README.md`:

- `core/` é C puro. Nenhum header do ESP-IDF, nenhum FreeRTOS, nenhum acesso a hardware.
- `firmware/` só recebe o que roda no ESP32-S3. Nenhum trace, mock ou cenário.
- `simulator/` pode depender de qualquer coisa, porque não vai para a placa.
- `test/` roda no host, sem toolchain de embarcado.

Essa separação existe para medir a meta de 90% de detecção rodando o algoritmo contra centenas de
traces em segundos, no Mac. Proposta que quebre a fronteira precisa justificar por que vale perder
isso.

## Comandos

```
make help    lista os alvos
make test    compila e roda os testes de host
make clean   apaga build/
```

O Makefile usa `-Werror`. Aviso de compilador quebra o build de propósito.

Alvo novo precisa de um comentário `## descrição` na própria linha, senão não aparece no `make help`.

## Como fechar uma tarefa

O plano de oito passos em `src/meuamparo/README.md` dá um critério de verificação por passo. Siga a
mesma regra em qualquer tarefa nova: passo sem critério verificável não conta como pronto. "Compila"
não é critério; "make test passa" é.

## Convenções em uso

Identificador em inglês com prefixo `ma_`: `ma_imu_sample_t`, `ma_accel_magnitude`. Comentário em
português, explicando a decisão e o motivo, não o que a linha já diz. Header com include guard
`MEUAMPARO_<ARQUIVO>_H`.

Os README e o `core/include/meuamparo/imu.h` são a referência de tom. Aquele comentário explica
por que usar magnitude em vez dos eixos separados — é esse nível que se espera, e não "calcula a
magnitude".

O repositório ainda não tem nenhum commit, então o idioma da mensagem de commit está em aberto.
Pergunte antes de assumir.
