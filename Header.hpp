# pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <utility>
#include <functional>



#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <X11/Xlib.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

inline void pause() {
#ifdef _WIN32
    system("pause");
#else
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
}
