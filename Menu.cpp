#include "Menu.h"
#include "MaterialBibliografico.h"
#include "Revista.h"
#include "Usuario.h"
#include "Libro.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Menu::Menu()
{
    contadorMateriales = 0;

    for (int i = 0; i < 100; i++)
    {
        biblioteca[i] = nullptr;
    }

    contadorUsuarios = 0;

    for (int i = 0; i < 100; i++)
    {
        ListaUsuarios[i] = nullptr;
    }
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> partes;
    std::string parte;
    std::stringstream ss(str);

    while (std::getline(ss, parte, delimiter))
    {
        partes.push_back(parte);
    }

    return partes;
}

bool Menu::LeerMateriales(std::string linea)
{
    std::vector<std::string> partes = split(linea, '/');

    if (partes.size() >= 6)
    {
        std::string tipo = partes[0];
        std::string nombre = partes[1];
        std::string autor = partes[2];

        try
        {
            int isbn = std::stoi(partes[3]);
            if (tipo == "Libro")
            {
                std::string fechaPublicacion = partes[4];
                std::string resumen = partes[5];

                MaterialBibliografico *nuevoLibro = new Libro(nombre, autor, isbn, fechaPublicacion, resumen);
                if (contadorMateriales < 100)
                {
                    biblioteca[contadorMateriales] = nuevoLibro;
                    contadorMateriales++;
                    std::cout << "Libro leido: " << nuevoLibro->getNombre() << ", Autor: " << nuevoLibro->getAutor() << ", ISBN: " << nuevoLibro->getIsbn() << std::endl;
                    return true;
                }
                else
                {
                    std::cout << "La biblioteca esta llena. No se puede agregar mas materiales." << std::endl;
                    delete nuevoLibro;
                }
            }
            else if (tipo == "Revista")
            {
                int Nedicion = std::stoi(partes[4]);
                std::string mesPublicacion = partes[5];

                MaterialBibliografico *nuevaRevista = new Revista(nombre, autor, isbn, Nedicion, mesPublicacion);
                if (contadorMateriales < 100)
                {
                    biblioteca[contadorMateriales] = nuevaRevista;
                    contadorMateriales++;
                    std::cout << "Revista leida: " << nuevaRevista->getNombre() << ", Autor: " << nuevaRevista->getAutor() << ", ISBN: " << nuevaRevista->getIsbn() << std::endl;
                    return true;
                }
                else
                {
                    std::cout << "La biblioteca esta llena. No se puede agregar mas materiales." << std::endl;
                    delete nuevaRevista;
                }
            }
            else
            {
                std::cout << "Tipo no identificado o numero de partes insuficiente para revista: " << nombre << std::endl;
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Error al convertir a entero: " << e.what() << " en la linea: " << linea << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Error: El numero esta fuera del rango: " << e.what() << " en la linea: " << linea << std::endl;
        }
    }
    else
    {
        std::cout << "Linea no contiene suficientes partes: " << linea << std::endl;
    }

    return false;
}

bool Menu::LeerUsuario(std::string linea)
{
    std::vector<std::string> partes = split(linea, '/');

    if (partes.size() >= 2)
    {
        std::string nombre = partes[0];
        int id = std::stoi(partes[1]);

        Usuario *nuevoUsuario = new Usuario(nombre, id);

        if (contadorUsuarios < 100)
        {
            ListaUsuarios[contadorUsuarios] = nuevoUsuario;
            contadorUsuarios++;
            std::cout << "Usuario leido: " << nuevoUsuario->getNombre() << ", ID: " << nuevoUsuario->getId() << std::endl;
            return true;
        }
        else
        {
            std::cout << "No se pueden agregar mas usuarios. La lista esta llena." << std::endl;
            delete nuevoUsuario;
        }
    }
    else
    {
        std::cout << "Error: La linea no tiene suficientes partes." << std::endl;
    }

    return false;
}

void Menu::LeerUsuariosyMateriales()
{
    std::ifstream archivoU("usuarios.txt");
    std::string linea;

    if (!archivoU)
    {
        std::cout << "No se pudo abrir el archivo de usuarios" << std::endl;
        return;
    }

    int contadorUsuarios = 0;
    while (std::getline(archivoU, linea))
    {
        LeerUsuario(linea);
        contadorUsuarios++;
    }
    archivoU.close();

    std::ifstream archivoM("materiales.txt");
    if (!archivoM)
    {
        std::cout << "No se pudo abrir el archivo de materiales" << std::endl;
        return;
    }

    std::string lineaM;
    int contadorMateriales = 0;
    while (std::getline(archivoM, lineaM))
    {
        LeerMateriales(lineaM);
        contadorMateriales++;
    }
    archivoM.close();
}

void Menu::MostrarMenu()
{

    bool Verdad = true;
    while (Verdad)
    {

        std::string opcion = "";
        std::cout << "1. Agregar material" << std::endl;
        std::cout << "2. Mostrar Informacion de Material" << std::endl;
        std::cout << "3. Buscar Material" << std::endl;
        std::cout << "4. Prestar y Devolver Material" << std::endl;
        std::cout << "5. Gestion de Usuario" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Ingrese su opcion a elegir: " << std::endl;
        std::getline(std::cin, opcion);

        if (opcion == "1")
        {
            AgregarMaterial();
        }
        else if (opcion == "2")
        {
            MostrarInfoMaterial();
        }
        else if (opcion == "3")
        {
            BuscarMaterial();
        }
        else if (opcion == "4")
        {
            OpcionesMateriales();
        }
        else if (opcion == "5")
        {
            OpcionesUsuarios();
        }

        else if (opcion == "6")
        {
            std::cout << "Saliendo del sistema..." << std::endl;
            Verdad = false;
        }
        else
        {
            std::cout << "Opcion no valida." << std::endl;
        }
    }
}

void Menu::OpcionesMateriales()
{
    std::string opcionMaterial;
    std::cout << "1.Prestar material" << std::endl;
    std::cout << "2.Devolver material" << std::endl;
    std::cout << "Ingrese su opcion a elegir: " << std::endl;
    std::getline(cin, opcionMaterial);

    if (opcionMaterial == "1")
    {
        PrestarMaterial();
    }
    else if (opcionMaterial == "2")
    {
        DevolverMaterial();
    }
    else
    {
        std::cout << "Opcion invalida" << std::endl;
    }
}
void Menu::OpcionesUsuarios()
{
    std::string opcionUsuario;
    std::cout << "1. Crear Usuario" << std::endl;
    std::cout << "2. Buscar Usuario" << std::endl;
    std::cout << "3. Borrar Usuario" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Ingrese su opcion a elegir: " << std::endl;

    std::getline(std::cin, opcionUsuario);

    if (std::stoi(opcionUsuario) == 1)
    {
        CrearUsuario();
    }
    else if (std::stoi(opcionUsuario) == 2)
    {
        BuscarUsuario();
    }
    else
    {
        BorrarUsuario();
    }
}

void Menu::AgregarMaterial()
{
    bool EsVerdadero = true;
    std::string nombreMaterial;
    std::string categoria;
    std::string isbn;
    std::string autor;
    std::string fecha;
    std::string numEdicion;
    std::string resumen;
    std::string mes;

    if (contadorMateriales >= 100)
    {
        std::cout << "La biblioteca esta llena" << std::endl;
        return;
    }

    std::ofstream archivo("materiales.txt", std::ios::app);
    if (!archivo)
    {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    while (EsVerdadero)
    {
        std::cout << "Ingrese la categoria del material (Libro/Revista): ";
        std::getline(std::cin, categoria);

        if (categoria == "Libro")
        {
            std::cout << "Ingrese el nombre del Libro: ";
            std::getline(std::cin, nombreMaterial);

            std::cout << "Ingrese el autor del Libro: ";
            std::getline(std::cin, autor);

            std::cout << "Ingrese el ISBN del Libro: ";
            std::getline(std::cin, isbn);

            int isbnNum;
            try
            {
                isbnNum = std::stoi(isbn);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error: ISBN debe ser un numero valido." << std::endl;
                continue;
            }

            std::cout << "Ingrese la fecha de publicacion del Libro: ";
            std::getline(std::cin, fecha);

            std::cout << "Ingrese un resumen del Libro: ";
            std::getline(std::cin, resumen);

            biblioteca[contadorMateriales] = new Libro(nombreMaterial, autor, isbnNum, fecha, resumen);
            std::cout << "Libro creado: " << biblioteca[contadorMateriales]->getNombre() << std::endl;
            contadorMateriales++;

            archivo << categoria << "/" << nombreMaterial << "/" << autor << "/" << isbn << "/" << fecha << "/" << resumen << "\n";

            break;
        }
        else if (categoria == "Revista")
        {
            std::cout << "Ingrese el nombre de la Revista: ";
            std::getline(std::cin, nombreMaterial);

            std::cout << "Ingrese el autor de la Revista: ";
            std::getline(std::cin, autor);

            std::cout << "Ingrese el ISBN de la Revista: ";
            std::getline(std::cin, isbn);

            int isbnNum, numEdicionNum;
            try
            {
                isbnNum = std::stoi(isbn);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error: ISBN debe ser un numero valido." << std::endl;
                continue;
            }

            std::cout << "Ingrese el numero de edicion de la Revista: ";
            std::getline(std::cin, numEdicion);
            try
            {
                numEdicionNum = std::stoi(numEdicion);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error: El numero de edicion debe ser un numero valido." << std::endl;
                continue;
            }

            std::cout << "Ingrese el mes de publicacion de la Revista: ";
            std::getline(std::cin, mes);

            biblioteca[contadorMateriales] = new Revista(nombreMaterial, autor, isbnNum, numEdicionNum, mes);
            std::cout << "Revista creada: " << biblioteca[contadorMateriales]->getNombre() << std::endl;
            contadorMateriales++;

            archivo << categoria << "/" << nombreMaterial << "/" << autor << "/" << isbn << "/" << numEdicion << "/" << mes << "\n";

            break;
        }
        else
        {
            std::cout << "Categoria incorrecta, solo se aceptan libros y revistas." << std::endl;
        }
    }

    archivo.close();
}

void Menu::MostrarInfoMaterial()
{
    std::cout << "Informacion de materiales en la biblioteca:" << std::endl;
    for (int i = 0; i < contadorMateriales; i++)
    {
        biblioteca[i]->mostrarInformacion();
    }
}

void Menu::BuscarMaterial()
{
    std::string tituloBuscado, autorBuscado;
    std::string opcion = "";

    std::cout << "Seleccione el criterio de busqueda:" << std::endl;
    std::cout << "1. Buscar por titulo" << std::endl;
    std::cout << "2. Buscar por autor" << std::endl;
    std::cout << "3. Buscar por titulo y autor" << std::endl;
    std::cout << "Ingrese una opcion: ";

    std::getline(std::cin, opcion);
    bool encontrado = false;

    if (opcion == "1")
    {
        std::cout << "Ingrese el titulo del material: " << std::endl;
        std::getline(std::cin, tituloBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getNombre() == tituloBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Titulo: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    else if (opcion == "2")
    {
        std::cout << "Ingrese el autor del material: " << std::endl;
        std::getline(std::cin, autorBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getAutor() == autorBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Titulo: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    else if (opcion == "3")
    {
        std::cout << "Ingrese el titulo del material: " << std::endl;
        std::getline(std::cin, tituloBuscado);
        std::cout << "Ingrese el autor del material: " << std::endl;
        std::getline(std::cin, autorBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getNombre() == tituloBuscado && biblioteca[i]->getAutor() == autorBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Titulo: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    else
    {
        std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        return;
    }

    if (!encontrado)
    {
        std::cout << "No se ha encontrado un material que coincida con los criterios proporcionados." << std::endl;
    }
}

void Menu::PrestarMaterial()
{
    std::string idUsuario;
    std::cout << "Ingrese su ID para prestar material: ";
    std::getline(std::cin, idUsuario);

    Usuario* usuario = nullptr;

    for (int i = 0; i < contadorUsuarios; ++i)
    {
        if (ListaUsuarios[i]->getId() == std::stoi(idUsuario))
        {
            usuario = ListaUsuarios[i];
            break;
        }
    }

    if (usuario == nullptr)
    {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    std::string nombreMaterial;
    std::cout << "Ingrese el nombre del material a prestar: ";
    std::getline(std::cin, nombreMaterial);

    MaterialBibliografico* materialSeleccionado = nullptr;

    for (int i = 0; i < contadorMateriales; ++i)
    {
        if (biblioteca[i]->getNombre() == nombreMaterial)
        {
            materialSeleccionado = biblioteca[i];
            break;
        }
    }

    if (materialSeleccionado == nullptr)
    {
        std::cout << "Material no encontrado en la biblioteca." << std::endl;
        return;
    }

    usuario->PrestarMaterial(materialSeleccionado);
    std::cout << "Material prestado exitosamente: " << materialSeleccionado->getNombre() << std::endl;
}


void Menu::DevolverMaterial()
{
    std::string idUsuario;
    std::cout << "Ingrese su ID para devolver material: ";
    std::getline(std::cin, idUsuario);

    Usuario* usuario = nullptr;

    for (int i = 0; i < contadorUsuarios; ++i)
    {
        if (ListaUsuarios[i]->getId() == std::stoi(idUsuario))
        {
            usuario = ListaUsuarios[i];
            break;
        }
    }

    if (usuario == nullptr)
    {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    std::string nombreMaterial;
    std::cout << "Ingrese el nombre del material que desea devolver: ";
    std::getline(std::cin, nombreMaterial);

    bool encontrado = false;
    for (int i = 0; i < 5; ++i)
    {
        if (usuario->getMaterialBibliografico().find(nombreMaterial) != std::string::npos)
        {
            usuario->DevolverMaterial(i);
            encontrado = true;
            std::cout << "Material devuelto exitosamente: " << nombreMaterial << std::endl;
            break;
        }
    }

    if (!encontrado)
    {
        std::cout << "El material no se encontro en los prestamos del usuario." << std::endl;
    }
}



void Menu::CrearUsuario()
{
    std::string nombre ="";
    std::string id = "";

    std::cout << "Ingrese nombre del nuevo usuario: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese ID del nuevo usuario: ";
    std::cin >> id;
    cin.ignore();

    if (contadorUsuarios < 100)
    {
        Usuario *nuevoUsuario = new Usuario(nombre, std::stoi(id));
        ListaUsuarios[contadorUsuarios] = nuevoUsuario;
        contadorUsuarios++;
        std::cout << "Usuario creado: " << nuevoUsuario->getNombre() << ", ID: " << nuevoUsuario->getId() << std::endl;

        std::ofstream archivoUsuarios("usuarios.txt", std::ios::app);
        if (archivoUsuarios)
        {
            archivoUsuarios << nombre << "/" << id << "\n";
            archivoUsuarios.close();
        }
    }
    else
    {
        std::cout << "No se pueden agregar mas usuarios." << std::endl;
    }
}

void Menu::BuscarUsuario()
{
    std::string id;
    std::cout << "Ingrese ID del usuario a buscar: ";
    std::getline(std::cin, id);

    for (int i = 0; i < contadorUsuarios; ++i)
    {
        if (ListaUsuarios[i]->getId() == std::stoi(id))
        {
            std::cout << "Usuario encontrado: " << ListaUsuarios[i]->getNombre() << ", ID: " << ListaUsuarios[i]->getId() << std::endl;
            ListaUsuarios[i]->MostrarPrestados();
            return;
        }
    }

    std::cout << "Usuario no encontrado." << std::endl;
}

void Menu::BorrarUsuario()
{
    std::string id;
    std::cout << "Ingrese ID del Usuario a borrar: ";
    std::getline(std::cin, id);

    int indice = -1;

    for (int i = 0; i < contadorUsuarios; ++i)
    {
        if (ListaUsuarios[i]->getId() == std::stoi(id))
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    delete ListaUsuarios[indice];

    for (int i = indice; i < contadorUsuarios - 1; ++i)
    {
        ListaUsuarios[i] = ListaUsuarios[i + 1];
    }

    --contadorUsuarios;

    std::ifstream archivoLectura("usuarios.txt");
    std::ofstream archivoTemporal("usuarios_temp.txt");

    if (!archivoLectura || !archivoTemporal)
    {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoLectura, linea))
    {
        std::stringstream ss(linea);
        std::string nombre;
        int idArchivo;
        std::getline(ss, nombre, '/');
        ss >> idArchivo;

        if (idArchivo != std::stoi(id))
        {
            archivoTemporal << linea << std::endl;
        }
    }

    archivoLectura.close();
    archivoTemporal.close();

    std::remove("usuarios.txt");
    std::rename("usuarios_temp.txt", "usuarios.txt");

    std::cout << "Usuario borrado correctamente." << std::endl;
}

Menu::~Menu()
{
    for (int i = 0; i < contadorMateriales; ++i)
    {
        delete biblioteca[i];
    }

    for (int i = 0; i < contadorUsuarios; ++i)
    {
        delete ListaUsuarios[i];
    }

    std::cout << "Memoria liberada correctamente." << std::endl;
}
