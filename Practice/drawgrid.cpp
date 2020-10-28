// Simple example showing how to draw lines with the SGL library

#include <memory>
#include <SGL/sgl.hpp>  // Use #include "sgl.hpp" on macOS

class GridWindow : public sgl::Window {
public:
    // Constructor makes a width x height window
    GridWindow(double width, double height): 
          sgl::Window("Grid", 0, width, 0, height) {}

    // The paint method simply draws a grid
    void paint() override {
        sgl::set_color(sgl::BLACK);
        for (int x = 30; x <= get_max_x() - 30; x += 20)  
            sgl::draw_line(x, 30, x, get_max_y() - 30);
        for (int y = 30; y <= get_max_y() - 30; y += 20)
            sgl::draw_line(30, y, get_max_x() - 30, y);
    }

};

int main() {
    // Make a window and start the application
    sgl::run<GridWindow>(600.0, 400.0);
    std::cout << "What will this do";
}