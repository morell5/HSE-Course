#include <iostream>

void secondPlayerMove(int num_stones);

void firstPlayerMove(int num_stones) {
    if(!num_stones) {
        std::cout << "first: lose" << std::endl;
        return;
    }
    secondPlayerMove(--num_stones);
}

void secondPlayerMove(int num_stones) {
    if (!num_stones) {
        std::cout << "second: lose" << std::endl;
        return;
    }
    firstPlayerMove(num_stones / 2);
}

int main() {
    for (int num_stones = 1; num_stones < 6; num_stones++) {
        std::cout << num_stones << " : ";
        firstPlayerMove(num_stones);
    }
    return 0;
}