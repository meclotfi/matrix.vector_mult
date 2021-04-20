
//g++ "Mat-Vect mult.cpp" -g -I /home/meclotfi/Desktop/llvm/Halide/build/include -L /home/meclotfi/Desktop/llvm/Halide/build/src -lHalide -lpthread -ldl -o lesson_01 -std=c++11


#include "Halide.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace Halide;

void check_results(float* imp_c,float* imp_h,int lenght,float err_thresh)
{
bool Is_equal=true;
float ind_err,sum=0;
int index;
 for (int i = 0; i < lenght; i++) {
            ind_err=std::abs(imp_c[i] - imp_h[i]);
            if ((ind_err<err_thresh) && (Is_equal)){ Is_equal=true;index=i;}
            else Is_equal=false;
            sum+=ind_err;
        }
 
if (Is_equal)
{
    printf(">>> Results of the two Implementations (in C and Halide) matches with a MAE(Mean Absolute Error)  of %f \n",sum);
}
else
{
   printf(">>> Results of the two Implementations (in C and Halide) Does not match , an error is detected in index %d ",index);
}

}

void print_results(float* imp_c,float* imp_h,int lenght,float err_thresh)
{
printf("|------------------------------------------------------------------------------------------------|\n");
printf("| Index  |  Halide Implementation  output | C Implementation Output | Difference(absolute error) |\n");
printf("|------------------------------------------------------------------------------------------------\n");
bool Is_equal=true;

float erreur_thresh=0.001f;
float ind_err,sum;
 for (int i = 0; i < lenght; i++) {
            ind_err=std::abs(imp_c[i] - imp_h[i]);

            if ((ind_err<err_thresh) && (Is_equal)) Is_equal=true;
            else Is_equal=false;

            sum+=ind_err;
printf("|   %d               %f                     %f                  %f           \n",i,imp_c[i],imp_h[i],ind_err);
printf("|------------------------------------------------------------------------------------------------\n");
        }
 

}

// ###### C implementation of the generalized matrix vector implementation (alpha*AV+beta*Y)

void mat_mult_vect_C(float* M, float *V,float *Y,int l,int w,float *output,int a,int b) {

    int i, j;
    float sum=0; 
    for (i=0; i<l; i++)
    {
        output[i]=b*Y[i];
        sum=0;    
        for (j=0; j<w; j++)
        {
            sum += M[j*l+i] * V[j];
        }
        output[i]+=a*sum;
        
    }
    /*
    for (j=0; j<l; j++)
        {
            printf("%f\n",output[j]);
            
        }
    */
}


int main(int argc, char **argv) {

    int lenght=3;
    int width=2;
    int beta=0,alpha=1;
    float err_thresh=0.00001f;

//parsing arguments of commande line
   for (int i = 1; i < argc; i=i+2)
    {

        if(strcmp(argv[i],"-l")==0) lenght=atoi(argv[i+1]);
        if(strcmp(argv[i],"-w")==0) width=atoi(argv[i+1]);
        if(strcmp(argv[i],"-a")==0) alpha=atoi(argv[i+1]);
        if(strcmp(argv[i],"-b")==0) beta=atoi(argv[i+1]);
        if(strcmp(argv[i],"-e")==0) err_thresh=atof(argv[i+1]);
        
    }
  

    printf("This program realize generalized matrix vector multiplication :  <<  alpha(=%d) * M[%d,%d]V[%d] + beta(=%d) * Y[%d]  >> In both Halide and pure C and compare the results \n\n",alpha,lenght,width,width,beta,lenght); 
 
   

// Declaring Used Data Structures 
    Buffer<float> M(lenght,width);
    Buffer<float> V(width);
    Buffer<float> Y(lenght);
    Buffer<float> output_h(lenght);

// Randpm initialisation of matrix M and vectors V,Y

    // V
    for (int i = 0; i < width; i++) {
            //V(i) = 1.0f ;
            V(i)=(rand()%1024)/1024.0f;
        }
    // Y
    for (int i = 0; i < lenght; i++) {
            //Y(i) = 1.0f ;
            Y(i) =  (rand()%1024)/1024.0f;
        }
    // M
    for (int iy = 0; iy < width; iy++) {
        for (int ix = 0; ix < lenght; ix++) {
            M(ix, iy) = (rand()%1024)/1024.0f;
        }
    }


// ######### Halide implementation of the generalized matrix vector implementation ###############
    Var x, y;
    RDom k(0, width);

    // M*V
    Func mult_m_v("mult_m_v");
    mult_m_v(x)=0.0f;
    mult_m_v(x)=mult_m_v(x)+M(x,k) * V(k);

    // generalized mv mult: beta*Y + alpha* MV
    Func gen_mv_mult("gen_mv_mult");
    gen_mv_mult(x)=beta*Y(x)+alpha*mult_m_v(x);
  
  //Realizing the Multiplication in Halide and print the output
    gen_mv_mult.realize(output_h);
    /*
    for (int ix = 0; ix < lenght; ix++) {
            printf("output[%d]=%f \n",ix,output_h(ix));
        }
    */




// Executing C version of the generalized maultiplication
float output_c[lenght];
mat_mult_vect_C(M.data(),V.data(),Y.data(),lenght,width,output_c,alpha,beta); 




//Comparing the two results
check_results(output_c,output_h.data(),lenght,err_thresh);
char ch;
printf(" Enter y to see more details about the results [y/n] : ");
scanf("%c",&ch);
if(ch=='y')
{
    print_results(output_c,output_h.data(),lenght,err_thresh);
}
return 0;
}
