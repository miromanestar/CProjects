//  Name: Miro Manestar
//  Assignment number: 4
//  Assignment: Maze Generation
//  File name: manestar.cpp
//  Date last modified: October 28, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <memory>
#include <vector>
#include <GL/sgl.hpp>

class MazeWindow : public sgl::Window {
public:
    MazeWindow(double width, double height):
        sgl::Window("Maze Generator - Miro Manestar", 0, width, 0, height) { }

        void paint() override {
            sgl::set_color(sgl::BLACK);
            draw_cells(25, 40);
        }

        void draw_cells(int cellsX, int cellsY) {
            int cells = 0;

            double cellWidth = get_max_x()/(cellsX + 2);
            double cellHeight = get_max_y()/(cellsY + 2);
            
            //Build the initial maze
            for (int y = 1; y <= cellsY; y++) {
                for (int x = 1; x <= cellsX; x++) {
                    sgl::draw_rectangle(x * cellWidth, y * cellHeight, cellWidth, cellHeight);
                    sgl::draw_text(std::to_string(cells), x * cellWidth + cellWidth/2, y * cellHeight + cellHeight/2, 12);

                    //Remove wall for entrance and exit
                    if (cells == 0) {
                        sgl::set_color(sgl::WHITE);
                        sgl::draw_line(x * cellWidth, y * cellHeight, x * cellWidth, y * cellHeight + cellHeight);
                        sgl::set_color(sgl::BLACK);
                    } else if (x == cellsX && y == cellsY) {
                        sgl::set_color(sgl::WHITE);
                        sgl::draw_line(x * cellWidth + cellWidth, y * cellHeight, x * cellWidth + cellWidth, y * cellHeight + cellHeight);
                        sgl::set_color(sgl::BLACK);
                    }

                    cells++;
                }
            }
        }
};

class DisjointSet {
public:
    int find(int i) {

    }

    int combine(int a, int b) {

    }

    int split(int a, int b) {

    }

    int cardinality(int a, int b) {
        
    }
};

int main() {
    sgl::run<MazeWindow>(600.0, 400.0);
}