# Laboratório - Hierarquia de Memória, Cache e Pthreads

Aluna: Giulia Araki
RA: 10408954

## Arquivos
- varredura_linha.c
- varredura_coluna.c
- matmul_padrao.c
- matmul_bloco.c
- matmul_pthreads.c
- matmul_pthreads_bloco.c
- Makefile
- cachegrind_resumo.csv

## Exemplos
```bash
make
./varredura_linha 8192
./varredura_coluna 8192
./matmul_padrao 1536
./matmul_bloco 1536 64
./matmul_pthreads 1536 8
./matmul_pthreads_bloco 1536 128 8
```

Para reproduzir o profiling:
```bash
valgrind --tool=cachegrind --cache-sim=yes ./matmul_padrao 512
valgrind --tool=cachegrind --cache-sim=yes ./matmul_bloco 512 64
```

Observação: o arquivo cachegrind_resumo.csv contém a transcrição consolidada das métricas coletadas no Google Colab.
