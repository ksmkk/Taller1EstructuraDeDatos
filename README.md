# Simulador de Biblioteca Digital
Descripción
Este proyecto es un simulador de biblioteca digital que permite realizar las siguientes acciones:

Agregar nuevos libros y revistas.
Buscar materiales bibliográficos por título o autor.
Gestionar el préstamo y devolución de materiales.
Administrar usuarios de la biblioteca.
El proyecto está desarrollado en C++ y utiliza conceptos de Programación Orientada a Objetos (POO), punteros y asignación dinámica de memoria para gestionar los materiales bibliográficos y los usuarios.

Funcionalidades
Agregar Material a la Biblioteca:

Libros y revistas pueden ser añadidos a la biblioteca con atributos específicos como título, autor, ISBN, etc.
Mostrar Información de los Materiales:

Listado de todos los materiales en la biblioteca mostrando su información detallada.
Buscar Material:

Función para buscar materiales por título o autor.
Préstamo y Devolución de Material:

Los usuarios pueden pedir prestado un material (máximo 5 a la vez) y devolverlo. El estado de los materiales se actualiza automáticamente.
Gestión de Usuarios:

Los usuarios pueden ser creados, buscados o eliminados del sistema. Cada usuario tiene un registro de los materiales prestados.
Persistencia de Datos:

Los datos de la biblioteca y los usuarios se pueden guardar y cargar desde archivos de texto utilizando fstream.
Estructura del Código
Lenguaje de programación: C++
Compilador: g++
Estructura:
Código organizado en archivos .cpp y .h para mantener la modularidad.
Uso de punteros y arrays estáticos para gestionar la memoria.
Ejecución del Programa
Para ejecutar el programa, utiliza los siguientes comandos:

bash
Copiar código
g++ main.cpp Menu.cpp Libro.cpp Revista.cpp Usuario.cpp MaterialBibliografico.cpp -o simulador_biblioteca
./simulador_biblioteca
Ejemplo de Objetos Creados en el main
cpp
Copiar código
Menu* menu = new Menu();
menu->MostrarMenu();
menu: Objeto de tipo Menu que gestiona las interacciones con el usuario mediante un menú en consola.
