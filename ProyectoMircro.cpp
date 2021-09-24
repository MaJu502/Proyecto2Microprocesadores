/**
 * Universidad del Valle de Guatemala
 * CC3056-10 Programación de microprocesadores
 * Proyecto Microprocesadores grupo X
 * integrantes: 
 *      Marco Jurado 20308
 *      Andrés de la Roca
 *      José Auyón
 * 
 *  Adaptado de method 4 geeksforgeeks
 **/

//AGREGAR BARRERAS

 // Declaracion de librerias
#include <bits/stdc++.h>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Declaracion de variables globales en hilos y usos de barreras y mutex
#define F [2][2];
pthread_mutex_t lock; // Bloqueo de hilos
pthread_barrier_t barrera; //Barrera de los hilos


void multiply(int F[2][2], int M[2][2]);

void power(int F[2][2], int n);
 
int fib(int n)
{
    
    int F[2][2] = { { 1, 1 }, { 1, 0 } };
    if (n == 0)
        return 0;
         
    power(F, n - 1);
     
    return F[0][0];
}
 
void multiply(int F[2][2], int M[2][2])
{
    pthread_mutex_lock(&lock);

    int x = F[0][0] * M[0][0] +
            F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] +
            F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] +
            F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] +
            F[1][1] * M[1][1];
     
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;

    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}
 
void power(int F[2][2], int n)
{
    int i;
    int M[2][2] = { { 1, 1 }, { 1, 0 } };
        
    
    for(i = 2; i <= n; i++){
        err = pthread_create(&(tid[i]), NULL, &multiply(F,M), (void *)i);	//creacion de hilos con paso de parametros  ARREGLAR
        //Posiblemente se necesita variables globales F y M VERIFICAR
        if (err != 0)
             printf("\ncan't create thread :[%s]", strerror(err));		//impresion de mensaje si el hilo no se crea correctamente													
}
 
int main()
{
    //Ingreso de numero a ejecutar -------------------------------------
    int n = 0;
    cout<< "Ingrese el numero a calcular se sucesion fibonacci: "
    cin>>n;
    //------------------------------------------------------------------  
    
    //Definir cantidad de threads 
    pthread_t tid[n]; 

    //Execute a fib 
    cout << " " <<  fib(n); //Imprime resultado
    
    pthread_mutex_destroy(&mutex);

    return 0;
}
 
