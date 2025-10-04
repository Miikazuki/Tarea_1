#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;

void print_matrix(const vector<vector<double>>& M) {
    int r = M.size();
    int c = r ? M[0].size() : 0;
    cout.setf(std::ios::fixed); cout<<setprecision(8);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << M[i][j];
            if (j+1 < c) cout << '\t';
        }
        cout << '\n';
    }
}

vector<vector<double>> transpose(const vector<vector<double>>& A) {
    if (A.empty()) return {};
    int m = A.size(), n = A[0].size();
    vector<vector<double>> B(n, vector<double>(m));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            B[j][i] = A[i][j];
    return B;
}

vector<vector<double>> mul(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    if (A.empty() || B.empty()) return {};
    int m = A.size(), p = A[0].size();
    int p2 = B.size(), n = B[0].size();
    if (p != p2) return {};
    vector<vector<double>> C(m, vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i)
        for (int k = 0; k < p; ++k) {
            double aik = A[i][k];
            for (int j = 0; j < n; ++j)
                C[i][j] += aik * B[k][j];
        }
    return C;
}

bool gauss_jordan_invert(vector<vector<double>> A, vector<vector<double>>& inv) {
    int n = A.size();
    if (n == 0) return false;
    for (auto &row : A) if ((int)row.size() != n) return false;

    inv.assign(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) inv[i][i] = 1.0;

    for (int col = 0; col < n; ++col) {
        // encontrar pivote
        int sel = col;
        for (int i = col; i < n; ++i) if (fabs(A[i][col]) > fabs(A[sel][col])) sel = i;
        if (fabs(A[sel][col]) < EPS) return false; // singular
        swap(A[sel], A[col]);
        swap(inv[sel], inv[col]);

        double pivot = A[col][col];
        // normalizar
        for (int j = 0; j < n; ++j) { A[col][j] /= pivot; inv[col][j] /= pivot; }

        // eliminar
        for (int i = 0; i < n; ++i) if (i != col) {
            double factor = A[i][col];
            if (fabs(factor) < EPS) continue;
            for (int j = 0; j < n; ++j) {
                A[i][j] -= factor * A[col][j];
                inv[i][j] -= factor * inv[col][j];
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Calculadora de inversa / pseudo-inversa (entrada directa)\n";
    cout << "Modo de uso: ingrese m n seguido de m*n numeros (fila por fila).\n";
    cout << "Ejemplo (2x2 invertible):\n  2 2 1 2 3 4\n";
    cout << "Ejemplo (3x2 pseudo-inversa):\n  3 2 1 0 0 1 1 1\n";
    cout << "Ingrese filas (m) y columnas (n) separadas por espacio: ";
    int m,n;
    if (!(cin >> m >> n)) {
        cerr << "Entrada invalida. Terminando.\n";
        return 1;
    }
    if (m <= 0 || n <= 0) {
        cerr << "Dimensiones deben ser positivas.\n";
        return 1;
    }

    vector<vector<double>> A(m, vector<double>(n));
    cout << "Ingrese los " << (m*n) << " elementos (fila por fila), separadas por espacios o saltos de linea:\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
                if (!(cin >> A[i][j])) {
                cerr << "Lectura de elementos fallo.\n";
                return 1;
            }
        }
    }

    cout << "\nMatriz A ("<<m<<"x"<<n<<"):\n";
    print_matrix(A);

    if (m == n) {
        vector<vector<double>> inv;
        bool ok = gauss_jordan_invert(A, inv);
        if (ok) {
            cout << "\nLa matriz es cuadrada e invertible. Inversa A^{-1}:\n";
            print_matrix(inv);
        } else {
            cout << "\nLa matriz cuadrada NO es invertible (singular)." << '\n';
            cout << "Razon: durante Gauss-Jordan se encontro un pivote cercano a cero -> determinante ~ 0." << '\n';
            cout << "Para obtener una pseudo-inversa en casos singulares se requiere descomposicion SVD," << '\n';
            cout << "que no esta implementada en este programa.\n";
        }
    } else {
        // No cuadrada: Intenta Moore-Penrose usando (A^T A)^{-1} A^T o A^T (A A^T)^{-1}
        auto AT = transpose(A);
        // Primero probar si tiene rango completo por columnas (m >= n): inv(A^T * A) * A^T
        if (m >= n) {
            auto ATA = mul(AT, A); // n x n
            vector<vector<double>> invATA;
            bool ok = gauss_jordan_invert(ATA, invATA);
            if (ok) {
                auto pinv = mul(invATA, AT); // n x m
                cout << "\nMatriz no cuadrada (m >= n). Se calculó pseudo-inversa A^+ = (A^T A)^{-1} A^T\n";
                print_matrix(pinv);
            } else {
                // probar la otra formula si es posible
                if (n > m) {
                    // Se manejara abajo
                }
                // Intenta A*A^T
                auto AAT = mul(A, AT); // m x m
                vector<vector<double>> invAAT;
                bool ok2 = gauss_jordan_invert(AAT, invAAT);
                if (ok2) {
                    auto pinv = mul(AT, invAAT); // n x m
                    cout << "\nMatriz no cuadrada. Se calculo pseudo-inversa alternativa A^+ = A^T (A A^T)^{-1\n";
                    print_matrix(pinv);
                } else {
                    cout << "\nNo fue posible calcular la pseudo-inversa por formulas (A^T A)^{-1} A^T ni A^T (A A^T)^{-1).\n";
                    cout << "Probablemente la matriz es de rango deficiente. Se requiere SVD para una pseudo-inversa general.\n";
                }
            }
        } else { // m < n
            // Caso m < n
            auto AAT = mul(A, AT); // m x m
            vector<vector<double>> invAAT;
            bool ok = gauss_jordan_invert(AAT, invAAT);
            if (ok) {
                auto AT = transpose(A);
                auto pinv = mul(AT, invAAT); // n x m
                cout << "\nMatriz no cuadrada (m < n). Se calculo pseudo-inversa A^+ = A^T (A A^T)^{-1\n";
                print_matrix(pinv);
            } else {
                // probar la otra fórmula
                auto AT = transpose(A);
                auto ATA = mul(AT, A);
                vector<vector<double>> invATA;
                bool ok2 = gauss_jordan_invert(ATA, invATA);
                if (ok2) {
                    auto pinv = mul(invATA, AT);
                    cout << "\nMatriz no cuadrada. Se calculo pseudo-inversa alternativa A^+ = (A^T A)^{-1} A^T\n";
                    print_matrix(pinv);
                } else {
                    cout << "\nNo fue posible calcular la pseudo-inversa por formulas (A^T A)^{-1} A^T ni A^T (A A^T)^{-1).\n";
                    cout << "Probablemente la matriz es de rango deficiente. Se requiere SVD para una pseudo-inversa general.\n";
                }
            }
        }
    }

    return 0;
}
