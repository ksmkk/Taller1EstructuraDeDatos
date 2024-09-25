
#include "MaterialBibliografico.h"
#include <iostream>
using namespace std;

MaterialBibliografico::MaterialBibliografico(std::string tipo, std::string nombre, std::string autor, int isbn) {
    this ->tipo = tipo;
    this->nombre = nombre;
    this->autor = autor;
    this -> isbn = isbn;

}
void MaterialBibliografico::mostrarInformacion() {
    std::cout<<"Nombre: "<<this->nombre<<std::endl;
    std::cout<<"autor: "<<this->autor<<std::endl;
    std::cout<<"isbn: "<<this->isbn<<std::endl;
}

void MaterialBibliografico::setTipo(std::string tipo) {
    this -> tipo = tipo;
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

string MaterialBibliografico::getTipo() {
    return tipo;
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

bool MaterialBibliografico::getPrestado() {
    return prestado;
}

void MaterialBibliografico::prestar() { 
    prestado = true; 
}

void MaterialBibliografico::devolver() { 
    prestado = false; 
}