#! bin/bash
# Load the user defined parameters
l="3"
w="2"
a="1"
b="0"
err="0.00001"
#change this two paths to point to Halide.h location(include) and Halide.so(sources) respectively
path_to_h="/home/meclotfi/Desktop/llvm/Halide/build/include"
path_to_so="/home/meclotfi/Desktop/llvm/Halide/build/src"

while [[ $# > 0 ]]
do
     case "$1" in
                -l|--length)
                        l="$2"
                        shift
                        ;;
                -w|--width)
                        w="$2"
                        shift
                        ;;
                -a|--alpha)
                        a="$2"
                        shift
                        ;;
                -b|--beta)
                        b="$2"
                        shift
                        ;;
                -ph|--path_to_h)
                        path_to_h="$2"
                        shift
                        ;;
                -ps|--path_to_iso)
                        path_to_so="$2"
                        shift
                        ;;
                -e|--accepted_error)
                        err="$2"
                        shift
                        ;;
                --help|*)
echo "comp: comp [ -l | -w | -a | -b | -ph | -ps ]

       Compile and run a program that realize generalized matrix vector multiplication 
       (gemv routine in Blas Library) <<  alpha * M[l,w].V[w] + beta * Y[w]  >> 
       ( M a matrix of size (l,w)  and V,Y vectors   of size respectively w , l )  
       In both Halide and pure C then  compare the results to check they are matching.
          
    *Impotante Note:
    
           it is neccessary to install Halide and change the paths to Halide.h headers 
           and libHalide.iso (in the script directly or by passing them as parameters
            -ph and -ps ) in order to run this script 
      
    
    Options:
    
 -l,--lenght           Allow to change the lenght of the matrix M which also 
                          set the size of the output vector to be the same (default 16)
                
 -w,--width	        Allow to change the lenght of the matrix M which also 
                          set the size of the vector Y to be the same (default 24)
                
 -a,--alpha	        Allow to change the value of the scalar alpha used in computing 
                          the output alpha * M[l,w]V[w] + beta * Y[w] (default 1)
                
 -b,--beta	        Allow to change the value of the scalar beta used in computing the
                          output alpha * M[l,w]V[w] + beta * Y[w] (default 0)
    		
 -ph,--path_to_iso	Allow to change the path to Halide.h headers,Noting that it is  
                          neccessary to install Halide and change this path in order 
                          to run this script  
    		
 -ps,--path_to_h	Allow to change the path to libHalide.iso,Noting that it is  
                          neccessary to install Halide and change this path in order 
                          to run this script 
 
 -e,--accepted_error   Allow to change the error acceted during the comparing of the output
                          of the two implementations(C and Halide)(default 0.00001)   
               
   --help              display this help and exit
   
    "
                    exit 1
                    ;;
    esac
    shift

done


g++ "Mat-Vect mult .cpp" -g -I $path_to_h  -L $path_to_so  -lHalide -lpthread -ldl -o exe -std=c++11
./exe -l $l -w $w -a $a -b $b -e $err$

