#include "searchable_bag.hpp"

class set : public searchable_bag {
private:
    searchable_bag& bag;
public:
    set();
    set(const set& other);
    set& operator=(const set& other);
    ~set();

    set(searchable_bag& bag);
    void insert(int value);
    void insert(int* values, int count);
    void print() const;
    void clear();
    bool has(int value) const;
    const searchable_bag& get_bag() const;
};