#include <iostream>
#include "Menu.h"
using namespace std;
int main() {
    Menu* menu = new Menu();
    menu->MostrarMenu();
    
    delete menu;
    return 0;
}

