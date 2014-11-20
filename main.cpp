#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

#include "tinythread.h"
#include "millisleep.h"
#include "Song.h"
#include "Request.h"

using namespace std;
using namespace tthread;

void CargarListaCaciones(std::vector<Song> &vCanciones);

class RadioApp {
    vector<Request> vPeticiones;    //Peticiones que se van a reproducir
    vector<Song> vCanciones;        //Canciones del documento .txt
    
    thread threadReproducirCanciones;
    mutex semaforo;
    bool pinchar;

    static void hebraReproducirCanciones(void *arg) {
        RadioApp *radioApp = static_cast<RadioApp *> (arg);
        radioApp->reproducirCanciones();
    }

public:

    RadioApp() : threadReproducirCanciones(hebraReproducirCanciones, this) {
        pinchar = true;
    }

    void reproducirCanciones() {
        do {
            // Esperar 1 seg. hasta ver si hay alguna canción nueva en la lista de peticiones
            millisleep(1000); 
            
            while (pinchar && !vPeticiones.empty()) {
                // Sacar una canción y reproducirla
                semaforo.lock();
                //Coge la que tenga más prioridad (última)
                int cancion = vPeticiones.back().getCod();
                vPeticiones.erase(vPeticiones.end());
                semaforo.unlock();

                cout << "Reproduciendo canción " << 
                        vCanciones[cancion - 1].GetTitle() << 
                        " de " << vCanciones[cancion - 1].GetArtist() <<
                        "... (" << vCanciones[cancion - 1].GetCode() << ")" << endl;
                // Simular el tiempo de reproducción de la canción (entre 2 y 12 seg.)
                millisleep(2000 + 1000 * (rand() % 10));
            }
            
        } while (pinchar);
    }

    void solicitarCanciones() {
        int cancion; //Código de la canción que se añadirá a vPeticiones
        
        CargarListaCaciones(vCanciones);
        
        cout << "¡Bienvenido a Radionauta v4!" << endl;
        cout << "Introduce el código de la canción que quieres reproducir:" 
                << endl;
        
        // Pedir canciones hasta que se introduce "0"
        do {
            cin >> cancion;

            //Asegurarse de que la canción introducida es válida
            while (cancion < 0 || cancion > vCanciones.size()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Lo sentimos, no disponemos de esa canción." << endl;
                cin >> cancion;
            }
            
            semaforo.lock();
            
            //Código fuente para añadir canciones a vPeticiones
            Request peticion(cancion); 
            vPeticiones.push_back(peticion);
            
            semaforo.unlock();

        } while (cancion != 0);
        
      
        pinchar = false;
        threadReproducirCanciones.join();
    }
};

/**
 * 
 * @param lSongs    Lista con las canciones (por referencia)
 * @return          void
 * @description     Este procedimiento carga en la lista de canciones todas las
 *                  canciones que se encuentran en el archivo de canciones para
 *                  tal fin ("canciones.txt") en el directorio del proyecto.
 */
void CargarListaCaciones(std::vector<Song> &vCanciones) {
    try {
        // Opens a file
        fstream fi("canciones.txt");
        string line, atribute[3];

        while (!fi.eof()) {
            getline(fi, line);
            stringstream lineStream(line);

            int i = 0;
            while (getline(lineStream, atribute[i], '|')) {
                i++;
            };

            int cod = atoi(atribute[0].c_str());
            Song s(cod, atribute[1], atribute[2]);
            vCanciones.push_back(s);
        }
        fi.close();
        vCanciones.pop_back();
    } catch (std::exception &e) {
        cout << "The file could not be open";
    }
}

int main(int argc, char** argv) {
    RadioApp app;
    app.solicitarCanciones();

    return 0;
}