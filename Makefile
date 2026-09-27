CC=gcc
CFLAGS=-Wall -std=c11
PTHREAD=-pthread

all: varredura_linha varredura_coluna matmul_padrao matmul_bloco matmul_pthreads matmul_pthreads_bloco

varredura_linha: varredura_linha.c
	$(CC) -O3 $(CFLAGS) $< -o $@
varredura_coluna: varredura_coluna.c
	$(CC) -O3 $(CFLAGS) $< -o $@
matmul_padrao: matmul_padrao.c
	$(CC) -O3 $(CFLAGS) $< -o $@
matmul_bloco: matmul_bloco.c
	$(CC) -O3 $(CFLAGS) $< -o $@
matmul_pthreads: matmul_pthreads.c
	$(CC) -O3 $(CFLAGS) $(PTHREAD) $< -o $@
matmul_pthreads_bloco: matmul_pthreads_bloco.c
	$(CC) -O3 $(CFLAGS) $(PTHREAD) $< -o $@
clean:
	rm -f varredura_linha varredura_coluna matmul_padrao matmul_bloco matmul_pthreads matmul_pthreads_bloco
