#include <iostream>
#include <vector>

class Map
{
    private:
    std::vector < std::vector<char> > map;
    int dimX, dimY;

    public:
        Map(int dimx, int dimy,char ch);
        void display();
        void setObject(int x, int y, char ch);
        //void resize(int dimx, int dimy, char ch);
        char getObject(int x, int y);
        bool isEmpty(int x, int y);
        bool isHill(int x, int y);
        bool isTrap(int x, int y);
        bool isGold(int x, int y);
        bool isInsideMap(int x, int y);
        int getDimX() {return dimX;}
        int getDimY() {return dimY;}
};
