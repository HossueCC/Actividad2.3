// =================================================================
//
// File: main.cpp
// Author: Hossue Edgardo Ceja Cartagena A01707761
// Date: 15/09/2022
//
// =================================================================
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


//Función para leer los archivos de entrada
vector<string> readLines(string filename){
	vector<string> lineas;
	ifstream file(filename);
	string linea;


	while (getline(file, linea)){
		lineas.push_back(linea);
	}


	return lineas;
}

//Función para ingresar una cadena a un vector de cadenas
vector<string> split(string linea){


	vector<string> palabras;
	string palabra;

	//Recorremos todo el vector hasta el tamaño de la linea
	for (int i = 0; i < linea.length(); i++){
		//Si el vector encuentra un espacio


		if (linea[i] == ' '){
			
			palabras.push_back(palabra);
			palabra = "";
		}

		else{
			
			palabra += linea[i];
		}
	}


	palabras.push_back(palabra);
	return palabras;
}

//Función para extraer las lineas que cuentan con el prefijo solicitado
vector<string> filter(vector<string> lineas, string palabra){
	
	vector<string> extraccion;
	
	for (string linea : lineas) {

		if (linea.find(palabra) != string:: npos) {
		
		extraccion.push_back(linea);
		}
	}

	//Extrae el prefijo solicitado
	return extraccion;
}

//Ordenamiento de los registros por fecha
vector<string> sortLines(vector<string> lineas){
	sort(lineas.begin(), lineas.end(), [](string a, string b) {
		
		vector<string> aSplit;
		vector<string> bSplit;
		string limitador = "-";
		size_t pos = 0;
		string token;
		
		//Extraemos el día
		while ((pos = a.find(limitador)) != string::npos) {
			//Guardamos la subcadena
			token = a.substr(0, pos);
			aSplit.push_back(token);
			a.erase(0, pos + limitador.length());
		}

		aSplit.push_back(a);
		
		//Extraemos el mes
		while ((pos = b.find(limitador)) != string::npos) {
			token = b.substr(0, pos);
			bSplit.push_back(token);
			b.erase(0, pos + limitador.length());
		}

		bSplit.push_back(b);
		return pair<string, string>(aSplit[1], aSplit[0]) < 
		pair<string, string>(bSplit[1], bSplit[0]);
	});


	return lineas;
}

//Funcion para mantener la ultima columna de cada linea
vector<string> keepLastColumn(vector<string> lineas){
	vector<string> columna;

	for (string linea : lineas) {

		vector<string> palabras = split(linea);
		columna.push_back(palabras[palabras.size() - 1]);
	}

	return columna;
}

//Formato de Impresión de archivo de salida
void month(vector<string> extraccion, ofstream& output, string mes, string fecha){
	vector<string> aux, M, R, columnM, columnR;

	output << mes << endl;
	//Formato de impresióm
	aux = filter(extraccion, fecha);

	//Puerto
	M = filter(aux, " M ");
	R = filter(aux, " R ");
	columnM = keepLastColumn(M);
	columnR = keepLastColumn(R);
	
	//Formato de salida Puerto M
	if(M.size() > 0){
		output << "M " << M.size() << ": "; 
		
		
		for (string linea : columnM){
			output << linea << " ";
		}
		output << endl;
	}

	//Formato de salida Puerto R
	if(R.size() > 0){
		output << "R " << R.size() << ": ";
		for (string linea : columnR){
			output << linea << " ";
		}
	}


	output << endl;
}



int main(int argc, char* argv[]) {
	string limitador = " ", token;
	string primeralinea;

	vector<string> lineas, firstLineSplit, extraccion;

	//Arreglo Mes	
	string monthArray[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
	
	
	string dateArray[12] = {"-01-", "-02-", "-03-", "-04-", "-05-", "-06-", "-07-", "-08-", "-09-", "-10-", "-11-", "-12-"};
	
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	//Restricción de Ejecución
	if (argc != 3) {
		cout << "Se requiere del siguiente formato para la ejecución: " << " <input file> <output file>" << endl;
		return -1;
	}else if (!input) {
		cout << "Error en el formato de ejecución" << argv[1] << endl;
		return -1;
	}else if (!output) {
		cout << "Error de impresión del archivo de salida " << argv[2] << endl;
		return -1;
	}


	//Leemos la entrada y almacenamos en vector
	lineas = readLines(argv[1]);
	primeralinea = lineas[0];
	firstLineSplit = split(primeralinea);

	// Extraemos y guardamos en el vector
	extraccion = filter(lineas, firstLineSplit[1]);
	extraccion.erase(extraccion.begin());
	//Ordenamos por fecha
	extraccion = sortLines(extraccion);



	//FORMATO DE SALIDA
	for (int i = 0; i < 12; i++){
		month(extraccion, output, monthArray[i], dateArray[i]);
	}

	input.close();
	output.close();

	return 0;
}
