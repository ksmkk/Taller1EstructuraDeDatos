

#ifndef REVISTA_H
#define REVISTA_H
#pragma once
#include "MaterialBibliografico.h"

class Revista : public MaterialBibliografico {
private:
    int Nedicion;
    std::string mesPublicacion;
    public:
    Revista(std::string nombre, std:: string autor, int isbn, int Nedicion, std::string mesPublicacion);
    void MostrarInformacion();
    std::string getMesPublicacion();
    int getNedicion();

    virtual ~Revista();
};
#endif //REVISTA_H
