 #include <stdio.h>  
 int main( int argc, char *argv[] )  
 {  
   printf("argc: %d \n", argc);  
   printf("Program name: %s \n", argv[0]);  
   if(argc > 1){  
     int i;  
     for(i = 1; i < argc; i++){  
       printf("Argument number <%d> is: %s \n", i, argv[i]);  
     }  
   }  
   return 0;  
 }  
