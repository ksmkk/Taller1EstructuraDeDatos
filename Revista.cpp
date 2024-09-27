#include "Revista.h"
#include<iostream>
using namespace std;

Revista::Revista(std::string nombre, std::string autor, int isbn, int Nedicion, std::string mesPublicacion)
    :MaterialBibliografico("Revista", nombre, autor, isbn)  
{
    this->Nedicion = Nedicion;
    this->mesPublicacion = mesPublicacion;
}

void Revista::MostrarInformacion() {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Numero de edicion: " << Nedicion << std::endl;
    std::cout << "Mes de publicacion: " << mesPublicacion << std::endl;
}

int Revista::getNedicion() {
    return Nedicion;
}

std::string Revista::getMesPublicacion() {
    return mesPublicacion;
}

Revista::~Revista() {
    std::cout << "Se destruyo la revista: " << nombre << std::endl;
}
