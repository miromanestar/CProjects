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
        if (Cardinality(set1) >= Cardinality(set2))
            set[set2] = set1;
        else
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
    int Cardinality(int a) {
        int count = 0;
        for (int i = 0; i < (int) set.size(); i++) {
            if (Find(set[i]) == a)
                count++;
        }

        return count;
    }
};

class MazeCell {
    double x, y;
    int cellIndex, width, height;
    double vertices[4][4];
public:
    MazeCell(double x, double y, double width, double height, int cell) : x(x), y(y), width(width), height(height), cellIndex(cell) { 
        vertices[0][0] = x; vertices[0][1] = y; vertices[0][2] = x; vertices[0][3] = y + height;
        vertices[1][0] = x; vertices[1][1] = y + height; vertices[1][2] = x + width; vertices[1][3] = y + height;
        vertices[2][0] = x + width; vertices[2][1] = y; vertices[2][2] = x + width; vertices[2][3] = y + height;
        vertices[3][0] = x; vertices[3][1] = y; vertices[3][2] = x + width; vertices[3][3] = y;
    }

    MazeCell() : x(0), y(0), cellIndex(0) { }
    double get_x() { return x; }
    double get_y() { return y; }
    int get_index() { return cellIndex; }
    auto get_vertices() { return vertices; }

    void del_left() { del_line(vertices[0][0], vertices[0][1], vertices[0][2], vertices[0][3]); }
    void del_top() { del_line(vertices[1][0], vertices[1][1], vertices[1][2], vertices[1][3]); }
    void del_right() { del_line(vertices[2][0], vertices[2][1], vertices[2][2], vertices[2][3]); }
    void del_bottom() { del_line(vertices[3][0], vertices[3][1], vertices[3][2], vertices[3][3]); }

    void del_line(double x0, double y0, double x1, double y1) {
        sgl::set_color(sgl::WHITE);
        sgl::draw_line(x0, y0, x1, y1);
        sgl::set_color(sgl::BLACK);
    }
};

class Maze: public sgl::Window {
    std::vector<std::vector<MazeCell>> maze;
    double cellWidth, cellHeight;
    int cellCount;
public:
    Maze(int cellsX, int cellsY) : maze(cellsY, std::vector<MazeCell>(cellsX)), cellCount(cellsX * cellsY),
        sgl::Window("Maze Generator - Miro Manestar", 0, 600, 0, 400) { 
            cellWidth = get_max_x()/(cellsX + 2);
            cellHeight = get_max_y()/(cellsY + 2);
        }

    void paint() override {
        sgl::set_color(sgl::BLACK);
        make_maze();
        
    }

    void make_maze() {
        for (int y = 0; y < (int) maze.size(); y++) {
            for (int x = 0; x < (int) maze[y].size(); x++) {
                int cellIndex = get_index(x, y);
                maze[y][x] = MazeCell((x + 1) * cellWidth, (y + 1) * cellHeight, cellWidth, cellHeight, cellIndex);
                sgl::draw_rectangle(maze[y][x].get_x(), maze[y][x].get_y(), cellWidth, cellHeight);

                if (cellIndex == 0) {
                    sgl::set_color(sgl::WHITE);
                    sgl::draw_line(maze[y][x].get_x(), maze[y][x].get_y(), maze[y][x].get_x(), maze[y][x].get_y() + cellHeight);
                    sgl::set_color(sgl::BLACK);
                } else if (cellIndex == cellCount - 1) {
                    sgl::set_color(sgl::WHITE);
                    sgl::draw_line(maze[y][x].get_x() + cellWidth, maze[y][x].get_y(), maze[y][x].get_x() + cellWidth, maze[y][x].get_y() + cellHeight);
                    sgl::set_color(sgl::BLACK);
                }
            }
        }


    int get_index(int x, int y) { return y * maze[y].size() + x; }
    int get_x(int index) { return index % maze.size(); }
    int get_y(int index) { return index/maze.size(); }
};

int main() {
   sgl::run<Maze>(40, 25);
}