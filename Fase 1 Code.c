// Lucas Alves - Projeto 1 - Estruturas de dados avançadas 

//Bibliotecas
#include<stdio.h>
#include <string.h>


/*Explicação de algumas variaveis
    data = Numero da matriz
    column = Coluna da matriz
    row = Linha da matriz
    head = Apontador para o 1º node da linked list
    next = Apontador para o proximo node
    newNode = Novo node a ser adicionado na linked list
    temp = Node temporario para percorrer a linked list
    filename = Nome do ficheiro que contem a matriz
    file = Ficheiro que contem a matriz
    line = Linha do ficheiro
    maxRow = Numero maximo de linhas
    maxColumn = Numero maximo de colunas
    choice = Escolha do utilizador
    newValue = Novo valor a ser atribuido ao node
    newRow = Nova linha a ser adicionada
    newColumn = Nova coluna a ser adicionada
    rowIndex = Indice da linha a ser removida
    columnIndex = Indice da coluna a ser removida
    i = Variavel de controle para loops
*/

//Constituição do node da linked list
typedef struct Node {
    //Damos os tipos de dados que queremos obter neste caso o numero e a sua posição na matriz
    int data;
    int column;
    int row;

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

    printf("Data: %d, Column: %d, Row: %d\n", node->data, node->column, node->row);
}


//Variaveis para armazenar o número máximo de linhas e colunas
int maxRow = 0;
int maxColumn = 0;

//Função para imprimir a matriz a partir da linked list
int printMatrixFromList() {
    // Primeiro, percorrer a linked list para encontrar o número máximo de linhas e colunas
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

    // Agora, para cada linha e coluna, encontre o node correspondente e imprima-o
    for (int i = 0; i <= maxRow; i++) {
        for (int j = 0; j <= maxColumn; j++) {
            temp = head;
            // Percorrer a linked list para encontrar o node correspondente
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
void addRow(int maxColumn, int maxRow) {
    int newValueForNewLine;
    //Perguntar ao usuario quais valores ele deseja adicionar à nova linha e adicionar os valores à linked list
    for  (int i = 0; i <= maxColumn; i++) {
        printf("Indique o %dº valor da nova linha: ", (i+1));
        scanf("%d", &newValueForNewLine);

        //Alocar espaço para o novo node
        Node *newNode = (Node*) malloc(sizeof(Node));

        //Atribuir os valores ao novo node
        newNode->data = newValueForNewLine; //Numero 
        newNode->column = i; //Coluna
        newNode->row = maxRow + 1; //Linha
        newNode->next = head; //Apontar para o proximo node
        head = newNode; //Atualizar a head para apontar para o novo node
    }
}


//Função para escolher o que fazer
void chooseWhatToDo() {
    int choice;
    int row;
    int column;
    char newValue[4]; // Array para armazenar até 3 dígitos e o caractere nulo '\0'
    int newValueInt;

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

            printf("Novo valor até 3 digitos: ");
            fgets(newValue, sizeof(newValue), stdin);
            // Remover o '\n' que fgets adiciona no final da string
            newValue[strcspn(newValue, "\n")] = 0;
            if (atoi(newValue) < 0 || atoi(newValue) > 999){
                printf("Valor inválido.\n");
                break;
            }
            newValueInt = atoi(newValue);

            //A linha e a coluna são subtraídas por 1 porque o utilizador começa a contar a partir de 1, 
            //mas o programa começa a contar a partir de 0
            changeNodeValue(head, (row - 1), (column - 1), newValueInt);
            break;
        case 2:
            //Adicionar uma linha
            addRow(maxColumn, maxRow);
            break;
        case 3:
            //Adicionar uma coluna

            break;
        case 4:
            //Remover uma linha
         
            break;
        case 5:
            //Remover uma coluna
            
            break;
        case 6:
            //Cálculo da soma máxima possível
            
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
    //printListInOrder(head);
    chooseWhatToDo();
    return 0;
}
