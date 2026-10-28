# Empacota o core/ como componente do ESP-IDF sem copiar arquivo nenhum: os mesmos .c
# que o `make test` compila no Mac são os que vão para a placa.
set(MA_CORE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../core")

file(GLOB MA_CORE_SRCS "${MA_CORE_DIR}/src/*.c")

idf_component_register(SRCS ${MA_CORE_SRCS}
                       INCLUDE_DIRS "${MA_CORE_DIR}/include")
