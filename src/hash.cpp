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

vector<int> CoordinateRead(int cont)
{

    ifstream coordinatesfile;
    string coordinateline;
    char sep = ',';
    if (cont == 0)
    {
        coordinatesfile.open("coordenadas.txt");
        getline(coordinatesfile, coordinateline);

        vector<int> Coordinates = Tokenizer(coordinateline, sep);

        coordinatesfile.close();
        return Coordinates;
    }
    else
    {
        vector<int> Coordinates;
        return Coordinates;
    }
}

void ManipulaArquivo(int matrix_size)
{

    string line, **matrix;
    char option;
    int **matrix_int, **transp_matrix, **mult_matrix;
    int linha1 = 0, coluna1 = 0, linha2 = 0, coluna2 = 0, matrixline = 0, matrixcolumn = 0, cont = 0, linha = 0, size = 0;
    ifstream matrixfile;
    HashTable h;
    int M = 100;
    int cont2 = 0, cont3 = 0, hash = 0;
    int *key;
    Initialize(&h, M);
    vector<int> Coordinates;

    while (option != 'N' || option != 'n')
    {
        //iniciliza o vetor da key
        key = (int *)calloc(4, sizeof(int));

        if (cont3 == 0)
        {
            Coordinates = CoordinateRead(cont3);
            for (size_t i = 0; i < Coordinates.size(); i++)
            {
                if (i == 0)
                {
                    linha1 = Coordinates[i];
                }
                if (i == 1)
                {
                    coluna1 = Coordinates[i];
                }
                if (i == 2)
                {
                    linha2 = Coordinates[i];
                }
                if (i == 3)
                {
                    coluna2 = Coordinates[i];
                }
            }
            cont3++;
        }
        else
        {
            cout << "Deseja continuar inserindo novas coordenadas (S - sim / N- não)? ";
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
                Coordinates.clear();
                for (size_t i = 0; i < 4; i++)
                {
                    if (i == 0)
                    {
                        Coordinates.push_back(linha1);
                    }
                    if (i == 1)
                    {
                        Coordinates.push_back(coluna1);
                    }
                    if (i == 2)
                    {
                        Coordinates.push_back(linha2);
                    }
                    if (i == 3)
                    {
                        Coordinates.push_back(coluna2);
                    }
                }
                // faz o calculo das linhas pois se ja tiver inserida precisa dessas variaveis para imprimir
                matrixline = ((linha2 - (linha1)));
                matrixcolumn = (coluna2 - (coluna1));
                matrixline++;
                matrixcolumn++;
                
                // Faz a verificação se as coordenadas são iguais
                for (int i = 0; i < h.M; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (h.table[i].key[j] == Coordinates[j])
                        {
                            cont2++;
                            if (cont2 == 3)
                            {
                                cout << "\nA matriz que contém as coordenadas inseridas já foi multiplicada!" << endl;
                                PrintMatrix(matrixline, matrixline, h.table[i].matrix);
                                return;
                            }
                        }
                        
                    }
                }
            }else{
                cout << "\nPrograma encerrado!" << endl;
                return;
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
        matrix = (string **)calloc(matrixline, 1 + sizeof(string *)); // alloca um ponteiro extra
        for (int i = 0; i < matrixline; i++)
        {
            matrix[i] = (string *)calloc(matrixcolumn, sizeof(string));
        }
        matrix[matrixline] = NULL; // coloca o ponteiro extra como NULL

        linha = 0;
        for (int i = 0; i < (matrix_size); i++)
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
                    if (linha == matrixline){
                        i = matrix_size;
                    }
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

        cout << "\nA multiplicação da matriz recortada e sua transposta resultou em:";
        PrintMatrix(matrixline, matrixline, mult_matrix);

        for (size_t i = 0; i < Coordinates.size(); i++)
        {
            key[i] = Coordinates[i];
        }

        Insert(&h, key, mult_matrix, hash, matrixline, matrixline);
        hash++;
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

void Initialize(HashTable *h, int M)
{
    h->table = (DataTable *)malloc(M * sizeof(DataTable));    

    for (int i = 0; i < M; i++)
    {
        h->table[i].key = (int *)calloc(4, sizeof(int));
    }

    h->M = M;
}

void Insert(HashTable *h, int *key, int **matrix, int hash, int matrixline, int matrixcolumn)
{
    int idx = hash;

    h->table[idx].key = key;

    h->table[idx].matrix = (int **)calloc(matrixline, 1 + sizeof(int *)); // alloc one extra ptr
    for (int i = 0; i < matrixline; i++)
    {
        h->table[idx].matrix[i] = (int *)calloc(matrixcolumn, sizeof(int));
    }
    h->table[idx].matrix[matrixline] = NULL; // set the extra ptr to NULL

    for (int i = 0; i < matrixline; i++)
    {
        for (int j = 0; j < matrixcolumn; j++)
        {
            h->table[idx].matrix[i][j] = matrix[i][j];
        }
    }

    cout << "\nA matriz informada acima foi inserida com sucesso na Hash com chave ' ";
    for (size_t i = 0; i < 4; i++)
    {
        cout << h->table[idx].key[i] << " ";
    }

    cout << "'\n\n";
}