#include "Libro.h"
#include<iostream>

Libro::Libro(std::string nombre, std:: string autor, int isbn, std::string fechaPublicacion, std::string resumen)
    :MaterialBibliografico(nombre, autor, isbn ){
    this -> fechaPublicacion = fechaPublicacion;
    this -> resumen = resumen;
}
std::string Libro::getresumen() {
    return resumen;
}
std::string Libro::getfechaPublicacion() {
    return fechaPublicacion;
}
void Libro::MostrarInformacion() {
    std::cout <<"Fecha de publicación: "<<fechaPublicacion<< std::endl;
    std::cout <<"Resumen: "<<resumen<< std::endl;
}
void Libro::setresumen(std::string resumen) {
    this->resumen = resumen;
}
 Libro:: ~Libro() {

}
