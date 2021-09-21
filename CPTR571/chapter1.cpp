class Gadget {
public:
    Gadget() = delete;
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