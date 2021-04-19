# matrix.vector_mult

A script that Compile and run a program (Mat-Vect mult .cpp) that realize generalized matrix vector multiplication  (gemv routine in Blas Library)
<<  alpha * M[l,w].V[w] + beta * Y[w]  >> ( M a matrix of size (l,w)  and V,Y vectors   of size respectively w , l )  
In both Halide and pure C then  compare the results to check they are matching.

## How to Use the Script?

1. It is neccessary to install Halide and change the paths to Halide.h headers and libHalide.iso (in the script file directly or by passing them as parameters
   -ph and -ps ) in order for this script to run correctly .
   
2. The Script is written in bash script language so in order to run it you should use bash interpreter which is included by default in
Unix systems(Linux and MacOS)
the command to run the script is : #bash ./comp.sh
