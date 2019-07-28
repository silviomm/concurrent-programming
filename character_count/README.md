Para rodar ​ qualquer​ dos programas, é ​ necessário​ que os arquivos:
- validos​.​ txt
- timer​.h
Estejam na mesma pasta que “arquivo.c”
----------------------------------------------------------------------------------------
Arquivos “seq_xxx.c”:
- gcc -o seq_xxx seq_xxx.c
- ./seq_xxx entrada.txt saida.csv
----------------------------------------------------------------------------------------
Arquivos “conc_xxx.c”:
- gcc -o conc_xxx conc_xxx.c -lpthread
- ./conc_xxx entrada.txt saida.csv <nthreads>
----------------------------------------------------------------------------------------
Arquivo “ascii.c”:
- gcc -o ascii ascii.c -lpthread
- ./ascii entrada.txt saida.csv <nthreads>
----------------------------------------------------------------------------------------