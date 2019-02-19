#include <iomanip> //for setw()
#include <ctime>
#include <windows.h>
#include "Rover.h"
using namespace std;
/*************************************
*
* This file contains the constructors
* and Functions for the Mars Map.
*
**************************************/
/******** Map Constructors ***********/

Map::Map()
{

}

/*
Map::Map(int x, int y)
{
    dimX = x; dimY = y;
    vector < vector<char> > v (dimY, vector<char>(dimX,' '));
    map = v;
}
****Not necessary*****/

Map::Map(int x, int y, char ch)
{

    dimX = x; dimY = y;
    vector < vector<char> > v (dimY, vector<char>(dimX,ch));
    map = v;
}


/*************************************
*           display()
* This function displays the Map
* Properly. It also shows the Heading
* And footer part of the program.
**************************************/
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

/****************************************
*       setObject(),getObject
* These are the setter and getter functions.
* These are used to fetch and update
* private data`s to the program.
******************************************/

void Map::setObject(int x, int y, char ch)
{
    map[y][x] = ch;
    return;
}


char Map::getObject(int x, int y)
{
    return map[y][x];
}

/***************************************
*       Checking Functions
* These functions will check a specific
* location of the map and return a boolean
* value depending on the type of object.
****************************************/

bool Map::isEmpty(int x, int y)
{
    if (map[y][x] == ' ')
        return true;
    else
        return false;

}

bool Map::isHill(int x, int y)
{
    if(map[y][x] == 178)
        return true;
    else
        return false;
}

bool Map::isTrap(int x, int y)
{
    if(map[y][x] == '#')
        return true;
    else
        return false;
}

bool Map::isGold(int x, int y)
{
    if(map[y][x] == '*')
        return true;
    else
        return false;
}

bool Map::isInsideMap(int x, int y)
{
    if ((x < 0)||(x > dimX)||(y < 0)||(y > dimY))
        return false;
    return true;
}

/***********************************
*           populate()
* Calling this function will set
* random objects on the map.
*
************************************/
void Map::populate()
{
    char charlist[] =
        {'*',
        '#','#',
        178, 178,
        ' ', ' ', ' ', ' ', ' ', ' '};
    srand(time(NULL));
    for(int i = 0; i < dimY; i++)
    {
        for(int j = 0; j < dimX; j++)
        {
            int r = rand() % 11;
            map[i][j] = charlist[r];
        }
    }
}


//Rover Constuctors

Rover::Rover() : mapper()
{

}

Rover::Rover(int height, int width) : mapper(height,width,'?')
{
    x = (height/2);
    y = (width/2);
    mapper.setObject(x,y,'^');
    heading = north;
}

void Rover::land(Map& mars)
{
    p_mars = &mars;
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
        case north:
            {
                int temp_y = (y-1);
                if((mapper.isInsideMap(x,temp_y)==true)&&(mapper.isHill(x,temp_y)==false))
                {
                    y--;
                    if(mapper.isGold(x,y)==true)
                    {
                        //gold++;
                        mapper.setObject(x,y,'^');
                        mapper.setObject(x,(y+1),' ');
                    }
                    else if(mapper.isTrap(x,y)==true)
                    {
                        cout<<"Sorry you are dead!!" << endl;
                    }
                    else
                    {
                        mapper.setObject(x,y,'^');
                        mapper.setObject(x,(y+1),' ');
                    }

                }
                break;
            }
    }

}

void Rover::displayMapper()
{
    switch(heading)
    {
        case north:
            {
                mapper.setObject(x,(y-1),p_mars->getObject(x,(y-1)));
                mapper.setObject((x+1),(y-1),p_mars->getObject((x+1),(y-1)));
                mapper.setObject((x-1),(y-1),p_mars->getObject((x-1),(y-1)));
            }
    }
    mapper.display();
}

int main()
{
    Map m(15,5,' ');
    m.populate();
    m.display();
    Rover r(m.getDimX(),m.getDimY());
    r.land(m);
    r.displayMapper();
    Sleep(3000);
    r.move();
    r.displayMapper();

}
