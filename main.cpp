#include "Partido.h"
#include "Candidato.h"
#include "Inscripcion.h"
#include "Libreria/Lista.h"
#include <iostream>
using namespace std;

int main() {
    Inscripcion inscripcion;
    //inscripcion.mensaje();
    int opcionInicial;
    string cedEliminar;

    // Menu inicial
    inscripcion.printFullLine();
    inscripcion.printCentered("Bienvenido al sistema de gestion de elecciones.");
    inscripcion.printFullLine();
    cout << " 1. Entrar al sistema de gestion de candidatos" << endl;
    cout << " 2. Salir" << endl;
    cout << " \n Elige una opcion: "<<endl;
    cin >> opcionInicial;
    cin.ignore(); // Limpiar el buffer de entrada

    if (opcionInicial == 1) {
        int opcion;
        do {
            cout << "\n--- Menu de gestion de candidatos ---" << endl;
            cout << " 1. Registrar Partido" << endl;
            cout << " 2. Registrar candidato" << endl;
            cout << " 3. Mostrar candidatos" << endl;
            cout << " 4. Buscar candidato" << endl;
            cout << " 5. Modificar candidato" << endl;
            cout << " 6. Eliminar candidato" << endl;
            cout << " 7. Resumen Inscripcion" << endl;
            cout << " 8. Mostrar Partidos Registrados" << endl;
            cout << " 9. Salir\n" << endl;
            cout << " Elige una opcion: \n";
            cin >> opcion;
            cin.ignore(); // Limpiar el buffer de entrada

            switch(opcion) {
            	case 1:{
            		if(inscripcion.RegistrarPartido() <= 0);
						break;
					break;
				}
                case 2: {
                    string cedula, nombre, apellido,nombrePartido;
                    int idPartido,preguntaPartido;
                    
                    cout<<" Desea Crear un partido? 1.SI 2.NO"<<endl;
                    cin>> preguntaPartido;
                    
                    if(preguntaPartido == 1){
                    	idPartido = inscripcion.RegistrarPartido();
                    	if(idPartido <= 0)
                    		break;					
					}

                    cout << " Cedula del candidato: \n";
                    cin>>cedula;
                    cout << " Nombre del candidato: \n";
                    cin>>nombre;
                    cout << " Apellido del candidato: \n";
                    cin>>apellido;
                    if(preguntaPartido != 1){
	                    cout << " ID del Partido del candidato: \n";
	                    cin >> idPartido;      	
					}
                
                    Candidato candidato(cedula, nombre, apellido, idPartido);
                    
                    if(preguntaPartido != 1){
	                    if(!inscripcion.verificarSiExistePartido(idPartido,false))
	                    	break;
					}
                    
                    
                    cout << "\n Registrando candidato: \n" << " C.I: "<<candidato.getCedula() <<"\n"<< " Nombre Completo: "<< candidato.getNombre() << " " << candidato.getApellido() << "\n" << " En el Partido: " <<candidato.getNombrePartido()<<"\n ..."<< endl;


                    if(inscripcion.verificarDisponibilidad(candidato) && !inscripcion.verificarSiExisteCantidato(candidato)){
                        inscripcion.RegistrarCandidato(candidato);
                        cout << "\n Candidato registrado exitosamente." << endl; // Mensaje de depuración
                    }
                    
                    break;
                }
                case 3:
                    inscripcion.MostrarPartidos();
                    break;
                case 4: {

                    string cedulaCandidato;
                    cout << "Ingrese la cedula del candidato" << endl;
                    //cin.ignore();
                    getline(cin, cedulaCandidato);

                    Candidato candi = inscripcion.BuscarCandidato(cedulaCandidato);
                    if (!candi.getNombre().empty())
                    {
                        cout << "Candidato encontrado: " << endl;
                        cout << " Cedula: " << candi.getCedula();
                        cout << " Nombre Completo: " << candi.getNombre() << " " << candi.getApellido();
                        cout << " Partido: " << candi.getNombrePartido();
                        cout << " Status: " << candi.getStatus();
                    }
                    break;

                }
                case 5: {
                	string cedulaModificar;
                	cout<<"Ingrese la cedula del candidato a modificar: "; cin>>cedulaModificar;
                	inscripcion.ModificarCandidato(cedulaModificar);
					break;
                }

                case 6:
                    cout << "Ingrese la cedula del candidato a eliminar: ";
                    cin >> cedEliminar;
                    cin.ignore(); // Limpiar el buffer de entrada
                    inscripcion.EliminarCandidato(cedEliminar);
                    break;

                case 7:{
                    inscripcion.ReporteGeneral();
					break;
				}   
                case 8:{
                    inscripcion.mostrarReporteCompleto();
					break;
				}
               	
				case 9:
					 cout << "Saliendo del sistema de gestion de candidatos." << endl;
				break;
                default:
                    cout << "Opcion no valida. Intenta de nuevo." << endl;
            }
        } while (opcion != 7);
    } else if (opcionInicial == 2) {
        cout << "Saliendo del programa." << endl;
    } else {
        cout << "Opcion no valida. Terminando el programa." << endl;
    }

    system("pause");
    return 0;
}
