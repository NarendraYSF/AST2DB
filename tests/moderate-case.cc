
struct Point {
    int x;
    int y;

    void print() const;
};


int add(int a, int b);
void printInt(int value);
void printPoint(const Point* p);

void Point::print() const {
    
    printInt(x);
    printInt(y);
}


int main() {
    
    int a = 5;
    int b = 10;
    int sum = add(a, b);

    
    if (sum > 10) {
        printInt(sum);
    } else {
        printInt(0);
    }

    
    for (int i = 0; i < 3; ++i) {
        printInt(i);
    }

    
    Point p1 = {1, 2};
    p1.print();

    
    Point* p2 = &p1;
    printPoint(p2);

    return 0;
}


int add(int a, int b) {
    return a + b;
}


void printInt(int value) {
    
}


void printPoint(const Point* p) {
    if (p) {
        p->print();
    }
}
