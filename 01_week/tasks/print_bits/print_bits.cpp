#include <cstddef>
#include <stdexcept>


 void PrintBits(long long value, size_t bytes) {
    using std::cout;
    using ULL = unsigned long long;
    constexpr char BITS_IN_BYTE = 8;
    constexpr char BYTES_IN_LONG_LONG = sizeof(long long);

    size_t bits = bytes * BITS_IN_BYTE;

    // Сдвиг, чтобы напечатать младшие байты
    ULL mask = (bytes == BYTES_IN_LONG_LONG) 
      ? ~0ULL 
      : ((1ULL << (bits)) - 1);  
    
    ULL valueWithMask = static_cast<ULL>(value) & mask;
    cout << "0b";
    
    for(size_t i = 0; i < bits; ++i) {
      size_t bitIndex = bits - i - 1;
      bool bit = (valueWithMask >> bitIndex) & 1; // определение бита на позиции bitIndex
      cout << (bit ? '1' : '0');
      
      if(bitIndex % 4 == 0 && bitIndex != 0) {
        cout << '\'';
      }
    }

    cout << '\n';
}
