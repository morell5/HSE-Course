#include <iostream>
#include <exception>
#include <filesystem>
#include <fstream>
#include <vector>
#include <chrono>

    
class Worker;

enum Commands {
    LOAD,
    SORT,
    PRINT    
};

class Mediator {
public:
   virtual void Notify(Worker* worker, Commands cmd) const = 0;
};

class Worker {
public:
    Worker() : mediator(nullptr) {};
    
    void SetMediator(Mediator* mediator);

protected:
    Mediator* mediator;
};

void Worker::SetMediator(Mediator* mediator) {
    this->mediator = mediator;
}

class SortingWorker : public Worker {
public:
    virtual void Sort(std::vector<int>& v) = 0;
};

class QuickSortWorker : public SortingWorker {
public:
    void Sort(std::vector<int>& v) override {

        qsort(v, 0, v.size());

        mediator->Notify(this, SORT);
    }
private:
    void qsort(std::vector<int>& v, std::size_t left, std::size_t right) {
        if ( left < right ) {
            std::size_t pos = Partition(v, left, right);
            qsort(v, left, pos);
            qsort(v, pos + 1, right);
        }
    }   
    int Partition(std::vector<int>& v, std::size_t left, std::size_t right) {
       std::size_t pivot = v[static_cast<std::size_t>(left + right) / 2];
       std::size_t i = left;
       std::size_t j = right;
                  
       while (i <= j ) {
           while (v[i] < pivot) {
               i++;
           }
           while (v[j] > pivot) {
               j--;
           }
          
           if (i >= j) {
               break;
           }
            std::swap(v[i++], v[j--]);
       }
    }
};

class Decorator : public SortingWorker {
 protected:
  SortingWorker*  component;

 public:
    Decorator(SortingWorker* component) :  component(component) {}
    void Sort(std::vector<int>& v) {
        component->Sort(v);
    }
};

class TimerDecorator : public Decorator {
 public:
  TimerDecorator(QuickSortWorker* component) :  Decorator(component) {}
    void Sort(std::vector<int>& v) {
        auto start = std::chrono::high_resolution_clock::now();
        Decorator::Sort(v);
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << elapsed.count() << std::endl;
    }
};

class DataLoaderWorker : public Worker {
public:
    DataLoaderWorker(std::filesystem::path& path) : path_(std::move(path)) {}

    void Load() {
        std::cout << "Load:completed" << std::endl;
        std::fstream fs;
        fs.open(this->path_);
        int num;
        fs >> num;
        while (!fs.eof() && fs >> num) {
            v.push_back(num);
        }
        mediator->Notify(this, LOAD);
    }

    std::vector<int>& Get() {
        return v;
    }

private:
    std::filesystem::path path_;
    std::vector<int> v;
};

class PrinterWorker : public Worker {
public:
    void Print(const std::vector<int>& v) {
        std::cout << "Print:completed" << std::endl;
        for (auto x: v) {
            std::cout << x << std::endl;
        }
    }
};

class SortMediator : public Mediator {
public:
    SortMediator(DataLoaderWorker* dataloader, SortingWorker* sorter, PrinterWorker* printer) :
        dataloader(dataloader),
        sorter(sorter),
        printer(printer) {
            dataloader->SetMediator(this);
            sorter->SetMediator(this);
            printer->SetMediator(this);
        };

    void Notify(Commands cmd) const override {
        switch (cmd) {
            case Commands::LOAD: {
                sorter->Sort(dataloader->Get());
                break;
            }
            case Commands::SORT: {
                printer->Print(dataloader->Get());
                break;
            }
        }
    }
private:
    DataLoaderWorker* dataloader;
    SortingWorker* sorter;
    PrinterWorker* printer;
};

int main() {
    
    std::filesystem::path path = "./input.txt";
    DataLoaderWorker* dataloader = new DataLoaderWorker(path);
    SortingWorker* qsort_worker = new QuickSortWorker;
    PrinterWorker* print_worker = new PrinterWorker;
    Decorator* qsort_docrator = new Decorator(qsort_worker);

    SortMediator* qsort_mediator = new SortMediator(dataloader, qsort_docrator, print_worker);
    dataloader->Load();
    
    return 0;
}