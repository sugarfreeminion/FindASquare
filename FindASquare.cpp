/*************************************************************************
 * Author:          sugarfreeoh
 * Date:            20 March 2016
 * Description:     Check if four coordinates make a square.
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct coordinate
{
    unsigned int x;
    unsigned int y;
};

void ParseCoordinate(string sCoord, coordinate &coord);
double Distance(coordinate &pointOne, coordinate &pointTwo);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string line;
        string t;

        coordinate a;
        coordinate b;
        coordinate c;
        coordinate d;

        string delimiter = ", ";

        while(getline(inputFile,line))
        {
            size_t pointOneLoc;
            size_t pointTwoLoc;
            size_t pointThreeLoc;
            
            string pointOne;
            string pointTwo;
            string pointThree;
            string pointFour;
            
            vector<double> distances;

            stringstream ss;

            unsigned int countSides = 0;

            bool hasEqualSides = false;
            bool hasEqualDiagonals = false;

            //cout << "Input Line: " << line << endl;

            ss << line;

            pointOneLoc = line.find(delimiter);
            pointTwoLoc = line.find(delimiter,pointOneLoc+delimiter.size());
            pointThreeLoc = line.find(delimiter,pointTwoLoc+delimiter.size());

            pointOne = line.substr(1,pointOneLoc-2);
            ParseCoordinate(pointOne,a);

            pointTwo = line.substr(pointOneLoc+delimiter.size()+1,pointTwoLoc - pointOneLoc - delimiter.size()-2);
            ParseCoordinate(pointTwo,b);

            pointThree = line.substr(pointTwoLoc+delimiter.size()+1,pointThreeLoc - pointTwoLoc - delimiter.size() - 2);
            ParseCoordinate(pointThree,c);

            pointFour = line.substr(pointThreeLoc+delimiter.size()+1,line.size()-pointThreeLoc - delimiter.size() - 2);
            ParseCoordinate(pointFour,d);

            /*
            cout << "A: " << a.x << "," << a.y << endl;
            cout << "B: " << b.x << "," << b.y << endl;
            cout << "C: " << c.x << "," << c.y << endl;
            cout << "D: " << d.x << "," << d.y << endl;

            cout << "Distance from A to B: " << Distance(a,b) << endl;
            cout << "Distance from A to C: " << Distance(a,c) << endl;
            cout << "Distance from A to D: " << Distance(a,d) << endl;

            cout << "Distance from D to B: " << Distance(d,b) << endl;
            cout << "Distance from D to C: " << Distance(d,c) << endl;

            cout << "Distance from C to B: " << Distance(c,b) << endl;
            */

            distances.push_back(Distance(a,b));
            distances.push_back(Distance(a,c));
            distances.push_back(Distance(a,d));
            distances.push_back(Distance(d,b));
            distances.push_back(Distance(c,d));
            distances.push_back(Distance(b,c));

            for(vector<double>::iterator it=distances.begin();
                it!=distances.end();
                ++it)
            {
                countSides = count(distances.begin(),distances.end(),*it);

                if(countSides == 2)
                    hasEqualDiagonals = true;
                if(countSides == 4)
                    hasEqualSides = true;

                if(hasEqualDiagonals && hasEqualSides)
                    break;
            }

            if(hasEqualDiagonals && hasEqualSides)
                cout << "true" << endl;
            else
                cout << "false" << endl;

            ss.str("");
            ss.clear();
        }
    }

    return 0;
}

double Distance(coordinate &a, coordinate &b)
{
    unsigned int tempX; 
    unsigned int tempY; 

    if(a.x > b.x)
        tempX = a.x - b.x;
    else
        tempX = b.x - a.x;

    if(a.y > b.y)
        tempY = a.y - b.y;
    else
        tempY = b.y - a.y;

    double result = sqrt(pow(tempX,2) + pow(tempY,2));

    return result;
}

void ParseCoordinate(string sCoord, coordinate &coord)
{
    size_t delimiterLoc;

    string temp;

    stringstream ss;

    delimiterLoc = sCoord.find(',');

    temp = sCoord.substr(0,delimiterLoc);

    ss << temp;
    ss >> coord.x;

    ss.str("");
    ss.clear();

    temp = sCoord.substr(delimiterLoc+1);

    ss << temp;
    ss >> coord.y;
}
