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

typedef struct DataTable DataTable;
typedef struct HashTable HashTable;

struct DataTable
{
    int *key;
    int **matrix;
};

struct HashTable
{
    DataTable *table;
    int M;
};

int EscritaArquivo();
vector<int> Tokenizer(const string &str, char sep);
vector<int> CoordinateRead();
void ManipulaArquivo(int matrix_size);
void PrintMatrix(int linha, int coluna, int **matrix);
void Initialize(HashTable *h, int M);
void Insert(HashTable *h, int *key, int **matrix, int hash, int matrixline, int matrixcolumn);

#endif