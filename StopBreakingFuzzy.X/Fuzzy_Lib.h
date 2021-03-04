/* 
 * File:   Fuzzy_Lib.h
 * Author: Jesús Lara
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  

#include <xc.h> // include processor files - each processor file is guarded.  
//Variables
float f=0;
int P=0;

//FUZZ


// FUNCIONES
int Fuz (int X,int Y);
int pimf(int x, float a, float b, float c,float d);

// ----------------------------CUERPO DE FUNCIONES----------------------------//


int pimf(int x, float a, float b, float c,float d){
    //float f=0;
    if (x<=a){
        f = 0;
    }
    else if (a<=x & x<=(a+b)/2){
        f = 2*((x-a)/(b-a))*((x-a)/(b-a))*100;
        
    }
    else if ((a+b)/2<=x & x<=b){
        f = 100-2*((x-b)/(b-a))*((x-b)/(b-a))*100;
    }
    else if (b<=x & x<=c){
        f = 100;
    }
    else if (c<=x & x<=(c+d)/2){
        f = 100-2*((x-c)/(d-c))*((x-c)/(d-c))*100;
    }
    else if ((c+d)/2<=x & x<=d){
        f = 2*((x-c)/(d-c))*((x-c)/(d-c))*100;
    }
    else if (x>=d){
        f = 0;
    }
    P =(int) f;
    return P;
}

        /*delay_ms(100);
        CCPR2L=125;
        for (i=125; i>=0; i--){
        CCPR2L = i;
        delay_ms(20);*/

int Fuz (int X,int Y){
    int A[4]={0,0,0,0}; //Reutilizacion C
	int B[4]={0,0,0,0}; //Reutilizacion Max
    //int C[4]={0,0,0,0}; 
	int n=0;
    int Min[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //int Max[5]={0,0,0,0,0};
    int CL[5]={0,0,0,0,0};
    int FCL=0;
	int Centroid=0;
    
    int universe_min = 0;
    int universe_max = 100;
    float step = 5;   //Can be decreased to increase processing speed
    int N = 0;      //Numerador
    int D= 0;       //Denominador
    int z = 0 ; //z = universe_min;
    //Evaluate input (X) in distance membership functions
	A[0] = pimf(X,-1,-1,40,133);
	A[1] = pimf(X,15,123,143,267);
	A[2] = pimf(X,133,256,276,400);
    A[3] = pimf(X,266,390,400,1000);
	//Evaluate input (Y) in velocity membership functions
	B[0] = pimf(Y,-1,-1,8,28);
    B[1] = pimf(Y,0,26,30,56);
    B[2] = pimf(Y,28,54,58,85);
    B[3] = pimf(Y,56,83,100,1000);
	//Find minimun between combinations of inputs membership functions
    for(int j=0;j<=3;j++){
		for(int i=0;i<=3;i++){
			if(A[j]<=B[i]){
				Min[n]=A[j];
				}
			else{
				Min[n]=B[i];
				}
            n++;
		}
	}
	//Inference table (max)
    if (Min[0]>=Min[1] & Min[0]>=Min[2] & Min[0]>=Min[3]){
        B[0] = Min[0];
    } 
    else if(Min[1]>=Min[0] & Min[1]>=Min[2] & Min[1]>=Min[3]){
        B[0] = Min[1];
    }
    else if (Min[2]>=Min[0] & Min[2]>=Min[1] & Min[2]>=Min[3]){
        B[0] = Min[2];
    }
    else { 
        B[0] = Min[3];
    }
    //**************************************************************************
    if (Min[4]>=Min[5] & Min[4]>=Min[6] & Min[4]>=Min[7]){  
        B[1] = Min[4];
    }
    else if (Min[5]>=Min[4] & Min[5]>=Min[6] & Min[5]>=Min[7]){
        B[1] = Min[5];
    }
    else if (Min[6]>=Min[4] & Min[6]>=Min[5] & Min[6]>=Min[7]){
        B[1] = Min[6];
    }
    else{ 
        B[1] = Min[7];
    }
    //**************************************************************************
    if (Min[10]>=Min[11] && Min[10]>=Min[12] & Min[10]>=Min[13]){
        B[2] = Min[10];
    }
    else if (Min[11]>=Min[10] & Min[11]>=Min[12] & Min[11]>=Min[13]){
        B[2] = Min[11];
    }
    else if (Min[12]>=Min[10] & Min[12]>=Min[11] & Min[12]>=Min[13]){
        B[2] = Min[10];
    }
    else{
        B[2] = Min[13];
    }
    //**************************************************************************
    if (Min[8]>=Min[10] & Min[8]>=Min[14] & Min[18]>=Min[15]){
        B[3] = Min[8];
    }
    else if (Min[9]>=Min[8] & Min[9]>=Min[14] & Min[9]>=Min[15]){
        B[3] = Min[9];
    }
    else if (Min[14]>=Min[8] & Min[14]>=Min[9] & Min[14]>=Min[15]){
        B[3] = Min[14];
    }
    else{
        B[3] = Min[15];
    }
    
    //**************************************************************************/
    
    // FUZZY INFERENCE SYSTEM -- DEFUZZYFICATION

    
    for (z=0; z<=100; z=step+z){
            //Evaluate z in breaking membership functions (outputs)
            A[0] = pimf(z,-1,-1,10,33);      //EVALUACION DE C REUTILIZANDO A
            A[1] = pimf(z,5,31,35,66);
            A[2] = pimf(z,33,64,68,100);
            A[3] = pimf(z,66,98,100,1000);

            //Find the cutlines
            for (int ii=0; ii<=3;ii++){
                if (B[ii]<= A[ii]){
                    CL[ii] = B[ii];
                }
                else{
                    CL[ii] = A[ii];
                }        
            }
            //Find the final cutline
            if (CL[0]>=CL[1] & CL[0]>=CL[2] & CL[0]>=CL[3]){
                FCL = CL[0];
            }
            else if (CL[1]>=CL[0] & CL[1]>=CL[2] & CL[1]>=CL[3]){ 
                FCL = CL[1];
            }
            else if (CL[2]>=CL[0] & CL[2]>=CL[1] & CL[2]>=CL[3]){ 
                FCL = CL[2];
            }
            else{
                FCL = CL[3];
            }
            //Defuzzyfication (process)
            N = N + FCL*z;
            D = D + FCL;
            z=z+step;
    }
    f=N/D;
    Centroid = (int) f; 
    
        return Centroid;
}


