	#include<iostream>
	#include<math.h>
	#include<stdbool.h>
	#include<vector>
	#include <windows.h>
	#include <stdio.h>
	
	
	using namespace std;
	// imprime los datos en de las ecuaciones ingresadas
	void imprimirArreglo(vector<double>& matriz, vector<double>& vectorB ,int n){
		int j=0;
		cout<< "\nEl sistema de ecuaciones ingresado es\n"; 
		for(int i=0;i<matriz.size();i++){
			cout<<matriz[i]<<"\t";		
			if(i%n==(n-1)){
		   		cout<<" = "<< vectorB[j]<<"\n";	
				j++;	
			}
		}
	}
	
	
	// llena los datos de las ecuaciones en la matriz de coeficiente y en el vector de valores independientes
	void llenarArreglo(vector<double>& matriz,vector<double>& vectorB,int n){
	  	double numIngresado; 
	 	int j=0; 
	  	for( int i=0; i<matriz.size(); i++){
	  		if(i%n==0)
	  			cout<<"\n-----Ingrese los valores de la ecuacion  ["<<i/n<<"]------\n";
	  
			cout<<"\nIngrese el numero en la posicion ["<<i/n<<"]["<<i%n<<"]\n";
		  	cin>>numIngresado;
		  	matriz[i]=numIngresado;
		  	if(i%n==(n-1)){
			 	cout<<"\nIngrese el numero independiente de la ecuacion  ["<<j<<"]\n";
		  		cin>>numIngresado;
		  		vectorB[j]=numIngresado;
			  	j++;
			} 
	  	}  
	}
	
	// Validar que la matriz sea extrictamente diagonal dominante
	bool validarConvergencia(vector<double>& matriz, int n){
		double sum=0, aux;
		for(int j=0;j<n;j++){
			for(int i=0; i<n;i++){
				if(i!=j){
					//sumamos los cuadrado de cada elemento de la fila, excepto el valor de la diagonal mayor
					sum=sum+pow(matriz[j*n+i],2);
				}
				else {
					//guardamos el valor de la diagonal mayor
					aux=matriz[j*n+i];
				}	
			}
			// verificamos que el cuadrado del valor de la diagonal mayor sea mayor que la suma de los cuadrados de los otros elementos de la fila
			//  (A[1][1])^2> (A[1][0]^2+A[1][2]^2+A[1][n]^2)
			if (pow(aux,2)<sum){
				cout<<"\nEl programa no convergera hacia un resultado ingrese otra matriz o salga del programa\n";
				return false;
			}	
		}	
		return true;		
	}
	
		//Se llenan los valores iniciales de las soluciones o se ponen por default 0
	void llenarValoresIniciales(double valoresIniciales[], int n, bool verificar){
		if(verificar){
			for(int i=0;i<n;i++){
				cout<<"\ningrese el valor inicial de X"<<i<<" : ";
				cin>>valoresIniciales[i];
			}
		}
		else{
				for(int i=0;i<n;i++)
					valoresIniciales[i]=0;
		}
		
		cout<<" los valores iniciales son:\n ";
		for(int i=0;i<n;i++){
			cout<<"\t X"<<i<<" = "<<valoresIniciales[i];
		}
	}
	
	// calcula el error por iteracion
	double calcularError(vector<double>& matrizCoeficientes,vector<double>&vectorValIndependientes,double valoresIniciales[],int n){
		double maximoError=0;
		double suma=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				suma=suma+matrizCoeficientes[i*n+j]*valoresIniciales[j];
			}
			if(maximoError<abs(vectorValIndependientes[i]-suma)){
				maximoError=abs(vectorValIndependientes[i]-suma);
				
			}
			suma=0;
		}
		return maximoError;
	}
	
	//metodo jacobi
	int Jacobi(vector<double>& matrizCoeficientes,vector<double>&vectorValIndependientes, double vectorSolucion[], double valoresIniciales[],int n, double errorPermitido){	
		//inicializamos el contador de ciclos
		int cont=0;
		double sum=0;
		double errorObtenido=8.0;
		// se repetira los ciclos necesarios para llegar a converguer o cuando se repita 1000 veces 
		while(cont<1000 && errorObtenido>errorPermitido){
			for (int i=0; i<n; i++){
				for (int j=0; j<n; j++){
					if (i!=j){	
						// sumamos la multiplicacion de los coeficientes*las soluciones temporales(sumatoria de (C0*X0+C1*X1+....Cn*Xn)
						sum=sum+matrizCoeficientes[i*n+j]*valoresIniciales[j];
					}
				}
				//restamos del valor independiente la suma antes calculada y lo dividimos para el coeficiente que acompaña a esta solucion(X0,X1...Xn)
				vectorSolucion[i]=(vectorValIndependientes[i]-sum)/matrizCoeficientes[i*n+i];
				sum=0;
			}
			cont ++;
			//pasamos las soluciones temporales al vector de valores iniciales para usarlos en el siguiente ciclo
			for (int i=0; i<n; i++) {
				valoresIniciales[i]=vectorSolucion[i];
			}
		
			
			errorObtenido=calcularError(matrizCoeficientes, vectorValIndependientes, valoresIniciales,n);
			
		}
			//mostramos la solucion Final
			cout<<"\n------------*********Resultados METODO JACOBI********------------\n";
			cout<<"Las soluciones son: \n";
			for (int i=0; i<n; i++) {
			cout<<"El valor de vectorSolucion"<<(i)<<" es: "<<vectorSolucion[i]<<"\n";
			}	
		return cont;
	}
	
	//metodo gauss seidel
	int GaussSeidel(vector<double>& matrizCoeficientes,vector<double>&vectorValIndependientes, double vectorSolucion[], double valoresIniciales[],int n, double errorPermitido){
		//inicializamos el contador de ciclos
		int cont=0;
		double sum=0;
		double errorObtenido=8.0;
		// se repetira los ciclos necesarios para llegar a converguer o cuando se repita 1000 veces 
		while(cont<1000 && errorObtenido>errorPermitido){
			for (int i=0; i<n; i++){
				for (int j=0; j<n; j++){
					if (i!=j){	
						// sumamos la multiplicacion de los coeficientes*las soluciones temporales(sumatoria de (C0*X0+C1*X1+....Cn*Xn)
						sum=sum+matrizCoeficientes[i*n+j]*valoresIniciales[j];
					}
				}
				//restamos del valor independiente la suma antes calculada y lo dividimos para el coeficiente que acompaña a esta solucion(X0,X1...Xn)
				//guardamos los valores calculados directamente en el vector de valores iniciales para usarlos en este mismo ciclo 
				valoresIniciales[i]=(vectorValIndependientes[i]-sum)/matrizCoeficientes[i*n+i];
				sum=0;
			}
			cont ++;
			errorObtenido=calcularError(matrizCoeficientes, vectorValIndependientes, valoresIniciales,n);
		}
			for (int i=0; i<n; i++) {
				vectorSolucion[i]=valoresIniciales[i];
			}
			//mostramos la solucion Final
			cout<<"\n------------*********Resultados METODO GAUSS-SEIDEL********------------\n";
			cout<<"Las soluciones son: \n";
			for (int i=0; i<n; i++) {
				cout<<"El valor de vectorSolucion"<<(i)<<" es: "<<vectorSolucion[i]<<"\n";
			}
		return cont;
	}
	
	
	// funcion para medir el tiempo de ejecucion
	/* retorna "a - b" en segundos */
	double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
	{
	  LARGE_INTEGER freq;
	  QueryPerformanceFrequency(&freq);
	  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
	}
	/////////////main////////////////////////////// 
	int main() {
		
		//se ingresa el orden del sistema de ecuaciones y los valores de estas
		int n,aux, opcion;
		double errorPermitido;
		bool verifica;
	  	cout<<"Ingrese el orden del sistema de ecuaciones\n";
	  	cin >> n;
	  	vector<double> matrizCoeficientes(n*n,0);
		vector<double> vectorValIndependientes(n,0);
		do{
			verifica=false;
			cout<<"Ingrese los valores de las ecuaciones 1,2,3....n\n";
			llenarArreglo(matrizCoeficientes,vectorValIndependientes,n);
	  		imprimirArreglo(matrizCoeficientes,vectorValIndependientes, n);
			if(!validarConvergencia(matrizCoeficientes,n)){
				cout<<"Digite\n 1.- Para ingresar nuevos valores \n2.- Para salir\n";
				cin>>aux;
				if(aux==1)
					verifica=true;
				else
					exit(-1);
			}
		}while(verifica);
		
		//  llenan los valores iniciales y elerror que se Permite
		fflush(stdin);  
	  	double valoresIniciales[n],vectorSoluciones[n];
	  	cout<<"\n----------------------------------------------------------\n";
	  	cout<<"\nIngrese el error permitido \n";
	  	cin>>errorPermitido;
	  	fflush(stdin);
	  	cout<<"\n----------------------------------------------------------\n";
	  	cout<<"\nDesea ingresar valores iniciales, Digite \n 1.-SI\n 2.-NO\n";
	  	cin>>aux;
	  	if(aux==1)
	  		llenarValoresIniciales(valoresIniciales,n,true);
		else
			llenarValoresIniciales(valoresIniciales,n,false);
			
		// vaiables para medir el tiempo de ejecuion 
		LARGE_INTEGER t_ini, t_fin, t_ini1, t_fin1;
	  	double secs, secs1;
		 // variables de los ciclos de cada metodo	
	  	int numCiclosJacobi,numCiclosGauss; 
	  	
	  	// Menu para escoger el metodo para resolver
		cout<<"\nseleccione el metodo a utilizar \n 1- Metodo Jacobi\n 2- Metodo Gauss-Seidel\n 3- los dos\n 4- salir";
		cin>>opcion;
		switch(opcion){
			
			case 1:
				// metodo Jacobi Se calcula el tiempo de ejecucion y las iteraciones realizadas
				QueryPerformanceCounter(&t_ini);
				numCiclosJacobi=Jacobi(matrizCoeficientes,vectorValIndependientes,vectorSoluciones,valoresIniciales,n,errorPermitido);
				QueryPerformanceCounter(&t_fin);
				secs = performancecounter_diff(&t_fin, &t_ini);
				cout<<"\nEl tiempo de ejecucion con el metodo jacobi es " <<secs * 1000.0<<"milisegundos";
				cout<<"\n El numero de ciclos necesarios para hallar la solucion es: "<<numCiclosJacobi<<"\n";
				 
				break;
			case 2:
				 // metodo Gauss Se calcula el tiempo de ejecucion y las iteraciones realizadas
				QueryPerformanceCounter(&t_ini);
				numCiclosGauss=GaussSeidel(matrizCoeficientes,vectorValIndependientes,vectorSoluciones,valoresIniciales,n,errorPermitido);
				QueryPerformanceCounter(&t_fin);
				secs = performancecounter_diff(&t_fin, &t_ini);
				cout<<"\nEl tiempo de ejecucion con el metodo GaussSeidel es " <<secs * 1000.0<<"milisegundos";
				cout<<"\n El numero de ciclos necesarios para hallar la solucion es: "<<numCiclosGauss<<"\n";
				break;
			case 3:
				//metodo jacobi Se calcula el tiempo de ejecucion y las iteraciones realizadas
				QueryPerformanceCounter(&t_ini);
				numCiclosJacobi=Jacobi(matrizCoeficientes,vectorValIndependientes,vectorSoluciones,valoresIniciales,n,errorPermitido);
				QueryPerformanceCounter(&t_fin);
				secs = performancecounter_diff(&t_fin, &t_ini);
				 cout<<"\nEl tiempo de ejecucion con el metodo jacobi es " <<secs * 1000.0<<"milisegundos";
				 cout<<"\n El numero de ciclos necesarios para hallar la solucion es: "<<numCiclosJacobi<<"\n";
				 // metodo Gauss Se calcula el tiempo de ejecucion y las iteraciones realizadas
				QueryPerformanceCounter(&t_ini1);
				numCiclosGauss=GaussSeidel(matrizCoeficientes,vectorValIndependientes,vectorSoluciones,valoresIniciales,n,errorPermitido);
				QueryPerformanceCounter(&t_fin1);
				secs1 = performancecounter_diff(&t_fin1, &t_ini1);
				cout<<"\nEl tiempo de ejecucion con el metodo GaussSeidel es " <<secs1 * 1000.0<<"milisegundos";
				cout<<"\n El numero de ciclos necesarios para hallar la solucion es: "<<numCiclosGauss<<"\n";
				break;
			case 4:
				exit(-1);
				break;
			default:
				cout<<"\nescoja una opcion valida\n";
				break;
		}
		return 0;
	}
