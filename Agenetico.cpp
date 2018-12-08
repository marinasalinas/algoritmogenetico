
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

// parámetros del algoritmo genético
int tam_genes = 30; //cantidad de genes
int tam_pop = 15; // cantidad de individuos de la población
int tam_torneo = 10; // tamaño del torneo
int generaciones = 50; // cantidad de generaciones
double prob_mutuacion = 0.2; // probabilidades de mutuacion
double prob_cruce = 0.7; // probabilidades de cruzamiento

// poblacion
vector<vector<int> > poblacion;

void inicializapoblacion()
{
	for(int i = 0; i < tam_pop; i++)
	{
		vector<int> individuo;

		for(int j = 0; j < tam_genes; j++)
		{
			int num = rand() % 2; // elige un número en el intervalo [0,1]
			individuo.push_back(num); // inserte el vector del individuo
		}

		poblacion.push_back(individuo); // se inserta en el vector de la poblacion
	}
}

void mostrarpoblacion()
{
	for(int i = 0; i < tam_pop; i++)
	{
		for(int j = 0; j < tam_genes; j++)
			cout << poblacion[i][j] << " ";
		cout << endl;
	}
}

// retorna o score do indivíduo
int obterpuntuacion(vector<int> individuo)
{
	// el score es la suma de los valores de los genes
	int suma = 0;

	for(int i = 0; i < tam_genes; i++)
		suma += individuo[i];
	return suma;
}

// realiza la mutuacion
void mutuacion(vector<int>& individuo)
{
	//escogiendo un gen aleatoriamente en el intervalo [0, tam_genes - 1]
	int gene = rand() % tam_genes;

	// modifica el valor del gen elegido
	if(individuo[gene] == 0)
		individuo[gene] = 1;
	else
		individuo[gene] = 0;
}

// realiza o cruzamento
void cruzamiento(int indice_pai1, int indice_pai2, vector<int>& hijo)
{
	// se elige un punto aleatoriamente en el intervalo [0, tam_genes - 1
	int punto = rand() % tam_genes;

	for(int i = 0; i <= punto; i++)
		hijo.push_back(poblacion[indice_pai1][i]);
	for(int i = punto + 1; i < tam_genes; i++)
		hijo.push_back(poblacion[indice_pai2][i]);
}

// regresa el índice del mejor individuo de la población
int obtermejor()
{
	int indice_mejor = 0;
	int score_mejor = obterpuntuacion(poblacion[0]);

	for(int i = 1; i < tam_pop; i++)
	{
		int score = obterpuntuacion(poblacion[i]);
		if(score > score_mejor)
		{
			indice_mejor = i;
			score_mejor = score;
		}
	}

	return indice_mejor;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	inicializapoblacion();
	//mostrarpoblacion();

	for(int i = 0; i < generaciones; i++)
	{
		for(int j = 0; j < tam_torneo; j++)
		{

			// calcula la probabilidad de cruzamiento
			double prob = ((double) rand() / ((double)RAND_MAX + 1));

			if(prob < prob_cruce)
			{
				// elige a dos padres
				int indice_pai1 = rand() % tam_pop;
				int indice_pai2;

				// garantiza que los índices de los padres no son iguales
				do
				{
					indice_pai2 = rand() % tam_pop;
				}
				while(indice_pai1 == indice_pai2);

				vector<int> hijo;

				// aplica o cruce de 1 punto
				cruzamiento(indice_pai1, indice_pai2, hijo);

				// calcula las probabilidades de mutuacion
				prob = ((double) rand() / ((double)RAND_MAX + 1));

				if(prob < prob_mutuacion)
					mutuacion(hijo);

				int score_pai = obterpuntuacion(poblacion[indice_pai1]);
				int score_hijo = obterpuntuacion(hijo);

				/*si la puntuación del niño es mejor,
				que el padre1, entonces sustituye al padre 1 por el hijo
				*/
				if(score_hijo > score_pai)
				{
					//Hace la copia de los genes del hijo para el padre
					for(int k = 0; k < tam_genes; k++)
						poblacion[indice_pai1][k] = hijo[k];
				}
			}
		}

		cout << "generar " << i + 1 << endl;
		cout << "mejor: ";

		int indice_mejor = obtermejor();
		int score_mejor = obterpuntuacion(poblacion[indice_mejor]);

		for(int j = 0; j < tam_genes; j++)
			cout << poblacion[indice_mejor][j] << " ";

		cout << "\npuntuacion: " << score_mejor << "\n\n";

		//verifica si encontró la solución óptima global
		if(score_mejor == tam_genes)
			break;
	}

	return 0;
}
