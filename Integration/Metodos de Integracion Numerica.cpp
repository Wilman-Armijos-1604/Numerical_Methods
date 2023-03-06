#include<iostream>
#include<math.h>
#include<time.h>
#define pi 3.1415926535893
#define e 2.71828182845904

using namespace std;

//En este apartado se escribe la función que se pretende sea integrada
double funcion(double x){
	return sqrt(1+pow(x,2));
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

//Esta función, realiza todo lo relacionado con el método de Simpson, así como con el pedido de los límites
void simpson(){
	int it=iteraciones();
	int f_it=formaIteracion();
	//Primero, se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
	switch(f_it) {
		case 1: {
			double n, resultado, Xo, Xf, h, aux, sumPar=0, sumImp=0, secs;
			int i=1;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el numero de intervalos para aproximar la integral \n";
			cin>>n;
			cout<<"Ingrese el limite inferior de la integral \n";
			cin>>Xo;
			cout<<"Ingrese el limite superior de la integral \n";
			cin>>Xf;
			h=(Xf-Xo)/n;
			aux=Xo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			if (it==1){
				cout<<funcion(aux)<<"\n";
			}
			while (i<n) {	//El metodo recorre todo el número de intervalos dados en un principio
				 if (i%2==0){
				 	sumPar=sumPar+2*funcion(aux+i*h);	//Aquí, si se da el caso que el punto a evaluarse es par,
				 	//se sumará dentro de un apartado solamente para tales puntos pares, multiplicados por su factor 2
				 	if (it==1){
					 	cout<<sumPar<<"\n";
					 }
				 }
				 else {
				 	sumImp=sumImp+4*funcion(aux+i*h);	//Aquí, si se da el caso que el punto a evaluarse es impar,
				 	//se sumará dentro de un apartado solamente para tales puntos impares, multiplicados por su factor 4
				 	if (it==1){
					 	cout<<sumImp<<"\n";
					 }
				 }
			i++;
			}
			if (it==1){
				cout<<funcion(Xf)<<"\n";
			}
			//Una vez encontradas las sumas parciales, solamente se realizan la suma de los dos datos anteriores, junto con la función
			//evaluada en los l{imites, toda la suma de multiplica por nuestro ancho de intervalo, en este caso h, y se divide para 3
			//y de esta forma, se habrá encontrado el resultado
			resultado=((h)*(funcion(Xo)+funcion(Xf)+sumPar+sumImp))/3;
			cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}
		
		case 2: {
			double err, resultado, Xo, Xf, h, aux, sumPar=0, sumImp=0, secs;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el margen de error para el metodo \n";
			cin>>err;
			cout<<"Ingrese el limite inferior de la integral \n";
			cin>>Xo;
			cout<<"Ingrese el limite superior de la integral \n";
			cin>>Xf;
			h=sqrt(1-err*0.01)/100;	//Se calcula el ancho del intervalo a partir del margen de error, como la raíz cuadrada de 1 menos
			//el error multiplicado por 0.01, y todo a su vez dividido para 100
			cout<<"El valor de h es: "<<h<<"\n";
			double n=(Xf-Xo)/h;
			aux=Xo;
			int i=1;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			if (it==1){
				cout<<funcion(aux)<<"\n";
			}
			while (i<n) {	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
				 if (i%2==0){
				 	sumPar=sumPar+2*funcion(aux+i*h);	//Aquí, si se da el caso que el punto a evaluarse es par,
				 	//se sumará dentro de un apartado solamente para tales puntos pares, multiplicados por su factor 2
				 	if (it==1){
					 	cout<<sumPar<<"\n";
					 }
				 }
				 else {
				 	sumImp=sumImp+4*funcion(aux+i*h);	//Aquí, si se da el caso que el punto a evaluarse es impar,
				 	//se sumará dentro de un apartado solamente para tales puntos impares, multiplicados por su factor 4
				 	if (it==1){
					 	cout<<sumImp<<"\n";
					 }
				 }
			i++;
			}
			if (it==1){
				cout<<funcion(Xf)<<"\n";
			}
			//Una vez encontradas las sumas parciales, solamente se realizan la suma de los dos datos anteriores, junto con la función
			//evaluada en los l{imites, toda la suma de multiplica por nuestro ancho de intervalo, en este caso h, y se divide para 3
			//y de esta forma, se habrá encontrado el resultado
			resultado=((h)*(funcion(Xo)+funcion(Xf)+sumPar+sumImp))/3;
			cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}	
	}
}

//Esta función, realiza todo lo relacionado con la regla del trapecio, así como con el pedido de los límites
void trapecios() {
	int it=iteraciones();
	int f_it=formaIteracion();
	//Primero, se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
	switch(f_it) {
		case 1: {
			double n, resultado, Xo, Xf, h, aux, sum=0, secs;
			clock_t t_ini, t_fin;
			int i=0;
			cout<<"Ingrese el numero de intervalos para aproximar la integral \n";
			cin>>n;
			cout<<"Ingrese el limite inferior de la integral \n";
			cin>>Xo;
			cout<<"Ingrese el limite superior de la integral \n";
			cin>>Xf;
			h=(Xf-Xo)/n;
			aux=Xo;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			if (it==1){
				cout<<funcion(aux)<<"\n";
			}
			while (i<n) { 	//El metodo recorre todo el número de intervalos dados en un principio
				//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
				//evaluada en cada uno de los puntos Xi
				sum=sum+funcion(aux+i*h);
				if(it==1) {
					cout<<funcion(aux+i*h)<<"\n";
				}
			i++;
			}
			if (it==1){
				cout<<funcion(Xf)<<"\n";
			}
			//El resultado final será igual a la suma de la función evaluda  en ambos extremos, dividida para 2
			//a lo que se suma el valor obtenido dentro del ciclo, y finalmente se multiplica por el ancho del intervalo h
			resultado=(sum+(funcion(aux)+funcion(Xf))/2)*h;
			cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}
		
		case 2: {
			double err, resultado, Xo, Xf, h, aux, sum=0, secs;
			clock_t t_ini, t_fin;
			cout<<"Ingrese el margen de error para el metodo \n";
			cin>>err;
			cout<<"Ingrese el limite inferior de la integral \n";
			cin>>Xo;
			cout<<"Ingrese el limite superior de la integral \n";
			cin>>Xf;
			h=sqrt(1-err*0.01)/100;	//Se calcula el ancho del intervalo a partir del margen de error, como la raíz cuadrada de 1 menos
			//el error multiplicado por 0.01, y todo a su vez dividido para 100
			cout<<"El valor de h es: "<<h<<"\n";
			double n=(Xf-Xo)/h;
			aux=Xo;
			int i=1;
			t_ini=clock();
			//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
			//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
			if (it==1){
				cout<<funcion(aux)<<"\n";
			}
			while (i<n) {	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
				//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
				//evaluada en cada uno de los puntos Xi
				sum=sum+funcion(aux+i*h);
				if(it==1) {
					cout<<funcion(aux+i*h)<<"\n";
				}
			i++;
			}
			if (it==1){
				cout<<funcion(Xf)<<"\n";
			}
			//El resultado final será igual a la suma de la función evaluda  en ambos extremos, dividida para 2
			//a lo que se suma el valor obtenido dentro del ciclo, y finalmente se multiplica por el ancho del intervalo h
			resultado=(sum+(funcion(aux)+funcion(Xf))/2)*h;
			cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
			t_fin=clock();
			secs=double(t_fin-t_ini);
			cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
			exit(-1);
			break;
		}	
	}
}

//Esta funcion permite definir que tipo de rectangulos se quiere para el metodo de rectángulo
//Sea por exceso, por defecto, o de forma central
int modoRect(){
	int op4;
	cout<<"Si desea aplicar el metodo de rectangulos por exceso, ingrese 1: \n";
	cout<<"Si desea aplicar el metodo de rectangulos por defecto, ingrese 2: \n";
	cout<<"Si desea aplicar el metodo de rectangulos centrales, ingrese 3: \n";
	cin>>op4;
	//El switch case, determina el caso de ingreso de un valor u otro, además de controlar datos no admitidos
	switch (op4) {
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		default:
			cout<<"Eliga una opcion valida mostrada anteriormente \n";			
	}
}

//Esta función, realiza todo lo relacionado con la regla del rectángulo, así como con el pedido de los límites
void rectangulos(){
	int mod=modoRect();
	int it=iteraciones();
	int f_it=formaIteracion();
	//Este switch case, recoge el dato del tipo de rectángulo escogido
	switch(mod) {
		case 1: {
			//En cambio, en este otro se verifica que opción se ha elegido entre dar el número de intervalos o el margen de error
			switch (f_it){
				case 1: {
					double n, resultado, Xo, Xf, h, aux, sum=0, secs;
					clock_t t_ini, t_fin;
					int i=1;
					cout<<"Ingrese el numero de intervalos para aproximar la integral \n";
					cin>>n;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=(Xf-Xo)/n;
					aux=Xo;
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
					while (i<n){ 	//El metodo recorre todo el número de intervalos dados en un principio
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos Xi, con i iniciado en 1 y menor que n
						sum=sum+funcion(aux+i*h);
						if (it==1){
							cout<<funcion(aux+i*h)<<"\n";
						}
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);
					break;
				}
				case 2:{
					double err, resultado, Xo, Xf, h, aux, sum=0, secs;
					clock_t t_ini, t_fin;
					int i=1;
					cout<<"Ingrese el margen de error para el metodo \n";
					cin>>err;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=sqrt(1-err*0.01)/100;	//Se calcula el ancho del intervalo a partir del margen de error, como la raíz cuadrada de 1 menos
					//el error multiplicado por 0.01, y todo a su vez dividido para 100
					cout<<"El valor de h es: "<<h<<"\n";
					double n=(Xf-Xo)/h;
					aux=Xo;
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
					while (i<n){	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos Xi, con i iniciado en 1 y menor que n
						sum=sum+funcion(aux+i*h);
						if (it==1){
							cout<<funcion(aux+i*h)<<"\n";
						}						
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);
					break;
				}
			}
			break;
		}
		case 2: {
			switch (f_it){
				case 1: {
					double n, resultado, Xo, Xf, h, aux, sum=0, secs;
					int i=0;
					clock_t t_ini, t_fin;
					cout<<"Ingrese el numero de intervalos para aproximar la integral \n";
					cin>>n;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=(Xf-Xo)/n;
					aux=Xo;	
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
					while (i<=n){ 	//El metodo recorre todo el número de intervalos dados en un principio
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos Xi, con i iniciado en 0 y menor o igual que n	
						sum=sum+funcion(aux+i*h);						
						if (it==1){
							cout<<funcion(aux+i*h)<<"\n";
						}
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);		
					break;
				}
				case 2:{
					double err, resultado, Xo, Xf, h, aux, sum=0, secs;
					clock_t t_ini, t_fin;
					int i=0;
					cout<<"Ingrese el margen de error para el metodo \n";
					cin>>err;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=sqrt(1-err*0.01)/100;	//Se calcula el ancho del intervalo a partir del margen de error, como la raíz cuadrada de 1 menos
					//el error multiplicado por 0.01, y todo a su vez dividido para 100
					cout<<"El valor de h es: "<<h<<"\n";
					double n=(Xf-Xo)/h;
					aux=Xo;	
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión		
					while (i<=n){	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos Xi, con i iniciado en 0 y menor o igual que n						
						sum=sum+funcion(aux+i*h);						
						if (it==1){
							cout<<funcion(aux+i*h)<<"\n";
						}
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);
					break;
				}
			}
			break;
		}
		case 3: {
			switch (f_it){
				case 1: {
					double n, resultado, Xo, Xf, h, aux, sum=0, secs;
					clock_t t_ini, t_fin;
					int i=0;
					cout<<"Ingrese el numero de intervalos para aproximar la integral \n";
					cin>>n;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=(Xf-Xo)/n;
					aux=Xo;	
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
					while (i<=n){ 	//El metodo recorre todo el número de intervalos dados en un principio
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos medios Xi, con i iniciado en 1 y menor o igual que n						
						sum=sum+funcion(aux+05*i*h);
						if (it==1){
							cout<<funcion(aux+(2*i+h)/2*h)<<"\n";
						}
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);		
					break;
				}
				case 2:{
					double err, resultado, Xo, Xf, h, aux, sum=0, secs;
					clock_t t_ini, t_fin;
					cout<<"Ingrese el margen de error para el metodo \n";
					cin>>err;
					cout<<"Ingrese el limite inferior de la integral \n";
					cin>>Xo;
					cout<<"Ingrese el limite superior de la integral \n";
					cin>>Xf;
					h=sqrt(1-err*0.01)/100;	//Se calcula el ancho del intervalo a partir del margen de error, como la raíz cuadrada de 1 menos
					//el error multiplicado por 0.01, y todo a su vez dividido para 100
					cout<<"El valor de h es: "<<h<<"\n";
					double n=(Xf-Xo)/h;
					aux=Xo;
					int i=1;
					t_ini=clock();
					//Los ifs repartidos con it==1, permiten verificar si se desea imprimir los resultados parciales
					//Si se da el caso, se imprime absolutamente todo, caso contrario, se omite su impresión
					while (i<=n){	//El metodo recorre todo el número de intervalos calculado a partir del margen de error dado
						//Un valor sum inicializado en 0, se ve incrementado con los valores de la función
						//evaluada en cada uno de los puntos medios Xi, con i iniciado en 1 y menor o igual que n						
						sum=sum+funcion(aux+05*i*h);
						if (it==h*sum){
							cout<<funcion(aux+(2*i+h)/2*h)<<"\n";
						}
					i++;
					}
					//El resultado será unicamente igual a la suma calculada anteriormente, multiplicada por el ancho del intervalo
					resultado=h*sum;
					cout<<"El resultado de evaluar la funcion de "<<Xo<<" hasta "<<Xf<<" es igual a: "<<resultado<<"\n";
					t_fin=clock();
					secs=double(t_fin-t_ini);
					cout<<"El tiempo de ejecucion del programa fue de: "<<secs/1000<<" segundos \n";
					exit(-1);				
					break;
				}
			}
			break;
		}
	}
}

//Este aparto, es el que permite definir que metodo sera el elgido para encontrar la solucion de la integral
void metodo(){
	int op1;
	cout<<"Si desea evaluar la integral por el metodo de simpson, ingrese 1: \n";
	cout<<"Si desea evaluar la integral por el metodo de trapezios, ingrese 2: \n";
	cout<<"Si desea evaluar la integral por el metodo de rectangulos, ingrese 3: \n";
	cin>>op1;
	//El switch case, determina el caso de ingreso de un valor u otro, además de controlar datos no admitidos	
	switch (op1){
		case 1:
			simpson();
		case 2:
			trapecios();
		case 3:
			rectangulos();
		default:
			cout<<"Eliga una opcion valida mostrada anteriormente \n";
			metodo();
	}
}


int main() {	
	cout<<"\t\t\t\t\tESCUELA POLITECNICA NACIONAL\n\t\t\t\t     FACULTAD DE INGENIERIA EN SISTEMAS\n"
	<<"CARRERA: INGENIERIA EN SISTEMAS INFORMATICOS Y DE COMPUTACION\nMATERIA: METODOS NUMERICOS\n"
	<<"DOCENTE:EDGAR TORRES\nCURSO: GR1COM\nTEMA: INTEGRACION NUMERICA\nMOTIVO: PROGRAMA EN C++"
	<<"INTEGARNTES:\n- Alvarez Jeremy\n- Armijos Wilman\n- Aviles Javier\n- Calva Carlos"
	<<"\n- Chilan Michael\n- Facunda Andres\n- Morales Jhouse\n- Narvaez Jorge\n\n";
	//A partir de aquí, las funciones son llamadas dentro de otras para cumplir con la funcionalidad del programa
	metodo();
	return 0;
}

