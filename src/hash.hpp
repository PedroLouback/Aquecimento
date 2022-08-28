#ifndef HASH_HPP
#define HASH_HPP

#include <stdbool.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef struct Item Item;
typedef struct Block Block;
typedef struct Lista Lista;

struct Item
{
    int** matrix;
    vector<int> key;
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

int EscritaArquivo();
vector<int> Tokenizer(const string &str, char sep);
vector<int> CoordinateRead();
void ManipulaArquivo(int matrix_size);
void PrintMatrix(int linha, int coluna, int **matrix);
void FHVazia(Hash *l);
void HInsert(Hash *l, Item d);

#endif