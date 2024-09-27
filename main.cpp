#include <iostream>
#include "Menu.h"
using namespace std;
int main() {
    Menu* menu = new Menu();
    menu->LeerUsuariosyMateriales();
    menu->MostrarMenu();
    
    delete menu;
    return 0;
}

