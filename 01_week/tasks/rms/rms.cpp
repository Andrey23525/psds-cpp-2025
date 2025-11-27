#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if(size == 0) return 0.0;
    if(values == nullptr) return 0.0; 

    long double sumOfSquares = 0;
    
    for(size_t i = 0; i < size; ++i) {
      double &value = values[i];
      sumOfSquares += value * value;
    }
    
    return sqrt(sumOfSquares / size);
}
