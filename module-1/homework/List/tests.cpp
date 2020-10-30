#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>

#include "list.h"

size_t RandomUInt(size_t max = -1) {
    static std::mt19937 rand(std::random_device{}());

    std::uniform_int_distribution<size_t> dist{0, max};
    return dist(rand);
}

size_t RandomUInt(size_t min, size_t max) {
    return min + RandomUInt(max - min);
}

bool TossCoin() {
    return RandomUInt(1) == 0;
}


template <class T>
void RandomFill(T& container, size_t count, size_t max = -1) {
    while (count > 0) {
        container.push_back(RandomUInt(max));
        --count;
    }
}


std::list<int> ToStdList(const task::list& list_task) {
    task::list list_task_copy = list_task;
    std::list<int> list_std;
    while (!list_task_copy.empty()) {
        list_std.push_back(list_task_copy.front());
        list_task_copy.pop_front();
    }
    return list_std;
}


void FailWithMsg(const std::string& msg, int line) {
    std::cerr << "Test failed!\n";
    std::cerr << "[Line " << line << "] "  << msg << std::endl;
    std::exit(EXIT_FAILURE);
}


template <class T, class T_>
bool EqualWrapper(T cont1, T_ cont2) {
    return std::equal(cont1.begin(), cont1.end(), cont2.begin(), cont2.end());
}

#define ASSERT_TRUE(cond) \
    if (!(cond)) {FailWithMsg("Assertion failed: " #cond, __LINE__);};

#define ASSERT_TRUE_MSG(cond, msg) \
    if (!(cond)) {FailWithMsg(msg, __LINE__);};

#define ASSERT_EQUAL_MSG(cont1, cont2, msg) \
    ASSERT_TRUE_MSG(EqualWrapper(cont1, cont2), msg)


int main() {

    {
        task::list list;
        list.push_back(42);
        ASSERT_TRUE(list.size() == 1)
        list.push_back(2);
        list.pop_front();
        ASSERT_TRUE(list.front() == 2)
        list.pop_back();
        ASSERT_TRUE(list.empty())
    }


    {
        task::list list;
        list.push_front(3);
        ASSERT_TRUE(!list.empty())
        list.push_front(4);
        ASSERT_TRUE(list.back() == 3)
        list.clear();
        list.clear();
        ASSERT_TRUE(list.size() == 0)
        list.resize(10);
        ASSERT_TRUE(list.size() == 10)
        ASSERT_TRUE(list.back() == int())
    }


    {
        task::list list(5, 30);
        ASSERT_TRUE(list.front() == 30)
        ASSERT_TRUE(list.back() == 30)

        list.push_front(29);
        const task::list list2 = list;
        ASSERT_TRUE(list2.front() == 29)
        ASSERT_TRUE(list2.back() == 30)
    }


    {
        task::list list;
        RandomFill(list, RandomUInt(1000, 5000));

        task::list list2 = list;

        list.sort();

        {
            auto list_std = ToStdList(list);
            ASSERT_TRUE(std::is_sorted(list_std.begin(), list_std.end()))
        }

        task::list list3(10);
        list = list2 = list3;

        ASSERT_EQUAL_MSG(ToStdList(list), ToStdList(list3), "Assignment operator")
    }


    {
        task::list list_task;

        RandomFill(list_task, RandomUInt(1000, 5000), 100);

        std::list<int> list_std = ToStdList(list_task);

        list_task.sort();
        list_std.sort();

        ASSERT_EQUAL_MSG(ToStdList(list_task), list_std, "list::sort")

        list_task.unique();
        list_std.unique();

        ASSERT_EQUAL_MSG(ToStdList(list_task), list_std, "list::unique")

        task::list list_task2;

        RandomFill(list_task2, RandomUInt(1000, 5000), 100);

        std::list<int> list_std2 = ToStdList(list_task2);

        list_task2.remove(list_task2.front());
        list_std2.remove(list_std2.front());

        ASSERT_EQUAL_MSG(ToStdList(list_task2), list_std2, "list::remove")

        list_task.swap(list_task2);
        list_std.swap(list_std2);

        ASSERT_EQUAL_MSG(ToStdList(list_task), list_std, "list::swap")
        ASSERT_EQUAL_MSG(ToStdList(list_task2), list_std2, "list::swap")
    }

    {
        const size_t LIST_COUNT = 5;
        const size_t ITER_COUNT = 30000;

        std::vector<task::list> lists_task(LIST_COUNT);
        std::vector<std::list<int>> lists_std(LIST_COUNT);

        for (size_t iter = 0; iter < ITER_COUNT; ++iter) {
            for (size_t list = 0; list < LIST_COUNT; ++list) {
                size_t case_type = lists_task[list].empty() ? 0 : RandomUInt(3);
                switch (case_type) {
                    case 0 : {
                        // Random Push
                        auto val = RandomUInt();
                        if (TossCoin()) {
                            lists_task[list].push_back(val);
                            lists_std[list].push_back(val);
                        } else {
                            lists_task[list].push_front(val);
                            lists_std[list].push_front(val);
                        }
                        break;
                    }
                    case 1: {
                        // Random Pop
                        if (TossCoin()) {
                            lists_task[list].pop_back();
                            lists_std[list].pop_back();
                        } else {
                            lists_task[list].pop_front();
                            lists_std[list].pop_front();
                        }
                        break;
                    }
                    case 2: {
                        lists_task[list].remove(lists_task[list].back());
                        lists_std[list].remove(lists_std[list].back());
                        break;
                    } 
                    case 3: {
                        lists_task[list].sort();
                        lists_std[list].sort();
                        break;
                    }
                }
            }
        }
    }
}