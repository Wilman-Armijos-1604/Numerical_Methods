// calcula las raiz de una funcion usando la derivada numerica y newton raphson

	#include<iostream>
	#include<stdio.h>
	#include<math.h>
	
	using namespace std;
// escribimos la funcion y la evaluamos	
	double Funcion(double x){
		return pow(x,2)+2;
	}
	
//calculamos la derivada numerica
	double Derivada(double x){
		double h=0.0000002;
		return (Funcion(x+h)-Funcion(x-h))/(2*h);
	}
// aplicamos el metodo de newton raphson
	double MetodoNewtonRaphson(double x){
		
		return x-(Funcion(x)/Derivada(x));
	}
	
	
	int main(){
		// pedimos los datos SEMILLA, ERROR REQUERIDO
		double ErrorRelativoRequerido, ErrorRelativoObtenido [101], ErrorAbsoluto[101],ValoresObtenidos[102];
		cout<<"Ingrese la semilla ";
		cin>>ValoresObtenidos[0];
		cout<<"Ingrese el porcentaje de error relativo";
		cin>>ErrorRelativoRequerido;
		// inicializamos el contador, cuenta las veces que busca una raiz
		int n=0;
		
		do{
			//obtenemos el valor de x+1 llamando  ala funcion metodonewtonraphson
			ValoresObtenidos[n+1]=MetodoNewtonRaphson(ValoresObtenidos[n]);
			// Se calcula los error relativo y absoluto
			ErrorAbsoluto[n]=ValoresObtenidos[n+1]-ValoresObtenidos[n];
			ErrorRelativoObtenido[n]=ErrorAbsoluto[n]/ValoresObtenidos[n+1];
			n++;
			// si el error relativoobtenido es menor al error requerido  o si el numero de iteraciones es mayor a 101 el ciclo termina
		}while(abs(ErrorRelativoObtenido[n-1])>ErrorRelativoRequerido && n<=100);
		// si se realizaron mas de 101 iteraciones se manda el mensaje del cout caso contrario se muestra la tabla de resultados
		if(n==99){
			cout<<"la Funcion no converge";
			return 0;
		}
		cout<<" \t----LOS RESULTADOS SE MUESTRAN EN LA SIGUIENTE TABLA---\n It\tXn\tXn+1\tea\ter\n";
		for(int i=0;i<n;i++){
			cout<<i+1<<"\t"<<ValoresObtenidos[i]<<"\t"<<ValoresObtenidos[i+1]<<"\t"<<ErrorAbsoluto[i]<<"\t"<<ErrorRelativoObtenido[i]<<"\n";
		}
		return 0;
	}
