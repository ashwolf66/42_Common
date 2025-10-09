#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other)
{
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
    if (this != &other)
        tree_bag::operator=(other);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
}

void searchable_tree_bag::insert(int value)
{
    tree_bag::insert(value);
}

void searchable_tree_bag::insert(int* values, int count)
{
    tree_bag::insert(values, count);
}

void searchable_tree_bag::print() const
{
    tree_bag::print();
}

void searchable_tree_bag::clear()
{
    tree_bag::clear();
}

bool searchable_tree_bag::has(int value) const
{
    node* current = tree;
    while (current)
    {
        if (value == current->data)
            return true;
        else if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}