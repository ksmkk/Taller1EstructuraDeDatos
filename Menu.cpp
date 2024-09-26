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

    if (partes.size() >= 5)
    {
        std::string tipo = partes[0];
        std::string nombre = partes[1];
        std::string autor = partes[2];
        int isbn = std::stoi(partes[3]);

        MaterialBibliografico *material = nullptr;

        if (tipo == "Libro" && partes.size() >= 6)
        {
            std::string fechaPublicacion = partes[4];
            std::string resumen = partes[5];

            material = new Libro(nombre, autor, isbn, fechaPublicacion, resumen);
        }
        else if (tipo == "Revista" && partes.size() >= 6)
        {
            int Nedicion = std::stoi(partes[4]);
            std::string mesPublicacion = partes[5];

            material = new Revista(nombre, autor, isbn, Nedicion, mesPublicacion);
        }
        else
        {
            std::cout << "Tipo no identificado: " << tipo << std::endl;
            return false;
        }
        if (material != nullptr)
        {
            if (contadorMateriales < 100)
            {
                biblioteca[contadorMateriales] = material;
                contadorMateriales++;

                return true;
            }
            else
            {
                std::cout << "La biblioteca está llena. No se puede agregar más materiales." << std::endl;

                delete material;
            }
        }
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

        Usuario nuevoUsuario(nombre, id);
        std::cout << "Usuario leído: " << nuevoUsuario.getNombre() << ", ID: " << nuevoUsuario.getId() << std::endl;

        return true;
    }

    return false;
}

void Menu::LeerUsuariosyMateriales()
{

    std::ifstream archivoU("usuarios.txt");
    std::string linea;

    int contadorUsuarios = 0;
    while (std::getline(archivoU, linea))
    {
        if (contadorUsuarios != 0)
        {
            LeerUsuario(linea);
        }
        contadorUsuarios++;
    }

    std::ifstream archivoM("materiales.txt");
    std::string lineaM;

    int contadorMateriales = 0;
    while (std::getline(archivoM, linea))
    {
        if (contadorMateriales != 0)
        {
            LeerMateriales(lineaM);
        }
        contadorMateriales++;
    }

    if (!archivoU || !archivoM)
    {
        std::cout << "No se pudo leer el archivo" << std::endl;
    }
}

void Menu::MostrarMenu()
{

    int opcion;
    bool Verdad = true;

    while (Verdad)
    {

        std::cout << "1. Agregar material" << std::endl;
        std::cout << "2. Mostrar Informacion de Material" << std::endl;
        std::cout << "3. Buscar Material" << std::endl;
        std::cout << "4. Prestar y Devolver Material" << std::endl;
        std::cout << "5. Gestion de Usuario" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Ingrese su opcion a elegir: " << std::endl;
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            AgregarMaterial();
            break;
        case 2:
            MostrarInfoMaterial();
            break;
        case 3:
            BuscarMaterial();
            break;
        case 4:
            OpcionesMateriales();
            break;
        case 5:
            OpcionesUsuarios();
            break;

        case 6:
            std::cout << "Saliendo del sistema..." << std::endl;
            Verdad = false;
            break;
        default:
            std::string a="";
            std::cout << "Opción no válida." << std::endl;
            std::getline(std::cin, a);
            break;
        }
    }
}
void Menu::OpcionesMateriales(){
            int opcionMaterial;
            std::cout << "1.Prestar material" << std::endl;
            std::cout << "2.Devolver material" << std::endl;
            std::cout << "Ingrese su opcion a elegir: " << std::endl;
            std::cin >> opcionMaterial;
            if (opcionMaterial == 1)
            {
                PrestarMaterial();
            }
            else if (opcionMaterial == 2)
            {
                DevolverMaterial();
            }
            else
            {
                std::cout << "Opcion invalida" << std::endl;
            }
}
void Menu::OpcionesUsuarios(){
            int opcionUsuario;
            std::cout << "1. Crear Usuario" << std::endl;
            std::cout << "2. Buscar Usuario" << std::endl;
            std::cout << "3. Borrar Usuario" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Ingrese su opcion a elegir: " << std::endl;
            std::cin >> opcionUsuario;


            if (opcionUsuario == 1)
            {
                CrearUsuario();
                
            }
            else if (opcionUsuario == 2)
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
    int isbn;
    std::string autor;
    std::string fecha;
    int numEdicion;
    std::string resumen;
    std::string mes;

    if (contadorMateriales >= 100)
    {
        std::cout << "La biblioteca está llena" << std::endl;
        return;
    }

    while (EsVerdadero)
    {

        std::cout << "Ingrese la categoria del material (Libro/Revista): ";
        std::cin >> categoria;

        std::ofstream archivo("materiales.txt" , std::ios::app);

        if (!archivo) {
            std::cout << "Error al abrir el archivo." << std::endl;
        }

        if (categoria == "Libro")
        {
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
            std::cout << "Libro creado: " << biblioteca[contadorMateriales]->getNombre() << std::endl;
            contadorMateriales++;
            archivo << categoria<<"/"<<nombreMaterial<<"/"<<autor<<"/"<<isbn<<"/"<<fecha<<"/"<<resumen<< endl;
            break;
        }
        else if (categoria == "Revista")
        {
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
            std::cout << "Revista creada: " << biblioteca[contadorMateriales]->getNombre() << std::endl;
            contadorMateriales++;

            archivo<< categoria<<"/"<<nombreMaterial<<"/"<<autor<<"/"<<isbn<<"/"<<numEdicion<<"/"<<mes<< std::endl;
            break;
        } else {
            std::cout << "Categoria incorrecta, solo se aceptan libros y revistas." << std::endl;
        }
    }
}

void Menu::MostrarInfoMaterial()
{
    std::cout << "Información de materiales en la biblioteca:" << std::endl;
    for (int i = 0; i < contadorMateriales; i++)
    {
        biblioteca[i]->mostrarInformacion();
    }
}

void Menu::BuscarMaterial()
{
    std::string tituloBuscado, autorBuscado;
    int opcion;

    std::cout << "Seleccione el criterio de búsqueda:" << std::endl;
    std::cout << "1. Buscar por título" << std::endl;
    std::cout << "2. Buscar por autor" << std::endl;
    std::cout << "3. Buscar por título y autor" << std::endl;
    std::cout << "Ingrese una opción: "; 
    std::cin >> opcion;
    std::cin.ignore();

    bool encontrado = false;

    if (opcion == 1) {
        std::cout << "Ingrese el título del material: " << std::endl;
        std::getline(std::cin, tituloBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getNombre() == tituloBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Título: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    else if (opcion == 2) {
        std::cout << "Ingrese el autor del material: " << std::endl;
        std::getline(std::cin, autorBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getAutor() == autorBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Título: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    }
    else if (opcion == 3) {
        std::cout << "Ingrese el título del material: " << std::endl;
        std::getline(std::cin, tituloBuscado);
        std::cout << "Ingrese el autor del material: " << std::endl;
        std::getline(std::cin, autorBuscado);

        for (int i = 0; i < contadorMateriales; ++i)
        {
            if (biblioteca[i]->getNombre() == tituloBuscado && biblioteca[i]->getAutor() == autorBuscado)
            {
                std::cout << "Se ha encontrado el material: " << std::endl;
                std::cout << "Título: " << biblioteca[i]->getNombre() << std::endl;
                std::cout << "Autor: " << biblioteca[i]->getAutor() << std::endl;
                encontrado = true;
                break;
            }
        }
    } else {
        std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        return;
    }

    if (!encontrado) {
        std::cout << "No se ha encontrado un material que coincida con los criterios proporcionados." << std::endl;
    }
}


void Menu::PrestarMaterial()
{
    std::string nombre;
    std::cout << "Ingrese el nombre del material a prestar: " << std::endl;
    std::cin >> nombre;
    MaterialBibliografico *buscado;
    for (int i = 0; i < contadorMateriales; i++)
    {
        if (biblioteca[i]->getNombre() == nombre)
        {
            buscado = biblioteca[i];
        }
    }
    buscado->prestar();
}

void Menu::DevolverMaterial()
{
    std::string nombre;
    std::cout << "Ingrese el nombre del material a devolver: " << std::endl;
    std::cin >> nombre;
}

void Menu::CrearUsuario()
{

    std::cout<<"Creando Usuario... "<< std::endl;
    std::string nombre;
    std::string id;
    std::cout << "Ingrese nombre: " << std::endl;
    std::cin >> nombre;
    std::getline(std::cin, nombre);
    
    std::cout << "Ingrese id: " << std::endl;
    std::getline(std::cin, id);
    
    Usuario* creado = new Usuario(nombre, std::stoi(id));
    
    std::ofstream archivo("usuarios.txt" , std::ios::app);

    if (!archivo) {
        std::cout << "Error al abrir el archivo." << std::endl;
    }
    std::string out= nombre+"/"+id+"\n";
    archivo << out;

    archivo.close();

    std::cout << "archivo escrito correctamente" << std::endl;
}

void Menu::BuscarUsuario()
{
    std::string name;
    std::cout<<"Ingrese nombre del Usuario: "<<std::endl;
    std::cin>>name;

    for(int i= 0;i<contadorUsuarios;i++){
        if(ListaUsuarios[i]->getNombre() == name){
            std::cout<<"Se encontro el Usuario "<<ListaUsuarios[i]->getNombre()<<std::endl;
        }
    }
    
}

void Menu::BorrarUsuario()
{
    int id;
    std::cout << "Ingrese ID del Usuario a borrar: " << std::endl;
    std::cin >> id;

    int indice = -1;
    for (int i = 0; i < contadorUsuarios; ++i) {
        if (ListaUsuarios[i]->getId() == id) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        std::cout << "Usuario no encontrado." << std::endl;
        return;
    }

    delete ListaUsuarios[indice]; 
    for (int i = indice; i < contadorUsuarios - 1; ++i) {
        ListaUsuarios[i] = ListaUsuarios[i + 1]; 
    }
    --contadorUsuarios;

   
    std::ifstream archivoLectura("usuarios.txt");
    std::ofstream archivoTemporal("usuarios_temp.txt");

    if (!archivoLectura || !archivoTemporal) {
        std::cout << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoLectura, linea)) {
        
        std::stringstream ss(linea);
        std::string nombre;
        int idArchivo;
        std::getline(ss, nombre, '/');
        ss >> idArchivo;

        
        if (idArchivo != id) {
            archivoTemporal << linea << std::endl;
        }
    }

    archivoLectura.close();
    archivoTemporal.close();

    
    std::remove("usuarios.txt");
    std::rename("usuarios_temp.txt", "usuarios.txt");

    std::cout << "Usuario borrado correctamente." << std::endl;
}
