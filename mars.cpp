#include <iomanip> //for setw()
#include <ctime>
#include <windows.h>
//#include "Map.h"
#include "Rover.h"
using namespace std;

//Map constructor

Map::Map(int x, int y, char ch)
{
    dimX = x; dimY = y;
    vector < vector<char> > v (dimY, vector<char>(dimX,ch));
    map = v;
}

void Map::display()
{
    system("cls");
    cout << " --__--__--__--__--__--__--__--_" << endl;
    cout << " =      Mars Rover Mapper!     =" << endl;
    cout << " __--__--__--__--__--__--__--__-" << endl;
    cout << "\n\n";
    for(int i=0; i <= dimY; i++)
    {
        cout << "  ";
        for(int j=0; j < dimX; j++)     //Printing the plus-minus row
        {
            cout<<"+-";
            if(j == (dimX-1))
            {
                cout << "+";
            }
        }
        if(i==dimY)
        {
            break;      //To break at after printing last extra line.
        }
        cout << "\n" << setw(2) << (dimY-i)<<"|";
        for(int j=0; j < dimX; j++)
        {
            cout << map[i][j];
            cout << "|";
        }
        cout<< endl;
    }

    //Lower Digits
    cout << endl;
    cout << "  ";
    for (int j=0; j<dimX; ++j)
    {
        int digit = (j+1)/10;
        cout << " ";
        if (digit==0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;

    cout << "  ";
    for (int j=0; j<dimX; ++j)
    {
        cout << " " << (j+1)%10;
    }
    cout << endl << endl;
    cout << "Mission: Get all the golds!!, Do not get trapped!!\n"
            "L=Turn Left, R=Turn Right, M=Move, Q=Quit\n"
            <<(char)178<<"=Hill #=Trap *=Gold\n";
    return;
}

//Set Object Function
void Map::setObject(int x, int y, char ch)
{
    map[y][x] = ch;
    return;
}

//Get object
char Map::getObject(int x, int y)
{
    return map[y][x];
}

// Empty Check function
bool Map::isEmpty(int x, int y)
{
    if (map[y][x] == ' ')
        return true;
    else
        return false;

}

//Is Hill check
bool Map::isHill(int x, int y)
{
    if(map[y][x] == 178)
        return true;
    else
        return false;
}

//Trap check
bool Map::isTrap(int x, int y)
{
    if(map[y][x] == '#')
        return true;
    else
        return false;
}

//Is gold
bool Map::isGold(int x, int y)
{
    if(map[y][x] == '*')
        return true;
    else
        return false;
}

// Is Inside Map

bool Map::isInsideMap(int x, int y)
{
    if ((x < 0)||(x > dimX)||(y < 0)||(y > dimY))
        return false;
    return true;
}


Rover::Rover()
{
    x = 0;
    y = 0;
    heading = north;
}

void Rover::land(const Map mars)
{
    Map temp = mars;
    x = temp.getDimX()/2;
    y = temp.getDimY()/2;

    nm(temp.getDimX(),temp.getDimY(),'?');
    nm.setObject(x,y,'>');
}

bool Rover::turnLeft()
{
    switch(heading)
    {
        case north:
            {
                heading = west;
                return true;
            }
        case south:
            {
                heading = east;
                return true;
            }
        case west:
            {
                heading = south;
                return true;
            }
        case east:
            {
                heading = north;
                return true;
            }
    }
}

bool Rover::turnRight()
{
    switch(heading)
    {
        case north:
            {
                heading = east;
                return true;
            }
        case south:
            {
                heading = west;
                return true;
            }
        case west:
            {
                heading = north;
                return true;
            }
        case east:
            {
                heading = south;
                return true;
            }
    }


}



bool Rover::move()
{
    switch (heading)
    {
        case north: y++; return true; break;
        case west: x--;return true; break;
        case south: y--;return true; break;
        case east: x++;return true; break;
    }
}

int main()
{
    Map m(15,5,' ');
    Rover r;
    r.land(m);
}
