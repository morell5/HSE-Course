#include "shelf.h"

int main() {
    Shelf shelf(5);
    shelf.ForEachBook([](auto&& book){book.print();});   
    return 0;
}