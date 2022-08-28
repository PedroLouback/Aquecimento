#include "hash.hpp"

int EscritaArquivo()
{

    int matrix_size = 0, value = 0;
    ofstream matrixfile;

    cout << "\nInforme quantas linhas e colunas vai compor a matriz principal: ";
    cin >> matrix_size;

    matrixfile.open("matrix.txt");

    if (!matrixfile)
    {
        cout << "Arquivo não pode ser aberto" << endl;
        abort();
    }
    srand(time(NULL));
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            value = (rand() % 100);
            matrixfile << value << "\t";
        }
        matrixfile << "\n";
    }

    cout << "\nUm arquivo contendo uma matriz " << matrix_size << " x " << matrix_size << " foi criado" << endl;

    matrixfile.close();

    return matrix_size;
}

vector<int> Tokenizer(const string &str, char sep)
{
    vector<int> tokens;

    int i;
    stringstream ss(str);
    while (ss >> i)
    {
        tokens.push_back(i);
        if (ss.peek() == sep)
        {
            ss.ignore();
        }
    }

    return tokens;
}

vector<int> CoordinateRead()
{

    ifstream coordinatesfile;
    string coordinateline;
    char sep = ',';
    coordinatesfile.open("coordenadas.txt");
    getline(coordinatesfile, coordinateline);

    vector<int> Coordinates = Tokenizer(coordinateline, sep);

    coordinatesfile.close();

    return Coordinates;
}

void ManipulaArquivo(int matrix_size)
{

    string line, **matrix;
    char option;
    int **matrix_int, **transp_matrix, **mult_matrix;
    int linha1 = 0, coluna1 = 0, linha2 = 0, coluna2 = 0, matrixline = 0, matrixcolumn = 0, cont = 0, linha = 0, size = 0;
    ifstream matrixfile;
    Hash LinearHashing;
    Block *aux2;
    Item aux;
    int i = 0, j = 0, cont2 = 0, cont3 = 0;
    vector<int> key;

    while (option != 'N' || option != 'n')
    {
        if (cont3 == 0)
        {
            CoordinateRead();
            for (size_t i = 0; i < CoordinateRead().size(); i++)
            {
                if (i == 0)
                {
                    linha1 = CoordinateRead()[i];
                }
                if (i == 1)
                {
                    coluna1 = CoordinateRead()[i];
                }
                if (i == 2)
                {
                    linha2 = CoordinateRead()[i];
                }
                if (i == 3)
                {
                    coluna2 = CoordinateRead()[i];
                }
            }
            cont++;
        }
        else
        {
            cout << "Deseja continuar inserindo novas coordenadas (S - sim / N- não)?  ";
            cin >> option;
            if (option == 'S' || option == 's')
            {
                cout << "\nInforme o 'i' do 1º ponto: ";
                cin >> linha1;
                cout << "Informe o 'j' do 1º ponto: ";
                cin >> coluna1;
                cout << "\nInforme o 'i' do 2º ponto: ";
                cin >> linha2;
                cout << "Informe o 'j' do 2º ponto: ";
                cin >> coluna2;
                for (size_t i = 0; i < CoordinateRead().size(); i++)
                {
                    if (i == 0)
                    {
                        CoordinateRead()[i] = linha1;
                    }
                    if (i == 1)
                    {
                        CoordinateRead()[i] = coluna1;
                    }
                    if (i == 2)
                    {
                        CoordinateRead()[i] = linha2;
                    }
                    if (i == 3)
                    {
                        CoordinateRead()[i] = coluna2;
                    }
                }
            }
        }

        matrixfile.open("matrix.txt");
        if (linha1 >= matrix_size || linha2 >= matrix_size)
        {
            cout << "\nERRO: Linha ou coluna inserida não existente!" << endl;
            exit(1);
        }

        // Calculo para descobrir o tamanho da matriz secundaria
        matrixline = ((linha2 - (linha1)));
        matrixcolumn = (coluna2 - (coluna1));
        matrixline++;
        matrixcolumn++;

        // Aloca a memoria para inserir a matriz de string
        matrix = (string **)malloc(sizeof(string *) * matrixline);
        for (int i = 0; i < matrixline; i++)
        {
            matrix[i] = (string *)malloc(sizeof(string) * matrixcolumn);
        }

        for (int i = 0; i < matrix_size; i++)
        {
            getline(matrixfile, line);
            if (i >= linha1)
            {
                if (i <= linha2)
                {
                    vector<string> tokens;
                    istringstream iss(line);
                    string number;
                    while (iss >> number)
                    {
                        tokens.push_back(number);
                    }
                    cont = 0;
                    for (int j = 0; j < matrixcolumn; j++)
                    {
                        if (cont <= matrixcolumn)
                        {
                            matrix[linha][j] = tokens[coluna1 + cont];
                            cont++;
                        }
                    }
                    linha++;
                }
            }
        }
        matrixfile.close();

        // Faz uma nova matriz só que de inteiro pois até aqui se trata de uma matriz de string

        // Aloca a matriz de inteiro
        matrix_int = (int **)malloc(sizeof(int *) * matrixline);
        for (int i = 0; i < matrixline; i++)
        {
            matrix_int[i] = (int *)malloc(sizeof(int) * matrixcolumn);
        }

        for (int i = 0; i < matrixline; i++)
        {
            for (int j = 0; j < matrixcolumn; j++)
            {
                matrix_int[i][j] = stoi(matrix[i][j]);
            }
        }

        cout << "\nMatriz recortada do ponto (" << linha1 << "," << coluna1 << ") ao (" << linha2 << "," << coluna2 << "):";
        PrintMatrix(matrixline, matrixcolumn, matrix_int);

        // Pega a matriz normal e passa para a transposta

        // Aloca a matriz transposta
        transp_matrix = (int **)malloc(sizeof(int *) * matrixcolumn);
        for (int i = 0; i < matrixcolumn; i++)
        {
            transp_matrix[i] = (int *)malloc(sizeof(int) * matrixline);
        }

        for (int i = 0; i < matrixcolumn; i++)
        {
            for (int j = 0; j < matrixline; j++)
            {
                transp_matrix[i][j] = matrix_int[j][i];
            }
        }

        cout << "\nA matriz transposta é:";
        PrintMatrix(matrixcolumn, matrixline, transp_matrix);

        // Faz a multiplicação de matriz

        size = (matrixline * matrixcolumn);

        // Aloca a matriz que vai receber o resultado da multiplicação
        mult_matrix = (int **)malloc(sizeof(int *) * size);
        for (int i = 0; i < size; i++)
        {
            mult_matrix[i] = (int *)malloc(sizeof(int) * size);
        }

        for (int i = 0; i < matrixline; i++)
        {
            for (int k = 0; k < matrixline; k++)
            {
                mult_matrix[i][k] = 0;
                for (int j = 0; j < matrixcolumn; j++)
                {
                    mult_matrix[i][k] += matrix_int[i][j] * transp_matrix[j][k];
                }
            }
        }

        cout << "\nA multiplicação de matriz resultou em:";
        PrintMatrix(matrixline, matrixline, mult_matrix);

        FHVazia(&LinearHashing);

        aux2 = LinearHashing.first;

        // Faz a verificação se as coordenadas são iguais
        while (aux2->prox != NULL)
        {
            for (size_t i = 0; i < CoordinateRead().size(); i++)
            {
                if (CoordinateRead()[i] == aux2->prox->data.key[i])
                {
                    cont2++;
                    if (cont2 == 3)
                    {
                        cout << "\nA matriz onde contém as coordenadas inseridas já foi multiplicada!" << endl;
                        PrintMatrix(matrixline, matrixline, aux2->prox->data.matrix);
                        return;
                    }
                }
            }
        }

        aux.matrix = (int **)malloc(sizeof(int *) * matrixline);
        for (i = 0; i < matrixline; i++)
        {
            aux.matrix[i] = (int *)malloc(sizeof(int) * matrixline);
        }

        for (i = 0; i < matrixline; i++)
        {
            for (j = 0; j < matrixline; j++)
            {
                aux.matrix[i][j] = mult_matrix[i][j];
            }
        }

        for (size_t i = 0; i < CoordinateRead().size(); i++)
        {
            aux.key[i] = CoordinateRead()[i];
        }

        HInsert(&LinearHashing, aux);
    }
}

void PrintMatrix(int matrixline, int matrixcolumn, int **matrix)
{

    for (int i = 0; i < matrixline; i++)
    {
        cout << "\n";
        for (int j = 0; j < matrixcolumn; j++)
        {
            cout << matrix[i][j] << "\t";
        }
    }
    cout << "\n\n";
}

void FHVazia(Hash *l)
{
    l->first = (Block *)malloc(sizeof(Block));
    l->last = l->first;
    l->first->prox = NULL;
}

void HInsert(Hash *l, Item d)
{
    l->last->prox = (Block *)malloc(sizeof(Block));
    l->last = l->last->prox;
    l->last->data = d;
    l->last->prox = NULL;
}