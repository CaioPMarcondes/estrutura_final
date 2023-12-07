#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Defini��o da estrutura do n� da �rvore
typedef struct TreeNode {
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Fun��o para criar um novo n� da �rvore
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Fun��o para avaliar a express�o matem�tica usando a �rvore
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

// Fun��o para imprimir a �rvore na nota��o infix
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

// Fun��o para liberar a mem�ria alocada para a �rvore
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// Fun��o para construir a �rvore a partir da express�o fornecida
TreeNode* buildTree(char expression[], int* index) {
    char token = expression[*index];
    (*index)++;

    if (token == '(') {
        TreeNode* root = createNode(expression[*index]);
        (*index)++; // Pular o espa�o em branco ap�s o operador
        root->left = buildTree(expression, index);
        (*index)++; // Pular o espa�o em branco antes do pr�ximo operando
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

    // Liberar mem�ria alocada para a �rvore
    freeTree(tree);

    return 0;
}
