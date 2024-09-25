#include "Menu.h"
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Usuario.h"
#include "Libro.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> partes;
    std::string parte;
    std::stringstream ss(str);

    while (std::getline(ss, parte, delimiter)) {
        partes.push_back(parte);
    }

    return partes;
}

bool Menu::LeerMateriales(std::string linea) {
     std::vector<std::string> partes = split(linea , ';');

    if (partes.size() >= 5)
    {
        std::string nombre = partes[1];
        std::string autor = partes[2];
        int isbn = std::stoi(partes[3]);

    }
    
}

bool Menu::LeerUsuario(std::string linea) {
    std::vector<std::string> partes = split(linea , ';');

    if (partes.size() >= 2) 
    {
        std::string nombre = partes[0];
        int id = std::stoi(partes[1]); // stoi funciona para convertir de string a int 

        Usuario nuevoUsuario(nombre , id);
        std::cout << "Usuario leído: " << nuevoUsuario.getNombre() << ", ID: " << nuevoUsuario.getId() << std::endl;

        return true;
    }
    
    return false;
}

void Menu::LeerUsuariosyMateriales() {
    
    std::ifstream archivoU("usuarios.txt");
    std::string linea;

    int contadorUsuarios = 0;
    while (std::getline(archivoU,linea)) {
        if (contadorUsuarios != 0)
        {
            LeerUsuario(linea);
        }
        contadorUsuarios++;
    }

    std::ifstream archivoM("materiales.txt");
    std::string lineaM;

    int contadorMateriales = 0;
    while (std::getline(archivoM,linea)) {
       if (contadorMateriales != 0)
        {
            LeerMateriales(lineaM);
        }
        contadorMateriales++;
    }


    if (!archivoU || !archivoM) {
        std::cout << "No se pudo leer el archivo" << std::endl;
    }
}

Menu::Menu() : contadorMateriales(0) {
}

void Menu::MostrarMenu() {
    int opcion;
    std::cout <<"1. Agregar material" << std::endl;
    std::cout <<"2. Mostrar Informacion de Material" << std::endl;
    std::cout <<"3. Buscar Material" << std::endl;
    std::cout <<"4. Prestar y Devolver Material" << std::endl;
    std::cout <<"5. Gestion de Usuario" << std::endl;
    std::cout <<"6. Salir" << std::endl;
    std::cout << "" << std::endl;
    std::cout <<"Ingrese su opcion a elegir: "<< std::endl;
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            AgregarMaterial();
            break;
        case 2:
            MostrarInfoMaterial();
            break;
        case 3:
            std::cout << "Función de búsqueda en construcción." << std::endl;
            break;
        case 4:
            std::cout << "Función de préstamo/devolución en construcción." << std::endl;
            break;
        case 5:
            int opcionUsuario;
            std::cout <<"1. Crear Usuario" << std::endl;
            std::cout <<"2. Buscar Usuario" << std::endl;
            std::cout <<"3. Borrar Usuario" << std::endl;
            std::cout << "" << std::endl;
            std::cout <<"Ingrese su opcion a elegir: "<< std::endl;
            std::cin >> opcionUsuario; 
            
            if (opcionUsuario == 1)
            {
                void CrearUsuario();
            } else if (opcionUsuario == 2) {
                void BuscarUsuario();
            } else {
                void BorrarUsuario();
            }

            
        case 6:
            std::cout << "Saliendo del sistema..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
            break;
    }
}

void Menu::AgregarMaterial() {
    bool EsVerdadero = true;
    std::string nombreMaterial;
    std::string categoria;
    int isbn;
    std::string autor;
    std::string fecha;
    int numEdicion;
    std::string resumen;
    std::string mes;

    if (contadorMateriales >= 100)
    {
        std::cout << "La biblioteca está llena"<<std::endl;
        return;
    }
    

    while (EsVerdadero) {
    
    std::cout << "Ingrese la categoría del material (Libro/Revista): ";
    std::cin >> categoria;

    if (categoria == "Libro") {
        std::cin.ignore();
        
        std::cout << "Ingrese el nombre del Libro: ";
        std::getline(std::cin, nombreMaterial);
    
        std::cout << "Ingrese el autor del Libro: ";
        std::getline(std::cin, autor);

        std::cout << "Ingrese el ISBN del Libro: ";
        std::cin >> isbn;
        std::cin.ignore();

        std::cout << "Ingrese la fecha de publicación del Libro: ";
        std::getline(std::cin, fecha);
        
        std::cout << "Ingrese un resumen del Libro: ";
        std::getline(std::cin, resumen);
        
        biblioteca[contadorMateriales] = new Libro(nombreMaterial, autor, isbn, fecha, resumen);
        std::cout << "Libro creado: " <<  biblioteca[contadorMateriales]->getAutor() << std::endl;
        contadorMateriales++;
        break;
    } 
    else if (categoria == "Revista") {
        std::cin.ignore();
        
        std::cout << "Ingrese el nombre de la Revista: ";
        std::getline(std::cin, nombreMaterial);
    
        std::cout << "Ingrese el autor de la Revista: ";
        std::getline(std::cin, autor);

        std::cout << "Ingrese el ISBN de la Revista: ";
        std::cin >> isbn;
        std::cin.ignore();

        std::cout << "Ingrese el numero de edicion de la Revista: ";
        std::cin >> numEdicion;
        std::cin.ignore();
        
        std::cout << "Ingrese el mes de publicacion de la Revista: ";
        std::getline(std::cin, mes);
        
        biblioteca[contadorMateriales] = new Revista(nombreMaterial, autor, isbn, numEdicion, mes);
        std::cout << "Revista creada: " <<  biblioteca[contadorMateriales]->getAutor() << std::endl;
        contadorMateriales++;
        break;
    } 
    else {
        std::cout << "Categoria incorrecta, solo se aceptan libros y revistas." << std::endl;
        }
    }
}

    

void Menu::MostrarInfoMaterial() {
    std::cout << "Información de materiales en la biblioteca:" << std::endl;
    for (int i = 0; i < contadorMateriales; i++) {
        biblioteca[i]->mostrarInformacion();
    }
}
