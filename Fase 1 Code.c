//Lucas Alves - Projeto 1 - Estruturas de dados avançadas 

//Bibliotecas
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/*Explicação de algumas variaveis
    data = Numero da matriz
    column = Coluna da matriz
    row = Linha da matriz
    dataCalc = Valor calculado para o problema de atribuição
    crossed = Variavel para verificar se o node foi cortado
    doubleCrossed = Variavel para verificar se o node foi cortado duas vezes
    head = Apontador para o 1º node da linked list
    next = Apontador para o proximo node
    newNode = Novo node a ser adicionado na linked list
    temp = Node temporario para percorrer a linked list
    filename = Nome do ficheiro que contem a matriz
    file = Ficheiro que contem a matriz
    line = Linha do ficheiro
    token = Valor do numero, ele considera o valor até ao ";"
    maxRow = Numero maximo de linhas
    maxColumn = Numero maximo de colunas
    choice = Escolha do utilizador
    newValue = Novo valor a ser atribuido ao node
    newRow = Nova linha a ser adicionada
    newColumn = Nova coluna a ser adicionada
    rowIndex = Indice da linha a ser removida
    columnIndex = Indice da coluna a ser removida
    i = Variavel de controle para loops
    j = Variavel de controle para loops
    reassing = Node temporario para percorrer a linked list
*/

//Constituição do node da linked list
typedef struct Node {
    //Damos os tipos de dados que queremos obter neste caso o numero e a sua posição na matriz
    int data;
    int column;
    int row;
    int dataCalc;
    bool crossed;
    bool doubleCrossed;

    struct Node* next;
} Node;

//Inicializar a head da linked list onde teremos o enderesso do 1º node
Node *head = NULL;


//Função para ler e carregar os dados para a linked list
void loadMatrixToList(char *filename) {

    //Abir o ficheiro em read mode
    FILE *file = fopen(filename, "r");

    //Verificar se o ficheiro foi aberto
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s.\n", filename);
        return;
    }

    //Ler o ficheiro linha a linha
    //Cada linha é separada por um enter e cada valor é separado por um ";"
    char line[256];
    int row = 0;
    while (fgets(line, sizeof(line), file)) {

        //Toke = valor do numero, ele considera o valor até ao ";"
        char *token;
        token = strtok(line, ";");
        int column = 0;

        //Ler os valores até ao final da linha
        while (token != NULL) {

           //Alocar espaço para o novo node
            Node *newNode = (Node*) malloc(sizeof(Node));

            //Atribuir os valores ao novo node
            newNode->data = atoi(token); //Numero 
            newNode->column = column; //Coluna
            newNode->row = row; //Linha
            newNode->dataCalc = 0; //Valor calculado para o problema de atribuição
            newNode->crossed = false; //Variavel para verificar se o node foi cortado
            newNode->doubleCrossed = false; //Variavel para verificar se o node foi cortado duas vezes
            newNode->next = head; //Apontar para o proximo node
            head = newNode; //Atualizar a head para apontar para o novo node

            //Passar para o proximo valor
            token = strtok(NULL, ";"); 
            column++;
        }
        //Passar para a proxima linha
        row++;
    }
    //Fechar o ficheiro
    fclose(file);
}


//Função para imprimir a linked list (Não será utilizada no projeto) 
//Mas serve como guia para verificar se a matriz foi carregada corretamente
void printListInOrder(Node* node) {
        //Se o node for NULL, retornar
        if (node == NULL) {
        return;
    }
    //Imprimir todos os nodes da linked list em ordem
    //Basicamente, chama continuamente a função para o proximo node até que o node seja NULL
    //Quando o node for NULL, a função retornará para o node anterior e imprimirá o valor do node
    printListInOrder(node->next);
    printf("Data: %d, Column: %d, Row: %d, DataCalc:%d, isCrossed:%d ,isdoubleCrossed:%d\n", node->data, node->column, node->row, node->dataCalc, node->crossed, node->doubleCrossed);
}


//Variaveis para armazenar o número máximo de linhas e colunas
int maxRow = 0;
int maxColumn = 0;

//Função para imprimir a matriz a partir da linked list
int printMatrixFromList() {
    //Primeiro, percorrer a linked list para encontrar o número máximo de linhas e colunas
    Node *temp = head;
    while (temp != NULL) {
        //Se a linha ou coluna atual for maior que a linha ou coluna máxima, atualize a linha ou coluna máxima
        if (temp->row > maxRow) {
            maxRow = temp->row;
        }
        if (temp->column > maxColumn) {
            maxColumn = temp->column;
        }
        temp = temp->next;
    }

    printf("\n");   

    //Agora, para cada linha e coluna, encontre o node correspondente e imprima-o
    for (int i = 0; i <= maxRow; i++) {
        for (int j = 0; j <= maxColumn; j++) {
            temp = head;
            //Percorrer a linked list para encontrar o node correspondente
            while (temp != NULL) {
                if (temp->row == i && temp->column == j) {
                    //Imprimir o valor do node
                    printf("%d ", temp->data);
                    break;
                }
                temp = temp->next;
            }
        }
        //Trocar de linha
        printf("\n");
    }
    return maxRow, maxColumn;
}


//Função para encontrar e trocar o valor de um node na linked list
void changeNodeValue(Node* head, int row, int column, int newValue) {
    //Percorrer a linked list para encontrar o node correspondente
    Node* temp = head;
    while (temp != NULL) {
        //Se o node for encontrado, atualize o valor do node e retorne
        if (temp->row == row && temp->column == column) {
            temp->data = newValue;
            return;
        }
        //Passar para o proximo node caso o node atual não seja o node que estamos procurando
        temp = temp->next;
    }
    //Mensagem de erro caso o node não seja encontrado
    printf("Valor não encontrado.\n");
}


//Funçao para adicionar uma linha à matriz
void addRow(int maxColumn, int maxRow, int rowIndex) {
    int newValueForNewLine;
    Node *temp = head;

    //Perguntar ao usuario quais valores ele deseja adicionar à nova linha e adicionar os valores à linked list
    for  (int i = 0; i <= maxColumn; i++) {
        printf("Indique o %dº valor da nova linha: ", (i+1));
        scanf("%d", &newValueForNewLine);

        //Alocar espaço para o novo node
        Node *newNode = (Node*) malloc(sizeof(Node));

        //Atribuir os valores ao novo node
        newNode->data = newValueForNewLine; //Numero 
        newNode->column = i; //Coluna
        newNode->row = rowIndex; //Linha
        newNode->dataCalc = 0; //Valor calculado para o problema de atribuição
        newNode->crossed = false; //Variavel para verificar se o node foi cortado
        newNode->doubleCrossed = false; //Variavel para verificar se o node foi cortado duas vezes
        newNode->next = head; //Apontar para o proximo node
        head = newNode; //Atualizar a head para apontar para o novo node
    }

    //Atualizar os índices das linhas
    while (temp != NULL) {
        if (temp->row >= rowIndex) {
            temp->row = temp->row + 1;
        }
        temp = temp->next;
    }

    //Atualizar o número máximo de linhas
    maxRow++;
}


//Função para adicionar uma coluna à matriz
void addColumn(int maxColumn, int maxRow, int columnIndex) {
    int newValueForNewColumn;
    Node *temp = head;
    
    //Perguntar ao usuario quais valores ele deseja adicionar à nova coluna e adicionar os valores à linked list
    for  (int i = 0; i <= maxRow; i++) {
        printf("Indique o %dº valor da nova coluna: ", (i+1));
        scanf("%d", &newValueForNewColumn);

        //Alocar espaço para o novo node
        Node *newNode = (Node*) malloc(sizeof(Node));

        //Atribuir os valores ao novo node
        newNode->data = newValueForNewColumn; //Numero 
        newNode->column = columnIndex; //Coluna
        newNode->row = i; //Linha
        newNode->dataCalc = 0; //Valor calculado para o problema de atribuição
        newNode->crossed = false; //Variavel para verificar se o node foi cortado
        newNode->doubleCrossed = false; //Variavel para verificar se o node foi cortado duas vezes
        newNode->next = head; //Apontar para o proximo node
        head = newNode; //Atualizar a head para apontar para o novo node
    }

    //Atualizar os índices das colunas
    while (temp != NULL) {
        if (temp->column >= columnIndex) {
            temp->column = temp->column + 1;
        }
        temp = temp->next;
    }

    //Atualizar o número máximo de colunas
    maxColumn++;
}


//Função para remover uma linha da matriz à escolha do utilizador
void removeRow(int rowIndex) {
    Node* temp = head;
    Node* prev = NULL;

    //Percorrer a lista ligada
    while (temp != NULL) {
        //Se o node atual deve ser removido
        if (temp->row == rowIndex) {
            //Se é o node da head
            if (temp == head) {
                head = temp->next;
            } else {
                //Se não é o node da head
                prev->next = temp->next;
            }

            Node* nodeToRemove = temp;
            temp = temp->next;

            free(nodeToRemove);
        } else {
            //Se o node atual não deve ser removido
            prev = temp;
            temp = temp->next;
        }
    }

    Node* reassing = head;

    //Atualizar os índices das linhas
    while (reassing != NULL) {
        if (reassing->row >= rowIndex) {
            reassing->row = reassing->row - 1;
        }
        reassing = reassing->next;
    }

    //Atualizar o número máximo de linhas
    maxRow--;
}


//Função para remover uma coluna da matriz à escolha do utilizador
void removeColumn(int columnIndex) {
    Node* temp = head;
    Node* prev = NULL;

    //Percorrer a lista ligada
    while (temp != NULL) {
        //Se o node atual deve ser removido
        if (temp->column == columnIndex) {
            //Se é o node da head
            if (temp == head) {
                head = temp->next;
            } else {
                //Se não é o node da head
                prev->next = temp->next;
            }

            Node* nodeToRemove = temp;
            temp = temp->next;
            
            free(nodeToRemove);
        } else {
            //Se o node atual não deve ser removido
            prev = temp;
            temp = temp->next;
        }
    }

    Node* reassing = head;

    //Atualizar os índices das colunas
    while (reassing != NULL) {
        if (reassing->column >= columnIndex) {
            reassing->column = reassing->column - 1;
        }
        reassing = reassing->next;
    }

    //Atualizar o número máximo de colunas
    maxColumn--;
}


//Igualar o valor para calculo ao valor real da matriz
void equalizeDataCalcToData(){
    Node *temp = head;

    //Percorrer a linked list para igualar o valor para calculo ao valor real da matriz
    while (temp != NULL) {
        temp->dataCalc = temp->data;
        temp = temp->next;
    }
}


//Função para encontrar o maior valor da matriz
int findMaxValue(){
    Node *temp = head;
    int maxValue = 0;

    //Percorrer a linked list para encontrar o maior valor
    while (temp != NULL) {
        //Se o valor do node atual for maior que o valor máximo, atualize o valor máximo
        if (temp->dataCalc > maxValue) {
            maxValue = temp->dataCalc;
        }
        //Passar para o proximo node
        temp = temp->next;
    }

    //Retornar o valor máximo
    return maxValue;
}


//Função para subtrair o maior valor da matriz por todos os valores
void subtractValueFromAll(int maxValue){
    Node *temp = head;

    //Percorrer a linked list para subtrair o valor de todos os nodes
    while (temp != NULL) {
        temp->dataCalc = maxValue - temp->dataCalc;
        temp = temp->next;
    }
}


//Função para encontrar o menor valor de uma linha e subtrair de todos os valores da linha
void subtractMinFromRow(int maxRow){
    Node *temp = head;
    int min;
    bool firstTime;

    //Percorrer a linked list para encontrar o menor valor de cada linha
    for (int i = 0; i <= maxRow; i++) {
        //Variavel para verificar se é a primeira vez que a linha está a ser percorrida
        firstTime = true;

        //Retornar ao inicio da linked list
        temp = head;

        //Se o node atual for da mesma linha que o node anterior e o valor do node atual for menor que o valor mínimo, atualize o valor mínimo
        while (temp != NULL) {
            if (temp->row == i) {

                //Atribuir um valor inicial para o min da linha
                if(firstTime){
                    min = temp->dataCalc;
                    firstTime = false;
                }

                //Se o valor do node atual for menor que o valor mínimo, atualize o valor mínimo
                if (temp->dataCalc < min) {
                    min = temp->dataCalc;
                }
            }
            temp = temp->next;
        }
        
        //Retornar ao inicio da linked list
        temp = head;

        //Subtrair o valor mínimo de todos os nodes da linha
        while (temp != NULL) {
            if (temp->row == i) {
                temp->dataCalc = temp->dataCalc - min;
            }
            temp = temp->next;
        }
    }
}


//Função para encontrar o menor valor de uma coluna e subtrair de todos os valores da coluna
void subtractMinFromColumn(int maxColumn){
    Node *temp = head;
    int min;
    bool firstTime;

    //Percorrer a linked list para encontrar o menor valor de cada coluna
    for (int i = 0; i <= maxColumn; i++) {
        //Variavel para verificar se é a primeira vez que a coluna está a ser percorrida
        firstTime = true;

        //Retornar ao inicio da linked list
        temp = head;

        //Se o node atual for da mesma coluna que o node anterior e o valor do node atual for menor que o valor mínimo, atualize o valor mínimo
        while (temp != NULL) {
            if (temp->column == i) {

                //Atribuir um valor inicial para o min da coluna
                if(firstTime) {
                    min = temp->dataCalc;
                    firstTime = false;
                }
            
                //Se o valor do node atual for menor que o valor mínimo, atualize o valor mínimo
                if (temp->dataCalc < min) {
                    min = temp->dataCalc;
                }
            }
            temp = temp->next;
        }
        
        //Retornar ao inicio da linked list
        temp = head;

        //Subtrair o valor mínimo de todos os nodes da coluna
        while (temp != NULL) {
            if (temp->column == i) {
                temp->dataCalc = temp->dataCalc - min;
            }
            temp = temp->next;
        }
    }
}


//Função para percorrer as linhas e colunas para encontrar zeros
int findZeros(){
    Node *temp;
    int zerosFound;
    int maxZerosFound = 0;
    int index = -1;
    bool inRow = true;
    int numberOfCuts = 0;

    //limpar os cortes e doubleCortes
    temp = head;
    while (temp != NULL){
        temp->crossed = false;
        temp->doubleCrossed = false;
        temp = temp->next;
    }

    do{    
        maxZerosFound = 0;
        index = -1;
        inRow = true;

        for (int i = 0; i <= maxRow; i++)
        {
            //Reinicar variaveis
            zerosFound = 0;
            temp = head;

            while (temp != NULL){
                if (temp->row == i){
                    if (temp->dataCalc == 0 && !temp->crossed){
                        zerosFound++;
                    }
                }
                temp = temp->next;
            }

            //Se o número de zeros encontrados for maior que o número máximo de zeros encontrados, 
            //atualize o número máximo de zeros encontrados e o índice da linha
            if (zerosFound > maxZerosFound){
                maxZerosFound = zerosFound;
                index = i;
                inRow = true;
            }
        }

        for (int i = 0; i <= maxColumn; i++)
        {
            //Reinicar variaveis
            zerosFound = 0;
            temp = head;

            while (temp != NULL){
                if (temp->column == i){
                    if (temp->dataCalc == 0 && !temp->crossed){
                        zerosFound++;
                    }
                }
                temp = temp->next;
            }

            //Se o número de zeros encontrados for maior que o número máximo de zeros encontrados, 
            //atualize o número máximo de zeros encontrados e o índice da coluna
            if (zerosFound > maxZerosFound){
                maxZerosFound = zerosFound;
                index = i;
                inRow = false;
            }
        }

       if (index != -1)
       {
            temp = head;
            while(temp != NULL){
                //Se o maior numero de zeros for em linha
                if(inRow){
                    //Se o node atual for da linha com mais zeros, cortar o node
                    if(temp->row == index){
                        //Se o node já foi cortado, cortar novamente
                        if (temp->crossed == true)
                            temp->doubleCrossed = true;
                        else
                            temp->crossed = true;
                    }        
                }
                //Se o maior numero de zeros for em coluna
                else{
                    //Se o node atual for da coluna com mais zeros, cortar o node
                    if(temp->column == index){
                        //Se o node já foi cortado, cortar novamente
                        if (temp->crossed == true)
                            temp->doubleCrossed = true;
                        else
                            temp->crossed = true;
                    }
                }
                temp = temp->next;   
            }
        }

        if (maxZerosFound > 0)
            numberOfCuts++;
     

    //Repetir até que todos os zeros estejam cortados
    }while(maxZerosFound != 0);

    //Retornar o número de cortes
    return numberOfCuts;
}


//Função para procurar o menor numero dos numeros não cortados e subtrair de todos os valores não cortados e adicionar a todos os valores cortados duas vezes
void subtractAndAddMin(){
    Node *temp = head;
    int minValue;
    bool firstTime = true;

    //Percorrer a linked list para encontrar o maior valor
    while (temp != NULL) { 
        //Atribuir um valor inicial para o min da linha
        if(firstTime && temp->crossed == false){
            minValue = temp->dataCalc;
            firstTime = false;
        }

        //Se o valor do node atual for menor que o valor minimo, atualize o valor minimo
        if (temp->dataCalc < minValue && temp->crossed == false) {
            minValue = temp->dataCalc;
        }
        //Passar para o proximo node
        temp = temp->next;
    }

    temp = head;

    while (temp != NULL) {
        //Subtrair o valor mínimo de todos os nodes não cortados
        if (temp->crossed == false) {
            temp->dataCalc = temp->dataCalc - minValue;
        }
        //Adicionar o valor mínimo a todos os nodes cortados duas vezes
        if (temp->doubleCrossed == true) {
            temp->dataCalc = temp->dataCalc + minValue;
        }
        //Passar para o proximo node
        temp = temp->next;
    } 
}


//Função do assingment problem
void assingmentProblem(int maxRow, int maxColumn){
    //https://cbom.atozmath.com/example/CBOM/Assignment.aspx?q=hm&q1=MAX
    //O metodo utilizado para resolver o problema de atribuição foi o hungarian method para maximização

    /*
    Breve explicação de como o hungarian method para maximização funciona

    Nota: O algoritmo assume que o número de linhas é igual ao número de colunas
          Se for o caso for o contrario, adicionar linhas ou colunas com valores Nulos

    1. Subtrair o maior valor da matriz por todos os valores ex: 5 - 3 = 2 -> linha 1 coluna 1, 5 - 4 = 1 -> linha 1 coluna 2, 5 - 2 = 3 -> linha 2 coluna 1, 5 - 1 = 4 -> linha 2 coluna 2
    2. Em cada linha, encontrar o menor valor e subtrair de todos os valores da linha
    3. Em cada coluna, encontrar o menor valor e subtrair de todos os valores da coluna
    4. Encontrar o menor número de linhas e colunas que cubram todos os zeros da matriz
    5. Se o número de cortes for igual ao número de linhas, o algoritmo termina
    6. Se o número de cortes for menor que o número de linhas, encontrar o menor valor da matriz que não foi cortado e subtrair de todos os valores não cortados
    7. Repetir os passos 4, 5 e 6 até que o número de cortes seja igual ao número de linhas
    8. O resultado final é a soma dos valores da matriz que estão na mesma linha ou coluna que o valor 0
    */
    int numberOfCuts = 0;

    equalizeDataCalcToData();

    int maxValue = findMaxValue();

    subtractValueFromAll(maxValue);
    subtractMinFromRow(maxRow);
    subtractMinFromColumn(maxColumn);

    //do
    
    while (numberOfCuts != maxRow+1){
        numberOfCuts = findZeros();
        subtractAndAddMin();
        printf("FIM numberOfCuts: %d\n", numberOfCuts);

    } 
     

}

//Função para escolher o que fazer
void chooseWhatToDo() {
    int choice;
    int row;
    int column;
    int newValue;

    printf("\n");
    printListInOrder(head);

    //Imprimir a matriz sempre que o menu for exibido
    printMatrixFromList();

    //Menu para escolher o que fazer
    printf("\nEscolha o que fazer:\n");
    printf("1. Trocar o valor de um elemento\n");
    printf("2. Adicionar uma linha\n");
    printf("3. Adicionar uma coluna\n");
    printf("4. Remover uma linha\n");
    printf("5. Remover uma coluna\n");
    printf("6. Calcular a soma máxima possível\n");
    printf("7. Sair\n");
    printf("Escolha: ");
    scanf("%d", &choice);
    printf("\n");

    //Chamar a função correspondente à escolha do utilizador
    switch (choice) {
        case 1:
            //Perguntar ao utilizador qual valor ele quer trocar e qual valor ele quer atribuir
            printf("Linha: ");
            scanf("%d", &row);
            if (row > maxRow || row < 1){
                printf("Linha inválida.\n");
                break;
            }

            printf("Coluna: ");
            scanf("%d", &column);
            if (column > maxColumn || column < 1){
                printf("Coluna inválida.\n");
                break;
            }

            printf("Novo valor: ");
            scanf("%d", &newValue);

            //A linha e a coluna são subtraídas por 1 porque o utilizador começa a contar a partir de 1, 
            //mas o programa começa a contar a partir de 0
            changeNodeValue(head, (row - 1), (column - 1), newValue);
            break;
        case 2:
            //Adicionar uma linha
            printf("Escolha a linha que deseja adicionar: ");
            scanf("%d", &row);

            if (row > maxRow + 1 || row < 1)
            {
                printf("Linha inválida.\n");
                break;
            }
            addRow(maxColumn, maxRow, row - 1);
            break;
        case 3:
            //Adicionar uma coluna
            printf("Escolha a coluna que deseja adicionar: ");
            scanf("%d", &column);

            if (column > maxColumn + 1 || column < 1)
            {
                printf("Coluna inválida.\n");
                break;
            }
            addColumn(maxColumn, maxRow, column - 1);
            break;
        case 4:
            //Remover uma linha
            printf("Escolha a linha que deseja remover: ");
            scanf("%d", &row);

            if (row - 1 > maxRow || row < 1){
                printf("Linha inválida.\n");
                break;
            }
            removeRow(row - 1);
            break;
        case 5:
            //Remover uma coluna
            printf("Escolha a coluna que deseja remover: ");
            scanf("%d", &column);

            if (column - 1 > maxColumn || column < 1){
                printf("Coluna inválida.\n");
                break;
            }
            removeColumn(column - 1);
            break;
        case 6:
            //Cálculo da soma máxima possível
            assingmentProblem(maxRow, maxColumn);
            break;
        case 7:
            //Sair do programa
            return;
        default:
            //Mensagem de erro caso a escolha seja inválida
            printf("Escolha inválida.\n");
    }
    //Chamar a função novamente para que o utilizador possa escolher o que fazer a seguir
    chooseWhatToDo();
}


//Função main
int main() {
    loadMatrixToList("matriz.txt");
    chooseWhatToDo();
    return 0;
}
