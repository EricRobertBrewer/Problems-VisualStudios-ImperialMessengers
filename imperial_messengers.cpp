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

#define DEBUG false

static const int CAPITAL = 0;
static const int NEIGHBOR_UNREACHABLE = -1;
static const int DISTANCE_UNDISCOVERED = -2;

int main(int argc, char* argv[]) {

    ifstream fin;
    fin.open("wikipedia.in");
    if (fin.fail()) {
        cout << "File open error. Couldn\'t open file " << argv[1] << "." << endl;
        exit(1);
    }

    int cities;
    fin >> cities;

    int distanceFromNeighbor[cities][cities];
    distanceFromNeighbor[0][0] = NEIGHBOR_UNREACHABLE;
    for (int i = 1; i < cities; i++) {
        for (int j = 0; j < i; j++) {
            string s;
            fin >> s;
            stringstream ss;
            ss << s;
            if (s.compare("x") == 0) {
                distanceFromNeighbor[i][j] = NEIGHBOR_UNREACHABLE;
            } else {
                ss >> distanceFromNeighbor[i][j];
            }
            distanceFromNeighbor[j][i] = distanceFromNeighbor[i][j];
        }
        distanceFromNeighbor[i][i] = NEIGHBOR_UNREACHABLE;
    }

    bool visited[cities];
    for (int i = 0; i < cities; i++) {
        visited[i] = false;
    }

    int distanceFromCapital[cities];
    distanceFromCapital[CAPITAL] = 0;
    for (int i = 1; i < cities; i++) {
        distanceFromCapital[i] = DISTANCE_UNDISCOVERED;
    }

    if (DEBUG) {
        for (int i = 0; i < cities; i++) {
            for (int j = 0; j < cities; j++) {
                cout << distanceFromNeighbor[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Here we go
    for (int pivot = 0; pivot < cities; pivot++) {
        if (!visited[pivot]) {
            for (int currentNeighbor = 1; currentNeighbor < cities; currentNeighbor++) {
                if (distanceFromNeighbor[pivot][currentNeighbor] != NEIGHBOR_UNREACHABLE) {
                    if (distanceFromCapital[currentNeighbor] == DISTANCE_UNDISCOVERED) {
                        distanceFromCapital[currentNeighbor] = distanceFromNeighbor[pivot][currentNeighbor] + distanceFromCapital[pivot];
                    } else if (distanceFromCapital[pivot] + distanceFromNeighbor[pivot][currentNeighbor] < distanceFromCapital[currentNeighbor]) {
                        distanceFromCapital[currentNeighbor] = distanceFromNeighbor[pivot][currentNeighbor] + distanceFromCapital[pivot];
                    }
                }
            }
            visited[pivot] = true;
        }
    }

    int greatest = distanceFromCapital[1];
    for (int i = 2; i < cities; i++) {
        if (distanceFromCapital[i] > greatest) {
            greatest = distanceFromCapital[i];
        }
    }
    cout << greatest << endl;

    return 0;
}
