#ifndef USUARIO_H
#define USUARIO_H
#pragma once
#include <string>
#include "MaterialBibliografico.h"
using namespace std;

class Usuario {
    private:
    string nombre;
    int id;
    MaterialBibliografico* listamaterialesPrestados[5];
    public:
    Usuario(string nombre, int id);
    string getNombre();
    int getId();
    string getMaterialBibliografico();
    
    void setNombre(string nombre);
    void setId(int id);
    
    void setMaterialBibliografico(MaterialBibliografico* material, int posicion);
    
    void PrestarMaterial(MaterialBibliografico* material);  
    void DevolverMaterial(int posicion); 
    void MostrarPrestados();
    ~Usuario();
};

#endif //USUARIO_H