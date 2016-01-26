/*
imperial_messengers.cpp
Imperial Messengers programming problem
sent by Visual Concepts studios, 2012
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

int getAnswer(string fileName);
bool hasDiscoveredUnvisitedCity(int distance[], bool visited[], int size);
int getClosestDiscoveredUnvisitedCity(int distance[], bool visited[], int size);
int getFarthestCity(int distance[], int size);

int main(int argc, char* argv[]) {

    cout << getAnswer("wikipedia.in") << endl;
    cout << getAnswer("sample.in") << endl;

    return 0;
}

static const int CAPITAL = 0;
static const int NEIGHBOR_UNREACHABLE = -1;
static const int DISTANCE_UNDISCOVERED = -2;

int getAnswer(string fileName) {
    ifstream fin;
    fin.open(fileName.c_str());
    if (fin.fail()) {
        cout << "File open error. Couldn\'t open file " << fileName << "." << endl;
        fin.close();
        return -1;
    }

    int cities;
    fin >> cities;

    int distanceBetweenNeighbors[cities][cities];
    distanceBetweenNeighbors[0][0] = NEIGHBOR_UNREACHABLE;
    for (int i = 1; i < cities; i++) {
        for (int j = 0; j < i; j++) {
            string s;
            fin >> s;
            stringstream ss;
            ss << s;
            if (s.compare("x") == 0) {
                distanceBetweenNeighbors[i][j] = NEIGHBOR_UNREACHABLE;
            } else {
                ss >> distanceBetweenNeighbors[i][j];
            }
            distanceBetweenNeighbors[j][i] = distanceBetweenNeighbors[i][j];
        }
        distanceBetweenNeighbors[i][i] = NEIGHBOR_UNREACHABLE;
    }
    fin.close();

    bool visited[cities];
    for (int i = 0; i < cities; i++) {
        visited[i] = false;
    }

    int distanceFromCapital[cities];
    distanceFromCapital[CAPITAL] = 0; // discovered
    for (int i = 1; i < cities; i++) {
        distanceFromCapital[i] = DISTANCE_UNDISCOVERED;
    }

    // Here we go
    while (hasDiscoveredUnvisitedCity(distanceFromCapital, visited, cities)) {
        int pivot = getClosestDiscoveredUnvisitedCity(distanceFromCapital, visited, cities);
        for (int currentNeighbor = 1/* skip capital */; currentNeighbor < cities; currentNeighbor++) {
            if (!visited[currentNeighbor] && distanceBetweenNeighbors[pivot][currentNeighbor] != NEIGHBOR_UNREACHABLE) {
                if (distanceFromCapital[currentNeighbor] == DISTANCE_UNDISCOVERED) {
                    distanceFromCapital[currentNeighbor] = distanceBetweenNeighbors[pivot][currentNeighbor] + distanceFromCapital[pivot];
                } else if (distanceFromCapital[pivot] + distanceBetweenNeighbors[pivot][currentNeighbor] < distanceFromCapital[currentNeighbor]) {
                    distanceFromCapital[currentNeighbor] = distanceBetweenNeighbors[pivot][currentNeighbor] + distanceFromCapital[pivot];
                }
            }
        }
        visited[pivot] = true;
    }

    int farthest = getFarthestCity(distanceFromCapital, cities);
    return distanceFromCapital[farthest];
}

/*
 * Returns true if an undiscovered, unvisited city exits; otherwise, false.
 */
bool hasDiscoveredUnvisitedCity(int distance[], bool visited[], int size) {
    for (int i = 0; i < size; i++) {
        if (!visited[i] && distance[i] != DISTANCE_UNDISCOVERED) {
            return true;
        }
    }
    return false;
}

/*
 * Returns the index of closest current city.
 */
int getClosestDiscoveredUnvisitedCity(int distance[], bool visited[], int size) {
    int closest = -1;
    for (int i = 0; i < size; i++) {
        if (!visited[i] && distance[i] != DISTANCE_UNDISCOVERED) {
            if (closest == -1 || distance[i] < distance[closest]) {
                closest = i;
            }
        }
    }
    return closest;
}

/*
 * Returns the index of the farthest city.
 */
int getFarthestCity(int distance[], int size) {
    int farthest = 1;
    for (int i = 2; i < size; i++) {
        if (distance[i] > distance[farthest]) {
            farthest = i;
        }
    }
    return farthest;
}
