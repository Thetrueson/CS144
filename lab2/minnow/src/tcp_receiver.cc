#include "tcp_receiver.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  // Your code here
  if ( message.RST ) {
    reassembler_.reader().set_error();
    RST_ = reassembler_.reader().has_error();
    return;
  } else if ( RST_ ) {
    return;
  }
  if ( message.SYN ) {
    this->zero_point = message.seqno;
    this->next = message.seqno + 1;
    this->is_start = true;
  }
  if ( message.FIN ) {
    this->is_last = message.seqno;
  }
  if ( is_start ) {
    over.push_back( message );
  }
  if ( !over.empty() && is_start ) {
    for ( uint64_t i = 0; i < over.size(); i++ ) {
      if ( over[i].SYN && over[i].FIN ) {
        this->reassembler_.insert( 0, over[i].payload, over[i].seqno == this->is_last );
      }
      if ( over[i].payload.size() || over[i].FIN ) {
        if ( over[i].seqno == zero_point && !over[i].SYN ) {
          break;
        }
        if ( over[i].SYN ) {
          this->start = over[i].seqno.unwrap( this->zero_point, this->all );
        } else {
          this->start = over[i].seqno.unwrap( this->zero_point, this->all ) - 1;
        }
        this->reassembler_.insert( this->start, over[i].payload, over[i].seqno == this->is_last );
      }
      this->all += over[i].sequence_length();
      this->next = zero_point + is_start + reassembler_.writer().bytes_pushed() + reassembler_.writer().is_closed();
    }
    over.clear();
  }
}

TCPReceiverMessage TCPReceiver::send() const
{
  // Your code here.
  TCPReceiverMessage message;
  if ( is_start ) {
    message.ackno = this->next;
  }
  message.RST = reassembler_.reader().has_error();
  message.window_size = min( this->reassembler_.writer().available_capacity(), static_cast<size_t>( UINT16_MAX ) );
  return message;
}
