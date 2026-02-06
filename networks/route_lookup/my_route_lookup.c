#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include <stdbool.h>

static int contadorNodos = 1;

// Estructura para representar un nodo del árbol binario
typedef struct Node {
    struct Node *left; // Puntero al hijo izquierdo
    struct Node *right; // Puntero al hijo derecho
    uint32_t prefix; // Prefijo de red
    int prefixLength; // Longitud del prefijo
    int outInterface; // Interfaz de salida
    int bitD;
} Node;

// Función para crear un nuevo nodo del árbol
static Node* createNode(int depthBit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error al asignar memoria para el nodo del árbol.\n");
        exit(1);
    }
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->prefix = 0;
    newNode->prefixLength = -1;
    newNode->outInterface = 0;
    newNode->bitD = depthBit;
    return newNode;
}

// Función para insertar una ruta en el Trie Patricia
void insertNode(Node **root, uint32_t prefix, int prefixLength, int outInterface) {
    if (*root == NULL) {
        // Creamos la raíz (profundidad 0)
        *root = createNode(0);
    }

    Node *actual = *root;

    // Ruta por defecto (/0)
    if (prefixLength == 0) {
        actual->prefix = prefix;
        actual->prefixLength = prefixLength;
        actual->outInterface = outInterface;
        return;
    }

    for (int i = 0; i < prefixLength; i++) {
        int bit = (prefix >> (32 - i - 1)) & 1;
        if (bit == 0) {
            if (actual->left == NULL) {
                actual->left = createNode(i + 1);
                contadorNodos++;
            }
            actual = actual->left;
        } else if (bit == 1) {
            if (actual->right == NULL) {
                actual->right = createNode(i + 1);
                contadorNodos++;
            }
            actual = actual->right;
        }
    }

    // Guardar la ruta en el nodo final
    actual->prefix = prefix;
    actual->prefixLength = prefixLength;
    actual->outInterface = outInterface;

}

// Función para buscar la interfaz de salida correspondiente a una dirección IP
int searchInterface(Node *root, uint32_t ipAddress, int *accessesNodes) {

    *accessesNodes = 0; // Inicializar el contador de accesos a nodos

    if (root == NULL) {
        return 0; // Si el árbol está vacío, no hay coincidencia
    }   

    int bestInterface = 0;
    int bestLength = -1;

    Node *current = root;
    int prevBit = -1;

    while (current != NULL) {
        (*accessesNodes)++;

        if (current->outInterface != 0 && current->prefixLength >= 0) {
            if (current->prefixLength == 0) {
                if (0 > bestLength) {
                    bestLength = 0;
                    bestInterface = current->outInterface;
                }
            } else {
                uint32_t mask = (current->prefixLength == 32) ? 0xFFFFFFFFu : (0xFFFFFFFFu << (32 - current->prefixLength));
                if ((current->prefix & mask) == (ipAddress & mask)) {
                    if (current->prefixLength > bestLength) {
                        bestLength = current->prefixLength;
                        bestInterface = current->outInterface;
                    }
                }
            }
        }

        if (current->bitD >= 32) {
            break;
        }
        if (current->bitD <= prevBit) {
            break;
        }

        int bit = (ipAddress >> (31 - current->bitD)) & 1;
        prevBit = current->bitD;
        current = bit ? current->right : current->left;
    }

    return bestInterface;
}


//COMPRIMIR ARBOL BINARIO 

// Función para comprimir el árbol trie
void comprimir_arbol(Node **raiz) {
    Node *temp = *raiz;

    if (temp == NULL) {
        return; // Si el nodo es nulo, no hay nada que comprimir, así que se retorna
    }

    // Si el nodo no contiene una ruta y tiene un único hijo, se comprime
    if (temp->outInterface == 0 && temp->prefixLength < 0 && temp->left != NULL && temp->right == NULL) {
        Node *hijo_cero = temp->left;
        if ((hijo_cero->left == NULL && hijo_cero->right != NULL) || (hijo_cero->left != NULL && hijo_cero->right == NULL)) {
            hijo_cero->bitD = temp->bitD;
        } //sis solo tiene un nieto
        free(temp); // Liberar el nodo actual
        *raiz = hijo_cero; // Asignar el hijo izquierdo como nueva raíz
        comprimir_arbol(raiz); // Llamar recursivamente para comprimir más nodos
        contadorNodos--;
    } 
    // Si el nodo tiene un hijo derecho único y su interfaz es 0, se comprime
    else if (temp->outInterface == 0 && temp->prefixLength < 0 && temp->left == NULL && temp->right != NULL) {
        Node *hijo_uno = temp->right;
        if ((hijo_uno->left == NULL && hijo_uno->right != NULL) || (hijo_uno->left != NULL && hijo_uno->right == NULL)) {
            hijo_uno->bitD = temp->bitD;
        }
        free(temp); // Liberar el nodo actual
        *raiz = hijo_uno; // Asignar el hijo derecho como nueva raíz
        comprimir_arbol(raiz); // Llamar recursivamente para comprimir más nodos
        contadorNodos--;
    } 
    // Si el nodo no es comprimible, se llama recursivamente a la función para los subárboles izquierdo y derecho
    else {
        comprimir_arbol(&(temp->left));
        comprimir_arbol(&(temp->right));
    }
}


void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

char* prefixToBinary(uint32_t prefix, int prefixLength) {
    char* binaryPrefix = (char*)malloc(33 * sizeof(char)); // 32 bits + '\0'
    if (binaryPrefix == NULL) {
        printf("Error al asignar memoria para la representación binaria del prefijo.\n");
        exit(1);
    }
    binaryPrefix[32] = '\0'; // Terminador de cadena

    for (int i = 0; i < 32; i++) {
        if (i < prefixLength) {
            // Extraer el i-ésimo bit del prefijo y agregarlo a la cadena binaria
            uint32_t bit = (prefix >> (31 - i)) & 1;
            binaryPrefix[i] = bit + '0';
        } else {
            // Rellenar con ceros si la longitud del prefijo es menor que 32 bits
            binaryPrefix[i] = '0';
        }
    }
    return binaryPrefix;
}

int main(int argc, char *argv[]) {
    int control;
    uint32_t prefijo, direccionIP;
    int longitudPrefijo, interfazSalida;
    int paquetesProcesados = 0;
    double totalAccesosNodo = 0;
    double tiempoTotalProcesamiento = 0;
    Node *root = NULL;
    
    if (argc != 3) {
        printf("Uso: %s FIB InputPacketFile\n", argv[0]);
        return 1;
    }
    
    control = initializeIO(argv[1], argv[2]);
    
    // Verificar si ocurrió un error en la inicialización
    if (control != OK) {
        printIOExplanationError(control); // Imprimir mensaje de error
    } else {
        // Leer las rutas de la tabla de enrutamiento y construir el árbol trie
        do {
            control = readFIBLine(&prefijo, &longitudPrefijo, &interfazSalida);
            if (control == OK) {
                insertNode(&root, prefijo, longitudPrefijo, interfazSalida);
            }
        } while (control == OK);

        // Comprimir el árbol después de insertar todas las rutas
        comprimir_arbol(&root);

        // Procesar los paquetes de entrada
        do {
            control = readInputPacketFileLine(&direccionIP); // Leer la dirección IP del paquete
            if (control != OK)
                break;

            struct timespec tiempoInicial, tiempoFinal;
            int numAccesses;
            double tiempoBusqueda;

            clock_gettime(CLOCK_MONOTONIC_RAW, &tiempoInicial); // Iniciar el temporizador

            int interfazSalidaEncontrada = searchInterface(root, direccionIP, &numAccesses); // Buscar la ruta en el árbol trie

            clock_gettime(CLOCK_MONOTONIC_RAW, &tiempoFinal); // Detener el temporizador

            // Calcular el tiempo de búsqueda en nanosegundos
            tiempoBusqueda = (tiempoFinal.tv_sec - tiempoInicial.tv_sec) * 1e9 + (tiempoFinal.tv_nsec - tiempoInicial.tv_nsec);

            // Actualizar los contadores de estadísticas
            paquetesProcesados++;
            totalAccesosNodo += numAccesses;
            tiempoTotalProcesamiento += tiempoBusqueda;

            // Imprimir la línea de salida con los resultados del paquete procesado
            printOutputLine(direccionIP, interfazSalidaEncontrada, &tiempoInicial, &tiempoFinal, &tiempoBusqueda, numAccesses);
        } while (control == OK);

        // Imprimir el resumen de estadísticas
        printSummary(contadorNodos, paquetesProcesados, totalAccesosNodo / paquetesProcesados, tiempoTotalProcesamiento / paquetesProcesados);
    }

    // Liberar la memoria y finalizar el programa
    freeTree(root);
    freeIO();
    return 0;
}


