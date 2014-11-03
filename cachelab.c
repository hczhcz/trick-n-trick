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
    #define ixcond (2 * j < M)
    #define ix (ixcond ? i + x1 : i - x1)
    #define jx j

    if (M != N || (M & 7) != 0 || (N & 7) != 0 || M <= 8 || N <= 8) {
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
        for (j = 0; j < M; j += x1) {
        for (i = ixcond ? 0 : N - x1; ixcond ? (i < N) : (i >= 0); i += ixcond ? x1 : -x1) {
            if (i == j) {
                // diagonal
                for (k = 0; k < x2; ++k) {
                    a = A[     i  + k][     j     ];
                    b = A[     i  + k][     j  + 1];
                    c = A[     i  + k][     j  + 2];
                    d = A[     i  + k][     j  + 3];
                    p = A[     i  + k][x2 + j     ];
                    q = A[     i  + k][x2 + j  + 1];
                    r = A[     i  + k][x2 + j  + 2];
                    s = A[     i  + k][x2 + j  + 3];

                    B[     jx + k][     ix    ] = a;
                    B[     jx + k][     ix + 1] = b;
                    B[     jx + k][     ix + 2] = c;
                    B[     jx + k][     ix + 3] = d;
                    B[     jx + k][x2 + ix    ] = p;
                    B[     jx + k][x2 + ix + 1] = q;
                    B[     jx + k][x2 + ix + 2] = r;
                    B[     jx + k][x2 + ix + 3] = s;
                }

                for (k = 0; k < x2; ++k) {
                    a = A[x2 + i  + k][     j     ];
                    b = A[x2 + i  + k][     j  + 1];
                    c = A[x2 + i  + k][     j  + 2];
                    d = A[x2 + i  + k][     j  + 3];
                    p = A[x2 + i  + k][x2 + j     ];
                    q = A[x2 + i  + k][x2 + j  + 1];
                    r = A[x2 + i  + k][x2 + j  + 2];
                    s = A[x2 + i  + k][x2 + j  + 3];

                    B[     j  + k][     i     ] = B[     jx + k][     ix    ];
                    B[     j  + k][     i  + 1] = B[     jx + k][     ix + 1];
                    B[     j  + k][     i  + 2] = B[     jx + k][     ix + 2];
                    B[     j  + k][     i  + 3] = B[     jx + k][     ix + 3];

                    B[     j  + k][x2 + i     ] = a;
                    B[     j  + k][x2 + i  + 1] = b;
                    B[     j  + k][x2 + i  + 2] = c;
                    B[     j  + k][x2 + i  + 3] = d;

                    B[     jx + k][     ix    ] = p;
                    B[     jx + k][     ix + 1] = q;
                    B[     jx + k][     ix + 2] = r;
                    B[     jx + k][     ix + 3] = s;
                }

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    if (k >= l) continue;
                    a = B[j + k][i + l];
                    b = B[j + l][i + k];
                    B[j + k][i + l] = b;
                    B[j + l][i + k] = a;
                }
                }

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    if (k >= l) continue;
                    a = B[j + k][x2 + i + l];
                    b = B[j + l][x2 + i + k];
                    B[j + k][x2 + i + l] = b;
                    B[j + l][x2 + i + k] = a;
                }
                }

                for (k = 0; k < x2; ++k) {
                    B[x2 + j  + k][x2 + i     ] = B[     jx + k][     ix    ];
                    B[x2 + j  + k][x2 + i  + 1] = B[     jx + k][     ix + 1];
                    B[x2 + j  + k][x2 + i  + 2] = B[     jx + k][     ix + 2];
                    B[x2 + j  + k][x2 + i  + 3] = B[     jx + k][     ix + 3];
                    B[x2 + j  + k][     i     ] = B[     jx + k][x2 + ix    ];
                    B[x2 + j  + k][     i  + 1] = B[     jx + k][x2 + ix + 1];
                    B[x2 + j  + k][     i  + 2] = B[     jx + k][x2 + ix + 2];
                    B[x2 + j  + k][     i  + 3] = B[     jx + k][x2 + ix + 3];
                }

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    if (k >= l) continue;
                    a = B[x2 + j + k][i + l];
                    b = B[x2 + j + l][i + k];
                    B[x2 + j + k][i + l] = b;
                    B[x2 + j + l][i + k] = a;
                }
                }

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    if (k >= l) continue;
                    a = B[x2 + j + k][x2 + i + l];
                    b = B[x2 + j + l][x2 + i + k];
                    B[x2 + j + k][x2 + i + l] = b;
                    B[x2 + j + l][x2 + i + k] = a;
                }
                }
            } else {
                // non-diagonal
                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    B[j + k][i + l] = A[i + l][j + k];
                }
                }

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    B[j + k][x2 + i + l] = A[i + l][x2 + j + k];
                }
                }

                for (k = 0; k < x2; ++k) {
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

                for (k = 0; k < x2; ++k) {
                for (l = 0; l < x2; ++l) {
                    B[x2 + j + k][x2 + i + l] = A[x2 + i + l][x2 + j + k];
                }
                }
            }
        }
        }
    }
}
