# Tarea_1

Repositorio para la entrega 1 del curso Programación Avanzada.

Este repositorio contiene, entre otros archivos, `Punto_5.cpp` — un programa en C++ que calcula la inversa de una
matriz o, cuando corresponde, intenta calcular la pseudo-inversa por fórmulas algebraicas.

## Contenido relevante
- `Punto_5.cpp` : Implementación en C++ para inversa y pseudo-inversa (uso directo por entrada estándar).
 - `Punto_4.cpp` : Implementación en C++ para cálculo de normas L2 (euclidiana) y L∞ de un arreglo (vector o matriz).

## Cómo compilar
En Windows (PowerShell) con g++ instalado (MinGW-w64 o similar):

```powershell
g++ -std=c++17 -O2 "d:/Prog_Avan/Tarea_1/Punto_5.cpp" -o "d:/Prog_Avan/Tarea_1/Punto_5.exe"
```

Esto genera el ejecutable `d:\Prog_Avan\Tarea_1\Punto_5.exe`.

## Cómo ejecutar

Opción interactiva (ejecución directa):

```powershell
d:\Prog_Avan\Tarea_1\Punto_5.exe
```

El programa pedirá `m n` (filas y columnas) y luego `m*n` números (fila por fila).

Ejemplos rápidos (usar `cmd /c` para piping desde PowerShell):

```powershell
# Matriz 2x2 invertible: [1 2; 3 4]
cmd /c "echo 2 2 1 2 3 4 | d:\Prog_Avan\Tarea_1\Punto_5.exe"

# Matriz 3x2 (pseudo-inversa por A^+ = (A^T A)^{-1} A^T si corresponde)
cmd /c "echo 3 2 1 0 0 1 1 1 | d:\Prog_Avan\Tarea_1\Punto_5.exe"
```

También es posible redirigir desde un archivo de entrada:

```powershell
d:\Prog_Avan\Tarea_1\Punto_5.exe < d:\Prog_Avan\Tarea_1\input.txt
```

Formato de `input.txt` (ejemplo 2x2):

```
2 2
1 2 3 4
```

## Metodología y notas técnicas

El programa usa métodos directos de álgebra lineal básica:

- Inversa de matriz cuadrada (n×n): Gauss-Jordan con pivoteo por magnitud.
	- Se transforma la matriz aumentada `[A | I]` y se reduce A a la identidad; el lado derecho queda como A^{-1}.
	- Si durante el proceso se encuentra un pivote cercano a 0 (umbral EPS = 1e-12), se declara la matriz singular y
		no invertible con este método.

- Pseudo-inversa (caso no cuadrado): el programa intenta fórmulas cerradas cuando las matrices intermedias son invertibles:
	- Si m >= n y A tiene rango completo por columnas: A^+ = (A^T A)^{-1} A^T.
	- Si m <= n y A tiene rango completo por filas: A^+ = A^T (A A^T)^{-1}.
	- El programa intenta estas rutas y, si las matrices `A^T A` o `A A^T` resultan singulares, informa que no pudo calcular la
		pseudo-inversa por estas fórmulas.

- Limitaciones y recomendación:
	- Las fórmulas anteriores requieren rango completo; no cubren el caso general de rango deficiente.
	- Para la pseudo-inversa de Moore–Penrose en todos los casos (incluyendo rango deficiente) y para mayor estabilidad numérica,
		es recomendable usar descomposición en valores singulares (SVD): A = U Σ V^T, y A^+ = V Σ^+ U^T.
	- Bibliotecas recomendadas: Eigen (C++), LAPACK/BLAS, o NumPy/SciPy (Python) para SVD y operaciones robustas.

## Parámetros numéricos
- Umbral para considerar pivotes como cero: `EPS = 1e-12` (se puede ajustar si los datos tienen otras escalas).
- La salida se imprime con 8 decimales por defecto (usar `setprecision` en el código para cambiarlo).

## Posibles mejoras
- Integrar Eigen y usar SVD para calcular la pseudo-inversa de Moore–Penrose de forma estable.
- Añadir manejo de archivos o opciones de línea de comandos para facilitar pruebas.
- Añadir tests automáticos y verificación de condición numérica (número de condición).

---

## Punto_4: normas L2 y L∞ (instrucciones y metodología)

`Punto_4.cpp` calcula la norma L2 (euclidiana) y la norma L∞ (max absoluto) de un arreglo que puede representar un vector o una matriz linealizada.

### Cómo compilar
En Windows (PowerShell) con g++ instalado:

```powershell
g++ -std=c++17 -O2 "d:/Prog_Avan/Tarea_1/Punto_4.cpp" -o "d:/Prog_Avan/Tarea_1/Punto_4.exe"
```

### Cómo ejecutar

Ejecuta el programa (modo interactivo):

```powershell
d:\Prog_Avan\Tarea_1\Punto_4.exe
```

Formato interactivo:
- Primero solicita el tipo: `1` para vector o `2` para matriz.
- Si `1`: solicita `n` (tamaño) y luego `n` valores.
- Si `2`: solicita `r c` y luego `r*c` valores (fila por fila).

Ejemplos rápidos (piping desde PowerShell usando `cmd /c`):

```powershell
# Vector de 3 elementos: [1, -2, 3]
cmd /c "echo 1 3 1 -2 3 | d:\Prog_Avan\Tarea_1\Punto_4.exe"

# Matriz 2x2: [[1,2],[3,4]]
cmd /c "echo 2 2 2 1 2 3 4 | d:\Prog_Avan\Tarea_1\Punto_4.exe"
```

### Qué imprime
- Norma L2 (euclidiana): sqrt(sum_i x_i^2)
- Norma L∞: max_i |x_i|

La salida se imprime con 6 decimales por defecto en `Punto_4.cpp`.

### Metodología y notas técnicas

- El programa lee los datos en un `vector<double>` (matriz linealizada si corresponde) y llama a `compute_norms`.
- `compute_norms` recorre todos los elementos, acumula la suma de cuadrados y mantiene el máximo absoluto.
- Complejidad temporal: O(N) donde N = número de elementos; espacio adicional O(1).

### Casos borde y recomendaciones
- Valida dimensiones positivas; retorna error si n, r o c <= 0.
- Para evitar errores de precisión en sumas de cuadrados con valores muy grandes, considerar técnicas como suma de Kahan o reescalado.
- Añadir validación de NaN/Inf si el origen de datos puede contener valores no finitos.

---
