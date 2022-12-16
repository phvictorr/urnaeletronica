#ifndef ARVORE_H
#define ARVORE_H

typedef struct Info_Est {
    int titulo_eleitor;
    char Nome[50];
    int voto;
    int quantidade_votos;
    int recebeu_voto;
}Info;

typedef struct No_Est {
    Info *info;
    struct No_Est *esq;
    struct No_Est *dir;
}No;

No *arvoreTitulos;
No *arvoreVotos;

#endif
