//  Name: Miro Manestar
//  Assignment number: 4
//  Assignment: Maze Generation
//  File name: manestar.cpp
//  Date last modified: October 28, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <memory>
#include <vector>
#include <GL/sgl.hpp>

class Maze : public sgl::Window {
    int cells = 0;
    int cellsX;
    int cellsY;
    double cellWidth;
    double cellHeight;
public:
    Maze(double width, double height, int cellsX, int cellsY): cellsX(cellsX), cellsY(cellsY),
        sgl::Window("Maze Generator - Miro Manestar", 0, width, 0, height) { 
            cellWidth = get_max_x()/(cellsX + 2);
            cellHeight = get_max_y()/(cellsY + 2);
        }

    void paint() override {
        sgl::set_color(sgl::BLACK);
        draw_cells();
        make_maze();
    }

    void draw_cells() {
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

    void make_maze() {
        //Retool Maze to utilize a 2d array and draw a maze from that
    }
};

class DisjointSet {
    std::vector<int> set;
public:
    DisjointSet(int numElements): set(numElements) { 
        for (int i = 0; i < (int) set.size(); i++) {
            set[i] = i;
        }
    }

    //Returns the "parent" element of an equivalence class
    int Find(int i) {
        if (set[i] != i)
            set[i] = Find(set[i]);
        return set[i];
    }

    //Combines two equivalence classes, smaller class is pointed to the larger class
    void Union(int a, int b) {
        int set1 = Find(a);
        int set2 = Find(b);
        if (Cardinality(set1) >= Cardinality(set2))
            set[set1] = set2;
        else
            set[set2] = set1;
    }

    //Takes a set and puts each element from it inside its own equivalence class
    void Split(int a) {
        std::vector<int> temp;
        for (int i = 0; i < (int) set.size(); i++) {
            if (Find(set[i]) == a) {
                temp.push_back(i);
            }
        }

        for (int item : temp) {
            set[item] = item;
        }
    }

    //Returns the number of items in a set
    int Cardinality(int a) {
        int count = 0;
        for (int i = 0; i < (int) set.size(); i++) {
            if (Find(set[i]) == a)
                count++;
        }

        return count;
    }
};

int main() {
    sgl::run<Maze>(600.0, 400.0, 25, 40);
}