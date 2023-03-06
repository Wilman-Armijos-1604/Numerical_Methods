	#include<iostream>
	#include<stdio.h>
	#include<math.h>
	
	using namespace std;
	
	double Funcion(double x){
		return pow(x,2)-2	;
	}
	double Derivada(double x){
		double h=0.0000002;
		return (Funcion(x+h)-Funcion(x-h))/(2*h);
	}
	double MetodoNewtonRaphson(double x){
		
		return 2*x;
	}
	int main(){
		double ErrorRelativoRequerido, ErrorRelativoObtenido [100], ErrorAbsoluto[100],ValoresObtenidos[101];
		
		cout<<"Ingrese la semilla ";
		cin>>ValoresObtenidos[0];
		cout<<"Ingrese el porcentaje de error relativo";
		cin>>ErrorRelativoRequerido;
		int n=0;
		int u=1;
		do{
			u=1;
			ValoresObtenidos[n+1]=MetodoNewtonRaphson(ValoresObtenidos[n]);
			ErrorAbsoluto[n]=ValoresObtenidos[n+1]-ValoresObtenidos[n];
			ErrorRelativoObtenido[n]=ErrorAbsoluto[n]/ValoresObtenidos[n+1];
			if(ErrorRelativoObtenido[n]<0)
			u=-1;
			n++;
		}while(ErrorRelativoObtenido[n-1]*u>ErrorRelativoRequerido && n<=100);
		if(n==101){
			cout<<"la Funcion no converge";
			return 0;
		}
		
		cout<<" \t----LOS RESULTADOS SE MUESTRAN EN LA SIGUIENTE TABLA---\n It\tXn\tXn+1\tea\ter\n";
		for(int i=0;i<n;i++){
			cout<<i+1<<"\t"<<ValoresObtenidos[i]<<"\t"<<ValoresObtenidos[i+1]<<"\t"<<ErrorAbsoluto[i]<<"\t"<<ErrorRelativoObtenido[i]<<"\n";
		}
		return 0;
	}
