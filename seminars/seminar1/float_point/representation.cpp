#include <cmath>                                                               
#include <iostream>

int main(void)                                                                  
{                                                                               
   double pi = 42.42;
   double mantissa;                                                                 
   int exponent;                                                                       
                                                                                                                                                 
   mantissa = std::frexp(pi, &exponent);                                                            
                                                                                
   std::cout << "mantissa: " << mantissa << " exponent: " << exponent;                
}                                                                               