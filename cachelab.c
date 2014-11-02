// ICS Lab 8: Cache

void transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, l, p, q, r, s;
    int a, b, c, d;
    (void) i;
    (void) j;
    (void) k;
    (void) l;
    (void) p;
    (void) q;
    (void) r;
    (void) s;

    #define w1 16
    #define h1 8
    #define w2 8
    #define h2 8
    #define w3 2
    #define h3 2
    #define x (i + k + p)
    #define y (j + l + q)
    #define x1 8
    #define x2 4

    if (M != N || (M & 7) != 0 || (N & 7) != 0) {
        // case: not completely aligned
        //       simple and unstable solution
        for (i = 0; i < N; i += w1) {
        for (j = 0; j < M; j += h1) {
        for (k = 0; k < w1; k += w2) {
        for (l = 0; l < h1; l += h2) {
        for (p = 0; p < w2; p += w3) {
        for (q = 0; q < h2; q += h3) {
            if (x     < N && y     < M) a = A[x    ][y    ];
            if (x     < N && y + 1 < M) b = A[x    ][y + 1];
            if (x + 1 < N && y     < M) c = A[x + 1][y    ];
            if (x + 1 < N && y + 1 < M) d = A[x + 1][y + 1];
            if (y     < M && x     < N) B[y    ][x    ] = a;
            if (y     < M && x + 1 < N) B[y    ][x + 1] = c;
            if (y + 1 < M && x     < N) B[y + 1][x    ] = b;
            if (y + 1 < M && x + 1 < N) B[y + 1][x + 1] = d;
        }
        }
        }
        }
        }
        }
    } else {
        // case: completely aligned
        //       stable solution with special optimization
        for (i = 0; i < N; i += x1) {
        for (j = 0; j < M; j += x1) {
            if (i == j) {
                // diagonal
                p = (i + x1) % M;
                q = j;

                for (k = 0;  k < x1;     ++k) {
                for (l = 0;  l < x1;     ++l) {
                    B[q + k][p + l] = A[i + k][j + l];
                }
                }

                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[j + k][i + l] = B[q + l][p + k];
                }
                }
                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[j + k][x2 + i + l] = B[q + l][x2 + p + k];
                }
                }
                for (k = 0;  k < x2;     ++k) {
                    a = B[j + k][x2 + i    ];
                    b = B[j + k][x2 + i + 1];
                    c = B[j + k][x2 + i + 2];
                    d = B[j + k][x2 + i + 3];
                    B[j + k][x2 + i    ] = B[x2 + q    ][p + k];
                    B[j + k][x2 + i + 1] = B[x2 + q + 1][p + k];
                    B[j + k][x2 + i + 2] = B[x2 + q + 2][p + k];
                    B[j + k][x2 + i + 3] = B[x2 + q + 3][p + k];
                    B[x2 + j + k][i    ] = a;
                    B[x2 + j + k][i + 1] = b;
                    B[x2 + j + k][i + 2] = c;
                    B[x2 + j + k][i + 3] = d;
                }
                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[x2 + j + k][x2 + i + l] = B[x2 + q + l][x2 + p + k];
                }
                }
            }
        }
        }

        for (j = 0; j < M; j += x1) {
        for (i = 0; i < N; i += x1) {
            if (i != j) {
                // non-diagonal
                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[j + k][i + l] = A[i + l][j + k];
                }
                }
                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[j + k][x2 + i + l] = A[i + l][x2 + j + k];
                }
                }
                for (k = 0;  k < x2;     ++k) {
                    a = B[j + k][x2 + i    ];
                    b = B[j + k][x2 + i + 1];
                    c = B[j + k][x2 + i + 2];
                    d = B[j + k][x2 + i + 3];
                    B[j + k][x2 + i    ] = A[x2 + i    ][j + k];
                    B[j + k][x2 + i + 1] = A[x2 + i + 1][j + k];
                    B[j + k][x2 + i + 2] = A[x2 + i + 2][j + k];
                    B[j + k][x2 + i + 3] = A[x2 + i + 3][j + k];
                    B[x2 + j + k][i    ] = a;
                    B[x2 + j + k][i + 1] = b;
                    B[x2 + j + k][i + 2] = c;
                    B[x2 + j + k][i + 3] = d;
                }
                for (k = 0;  k < x2;     ++k) {
                for (l = 0;  l < x2;     ++l) {
                    B[x2 + j + k][x2 + i + l] = A[x2 + i + l][x2 + j + k];
                }
                }
            }
        }
        }
    }
}
