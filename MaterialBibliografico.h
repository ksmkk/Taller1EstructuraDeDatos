

#ifndef MATERIALBIBLIOGRAFICO_H
#define MATERIALBIBLIOGRAFICO_H
#pragma once
#include <string>

class MaterialBibliografico {
protected:
    std::string nombre;
    int isbn = 0;
    std::string autor;
    bool prestado;
    public:
    MaterialBibliografico( std::string nombre, std::string autor,int isbn);
    virtual void mostrarInformacion();
    void setNombre(std::string nombre);
    void setIsbn(int isbn);
    void setAutor(std::string autor);
    void setPrestado(bool prestado);
    std::string getNombre();
    int getIsbn();
    std::string getAutor();
    bool getPrestado();
    void prestar();
    void devolver();

    virtual ~MaterialBibliografico();
};



#endif //MATERIALBIBLIOGRAFICO_H
