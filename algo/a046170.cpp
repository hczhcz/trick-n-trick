#include <iostream>

bool g[32][32];
long total;

void dfs(int n, int x, int y) {
    if (n == 3) {
        total +=
            + g[x - 1][y    ] * (
                + g[x - 2][y    ] * (
                    + g[x - 3][y    ]
                    + g[x - 2][y - 1]
                    + g[x - 2][y + 1]
                )
                + g[x - 1][y - 1] * (
                    + g[x - 2][y - 1]
                    + g[x - 1][y - 2]
                    + g[x    ][y - 1]
                )
                + g[x - 1][y + 1] * (
                    + g[x - 2][y + 1]
                    + g[x - 1][y + 2]
                    + g[x    ][y + 1]
                )
            )
            + g[x    ][y - 1] * (
                + g[x    ][y - 2] * (
                    + g[x    ][y - 3]
                    + g[x - 1][y - 2]
                    + g[x + 1][y - 2]
                )
                + g[x - 1][y - 1] * (
                    + g[x - 1][y - 2]
                    + g[x - 2][y - 1]
                    + g[x - 1][y    ]
                )
                + g[x + 1][y - 1] * (
                    + g[x + 1][y - 2]
                    + g[x + 2][y - 1]
                    + g[x + 1][y    ]
                )
            )
            + g[x + 1][y    ] * (
                + g[x + 2][y    ] * (
                    + g[x + 3][y    ]
                    + g[x + 2][y - 1]
                    + g[x + 2][y + 1]
                )
                + g[x + 1][y - 1] * (
                    + g[x + 2][y - 1]
                    + g[x + 1][y - 2]
                    + g[x    ][y - 1]
                )
                + g[x + 1][y + 1] * (
                    + g[x + 2][y + 1]
                    + g[x + 1][y + 2]
                    + g[x    ][y + 1]
                )
            )
            + g[x    ][y + 1] * (
                + g[x    ][y + 2] * (
                    + g[x    ][y + 3]
                    + g[x - 1][y + 2]
                    + g[x + 1][y + 2]
                )
                + g[x - 1][y + 1] * (
                    + g[x - 1][y + 2]
                    + g[x - 2][y + 1]
                    + g[x - 1][y    ]
                )
                + g[x + 1][y + 1] * (
                    + g[x + 1][y + 2]
                    + g[x + 2][y + 1]
                    + g[x + 1][y    ]
                )
            );
    } else if (n == 2) {
        total +=
            + g[x - 1][y    ] * (
                + g[x - 2][y    ]
                + g[x - 1][y - 1]
                + g[x - 1][y + 1]
            )
            + g[x    ][y - 1] * (
                + g[x    ][y - 2]
                + g[x - 1][y - 1]
                + g[x + 1][y - 1]
            )
            + g[x + 1][y    ] * (
                + g[x + 2][y    ]
                + g[x + 1][y - 1]
                + g[x + 1][y + 1]
            )
            + g[x    ][y + 1] * (
                + g[x    ][y + 2]
                + g[x - 1][y + 1]
                + g[x + 1][y + 1]
            );
    } else if (n == 1) {
        total +=
            + g[x - 1][y    ]
            + g[x    ][y - 1]
            + g[x + 1][y    ]
            + g[x    ][y + 1];
    } else if (n == 0) {
        total += 1;
    } else {
        g[x][y] = 0;

        if (g[x - 1][y    ]) {
            dfs(n - 1, x - 1, y);
        }

        if (g[x    ][y - 1]) {
            dfs(n - 1, x, y - 1);
        }

        if (g[x + 1][y    ]) {
            dfs(n - 1, x + 1, y);
        }

        if (g[x    ][y + 1]) {
            dfs(n - 1, x, y + 1);
        }

        g[x][y] = 1;
    }
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            g[i][j] = i >= 3 && j >= 3;
        }
    }

    g[3][3] = 0;
    dfs(n - 1, 3, 4);

    std::cout << total << std::endl;

    return 0;
}
