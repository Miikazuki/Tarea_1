#include <stdio.h>
#include "Operaciones.h"

int main() {
    // Variables para las operaciones
    int num1, num2;
    int opcion;
    int resultado;
    
    printf("=== CALCULADORA CON OPERACIONES BASICAS ===\n");
    printf("Ingrese el primer numero: ");
    scanf("%d", &num1);
    
    printf("Ingrese el segundo numero: ");
    scanf("%d", &num2);
    
    printf("\nSeleccione una operacion:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicacion\n");
    printf("4. Todas las operaciones\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    
    printf("\n=== RESULTADOS ===\n");
    
    switch(opcion) {
        case 1:
            resultado = suma(num1, num2);
            printf("%d + %d = %d\n", num1, num2, resultado);
            break;
            
        case 2:
            resultado = resta(num1, num2);
            printf("%d - %d = %d\n", num1, num2, resultado);
            break;
            
        case 3:
            resultado = multiplicacion(num1, num2);
            printf("%d * %d = %d\n", num1, num2, resultado);
            break;
            
        case 4:
            printf("%d + %d = %d\n", num1, num2, suma(num1, num2));
            printf("%d - %d = %d\n", num1, num2, resta(num1, num2));
            printf("%d * %d = %d\n", num1, num2, multiplicacion(num1, num2));
            break;
            
        default:
            printf("Opción no válida.\n");
            return 1;
    }
    
    return 0;
}