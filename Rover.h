#include "Map.h"
class Rover
{
    private:
        int x,y;
        enum Direction
        {
            north = 0,
            east = 1,
            south = 2,
            west = 3
        };
        Direction heading;
        char objectUnderRover;
        //Map* p_mars; //a pointer to the map for Mars
        //Map nm; //a map that keeps track of observed cells so far
    public:
        Rover();
        void land(const Map mars); //links a map of Mars to a Rover
        bool turnLeft();
        bool turnRight();
        bool move();
        //void displayMapper();
        //bool executeCommand(char command);
};
