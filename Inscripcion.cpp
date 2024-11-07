#include "Inscripcion.h"
#include <iostream>

Inscripcion::Inscripcion() {}

void mensaje(){
    std::cout << "mensaje de objeto inscripcion." << std::endl; // Mensaje de depuración
}

Candidato Inscripcion::CrearMarca() {
    Candidato candidatos;
    string ced, nomb, apel;
    int votos, idprd;

    ced = "-99999";
    nomb = "$$$$$";
    apel = "$$$$$";
    votos = -9999999;
    idprd = -9999999;

    candidatos.setCedula(ced);
    candidatos.setNombre(nomb);
    candidatos.setApellido(apel);
    candidatos.setIdPartido(idprd);
    //candidatos.setEstatusInicial();

    return candidatos;
}

Lista<Candidato> Inscripcion::getCandidatos() {
    	return candidatos;
	}
	
Lista<Partido> Inscripcion::getPartidos() {
    	return partidoss;
	}
	

bool Inscripcion::verificarDisponibilidad(Candidato cand){
    if (cand.getIdPartido() < 0 || cand.getIdPartido() >= 5) {
        std::cout << "ID de partido no válido." << std::endl;
        return false;
    }
    if (candidatosPorPartido[cand.getIdPartido()] >= 5) {
        std::cout << " El partido ya tiene 5 candidatos inscritos." << std::endl;
        return false;
    }
    if (candidatos.Contar() >= 25) {
        std::cout << " Se alcanzó el máximo de 25 candidatos." << std::endl;
        return false;
    }
    
    //std::cout << "\n Disponibilidad Aprobada" << std::endl; // Mensaje de depuración
    return true;
}

bool Inscripcion::verificarDisponibilidadPartido(Partido parti){
    if (parti.getId() <= 0 || trim(parti.getNombre()) == "") {
        return false;
    }

    return true;
}

bool Inscripcion::verificarSiExisteCantidato(Candidato cand){
	
	//std::cout << "\nverificarSiExisteCantidato\n" << std::endl;
	
	nodo<Candidato>* actual = candidatos.ObtPrimero();

    while (actual) {
        Candidato candidatoActual = candidatos.ObtInfo(actual);
        if(candidatoActual.getCedula() == cand.getCedula()){
        	std::cout << "\n Este Candidato ya Existe\n" << std::endl;
        	return true;
		}
        actual = candidatos.ObtProx(actual);
    }
    
    return false;
}

bool Inscripcion::verificarSiExistePartido(int idPartido,bool esRegistro){
	
	//cout<<"\nVERIFICAR SI EXISTE EL PARTIDO\n"<<endl;
	
	nodo<Partido>* actual = partidoss.ObtPrimero();
	
  	if(!actual && !esRegistro){
  		cout<<" No existen partidos Registrados"<<endl;
		return true;
	  }

    while (actual) {
        Partido partidoActual = partidoss.ObtInfo(actual);
        if(partidoActual.getId() == idPartido){
        	if(esRegistro)
        		std::cout << " Este Partido ya Existe" << std::endl;
        	return true;
		}
        actual = partidoss.ObtProx(actual);
    }
    
    return false;
}

void Inscripcion::RegistrarCandidato(Candidato cand) {

    candidatos.InsertarNodoCola(cand);
    partidos[cand.getIdPartido()].InsertarNodoCola(cand);
    candidatosPorPartido[cand.getIdPartido()]++;
    //std::cout << "Candidato inscrito exitosamente en RegistrarCandidato." << std::endl; // Mensaje de depuración
}

int Inscripcion::RegistrarPartido() {
	string nombrePartido;
	int idPartido;
	
	cout<<" Id del Partido: "<<endl;
	cin>>idPartido;
	
	cout<<" Nombre del partido: "<<endl;
	cin>>nombrePartido;
	Partido parti(idPartido,nombrePartido);
	
	if(!verificarDisponibilidadPartido(parti)){
      cout << "ID o nombre del partido no válido." << endl;
       return 0;
	}
	
	if(verificarSiExistePartido(parti.getId(),true)){
		cout<<" ¡El Partido con el Id: "<<parti.getId()<<" ya existe!"<<endl;
		return 0;
	}
	
    partidoss.InsertarNodoCola(parti);

    //std::cout << " Partido inscrito exitosamente en RegistrarPartido." << std::endl; // Mensaje de depuración
    return idPartido;
}

void Inscripcion::EliminarCandidato(string cedCandidato) {


    std::cout << "Entrando a EliminarCandidato." << std::endl; // Mensaje de depuración
    // Declara dos objetos de tipo Candidato: candAux y marca

    Candidato candAux, marca;
    // Declara una variable booleana para indicar si se encontró el candidato
    bool encontrado = false;
    // Crea un objeto "marca" que se usará como marcador
    marca = CrearMarca();

// Verifica si la lista de candidatos no está llena
    if (!candidatos.Llena()) {
// Inserta el marcador al final de la lista de candidatos
        candidatos.InsertarNodoCola(marca);
 // Mientras no se haya encontrado el candidato
        while (true){

           // Remueve el último nodo de la lista de candidatos y lo almacena en candAux
            candidatos.RemoverNodoCola(candAux);
          
          // Si el candidato removido es el marcador, se ha llegado al final de la lista

            if (candAux.getCedula() == marca.getCedula()) { break; }

           // Si el candidato removido tiene la cédula que se quiere eliminar
            if (candAux.getCedula() == cedCandidato) {

                    std::cout << "\n\nCandidato eliminado\n\n";
                    encontrado = true;
                    candidatosPorPartido[candAux.getIdPartido()]; // Actualizamos el contador de candidatos por partido
// Si no es el candidato a eliminar, se reinserta en lalista
            } else { candidatos.InsertarNodoCola(candAux); }
        }
      // Si no se encontró el candidato, se imprime un mensaje
        if (!encontrado) { std::cout << "Candidato no encontrado." << std::endl; }
    }
}

void Inscripcion::MostrarCandidatos() {

    nodo<Candidato>* actual = candidatos.ObtPrimero();
    if (!actual) {
        std::cout << "No hay candidatos inscritos en la cola." << std::endl;
        return;
    }

    std::cout << "Candidatos inscritos: \n" << std::endl;
    while (actual) {
        Candidato candidatoActual = candidatos.ObtInfo(actual);
        candidatoActual.mostrarInformacion();
        actual = candidatos.ObtProx(actual);
    }
}

void Inscripcion::MostrarPartidos() {

    nodo<Partido>* actual = partidoss.ObtPrimero();
    if (!actual) {
        std::cout << "\n No hay Partidos inscritos. \n" << std::endl;
        return;
    }

    std::cout << "\n Partidos inscritos: \n" << std::endl;
    while (actual) {
        Partido partidoActual = partidoss.ObtInfo(actual);
        partidoActual.mostrarInformacion();
        actual = partidoss.ObtProx(actual);
    }
}

void Inscripcion::ModificarCandidato(string cedula){
    Candidato candAux, marca;
    bool existe = false;
    marca = CrearMarca();
    if(!candidatos.Llena()){
        candidatos.InsertarNodoCola(marca);
        while(true){
        	candidatos.RemoverNodoCola(candAux);

        	if (candAux.getCedula() == marca.getCedula()) {
        		break;
        	}

        	if (candAux.getCedula() == cedula) {
        		cout << "\n\nIngrese los nuevos datos para el candidato con cedula "<<candAux.getCedula()<<" \n\n";
        		existe = true;
        		string nuevoNombre, nuevoApellido, nuevoStatus;
        		int idNuevoPartido;
        		cout<<"Nombre: "; cin>>nuevoNombre;
        		cout<<"Apellido: "; cin>>nuevoApellido;
        		cout<<"Nuevo ID del partido: "; cin>>idNuevoPartido;
        		cout<<"Nuevo estatus del candidato: "; cin>>nuevoStatus;

        		candAux.setNombre(nuevoNombre);
        		candAux.setApellido(nuevoApellido);
        		candAux.setIdPartido(idNuevoPartido);
        		candAux.setStatus(nuevoStatus);

        		cout << "Candidato modificado exitosamente.\n\n";
        	}
        	candidatos.InsertarNodoCola(candAux);
        }
        if (!existe) {
        	cout << "Candidato no encontrado." << endl;
        }
    }
}

void Inscripcion::ReporteGeneral() {

    
}

Candidato Inscripcion::BuscarCandidato(string ced) {

    if (candidatos.Vacia()) cout << "Lista vacia" << endl;
    Candidato encontrado;
    // crear marca 
    Candidato marca;

    marca = CrearMarca();

   // marca.getCedula() = "$$$";

    candidatos.InsFinal(marca);

    while (candidatos.ObtInfo(candidatos.ObtPrimero()).getCedula() != marca.getCedula()) {
        Candidato actual = candidatos.ObtInfo(candidatos.ObtPrimero());

        if (actual.getCedula() == ced) {
            encontrado = actual;
        }

        candidatos.InsFinal(actual);
        candidatos.AsigPrimero(candidatos.ObtProx(candidatos.ObtPrimero()));


    }

    Candidato primero = candidatos.ObtInfo(candidatos.ObtPrimero());
    if (primero.getCedula() == marca.getCedula()) {
        candidatos.EliComienzo(marca);
        // cout << "eliminada la marca!" << endl; 
    }

    if (encontrado.getNombre().empty()) {
        cout << "Candidato no encontrado" << endl;
        return Candidato();
    }

    return encontrado;
}

string Inscripcion::trim(const string& str) {
    // Encontrar la primera posición no blanca desde el inicio
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) // La cadena está completamente en blanco
        return "";

    // Encontrar la última posición no blanca desde el final
    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    // Retornar la subcadena que va desde `start` hasta `end`
    return str.substr(start, end - start + 1);
}

int Inscripcion::generarNumeroAleatorio(){
	 srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));	
	// generar numero aleatorio desde el 0 hasta el 9
	int numeroAleatorio = rand() % 10;
	return numeroAleatorio;
}         

string Inscripcion::generarEsloganAletorio(){
	return esloganes[generarNumeroAleatorio()];
}                    

bool Inscripcion::mostrarReporteCompleto(){
	int cont = 1;
	nodo<Partido>* actualPartido = partidoss.ObtPrimero();
    if (!actualPartido) {
        cout << "\n No hay Partidos inscritos. \n" << endl;
        return false;
    }
    
    nodo<Candidato>* actualCandidato = candidatos.ObtPrimero();
    if (!actualCandidato) {
        cout << "\n No hay Candidatos inscritos. \n" << endl;
        return false;
    }

	while(actualPartido){
		
		Partido parti = partidoss.ObtInfo(actualPartido);
		cout<<" Candidatos Por el partido: "<<endl;
        printFullLine();
        
        printCentered(parti.getNombre());
		printCentered(generarEsloganAletorio());

		printFullLine();
				
		actualCandidato = candidatos.ObtPrimero();
		while(actualCandidato){
		Candidato cand = candidatos.ObtInfo(actualCandidato);
              
        	
        	if(parti.getId() == cand.getIdPartido()){
        		
        		string nombreCompleto = cand.getNombre() + " " + cand.getApellido();
        		cout<<" "<<cont<<".";
        		cout<<"\n "<<nombreCompleto<<endl;
        		cout<<" C.I: "<<cand.getCedula()<<endl;
        		cont++;
			}
          	actualCandidato = candidatos.ObtProx(actualCandidato);
		}
		 cont = 1;
		 actualPartido = partidoss.ObtProx(actualPartido);
		 printFullLine();
	}   
	return true;   
}

void Inscripcion::printCentered(const string& text) {

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    } else {
        consoleWidth = 80; 
    }


    int padding = (consoleWidth - text.length()) / 2;

    cout << std::string(padding, ' ') << text << endl;
}

void Inscripcion::printFullLine(char symbol) {

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    } else {
        consoleWidth = 80; 
    }

    std::cout << std::string(consoleWidth, symbol) << std::endl;
}

