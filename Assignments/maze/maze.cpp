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
};

class Maze: public sgl::Window {
    std::vector<std::vector<MazeCell>> maze;
    double cellWidth, cellHeight;
    int cellCount;
public:
    Maze(int cellsX, int cellsY) : maze(cellsY, std::vector<MazeCell>(cellsX)),
        sgl::Window("Maze Generator - Miro Manestar", 0, 600, 0, 400) { 
            cellWidth = get_max_x()/(cellsX + 2);
            cellHeight = get_max_y()/(cellsY + 2);
            make_maze();
        }

    void paint() override {
        sgl::set_color(sgl::BLACK);
        draw_maze();
        
    }

    void make_maze() {
        for (int y = 0; y < (int) maze.size(); y++) {
            for (int x = 0; x < (int) maze[y].size(); x++) {
                maze[y][x] = MazeCell((x + 1) * cellWidth, (y + 1) * cellHeight, cellWidth, cellHeight, y * maze[y].size() + x);

                if (x == 0 && y == 0) {
                    sgl::set_color(sgl::WHITE);
                    sgl::draw_line((x + 1) * cellWidth, (y + 1) * cellHeight, (x + 1) * cellWidth, (y + 1) * cellHeight + cellHeight);
                    sgl::set_color(sgl::BLACK);
                } else if (x == maze[y].size() - 1 && y == maze.size() - 1) {
                    sgl::set_color(sgl::WHITE);
                    sgl::draw_line((x + 1) * cellWidth + cellWidth, (y + 1) * cellHeight, (x + 1) * cellWidth + cellWidth, (y + 1) * cellHeight + cellHeight);
                    sgl::set_color(sgl::BLACK);
                }
            }
        }
    }

    void draw_maze() {
        for (auto row : maze) {
            for (auto cell : row) {
                sgl::draw_rectangle(cell.get_x(), cell.get_y(), cellWidth, cellHeight);
            }
        }
    }
};

int main() {
   sgl::run<Maze>(40, 25);
}