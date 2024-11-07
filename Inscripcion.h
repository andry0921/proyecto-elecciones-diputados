
#ifndef Inscripcion_H
#define Inscripcion_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "Candidato.h"
#include "Partido.h"
#include "Libreria/Lista.h"
using namespace std;


 
class Inscripcion {

   private:
   	Lista<Candidato> candidatos;
    Lista<Partido> partidoss;
    int candidatosPorPartido[5] = {0};
    Lista<Candidato> partidos[5];
    
     string esloganes[10] = {
        "Tecnologizando el cambio.",
        "El futuro nos llama, respondamos juntos!",
        "Codifica tu futuro.",
        "La universidad del mañana, hoy.",
        "Mas que bytes, ideas.",
        "Conectados por la tecnologia, unidos por un mismo sueño.",
        "Tu voz, nuestra tecnologia.",
        "Juntos, haremos historia.",
        "Una comunidad, un futuro.",
        "La tecnologia al servicio de todos."
    };


   public:
    // Constructor
    Inscripcion();

    void mensaje();

    Candidato CrearMarca();
    
    Lista<Candidato> getCandidatos();
	
	Lista<Partido> getPartidos();

    //Verificar si se puede ingresar el candidato
    bool verificarDisponibilidad(Candidato);
    
    //Verificar si se puede ingresar el candidato
    bool verificarDisponibilidadPartido(Partido);
    
    //Verifica si existe el candidato en la lista
    bool verificarSiExisteCantidato(Candidato);
    //Verifica si existe el partido en la lista
    bool verificarSiExistePartido(int idPartido,bool esRegistro);

    // Metodo para registrar un candidato
    void RegistrarCandidato(Candidato);
    
    // Metodo para registrar un partido, regresa el Id del partido
    int RegistrarPartido();

    //Metodo para modificar candidato
    void ModificarCandidato(string);

    //Método para eliminar un candidato
    void EliminarCandidato(string);

    void MostrarCandidatos();
    void MostrarPartidos();
    
    Candidato BuscarCandidato(string cedula);

    // reportes
    void ReporteGeneral();
	bool mostrarReporteCompleto();
    
    //helpers
    void printCentered(const string& text);
	void printFullLine(char symbol = '-');
    string trim(const std::string& str);
	int generarNumeroAleatorio(); 
	string generarEsloganAletorio();


};

#endif
