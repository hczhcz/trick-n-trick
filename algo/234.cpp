// 2-3-4 tree demo
// by hczhcz

#include <utility>
#include <iostream>

using namespace std;

template <class T>
class tree234 {
private:
    struct node_t;
    typedef node_t *node_p;

    struct node_t {
        size_t type;
        node_p child[4];
        T data[3];

        node_t(): type(0) {}

        node_t(const T &value, node_p l, node_p r): type(1) {
            data[0] = value;
            child[0] = l;
            child[1] = r;
        }

        size_t find(const T &value) const {
            size_t i = 0;

            while (i < type && data[i] <= value) {
                ++i;
            }

            return i;
        }

        void insert_r(size_t i, const T &value, node_p node) {
            if (i == type) {
                ++type;
            } else {
                insert_r(i + 1, data[i], child[i + 1]);
            }

            data[i] = value;
            child[i + 1] = node;
        }

        void insert_l(size_t i, const T &value, node_p node) {
            insert_r(i, value, child[i]);

            child[i] = node;
        }

        void swap_r(size_t i, pair<T, node_p> &value) {
            swap(value.first, data[i]);
            swap(value.second, child[i + 1]);
        }

        void swap_l(size_t i, pair<T, node_p> &value) {
            swap(value.first, data[i]);
            swap(value.second, child[i]);
        }

        pair<T, node_p> erase_r(size_t i) {
            pair<T, node_p> result;
            swap(result.first, data[i]);
            swap(result.second, child[i + 1]);

            if (i == type - 1) {
                child[i + 1] = 0 /* nullptr */;

                --type;
            } else {
                data[i] = data[i + 1];
                child[i + 1] = child[i + 2];

                erase_r(i + 1);
            }

            return result;
        }

        pair<T, node_p> erase_l(size_t i) {
            swap(child[i], child[i + 1]);

            return erase_r(i);
        }

        void deepfree() {
            for (size_t i = 0; i <= type; ++i) {
                if (child[i]) {
                    child[i]->deepfree();
                }
            }

            delete this;
        }

        void print(ostream &stream) {
            stream << '(';

            for (size_t i = 0; i <= type; ++i) {
                if (child[i]) {
                    child[i]->print(stream);
                } else {
                    stream << '_';
                }
                if (i < type) {
                    stream << ' ' << data[i] << ' ';
                }
            }

            stream << ')';
        }

        ~node_t() {
            // nothing
        }
    };

    node_p entry;

public:
    tree234() {
        entry = new node_t();
    }

    ~tree234() {
        entry->deepfree();
    }

    bool find(const T &value, node_p node = 0 /* nullptr */) {
        if (!node) node = entry;

        size_t i = node->find(value);

        if (0 < i && node->data[i - 1] == value) {
            return true;
        } else if (node->child[i]) {
            return find(value, node->child[i]);
        } else {
            return false;
        }
    }

    size_t count(node_p node = 0 /* nullptr */) {
        if (!node) node = entry;

        size_t result = node->type;

        for (size_t i = 0; i <= node->type; ++i) {
            if (node->child[i]) {
                result += count(node->child[i]);
            }
        }

        return result;
    }

    void insert(
        const T &value,
        node_p node = 0 /* nullptr */, node_p parent = 0 /* nullptr */, size_t i = -1
    ) {
        if (!node) node = entry;

        if (node->type == 3) {
            node->type = 1;
            node_p r = new node_t(node->data[2], node->child[2], node->child[3]);

            if (node == entry) {
                entry = new node_t(node->data[1], node, r);

                node = entry;
            } else {
                parent->insert_r(i, node->data[1], r);

                node = parent;
            }
        }

        i = node->find(value);

        if (0 < i && node->data[i - 1] == value) {
            return; // already exist
        } else if (node->child[i]) {
            insert(value, node->child[i], node, i);
        } else {
            node->insert_r(i, value, 0 /* nullptr */); // insert l/r
            return;
        }
    }

    T erase(
        const T &value,
        node_p node = 0 /* nullptr */, node_p parent = 0 /* nullptr */, size_t xi = -1, size_t i = -1
    ) {
        if (!node) node = entry;

        xi = i;
        i = node->find(value);

        if (0 < i && node->data[i - 1] == value) {
            // ok
        } else if (node->child[i]) {
            return erase(value, node->child[i], node, xi, i);
        } else {
            T result;
            return result; // not found
        }

        node_p node1 = node->child[i - 1];

        if (node1) {
            parent = node;
            xi = i - 1;

            while (1) {
                if (node1->child[node1->type]) {
                    parent = node1;
                    xi = node1->type;
                    node1 = node1->child[node1->type];
                } else {
                    break;
                }
            }

            swap(node->data[i - 1], node1->data[node1->type - 1]);
            node = node1;
            i = node1->type;
        }

        T result = node->erase_r(i - 1).first; // erase l/r

        if (node->type == 0 && node != entry) {
            if (1 <= xi) {
                node_p sibling = parent->child[xi - 1];
                if (1 < sibling->type) {
                    pair<T, node_p> rdata = sibling->erase_r(sibling->type - 1);
                    parent->swap_r(xi - 1, rdata);
                    if (parent->child[xi - 1]) {
                        insert(rdata.first, parent->child[xi - 1], parent, xi - 1);
                    } else {
                        parent->child[xi - 1] = new node_t(rdata.first, 0 /* nullptr */, 0 /* nullptr */);
                    }
                } else {
                    pair<T, node_p> pdata = parent->erase_r(xi - 1);
                    insert(pdata.first, sibling, parent, xi - 1);
                }
            } else if (xi < parent->type) {
                node_p sibling = parent->child[xi + 1];
                if (1 < sibling->type) {
                    pair<T, node_p> ldata = sibling->erase_l(0);
                    parent->swap_l(xi, ldata);
                    if (parent->child[xi]) {
                        insert(ldata.first, parent->child[xi], parent, xi);
                    } else {
                        parent->child[xi] = new node_t(ldata.first, 0 /* nullptr */, 0 /* nullptr */);
                    }
                } else {
                    pair<T, node_p> pdata = parent->erase_l(xi);
                    insert(pdata.first, sibling, parent, xi);
                }
            }

            if (parent->type == 0) {
                // assert parent->child[0] is not null
                // assert parent->child[0]->type = 2
                node_p child = parent->child[0];

                parent->type = child->type;
                for (size_t n = 0; n < parent->type; ++n) {
                    parent->data[n] = child->data[n];
                }
                for (size_t n = 0; n <= parent->type; ++n) {
                    parent->child[n] = child->child[n];
                }
            }

            node->deepfree();
        }

        return result;
    }

    void print(ostream &stream) {
        entry->print(stream);
        stream << endl;
    }
};

int main() {
    tree234<int> t;

    t.insert(3);
    t.print(cout);
    t.insert(6);
    t.print(cout);
    t.insert(2);
    t.print(cout);
    t.insert(1);
    t.print(cout);
    t.insert(5);
    t.print(cout);
    t.insert(9);
    t.print(cout);
    t.insert(1);
    t.print(cout);
    t.insert(6);
    t.print(cout);
    t.insert(6);
    t.print(cout);
    t.insert(4);
    t.print(cout);
    t.insert(7);
    t.print(cout);
    t.insert(8);
    t.print(cout);
    t.insert(10);
    t.print(cout);
    t.insert(11);
    t.print(cout);
    t.insert(12);
    t.print(cout);

    cout << "5: " << t.find(5) << endl;
    cout << "6: " << t.find(6) << endl;
    cout << "7: " << t.find(7) << endl;
    cout << "c: " << t.count() << endl;

    t.erase(6);
    t.print(cout);
    t.erase(2);
    t.print(cout);
    t.erase(1);
    t.print(cout);
    t.erase(3);
    t.print(cout);
    t.erase(5);
    t.print(cout);
    t.erase(5);
    t.print(cout);
    t.erase(5);
    t.print(cout);
    t.erase(7);
    t.print(cout);
    t.erase(8);
    t.print(cout);
    t.erase(9);
    t.print(cout);
    t.erase(10);
    t.print(cout);
    t.erase(11);
    t.print(cout);
    t.erase(12);
    t.print(cout);
    t.erase(3);
    t.print(cout);
    t.erase(1);
    t.print(cout);
    t.erase(4);
    t.print(cout);

}
