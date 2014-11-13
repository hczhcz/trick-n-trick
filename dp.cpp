#include <tuple>
#include <map>
#include <iostream>

template <class Ret, class... Arg>
class DP {
private:
    std::map<
        std::tuple<const Arg...>, Ret
    > _data;

public:
    virtual const Ret gen(const Arg... key) = 0;

    virtual void gen_all() = 0;

    bool find(const Arg... key) const {
        return _data.find(std::make_tuple(key...)) != _data.end();
    }

    const Ret &at(const Arg... key) {
        auto got = _data.find(std::make_tuple(key...));

        if (got == _data.end()) {
            insert(gen(key...), key...);
            got = _data.find(std::make_tuple(key...));
        }

        return got->second;
    }

    void insert(const Ret &val, const Arg... key) {
        _data.insert(std::make_pair(std::make_tuple(key...), val));
    }

    void erase(const Arg... key) {
        _data.erase(std::make_tuple(key...));
    }
};

const size_t item_count = 10;
const size_t item_weight[item_count] = {2, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const size_t item_value[item_count] = {4, 5, 6, 9, 10, 8, 16, 15, 18, 12};
const size_t max_weight = 10;

class DP_test: public DP<size_t, size_t, size_t> {
public:
    virtual const size_t gen(
        const size_t to_weight, const size_t now_item
    ) {
        // naive version, without auto erase

        size_t a = (to_weight >= item_weight[now_item] && now_item >= 1) ?
            (at(
                to_weight - item_weight[now_item], now_item - 1
            ) + item_value[now_item]) : 0;

        size_t b = (now_item >= 1) ?
            at(
                to_weight, now_item - 1
            ) : 0;

        return (a > b) ? a : b;
    }

    virtual void gen_all() {
        for (size_t i = 0; i < item_count; ++i) {
            for (size_t w = 0; w <= max_weight; ++w) {
                insert(gen(w, i), w, i);
            }
        }
    }
};

int main() {
    DP_test a;
    a.gen_all();
    std::cout << a.at(max_weight, item_count - 1) << std::endl;

    return 0;
}
