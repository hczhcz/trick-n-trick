unsigned ham(unsigned i, unsigned j) {
    unsigned k = i ^ j;
    unsigned result = 0;
    while (k & -k) {
        k ^= (k & -k);
        ++result;
    }
    return result;
}
