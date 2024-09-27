#include "Usuario.h"
#include "MaterialBibliografico.h"
#include <iostream>

Usuario::Usuario(string nombre, int id) {
    this->nombre = nombre;
    this->id = id;
}

string Usuario::getNombre() {
    return this->nombre;
}

int Usuario::getId() {
    return this->id;
}

string Usuario::getMaterialBibliografico() {
    string result = "";
    for (int i = 0; i < 5; i++) {
        if (listamaterialesPrestados[i] != nullptr) {
            result += listamaterialesPrestados[i]->getNombre(); 
            result += "\n";
        }
    }
    return result;
}

void Usuario::setNombre(string nombre) {
    this->nombre = nombre;
}

void Usuario::setId(int id) {
    this->id = id;
}

void Usuario::setMaterialBibliografico(MaterialBibliografico* matBib, int posicion) {
    if (posicion >= 0 && posicion < 5) {
        listamaterialesPrestados[posicion] = matBib;
    }
}

void Usuario::PrestarMaterial(MaterialBibliografico* material) {
    for (int i = 0; i < 5; i++) {
        if (listamaterialesPrestados[i] == nullptr) {
            listamaterialesPrestados[i] = material;
            break;
        }
    }
}

void Usuario::DevolverMaterial(int posicion) {
    if (posicion >= 0 && posicion < 5) {
        listamaterialesPrestados[posicion] = nullptr;
    }
}

void Usuario::MostrarPrestados() {
    std::cout << "Materiales prestados: " << std::endl;
    for (int i = 0; i < 5; i++) {
        if (listamaterialesPrestados[i] != nullptr) {
            std::cout << listamaterialesPrestados[i]->getNombre() << std::endl;
        }
    }
}

Usuario::~Usuario() {
    std::cout << "Se destruyo el usuario: " << nombre<< std::endl;
}
