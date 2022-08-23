#ifndef HASH_HPP
#define HASH_HPP

#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <regex>

using namespace std;

typedef struct Item Item;
typedef struct Block Block;
typedef struct Lista Lista;

struct Item
{
    int val;
    int key;
};

struct Block
{
    Item data;
    Block *prox;
};

struct Hash
{
    Block *first;
    Block *last;
};

void EscritaArquivo();
void ManipulaArquivo(int matrix_size);
void PrintMatrix(int linha, int coluna, string **matrix);
void FHVazia(Hash *l);
void HInsert(Hash *l, Item d);
void HRemove(Hash *l, Item d);
void Swap(Block *a, Block *b);
void HImprime(Hash *l, int size);
int FoldSize(int vector_size);
void LinearHashing(int vector_size, int hash_size, int *input_vector);
int KeyCalculate1(int hash_value, int hash_size);

#endif