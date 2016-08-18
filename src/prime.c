#include <stdio.h>

/* Verifica se o numero e primo 
    ultilizando uma abordagem 
    simples
*/
int is_prime(unsigned int num) {
    
    if(num <= 1) return 0;
    
    //Percorre os numero se nao encontrar e primo
    for(int i = 2; i <= num / 2; i++) {
        if((num % i) == 0) return 0;

    }
   
    return 1; //é primo'
}
