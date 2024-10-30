#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  // Your code here.
  return Wrap32( zero_point + n );
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  uint64_t x = pow( 2, 32 );
  //  for(uint64_t i = 0;i<x;i++){
  uint64_t i = this->raw_value_ - zero_point.raw_value_;
  if ( *this == zero_point + i ) {
    uint64_t temp1 = i;
    uint64_t temp2 = i;
    uint64_t temp3 = i;
    temp1 += ( checkpoint / x ) * x;
    temp2 += ( checkpoint / x + 1 ) * x;
    temp3 += ( checkpoint / x - 1 ) * x;
    if ( ( temp1 > checkpoint ? temp1 - checkpoint : checkpoint - temp1 )
           < ( temp2 > checkpoint ? temp2 - checkpoint : checkpoint - temp2 )
         && ( temp1 > checkpoint ? temp1 - checkpoint : checkpoint - temp1 )
              < ( temp3 > checkpoint ? temp3 - checkpoint : checkpoint - temp3 ) ) {
      return temp1;
    } else if ( ( temp2 > checkpoint ? temp2 - checkpoint : checkpoint - temp2 )
                  < ( temp1 > checkpoint ? temp1 - checkpoint : checkpoint - temp1 )
                && ( temp2 > checkpoint ? temp2 - checkpoint : checkpoint - temp2 )
                     < ( temp3 > checkpoint ? temp3 - checkpoint : checkpoint - temp3 ) ) {
      return temp2;
    } else {
      return temp3;
    }
  }
  //  }
  return 0;
}
