#pragma once
#include <iostream>
#include <string>
#include <array>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Map {
public:
    static Map* instance;

    string mapPattern[25] = {
        "#######################", // 0  // #= Bricks
        "#Q  S  W#Q  S  W#"  , // 1  // X= Ghosts direction condition
        "#@### #### # #### ###@#"  , // 2  // c= Pacman char
        "# ### #### # #### ### #"  , // 3
        "#D  X S A A S X  F#"  , // 4
        "# ### # ####### # ### #"  , // 5
        "#E  F# ####### #D  R#"  , // 6
        "##### #E W#Q R# #####"  , // 7  //-------
        "##### #### # #### #####"  , // 8  // A=LRU
        "##### #Q AGA W# #####"  , // 9  // S=LRD
        "##### # ###-### # #####"  , // 12 // D=UDR
        "0====X F#BP*IC#D X====0"  , // 11 // F=UDL
        "##### # ####### # #####"  , // 12
        "##### #D0001000F# #####"  , // 13 // 1=Fruit location
        "##### # ####### # #####"  , // 14
        "##### # ####### # #####"  , // 15 // BPIC=Ghosts char
        "#Q  X A W#Q A X  W#"  , // 16
        "# ### #### # #### ### #"  , // 17
        "#E W#D S AcA S F#Q R#"  , // 18
        "### # # ####### # # ###"  , // 19
        "#Q A R#E W#Q R#E A W#"  , // 20
        "# ######## # ######## #"  , // 24
        "#@######## # ########@#"  , // 22
        "#E    A A    R#"  , // 23
        "#######################"  // 24
    };

    // 01234567890123456789012
    string mazeGrid[23][25];
    CircleShape dotsArr[222]; // 222 dots
    int dotsCount = 0;

    Map() {
        cout << "Maze class OK" << endl;
        instance = this;
    }

    ~Map() {}

    void initMap() {
        int colum = 0, row = 0;
        for (int i = 0; i < (map::mapW * map::mapH); i++) {
            if (colum >= map::mapW) {
                colum = 0;
                row++;
            }
            string str = mapPattern[row].substr(colum, 1);
            mazeGrid[colum][row] = str;

            if (isDot(str)) {
                dotsArr[dotsCount] = getDots(colum, row, str);
                dotsCount++;
            }

            colum++;
        }
    }

    void drawWall(RenderWindow* window) {
        for (int i = 0; i < dotsCount; i++) {
            window->draw(dotsArr[i]);
        }
    }

private:
    static int mapW, mapH;
    int wallShapeCount = 0;

    bool isDot(string str) {
        return str != "0" && str != "=" &&
            str != "B" && str != "P" &&
            str != "I" && str != "C" &&
            str != "G" && str != "*" &&
            str != "1" && str != "-" && str != "c";
    }

    CircleShape getDots(int col, int row, string str) {
        float radius = 3;
        int offset = 12;
        Color color = Color::Yellow;
        if (str == "@") {
            radius = 10;
            offset = 6;
        }

        CircleShape dot;
        dot.setRadius(radius);
        dot.setFillColor(color);
        dot.setPosition(col * 30 + offset, row * 30 + offset);
        return dot;
    }
};

Map* Map::instance;
int Map::mapW = 23;
int Map::mapH = 25;
