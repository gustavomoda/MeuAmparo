# Projeto ESP-IDF do MeuAmparo. Por enquanto só a demo do LED: o core entra como
# componente quando o detector de queda for para a placa.
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(meuamparo)
