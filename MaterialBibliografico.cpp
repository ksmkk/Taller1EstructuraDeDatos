
#include "MaterialBibliografico.h"
#include <iostream>
using namespace std;

MaterialBibliografico::MaterialBibliografico(std::string nombre, std::string autor, int isbn) {
    this->nombre = nombre;
    this->autor = autor;
    this -> isbn = isbn;

}
void MaterialBibliografico::mostrarInformacion() {
    std::cout<<"Nombre: "<<this->nombre<<std::endl;
    std::cout<<"autor: "<<this->autor<<std::endl;
    std::cout<<"isbn: "<<this->isbn<<std::endl;
}
void MaterialBibliografico::setNombre(std::string nombre) {
    this -> nombre = nombre;
}
void MaterialBibliografico::setAutor(std::string autor) {
    this -> autor = autor;
}
void MaterialBibliografico::setIsbn(int isbn) {
    this -> isbn = isbn;
}

void MaterialBibliografico::setPrestado(bool prestado) {
    this -> prestado = prestado;
}
string MaterialBibliografico::getNombre() {
    return  nombre;
}

int MaterialBibliografico::getIsbn() {
    return isbn;
}
MaterialBibliografico::~MaterialBibliografico() {
    std::cout<<"Se elimino: "<<this->nombre<<std::endl;
}

string MaterialBibliografico::getAutor() {
    return this -> autor;
}

void MaterialBibliografico::prestar() { 
    prestado = true; 
}

void MaterialBibliografico::devolver() { 
    prestado = false; 
}