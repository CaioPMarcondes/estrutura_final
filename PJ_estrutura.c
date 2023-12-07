#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Definição da estrutura do nó da árvore
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Função para criar um novo nó da árvore
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para avaliar a expressão matemática usando a árvore
int evaluateExpression(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    if (isdigit(root->data)) {
        return root->data - '0';
    }

    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        default:
            printf("Operador invalido: %c\n", root->data);
            exit(EXIT_FAILURE);
    }
}

// Função para imprimir a árvore na notação infix
void printInfix(TreeNode* root) {
    if (root != NULL) {
        if (root->left != NULL || root->right != NULL) {
            printf("(");
        }

        printInfix(root->left);
        printf("%c", root->data);
        printInfix(root->right);

        if (root->left != NULL || root->right != NULL) {
            printf(")");
        }
    }
}

// Função para liberar a memória alocada para a árvore
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Função para construir a árvore a partir da expressão fornecida
TreeNode* buildTree(char expression[], int* index) {
    char token = expression[*index];
    (*index)++;

    if (token == '(') {
        TreeNode* root = createNode(expression[*index]);
        (*index)++; // Pular o espaço em branco após o operador
        root->left = buildTree(expression, index);
        (*index)++; // Pular o espaço em branco antes do próximo operando
        root->right = buildTree(expression, index);
        (*index)++; // Pular o ')' no final
        return root;
    } else {
        return createNode(token);
    }
}

int main() {
    char expression[100];
    printf("Digite a expressao matematica: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strlen(expression) - 1] = '\0'; // Remover o '\n' no final da string

    int index = 0;
    TreeNode* tree = buildTree(expression, &index);

    printf("Expressao: ");
    printInfix(tree);
    printf("\nResultado: %d\n\n", evaluateExpression(tree));

    // Liberar memória alocada para a árvore
    freeTree(tree);

    return 0;
}
