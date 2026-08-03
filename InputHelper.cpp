//
// Created by Oscar Guevara Viveros on 7/7/26.
//

#include "InputHelper.h"
#include <iostream>
#include <fstream>
#include <limits>

double InputHelper::getEpsilon()
{
    double epsilon;
    while (true) //infinite loop, only way out is to break
    {
        std::cout << "Epsilon must be between 0 < epsilon <= 1 "; //always say this

        if (!(std::cin >> epsilon)) //did reading the number fail, fail = false then fail! = true so execute
        {
            std::cout << "That is not a number!\n";
            std::cin.clear(); //ignore the fail from cin >> epsilon
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard everything up until a new line
            continue;
        }
        if (epsilon > 0 && epsilon <= 1)
        {
            return epsilon; //if epsilon is between 0 and 1 break out and use it
        }
       // else
            std::cout << "Epsilon must be between 0 and 1\n";

    }
}

double InputHelper::checkDouble()
{
    double input; //output
    while (true) //infinite loop until you get a good user input (double)
    {
        if (!(std::cin >> input)) //while the input is not correct (char) (string) V
        {
            std::cout << "That is not a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // else
            return input; //any input other than char is valid - to +
    }
}

int InputHelper::checkInt()
{
    int input;

    while (true)
    {
        if (!(std::cin >> input))
        {
            std::cout << "That is not a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (input > 0)
        {
            return input;
        }
        //else
            std::cout << "Try again!\n";
    }
}

bool InputHelper::redChecker()
{
    int input;
    while (true)
    {
        if (!(std::cin >> input)){//if fails to read number do this if statement
            std::cout << "That is not a number!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignores the input until the end of the line
            continue;
        }
        if (0 <= input && 1 >= input) //input is 0 or 1
        {
            if (input == 0) //is Red
            {
                return true;
            }
            // is blue

            return false;

        }

        //else try again
        std::cout << "Must be 1 or 0\n";
    }
}

    //filereader
    std::vector<ColoredPoint> InputHelper::readPointsFromFile(const std::string& filename)
    {
        std::vector<ColoredPoint> points;
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cout << "Something went wrong with " << filename << "\n";
            return points;
        }
    int idCounter = 0;
    double x, y;
    int colorFlag;

    while (file >> x >> y >> colorFlag)
    {
        ColoredPoint p;
        p.point = Kernel::Point_2(x,y);
        p.isRed = (colorFlag == 0);
        p.number = idCounter++;
        points.push_back(p);
    }

    file.close();
    return points;
    }


