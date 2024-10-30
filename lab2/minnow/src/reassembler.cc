#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  this->assemble.insert( make_pair( first_index, data ) );
  if ( is_last_substring ) {
    this->is_over = true;
  }
  uint64_t o = 0;
  uint64_t l = 0;
  uint64_t k = 0;
  uint64_t p = 0;
  for ( auto item : this->assemble ) {
    if ( item.first + item.second.size() >= this->sum && item.first <= this->sum ) {
      uint64_t temp = this->output_.writer().available_capacity();
      p = 0;
      k = 0;
      l = 0;
      for ( uint64_t i = 0; i < item.second.size(); i++ ) {
        if ( vv.size() > i + item.first && vv[i + item.first] != item.second[i] ) {
          k++;
          continue;
        } else if ( vv.size() <= i + item.first && temp - p > 0 ) {
          vv.push_back( item.second[i] );
          p++;
        } else if ( temp - p <= 0 ) {
          l++;
        } else {
          k++;
        }
      }
      this->output_.writer().push( item.second.substr( this->sum - item.first ) );
      if ( item.first + item.second.size() >= this->sum && item.first <= this->sum && temp > 0 ) {
        this->sum = item.first + k + p;
      }
      o++;
      ;
    }
  }
  for ( uint64_t i = 0; i < o; i++ ) {
    this->assemble.erase( this->assemble.begin() );
  }
  if ( is_over && assemble.empty() && this->sum == l + vv.size() ) {
    this->output_.writer().close();
  }
  return;
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  uint64_t count = 0;
  set<char> s;
  for ( auto e : this->assemble ) {
    if ( this->output_.writer().available_capacity() > count && e.first >= this->sum ) {
      for ( auto e1 : e.second ) {
        s.insert( e1 );
      }
    }
  }
  count += s.size();
  if ( count >= this->output_.writer().available_capacity() && this->output_.writer().available_capacity() != 0 ) {
    count = this->output_.writer().available_capacity() - 1;
  }
  return count;
}
