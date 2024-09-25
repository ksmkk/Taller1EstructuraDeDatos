#ifndef MENU_H
#define MENU_H

#include "MaterialBibliografico.h" 
#include "Libro.h"
#include "Revista.h"
#include <iostream>

class Menu {
private:
    MaterialBibliografico *biblioteca[100];
    int contadorMateriales;
    
public:
    Menu();
    void MostrarMenu();
    void AgregarMaterial();
    void MostrarInfoMaterial();
    void LeerUsuariosyMateriales();
    bool LeerUsuario(std::string linea);
    bool LeerMateriales(std::string linea);
    void BuscarMaterial();
    void PrestarMaterial();
    void DevolverMaterial();
    void CrearUsuario();
    void BuscarUsuario();
    void BorrarUsuario();


};

#endif
