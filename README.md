# matrix.vector_mult

A script that Compile and run a program (Mat-Vect mult .cpp) that realize generalized matrix vector multiplication  (gemv routine in Blas Library)
<<  alpha * M[l,w].V[w] + beta * Y[w]  >> ( M a matrix of size (l,w)  and V,Y vectors   of size respectively w , l )  
In both Halide and pure C then  compare the results to check they are matching.

## How to Use the Script?

1. It is neccessary to install Halide and change the paths to Halide.h headers and libHalide.iso (in the script file directly or by passing them as parameters
   -ph and -ps ) in order for this script to run correctly .
   
2. The Script is written in bash script language so in order to run it you should use bash interpreter which is included by default in
Unix systems(Linux and MacOS) , The command to run the script is : #bash ./comp.sh \n

The comman come with several options that you can specify in order to change key parameters ,this options are presented below:
Options:
    
 * **-l,--lenght** :          Allow to change the lenght of the matrix M which also set the size of the output vector to be the same (default 16)
                
 * **-w,--width** :     Allow to change the lenght of the matrix M which also set the size of the vector Y to be the same (default 24)
                
 * **-a,--alpha** :	        Allow to change the value of the scalar alpha used in computing the output alpha * M[l,w]V[w] + beta * Y[w] (default 1)
                
 * **-b,--beta** :	        Allow to change the value of the scalar beta used in computing the output alpha * M[l,w]V[w] + beta * Y[w] (default 0)
    		
 * **-ph,--path_to_iso** :	Allow to change the path to Halide.h headers,Noting that it is  neccessary to install Halide and change this path in order  to run this script  
    		
 *  **-ps,--path_to_h** :	Allow to change the path to libHalide.iso,Noting that it is   neccessary to install Halide and change this path in order  to run this script 
 
 * **-e,--accepted_error** :   Allow to change the error acceted during the comparing of the output of the two implementations(C and Halide)(default 0.00001)   
               
  * **--help** :              display this help and exit
