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
    bool isOptimal;

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
    printf("Data: %d, Column: %d, Row: %d, DataCalc:%d, isCrossed:%d ,isdoubleCrossed:%d, isOptimal:%d\n", node->data, node->column, node->row, node->dataCalc, node->crossed, node->doubleCrossed, node->isOptimal);
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

    //Perguntar ao utilizador quais valores ele deseja adicionar à nova linha e adicionar os valores à linked list
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
    
    //Perguntar ao utilizador quais valores ele deseja adicionar à nova coluna e adicionar os valores à linked list
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


//Função para percorrer as linhas e colunas para encontrar zeros
void findZeros(){
    Node *temp = head;
    int numberOfZeros = 0;
    int maxNumberOfZeros = 0;
    int crossCandidate = 0;
    int rowsWithZeros;
    int columnsWithZeros;
    int numberOfCuts;
    int numberOfNewZerosInLine;
    int numberOfNewZerosInColumn;
    int maxNumberOfNewZeros;
    bool haveNewZeros;
    bool inRow = false;
    bool end = false;

    while(end == false){ 

        numberOfCuts = 0; 

        //Fazer cortes até que não haja mais zeros novos
        do{
            maxNumberOfZeros = 0;
            inRow = false;
            rowsWithZeros = 0;
            columnsWithZeros = 0;
            maxNumberOfNewZeros = 0;
            
            //Percorrer as linhas e colunas para encontrar o maior número de zeros e o maior número de zeros novos
            for(int i = 0; i <= maxRow; i++){
                numberOfZeros = 0;
                temp = head;
                numberOfNewZerosInLine = 0;
                haveNewZeros = false;

                while (temp != NULL)
                {
                    //Se o node atual for da linha atual e o valor do node atual for 0
                    if(temp->row == i && temp->dataCalc == 0){
                        //Se o node foi cortado, adicione o valor do node ao valor do node
                        if (temp->crossed == false){
                            //Tem novos zeros
                            haveNewZeros = true;
                            //Incrementar o número de zeros novos
                            numberOfNewZerosInLine++;
                        }
                        //Incrementar o número de zeros
                        numberOfZeros++;
                    }
                    temp = temp->next;
                }
 
                //Se o número de zeros da linha atual for maior que o número máximo de zeros e houver novos zeros
                if (numberOfZeros > maxNumberOfZeros && haveNewZeros == true && numberOfNewZerosInLine > maxNumberOfNewZeros){ 
                    //Atualize o número máximo de zeros, o número máximo de zeros novos, o candidato a corte e se o corte é na linha   
                    maxNumberOfZeros = numberOfZeros;
                    maxNumberOfNewZeros = numberOfNewZerosInLine;
                    crossCandidate = i;
                    inRow = true;
                }

                //Se houver zeros na linha atual
                if(numberOfZeros > 0){
                    rowsWithZeros++;
                }
            }

            //Percorrer as colunas para encontrar o maior número de zeros e o maior número de zeros novos
            for(int i = 0; i <= maxColumn; i++){
                numberOfZeros = 0;
                temp = head;
                haveNewZeros = false; 
                numberOfNewZerosInColumn = 0;

                while (temp != NULL)
                {
                    //Se o node atual for da coluna atual e o valor do node atual for 0
                    if(temp->column == i && temp->dataCalc == 0){
                        //Se o node foi cortado, adicione o valor do node ao valor do node
                        if (temp->crossed == false){
                            //Tem novos zeros
                            haveNewZeros = true; 
                            //Incrementar o número de zeros novos
                            numberOfNewZerosInColumn++;
                        }
                        //Incrementar o número de zeros
                        numberOfZeros++;
                    }
                    temp = temp->next;
                }

                //Se o número de zeros da coluna atual for maior que o número máximo de zeros e houver novos zeros
                if (numberOfZeros > maxNumberOfZeros && haveNewZeros == true && numberOfNewZerosInColumn >= maxNumberOfNewZeros){
                    //Atualize o número máximo de zeros, o número máximo de zeros novos, o candidato a corte e se o corte é na coluna
                    maxNumberOfZeros = numberOfZeros;
                    maxNumberOfNewZeros = numberOfNewZerosInColumn;
                    crossCandidate = i;
                    inRow = false;
                }
                
                //Se houver zeros na coluna atual
                if(numberOfZeros > 0){
                    columnsWithZeros++;
                }
            }

            //Se o número máximo de zeros for maior que 0
            if(maxNumberOfNewZeros > 0){
                temp = head;
                //Incrementar o número de cortes
                numberOfCuts++;             
                
                //printf("Corte na %s nº %d com %d zeros %d são novos.\n" , inRow ? "Linha" : "coluna", crossCandidate + 1, maxNumberOfZeros, inRow ? numberOfNewZerosInLine : numberOfNewZerosInColumn);
                
                while (temp != NULL)
                {
                    //Cortar todos os nodes da linha ou coluna do node que foi selecionado
                    if(inRow == true){
                        //Se o node atual for da linha do node que foi selecionado
                        if(temp->row == crossCandidate){
                            //Se o node foi cortado, cortar outra vez
                            if(temp->crossed == true){
                                temp->doubleCrossed = true;
                            //Se o node não foi cortado, cortar
                            }else{
                                temp->crossed = true;
                            }
                        }
                    }else{
                        //Se o node atual for da coluna do node que foi selecionado
                        if(temp->column == crossCandidate){
                            //Se o node foi cortado, cortar outra vez
                            if(temp->crossed == true){
                                temp->doubleCrossed = true;
                            //Se o node não foi cortado, cortar
                            }else{
                                temp->crossed = true;
                            }
                        }
                    }
                    temp = temp->next;
                }
            } 
        //Se o número de cortes for igual ao número de linhas, o algoritmo termina
        }while (numberOfNewZerosInColumn > 0 || numberOfNewZerosInLine > 0);
        
        //printf("zeros por Linhas: %d - zeros por colunas: %d - nº cortes: %d \n", rowsWithZeros, columnsWithZeros, numberOfCuts);
        //printf("Max linha: %d - Max coluna: %d\n", maxRow, maxColumn);
        
        subtractAndAddMin();

        //Se todas as colunas e linhas tiverem zeros e o número de cortes for igual ao número de linhas, o algoritmo termina
        if (rowsWithZeros == maxRow + 1 && columnsWithZeros == maxColumn + 1 && numberOfCuts == maxRow + 1)
        {    
            end = true;
        }

        //limpar crossed e doubleCrossed
        temp = head;
        while(temp != NULL){
            temp->crossed = false;
            temp->doubleCrossed = false;
            temp = temp->next;
        }
    }
}


//Função para selecionar os zeros para encontrar a soma máxima possível
void selectZeros(){
    Node *temp = head;
    int minNumberOfZeros; 
    int numberOfZeros;
    int rowIndex = 0;
    int columnIndex = 0;
    int value;
    int optimalValues = 0;

    //limpar crossed, doubleCrossed e isOptimal
    while (temp != NULL)
    {
        temp->crossed = false;
        temp->doubleCrossed = false;
        temp->isOptimal = false; 
        temp = temp->next;
    }

    while(optimalValues < maxRow + 1)
    { 
        printListInOrder(head);
        minNumberOfZeros = 99;
        value = 0;

        //Percorrer a linked list para encontrar o menor número de zeros
        for(int i = 0; i <= maxRow; i++){
            numberOfZeros = 0;

            temp = head;
            while(temp != NULL){
                if(temp->row == i && temp->dataCalc == 0 && temp->crossed == false){
                    numberOfZeros++;
                }
                temp = temp->next;
            }

            //Se o número de zeros da linha atual for menor que o número mínimo de zeros, atualize o número mínimo de zeros
            if(numberOfZeros < minNumberOfZeros && numberOfZeros > 0){
                minNumberOfZeros = numberOfZeros;
                //Guardar o indice da linha com o menor número de zeros
                rowIndex = i;
            }
        }

        //Se o número mínimo de zeros for 1
        if(minNumberOfZeros == 1){

            temp = head;
            while(temp != NULL){
                //Se o node atual for da linha com o menor número de zeros
                if(temp->row == rowIndex){
                    //Se o valor do node atual for 0 e o node não foi cortado
                    if (temp->dataCalc == 0 && temp->crossed == false){
                        //Encontramos um dos valores ótimos
                        temp->isOptimal = true;
                        //Guardar a coluna do node atual
                        columnIndex = temp->column;
                        optimalValues++;
                    }
                    //Cortar o node da linha com o menor número de zeros
                    temp->crossed = true;
                }  
                temp = temp->next;
            }

            temp = head;
            while(temp != NULL){
                //Cortar todos os nodes da coluna do node que foi selecionado
                if(temp->column == columnIndex){
                    temp->crossed = true;
                }
                temp = temp->next;
            }
        //Se o número mínimo de zeros for maior que 1, temos de encontrar o maior valor da linha com o menor número de zeros
        }else{
            temp = head;
            while(temp != NULL){
                //Se o node atual for da linha com o menor número de zeros, não foi cortado e o valor do node atual for 0
                if(temp->row == rowIndex && temp->crossed == false && temp->dataCalc == 0){
                    //Se o valor do node atual for maior que o valor guardado
                    if(temp->data > value){
                        //Atualizar o valor guardado
                        value = temp->data;
                        //Guardar a coluna do node atual
                        columnIndex = temp->column;
                    }
                }
                temp = temp->next;
            }

            temp = head;
            while(temp != NULL){
                //Cortar o node da linha com o menor número de zeros
                if(temp->row == rowIndex){
                    //Se o node atual for da coluna do node que foi selecionado
                    if(temp->column == columnIndex){
                        //Encontramos um dos valores ótimos
                        temp->isOptimal = true;
                        optimalValues++;
                    }
                    temp->crossed = true;
                }
                //Cortar todos os nodes da coluna do node que foi selecionado
                if(temp->column == columnIndex){
                    temp->crossed = true;
                }
                temp = temp->next;
            }
        }
    }
}


//Função do assingment problem
void assingmentProblem(){
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
    int cutsNeeded = 0;

    //Se o número de linhas for diferente do número de colunas, adicionar linhas ou colunas com valores Nulos no final da matriz
    //Para que o número de linhas seja igual ao número de colunas
    if (maxRow != maxColumn)
    {
        //Se o número de linhas for maior que o número de colunas, adicionar colunas com valores Nulos
        if (maxRow > maxColumn)
        {
            //i < (maxRow - maxColumn) para adicionar o número de colunas necessárias para que o número de linhas seja igual ao número de colunas
            for (int i = 0; i < (maxRow - maxColumn); i++)
            {   
                //j <= maxRow para adicionar o número de elementos necessarios para que o número de elementos na nova row seja igual ao número de elementos nas colunas existentes
                for (int j = 0; j <= maxRow; j++)
                {
                    //Alocar espaço para o novo node
                    Node *newNode = (Node*) malloc(sizeof(Node));

                    //Atribuir os valores ao novo node
                    newNode->data = 0; //Numero 
                    newNode->column = maxColumn + i + 1; //Coluna
                    newNode->row = j; //Linha
                    newNode->dataCalc = 0; //Valor calculado para o problema de atribuição
                    newNode->crossed = false; //Variavel para verificar se o node foi cortado
                    newNode->doubleCrossed = false; //Variavel para verificar se o node foi cortado duas vezes
                    newNode->next = head; //Apontar para o proximo node
                    head = newNode; //Atualizar a head para apontar para o novo node
                }
            }
            //Quando o número de colunas for igual ao número de linhas, atualize o número máximo de colunas
            maxColumn = maxRow;
        }
        //Se o número de colunas for maior que o número de linhas, adicionar linhas com valores Nulos
        else if (maxColumn > maxRow)
        {
            //i < (maxColumn - maxRow) para adicionar o número de linhas necessárias para que o número de linhas seja igual ao número de colunas
            for (int i = 0; i < (maxColumn - maxRow); i++)
            {
                //j <= maxColumn para adicionar o número de elementos necessarios para que o número de elementos na nova coluna seja igual ao número de elementos nas colunas existentes
                for (int j = 0; j <= maxColumn; j++)
                {
                    //Alocar espaço para o novo node
                    Node *newNode = (Node*) malloc(sizeof(Node));

                    //Atribuir os valores ao novo node
                    newNode->data = 0; //Numero 
                    newNode->column = j; //Coluna
                    newNode->row = maxRow + i + 1; //Linha
                    newNode->dataCalc = 0; //Valor calculado para o problema de atribuição
                    newNode->crossed = false; //Variavel para verificar se o node foi cortado
                    newNode->doubleCrossed = false; //Variavel para verificar se o node foi cortado duas vezes
                    newNode->next = head; //Apontar para o proximo node
                    head = newNode; //Atualizar a head para apontar para o novo node
                }
            }
            //Quando o número de linhas for igual ao número de colunas, atualize o número máximo de linhas
            maxRow = maxColumn;
        }
    }

    cutsNeeded = maxRow + 1;

    equalizeDataCalcToData();

    int maxValue = findMaxValue();

    subtractValueFromAll(maxValue);
    subtractMinFromRow(maxRow);
    subtractMinFromColumn(maxColumn);
    
    findZeros();

  
    selectZeros();

    int somaMaxima = 0;
    //Imprimir os numeros da soma máxima possível
    Node *temp = head;
    while(temp != NULL){
        if(temp->isOptimal == true){
            somaMaxima += temp->data;
            printf("Valor: %d, Linha: %d, Coluna: %d\n", temp->data, temp->row + 1, temp->column + 1);
        }
        temp = temp->next;
    }
    printf("Soma máxima possível: %d\n", somaMaxima);

}

//Função para escolher o que fazer
void chooseWhatToDo() {
    int choice;
    int row;
    int column;
    int newValue;

    printf("\n");
    //printListInOrder(head);

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
            if (row - 1 > maxRow || row < 1){
                printf("Linha inválida.\n");
                break;
            }

            printf("Coluna: ");
            scanf("%d", &column);
            if (column - 1> maxColumn || column < 1){
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

            //Row - 1 porque o utilizador começa a contar a partir de 1, mas o programa começa a contar a partir de 0
            //Row + 1 para poder adicionar uma linha após a última linha
            if (row - 1 > maxRow + 1 || row < 1)
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

            //Column - 1 porque o utilizador começa a contar a partir de 1, mas o programa começa a contar a partir de 0
            //Column + 1 para poder adicionar uma coluna após a última coluna
            if (column - 1 > maxColumn + 1 || column < 1)
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
            assingmentProblem();
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
