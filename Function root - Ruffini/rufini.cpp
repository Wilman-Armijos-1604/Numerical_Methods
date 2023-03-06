	#include<iostream>
	#include<stdio.h>
	#include<math.h>
	#include <string>
	#include <sstream>
	
	using namespace std;
	

	//funcion para mostrar el polinomio
	string ImprimirPolinomio(double coeficientes[],int grado){
			string polinomio="";
			int aux=grado;
			for(int i=0;i<grado;++i){
				std::ostringstream os;
				os <<coeficientes[i] ;	
				std::ostringstream os1;
				os1 <<(aux) ;
				polinomio=polinomio+" ("+ os.str()+")x^"+os1.str()+" + ";
				aux--;
				
			}
			std::ostringstream os;
			os <<coeficientes[grado] ;
			polinomio=polinomio+" ("+ os.str()+")\n";
		return polinomio;
	}
		//funcion para valuar el polinomio
	double Funcion(double x, int grado, double coeficientes[]){
		double resultado=0;
		int aux=grado;
		for(int i=0;i<=grado;i++){
			resultado=coeficientes[i]*pow(x,aux)+resultado;
			aux--;
		}
		return resultado;
	}
	//calculamos la derivada
	double Derivada(double x,int grado, double coeficientes[]){
		double h=0.0000002;
		return (Funcion(x+h,grado,coeficientes)-Funcion(x-h,grado,coeficientes))/(2*h);
	}
	//aplicamos el metodo de newton raphson
	double MetodoNewtonRaphson(double x,int grado, double coeficientes[]){
		
		return x-(Funcion(x,grado,coeficientes)/Derivada(x,grado,coeficientes));
	}
	
		//metodo de rufini
		void MetodoDeRuffini(int grado, double *coeficientes,double raiz){
			for(int i=1;i<=grado;++i){
				coeficientes[i]=coeficientes[i]+(coeficientes[i-1]*raiz);	
			}
		}
	
	
	// se aplica el metodo de Newton raphson para hallar la raiz
	double ObtenerRaiz(double semilla,double ErrorRelativoRequerido, int grado, double coeficientes[] , int *aux){
	
		double  ErrorRelativoObtenido [100], ErrorAbsoluto[100],ValoresObtenidos[102];
		ValoresObtenidos[0]=semilla;
		int n=0;
		int u=1;
		do{
			u=1;
			// se calcula el valor de x+1 con el metodo de Newton Raphson
			ValoresObtenidos[n+1]=MetodoNewtonRaphson(ValoresObtenidos[n],grado,coeficientes);
			// se calcula los errores relativos y absolutos
			ErrorAbsoluto[n]=ValoresObtenidos[n+1]-ValoresObtenidos[n];
			ErrorRelativoObtenido[n]=ErrorAbsoluto[n]/ValoresObtenidos[n+1];
			if(ErrorRelativoObtenido[n]<0)
			u=-1;
			n++;
		}while(ErrorRelativoObtenido[n-1]*u>ErrorRelativoRequerido && n<=100);
		// en caso de no tener mas raices  cambia el valor de x 
		if(n==101){
			*aux=*aux+3;
			return 0;
		}
	
		return ValoresObtenidos[n];
	}
	

	int main(){
		int grado;
		char a='a';
		string polinomio=" ";
		
		// se ingresan los datos GRADO DEL POLINOMIO COEFICIENTES SEMILLA Y ERROR REQUERIDO
		double semilla,ErrorRelativoRequerido;
		cout<<"Ingrese el grado del polinomio\n";
		cin>>grado;
		int x=1,num_raiz;
	
		double coeficientes[grado+1],raiz[grado];
		for(int i=0;i<=grado;++i){
				cout<<"Ingrese el coeficiente "<<a<<"\n";
				cin>>coeficientes[i];
				a++;
		}
		polinomio=ImprimirPolinomio(coeficientes,grado);
		cout<<"\nEl polinimio ingresado es\n";
		cout<<polinomio;
		cout<<"\nIngrese la semilla \n";
		cin>>semilla;
		cout<<"Ingrese el porcentaje de error relativo requerido \n";
		cin>>ErrorRelativoRequerido;
		for(int j=0;j<grado;j++){
			// se obtiene el valor de las raices 
			raiz[j]=ObtenerRaiz(semilla,ErrorRelativoRequerido,grado-j,coeficientes,&x);
			// si x es diferente de uno ya no hay mas raices y termina el ciclo 
			if(x!=1){
				num_raiz=j;
				break;
			}
			// se disminuye  un  grado del polinomio con rufini 
			MetodoDeRuffini(grado,coeficientes,raiz[j]);
			polinomio ="";
			polinomio=ImprimirPolinomio(coeficientes,grado-j-1);
				num_raiz=grado;
			cout<<"\nEl polinimio Nuevo es\n";
			cout<<polinomio;
		}
		// se muestra las raices
		if(num_raiz==0){
			cout<<"La funcion no convergue no existen raices";
			return 0;
		}
		if(num_raiz<grado){
			cout<<"La funcion ya no convergue,  no tiene mas existen raices";
		}
		for(int j=0;j<num_raiz;j++){
			cout<<"\n la raiz "<<(j+1)<<" es:"<<raiz[j];
		}
		return 0;
	}
