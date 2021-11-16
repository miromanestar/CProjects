class Gadget {
public:
    Gadget();
};

class Widget {
    Gadget gad;
public:
    Widget(const Gadget& g) {
        gad = g;
    }
};

int main() {

}