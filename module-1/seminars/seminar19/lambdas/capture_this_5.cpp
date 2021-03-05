// 1. Deprecated: C++20. Reason: "=" means capture by value, this - pointer => just copy pointer
        // run_in_thread([=]() {this->printer(x);});

        // 2. To capture "this" by value you should capture it explicitly
        // run_in_thread([=]() {this->printer(x);});

        // 3.  "this" by copy other by reference
        // run_in_thread([&, this]() {this->printer(x);});

        // 4. capture by "*this" captures Widget object explicitly
        // run_in_thread([*this]() {this->printer(x);});