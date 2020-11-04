//  Name: Miro Manestar
//  Assignment number: 4
//  Assignment: Maze Generation
//  File name: manestar.cpp
//  Date last modified: November 4, 2020
//  Honor statement: I have neither given nor received any unauthorized help on this assignment.

#include <memory>
#include <vector>
#include <GL/sgl.hpp>

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
        set[set1] = set2;
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
    int Cardinality() {
        int count = 0;
        for (int i = 0; i < (int) set.size(); i++) {
            if (set[i] == i)
                count++;
        }

        return count;
    }
};

class Vertex {
    double x, y;
public:
    Vertex(double x, double y) : x(x), y(y) { }
    Vertex() : x(0), y(0) { }
    double get_x() { return x; }
    double get_y() { return y; }
};

class Maze: public sgl::Window {
    std::vector<std::vector<Vertex>> innerVertices;
    double width, height;
    int rows, columns, count;
public:
    Maze(int r, int c) : innerVertices(r - 1, std::vector<Vertex>(c - 1)), rows(r), columns(c), count(r * c),
        sgl::Window("Maze Generator - Miro Manestar", 0, 600.0, 0, 400.0) { 
            width = get_max_x()/(columns + 2);
            height = get_max_y()/(rows + 2);
        }
    
    void paint() override {
        sgl::set_color(sgl::BLACK);
        make_maze();
    }

    void make_maze() {
        //Make a 2d array of the inside vertices so we don't have to worry about the outside walls
        for (int r = 2; r <= rows; r++) {
            for (int c = 2; c <= columns; c++) {
                innerVertices[r - 2][c - 2] = Vertex(c * width, r * height);
            }
        }

        //Draw maze grid with all walls
        for (int r = 1; r <= rows; r++) {
            for (int c = 1; c <= columns; c++) {
                sgl::draw_rectangle(c * width, r * height, width, height);
            }
        }

        //Create entrance and exit
        sgl::set_color(sgl::WHITE);
        sgl::draw_line(width, height, width, height * 2); //Entrance, bottom-right
        sgl::draw_line(width * columns + width, height * rows, width * columns + width, height * rows + height); //Exit, top-left
        
        DisjointSet set(count);
        while (set.Cardinality() > 42) {
            Vertex v = innerVertices[rand() % innerVertices.size()][rand() % innerVertices[0].size()];
            int dir = rand() % 4;
            //int cr = set.Cardinality();

            if (check_dir(v, dir, set)) {
                switch (dir) {
                    case 0: sgl::draw_line(v.get_x(), v.get_y(), v.get_x() - width, v.get_y()); break; //Left
                    case 1: sgl::draw_line(v.get_x(), v.get_y(), v.get_x(), v.get_y() + height); break; //Up
                    case 2: sgl::draw_line(v.get_x(), v.get_y(), v.get_x() + width, v.get_y()); break; //Right
                    case 3: sgl::draw_line(v.get_x(), v.get_y(), v.get_x(), v.get_y() - height); break; //Down
                }
            }
        }
    }

    bool check_dir(Vertex v, int direction, DisjointSet& set) {
        double r0, c0, r1, c1; //x,y coords of adjacent cells (From bottom left)
        int i0, i1; //Indexes of adjacent cells
        if (direction == 0) { //Left
            r0 = v.get_y() - height; c0 = v.get_x() - width;
            r1 = v.get_y(); c1 = v.get_x() - width;
        } else if (direction == 1) { //Up
            r0 = v.get_y(); c0 = v.get_x() - width;
            r1 = v.get_y(); c1 = v.get_x();
        } else if (direction == 2) { //Right
            r0 = v.get_y() - height; c0 = v.get_x();
            r1 = v.get_y(); c1 = v.get_x();
        } else if (direction == 3) { //Down
            r0 = v.get_y() - height; c0 = v.get_x() - width;
            r1 = v.get_y() - height; c1 = v.get_x();
        }

        i0 = get_index(c0/width - 1, r0/height - 1); i1 = get_index(c1/width - 1, r1/height - 1);
        if (i0 < count && i1 < count && set.Find(i0) != set.Find(i1)) {
            set.Union(i0, i1);
            return true;
        } else {
            return false;
        }
    }

    int get_index(int c, int r) { return r * columns + c; }
    int get_c(int i) { return i % columns; }
    int get_r(int i) { return i/columns; }
};

int main() {
    sgl::run<Maze>(25, 40);
}