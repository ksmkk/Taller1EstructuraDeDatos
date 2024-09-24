
#include "MaterialBibliografico.h"
#ifndef LIBRO_H
#define LIBRO_H
#pragma once
#include <iostream>
class Libro : public MaterialBibliografico {
private:
    std::string fechaPublicacion;
    std::string resumen;
public:

    Libro(std::string nombre, std:: string autor, int isbn, std::string fechaPublicacion, std::string resumen);

    void MostrarInformacion();
    std:: string getfechaPublicacion();
    std:: string getresumen();
    void setresumen(std::string resumen);
    virtual ~Libro();
};
#endif //LIBRO_H
