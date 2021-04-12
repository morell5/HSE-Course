
// прототип объектов, которые не требуется часто создавать, но надо получать
#include <iostream>
#include <string>
#include <unordered_map>

enum SquareFigureName {
    STAR
};

const char* enum_name2string_name[] = {
    "STAR",
    "a"
};

class SquareFigure;
std::ostream& operator<<(std::ostream& out, const SquareFigure& prot);

class SquareFigure {
public:
    
    SquareFigure(const char _symbol, int _width, unsigned short int _height) : 
        symbol(_symbol), 
        width( _width), 
        height(_height) {};

    virtual ~SquareFigure() = default;

    virtual SquareFigure* Clone() const = 0;

    int GetWidth() const { return width; }
    unsigned short int GetHeight() const { return height; }
    const char GetSymbol() const { return symbol; } 
    void Print() {
        std::cout << (*this);
    }

protected:
    const char symbol;
    const unsigned short int height;
    int width;
};

std::ostream& operator<<(std::ostream& out, const SquareFigure& prot) {
    for (unsigned short int i = 0; i < prot.GetHeight(); i++) {
        out << std::string(prot.GetWidth(), prot.GetSymbol());
        out.put('\n');
    }
    return out;
}

class StarSquareFigure : public SquareFigure {
public:

    StarSquareFigure(int _width, unsigned short int _height) : SquareFigure('*', _width, _height) {}

    SquareFigure* Clone() const override {
        return new StarSquareFigure(*this);
    }
};

class SquareFigureFactory {
private:
    std::unordered_map<SquareFigureName, SquareFigure*, std::hash<int>> name2figure;

public:
    SquareFigureFactory() {
        name2figure[SquareFigureName::STAR] = nullptr;
    }
    
    void SetPrototype(SquareFigureName name, SquareFigure* figure) {
        std::cout << "SquareFigure Name:" << enum_name2string_name[name]  << " width:"  << figure->GetWidth() << " setted!" << std::endl;
        name2figure[name] = figure;
    }

    SquareFigure* CreateSquareFigure(SquareFigureName name) {
        std::cout << "SquareFigure Name:" << enum_name2string_name[name]  << " created!" << std::endl;
        return name2figure[name]->Clone();
    }

    ~SquareFigureFactory() {
        if ( name2figure[SquareFigureName::STAR] ) {
            delete name2figure[SquareFigureName::STAR];
        }
    }
};

class SquareFigureProxy : public StarSquareFigure {
public:
    ~SquareFigureProxy() {
        if (fig) {
            delete fig;
        }
    }

    void Print() {
        if (hasSquareFigure()) {
            fig->Print();
            return;
        }
        std::cout << "No figure setted!" << std::endl;
        setDefault();
    }

    void SetFigure(StarSquareFigure* _fig) {
        std::cout << "Proxy: upd!" << std::endl;
        fig = _fig;
    }

private:
    bool hasSquareFigure() {
        return fig != nullptr;
    }

    void setDefault() {
        std::cout << "Default setted!" << std::endl;
        fig = new StarSquareFigure(3, 3);
    }

    StarSquareFigure* fig = nullptr;
};

int main() {
    SquareFigureFactory factory;
    SquareFigure* fig1 = new StarSquareFigure(2, 3);
    
    factory.SetPrototype(SquareFigureName::STAR, fig1);

    std::cout << *fig1 << std::endl;
    SquareFigure* fig1_clone = factory.CreateSquareFigure(SquareFigureName::STAR);

    std::cout << "Clone Printed:" << std::endl;
    std::cout << *fig1_clone;

    SquareFigureProxy p();
    return 0;
}