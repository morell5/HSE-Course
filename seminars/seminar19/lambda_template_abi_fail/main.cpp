#include "shelf.h"

int main() {
    Shelf shelf(5);
    // CE: Reason: template declaration and implmentaion in different files
    // See lecture18/templates_implementation minimal sample
    shelf.ForEachBook([](auto&& book){book.print();});   
    return 0;
}