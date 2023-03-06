#include<iostream>
#include<math.h>
#include<time.h>
#define pi 3.1415926535893
#define e 2.71828182845904

using namespace std;

//En este apartado se escribe la función que representa a la EDO
double funcion(double x, double y){
	return x+y;
}

//Este apartado permite describir la derivada de la funcion mostrada arriba
double derivada(double x, double y){
	return 1+funcion(x,y);
}

//Este apartado permite describir la segunda derivada de la funcion mostrada arriba
double derivada2(double x, double y){
	return derivada(x,y);
}

//Este apartado permite describir la tercera de la funcion mostrada arriba
double derivada3(double x, double y){
	return derivada2(x,y);
}

//Esta funcion devuelve el factorial de un numero pasado como parámetro, esta funcion es util para el metodo de Taylor
//Es la forma recursiva del factorial
int factorial(int n){
	if (n==0){
		return 1;
	}
	return n*factorial(n-1);
}

//Esta función, lo que hace es permitir al usuario escoger entre imprimir los resultados parciales del metodo
//o solamente imprimir el resultado final
int iteraciones(){
	int op3;
	cout<<"Si desea que aparezcan en pantalla todas las iteraciones del metodo, ingrese 1: \n";
	cout<<"Si desea conocer solamente el ultimo resultado del metodo, ingrese 2: \n";
	cin>>op3;
	//El switch case, determina el caso de ingreso de un valor u otro, además de controlar datos no admitidos
	switch (op3) {
		case 1:
			return 1;
		case 2:
			return 2;
		default:
			cout<<"Eliga una opcion valida mostrada anteriormente \n";
			iteraciones();
	}
}

//Esta función, permite elegir al usuario entre elegir el número de intervalos del método
//o dar un margen de error al método
int formaIteracion(){
	int op2;
	cout<<"Si desea ingresar el numero de iteraciones del metodo, ingrese 1: \n";
	cout<<"Si desea ingresar el margen de de error del metodo, ingrese 2: \n";
	cin>>op2;
	//El switch case, determina el caso de ingreso de un valor u otro, además de controlar datos no admitidos
	switch (op2){
		case 1:
			return 1;
		case 2:
			return 2;
		default:
			cout<<"Eliga una opcion valida mostrada anteriormente \n";
			formaIteracion();
	}
}

void rungeKutta() {
	int it=iteraciones();
	int f_it=formaIteracion();
	//Primero, se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
	switch(f_it) {
		case 1: {
			double n, Xo, Yo, Xf, auxX, auxY, k[4], h, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el numero de iteraciones para aproximar la EDO"<<"\n";
			cin>>n;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			auxX=Xo;
			h=(Xf-Xo)/n;
			auxY=Yo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos dados en un principio
				//Las siguientes cuatro lineas, almacenan el valor de k, k2, k3 y k4, necesarios para el computo de la solucion
				k[0]=funcion(auxX,auxY);	//La funcion es evaluada en los puntos de la iteracion
				k[1]=funcion(auxX+0.5*h,auxY+0.5*k[0]*h);	//La funcion es evualuada para x en el punto de la iteracion más la mitad del 
				//ancho de intervalo, en y en el punto de la iteración más la mitad del valor de k1 multiplicado por el ancho del intervalo
				k[2]=funcion(auxX+0.5*h,auxY+0.5*k[1]*h);	//La funcion es evualuada para x en el punto de la iteracion más la mitad del 
				//ancho de intervalo, en y en el punto de la iteración más la mitad del valor de k2 multiplicado por el ancho del intervalo
				k[3]=funcion(auxX+h,auxY+k[2]*h);	//La funcion es evualuada para x en el punto de la iteracion más el ancho de intervalo
				//en y se evalua el punto de la iteración más el valor de k3 multiplicado por el ancho del intervalo
				auxY=auxY+((h)*(k[0]+2*k[1]+2*k[2]+k[3])/6);	//La nueva aproximacion, será igual a la aproximación anterior, más el resultado de
				//sumar k1, k3, el doble de k2 y de k4, todo ello dividido para 6
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				i++;
				if (it==1 && i<n){
					cout<<auxY<<"\n";
				}
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}
		case 2: {
			double err, Xo, Yo, Xf, auxX, auxY, k[4], h, n, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el margen de error para aproximar la EDO"<<"\n";
			cin>>err;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			auxX=Xo;
			auxY=Yo;
			h=((Xf-Xo)/1000)*err;	//Se calcula el ancho del intervalo a partir del margen de error, como la diferencia entre los dos puntos
			//dados en el principio, divididos para un factor de 1000, y multiplicado por el error.	
			n=(Xf-Xo)/h;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
				//Las siguientes cuatro lineas, almacenan el valor de k, k2, k3 y k4, necesarios para el computo de la solucion
				k[0]=funcion(auxX,auxY);	//La funcion es evaluada en los puntos de la iteracion
				k[1]=funcion(auxX+0.5*h,auxY+0.5*k[0]*h);	//La funcion es evualuada para x en el punto de la iteracion más la mitad del 
				//ancho de intervalo, en y en el punto de la iteración más la mitad del valor de k1 multiplicado por el ancho del intervalo
				k[2]=funcion(auxX+0.5*h,auxY+0.5*k[1]*h);	//La funcion es evualuada para x en el punto de la iteracion más la mitad del 
				//ancho de intervalo, en y en el punto de la iteración más la mitad del valor de k2 multiplicado por el ancho del intervalo
				k[3]=funcion(auxX+h,auxY+k[2]*h);	//La funcion es evualuada para x en el punto de la iteracion más el ancho de intervalo
				//en y se evalua el punto de la iteración más el valor de k3 multiplicado por el ancho del intervalo
				auxY=auxY+((h)*(k[0]+2*k[1]+2*k[2]+k[3])/6);	//La nueva aproximacion, será igual a la aproximación anterior, más el resultado de
				//sumar k1, k3, el doble de k2 y de k4, todo ello dividido para 6
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				i++;
				if (it==1 && i<n){
					cout<<auxY<<"\n";
				}
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";			
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);			
			break;
		}
	}
}

void Euler() {
	int it=iteraciones();
	int f_it=formaIteracion();
	//Primero, se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
	switch(f_it) {
		case 1: {
			double n, Xo, Yo, Xf, auxX, auxY, h, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el numero de iteraciones para aproximar la EDO"<<"\n";
			cin>>n;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			h=(Xf-Xo)/n;
			auxX=Xo;
			auxY=Yo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos dados en un principio
				auxY=auxY+h*funcion(auxX, auxY);	//La nueva mejor aproximación, se calcula solamente como la suma entre la aproximación
				//anterior, y la función evaluada en los puntos anterior multiplicada por el ancho del intervalo
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				if (it==1 && i!=n){
					cout<<auxY<<"\n";
				}
				i++;
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);			
			break;
		}
		case 2: {
			double n, Xo, Yo, Xf, auxX, auxY, h, err, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el margen de error para aproximar la EDO"<<"\n";
			cin>>err;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			auxX=Xo;
			auxY=Yo;
			h=((Xf-Xo)/1000)*err;	//Se calcula el ancho del intervalo a partir del margen de error, como la diferencia entre los dos puntos
			//dados en el principio, divididos para un factor de 1000, y multiplicado por el error.	
			n=(Xf-Xo)/h;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
				auxY=auxY+h*funcion(auxX, auxY);	//La nueva mejor aproximación, se calcula solamente como la suma entre la aproximación
				//anterior, y la función evaluada en los puntos anterior multiplicada por el ancho del intervalo
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				if (it==1 && i!=n){
					cout<<auxY<<"\n";
				}
				i++;
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);			
			break;
		}
	}
}

void Taylor() {
	int it=iteraciones();
	int f_it=formaIteracion();
	//Primero, se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
	switch(f_it) {
		case 1: {
			double n, Xo, Yo, Xf, auxX, auxY, h, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el numero de iteraciones para aproximar la EDO"<<"\n";
			cin>>n;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			h=(Xf-Xo)/n;
			auxX=Xo;
			auxY=Yo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos dados en un principio
				auxY=auxY+(h/factorial(1))*funcion(auxX,auxY)+(pow(h,2)/factorial(2))*derivada(auxX,auxY)+(pow(h,3)/factorial(3))*derivada2(auxX,auxY)+(pow(h,4)/factorial(4))*derivada3(auxX,auxY);	//La nueva mejor aproximación, 
				//es igual a la aproximación anterior, más una sumatoria desde 1 hasta 2 en este caso (con un iterador i), de nuestro intervalo 
				//elevado a i, multipilicado por la i-ésima derivada evaluada en los puntos, y todo dividido para el factorial de i
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				if (it==1 && i!=n){
					cout<<auxY<<"\n";
				}
				i++;
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);		
			break;
		}
		case 2: {
			double n, Xo, Yo, Xf, auxX, auxY, h, err, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el margen de error para aproximar la EDO"<<"\n";
			cin>>err;
			cout<<"Ingrese el valor inicial de la solucion para x"<<"\n";
			cin>>Xo;
			cout<<"Ingrese el valor inicial de la solucion para y"<<"\n";
			cin>>Yo;
			cout<<"Ingrese el valor en el que quiere aproximar la aproximacion de la solucion"<<"\n";
			cin>>Xf;
			h=((Xf-Xo)/1000)*err;	//Se calcula el ancho del intervalo a partir del margen de error, como la diferencia entre los dos puntos
			//dados en el principio, divididos para un factor de 1000, y multiplicado por el error.	
			n=(Xf-Xo)/h;
			auxX=Xo;
			auxY=Yo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			while (i<=n) {	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
				auxY=auxY+(h/factorial(1))*funcion(auxX,auxY)+(pow(h,2)/factorial(2))*derivada(auxX,auxY);	//La nueva mejor aproximación, 
				//es igual a la aproximación anterior, más una sumatoria desde 1 hasta 2 en este caso (con un iterador i), de nuestro intervalo 
				//elevado a i, multipilicado por la i-ésima derivada evaluada en los puntos, y todo dividido para el factorial de i
				auxX=auxX+h;	//Al obtener la nueva aproximación, se procede a incrementar el valor de x con el ancho del intervalo
				if (it==1 && i!=n){
					cout<<auxY<<"\n";
				}
				i++;
			}
			cout<<"El resultado de la EDO evaluada en el punto "<<Xf<<" es: "<<auxY<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}
	}	
}

//Este aparto, es el que permite definir que metodo sera el elgido para encontrar la solucion de la integral
void metodo(){
	int op1;
	cout<<"Si desea resolver la EDO por el metodo de Runge-Kutte de Orden 4, ingrese 1: \n";
	cout<<"Si desea resolver la EDO por el metodo de Euler, ingrese 2: \n";
	cout<<"Si desea resolver la EDO por el metodo de Series de Taylor, ingrese 3: \n";
	cin>>op1;
	//El switch case, determina el caso de ingreso de un valor u otro, además de controlar datos no admitidos	
	switch (op1){
		case 1:
			rungeKutta();
		case 2:
			Euler();
		case 3:
			Taylor();
		default:
			cout<<"Eliga una opcion valida mostrada anteriormente \n";
			metodo();
	}
}

int main() {	
	cout<<"\t\t\t\t\tESCUELA POLITECNICA NACIONAL\n\t\t\t\t     FACULTAD DE INGENIERIA EN SISTEMAS\n"
	<<"CARRERA: INGENIERIA EN SISTEMAS INFORMATICOS Y DE COMPUTACION\nMATERIA: METODOS NUMERICOS\n"
	<<"DOCENTE:EDGAR TORRES\nCURSO: GR1COM\nTEMA: SOLUCION DE EDOs\\nMOTIVO: PROGRAMA EN C++"
	<<"INTEGARNTES:\n- Alvarez Jeremy\n- Armijos Wilman\n- Aviles Javier\n- Calva Carlos"
	<<"\n- Chilan Michael\n- Facunda Andres\n- Morales Jhouse\n- Narvaez Jorge\n\n";
	//A partir de aquí, las funciones son llamadas dentro de otras para cumplir con la funcionalidad del programa	
	metodo();
	return 0;
}
