/**
 * Universidad del Valle de Guatemala
 * CC3056-10 Programación de microprocesadores
 * Proyecto Microprocesadores grupo X
 * integrantes: 
 *      Marco Jurado 20308
 *      Andrés de la Roca 20332
 *      José Auyón 201579
 * 
 *  Adaptado de method 4 geeksforgeeks
 **/

 // Declaracion de librerias
#include <bits/stdc++.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
using namespace std;
 
//Declaracion de variables globales
pthread_mutex_t lock1; // Bloqueo de hilos
int result = 0;  //almacena resultado final
int F[2][2] = { { 1, 1 }, { 1, 0 } };
int M[2][2] = { { 1, 1 }, { 1, 0 } };
 
void *multiply(void *null)
{
    pthread_mutex_lock(&lock1); //Bloqueo por mutex
    int x = F[0][0] * M[0][0] +
            F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] +
            F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] +
            F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] +
            F[1][1] * M[1][1];
    
    //semaforo 
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
    //semaforo
    

    pthread_mutex_unlock(&lock1); //Desbloqueo por mutex
    pthread_exit(0); //Salida
}
 
// Driver code
int main()
{//Ingreso de numero a ejecutar -------------------------------------
    int err;
    int n = 0;
    cout<< "Ingrese el numero a calcular se sucesion fibonacci: ";
    cin>>n;
    //------------------------------------------------------------------  
    
    //Definir cantidad de threads 
    pthread_t tid[n]; 

    //Execute a fib 
    if ( n == 1 || n == 2 ){
        cout << " el resultado es: 1";
    }
    else if( n == 0 ){
        cout << " el resultado es: 0";
    }
    else{
        int i;
        for(i = 0; i < n; i++){
            err = pthread_create(&(tid[i]), NULL, multiply, NULL);
            if (err != 0){
                printf("\ncan't create thread :[%s]", strerror(err));
            }
        }
        

        result = F[0][0];
        cout << " el resultado es: " << result << endl;
    }
}