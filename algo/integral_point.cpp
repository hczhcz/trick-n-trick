#include <cmath>
#include <random>
#include <iostream>

using namespace std;

int sign(double x) {
    return (x > 1e-9) - (x < -1e-9);
}

int sign(double x, double xbase) {
    return sign(x - xbase);
}

double sqr(double x) {
    return x * x;
}

double len(double x, double y) {
    return sqrt(sqr(x) + sqr(y));
}

double len(double x, double y, double xbase, double ybase) {
    return len(x - xbase, y - ybase);
}

double cross(double x1, double y1, double x2, double y2) {
    return x1 * y2 - x2 * y1;
}

double cross(double x1, double y1, double x2, double y2, double xbase, double ybase) {
    return cross(x1 - xbase, y1 - ybase, x2 - xbase, y2 - ybase);
}

int side(double x1, double y1, double x2, double y2, double xbase, double ybase) {
    return sign(cross(x1, y1, x2, y2, xbase, ybase));
}

bool within(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3) {
    int s1 = side(x, y, x2, y2, x1, y1);
    int s2 = side(x, y, x3, y3, x2, y2);
    int s3 = side(x, y, x1, y1, x3, y3);

    return s1 * s2 != -1 && s2 * s3 != -1 && s3 * s1 != -1;
}

double totlen(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3) {
    double l1 = len(x, y, x1, y1);
    double l2 = len(x, y, x2, y2);
    double l3 = len(x, y, x3, y3);

    return l1 + l2 + l3;
}

bool test(double &best, int &xtarget, int &ytarget, int x, int y, double x1, double y1, double x2, double y2, double x3, double y3) {
    if (within(x, y, x1, y1, x2, y2, x3, y3)) {
        double t = totlen(x, y, x1, y1, x2, y2, x3, y3);

        if (sign(best, t) >= 0) {
            best = t;
            xtarget = x;
            ytarget = y;

            return true;
        }
    }

    return false;
}

bool test(double &best, double &xtarget, double &ytarget, double x, double y, double x1, double y1, double x2, double y2, double x3, double y3) {
    if (within(x, y, x1, y1, x2, y2, x3, y3)) {
        double t = totlen(x, y, x1, y1, x2, y2, x3, y3);

        if (best > t) {
            best = t;
            xtarget = x;
            ytarget = y;

            return true;
        }
    }

    return false;
}

void naive_solution(double &best, int &xtarget, int &ytarget, double x1, double y1, double x2, double y2, double x3, double y3) {
    best = INFINITY;

    for (int x = floor(min(min(x1, x2), x3)); x <= ceil(max(max(x1, x2), x3)); ++x) {
        for (int y = floor(min(min(y1, y2), y3)); y <= ceil(max(max(y1, y2), y3)); ++y) {
            test(best, xtarget, ytarget, x, y, x1, y1, x2, y2, x3, y3);
        }
    }
}

void line_drawing_step(double &best, int &xtarget, int &ytarget, double x1, double y1, double x2, double y2, double x3, double y3) {
    double l = len(x1, y1, x2, y2);
    double xstep = (x2 - x1) / l;
    double ystep = (y2 - y1) / l;

    double x = x1;
    double y = y1;

    while (true) {
        test(best, xtarget, ytarget, floor(x), floor(y), x1, y1, x2, y2, x3, y3);
        test(best, xtarget, ytarget, floor(x), ceil(y), x1, y1, x2, y2, x3, y3);
        test(best, xtarget, ytarget, ceil(x), floor(y), x1, y1, x2, y2, x3, y3);
        test(best, xtarget, ytarget, ceil(x), ceil(y), x1, y1, x2, y2, x3, y3);

        if (sign(x - xstep, x2) != sign(x, x2) || sign(y - ystep, y2) != sign(y, y2)) {
            break;
        }

        x += xstep;
        y += ystep;
    }
}

void line_drawing_fermat(double &best, int &xtarget, int &ytarget, double x1, double y1, double x2, double y2, double x3, double y3) {
    double best2 = best;
    double x = xtarget;
    double y = ytarget;

    for (double step = 1; step > 1e-5; step /= 2) {
        while (
            test(best2, x, y, x, y - step, x1, y1, x2, y2, x3, y3)
            || test(best2, x, y, x, y + step, x1, y1, x2, y2, x3, y3)
            || test(best2, x, y, x - step, y, x1, y1, x2, y2, x3, y3)
            || test(best2, x, y, x + step, y, x1, y1, x2, y2, x3, y3)
        );
    }

    test(best, xtarget, ytarget, floor(x), floor(y), x1, y1, x2, y2, x3, y3);
    test(best, xtarget, ytarget, floor(x), ceil(y), x1, y1, x2, y2, x3, y3);
    test(best, xtarget, ytarget, ceil(x), floor(y), x1, y1, x2, y2, x3, y3);
    test(best, xtarget, ytarget, ceil(x), ceil(y), x1, y1, x2, y2, x3, y3);
}

void line_drawing_solution(double &best, int &xtarget, int &ytarget, double x1, double y1, double x2, double y2, double x3, double y3) {
    best = INFINITY;

    line_drawing_step(best, xtarget, ytarget, x1, y1, x2, y2, x3, y3);
    line_drawing_step(best, xtarget, ytarget, x2, y2, x3, y3, x1, y1);
    line_drawing_step(best, xtarget, ytarget, x3, y3, x1, y1, x2, y2);

    line_drawing_fermat(best, xtarget, ytarget, x1, y1, x2, y2, x3, y3);

    for (int x = xtarget - 2; x <= xtarget + 2; ++x) {
        for (int y = ytarget - 2; y <= ytarget + 2; ++y) {
            test(best, xtarget, ytarget, x, y, x1, y1, x2, y2, x3, y3);
        }
    }
}

int main() {
    random_device rd;
    mt19937_64 gen {rd()};
    uniform_real_distribution<> random {-100, 100};

    for (int i = 0; i < 1000; ++i) {
        double x1 = random(gen);
        double y1 = random(gen);
        double x2 = random(gen);
        double y2 = random(gen);
        double x3 = random(gen);
        double y3 = random(gen);

        double best1;
        int xtarget1;
        int ytarget1;

        naive_solution(best1, xtarget1, ytarget1, x1, y1, x2, y2, x3, y3);

        double best2;
        int xtarget2;
        int ytarget2;

        line_drawing_solution(best2, xtarget2, ytarget2, x1, y1, x2, y2, x3, y3);

        if (xtarget1 != xtarget2 || ytarget1 != ytarget2) {
            cerr << "error:" << endl;
            cerr << '\t' << xtarget1 << ' ' << ytarget1 << '\t' << best1 << endl;
            cerr << '\t' << xtarget2 << ' ' << ytarget2 << '\t' << best2 << endl;
            cerr << '\t' << x1 << ' ' << y1 << '\t' << x2 << ' ' << y2 << '\t' << x3 << ' ' << y3 << endl;
        }
    }

    // if (best < INFINITY) {
    //     cout << xtarget << ' ' << ytarget << endl;
    // } else {
    //     cout << 'none' << endl;
    // }

    return 0;
}
