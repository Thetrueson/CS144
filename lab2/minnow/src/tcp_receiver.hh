#pragma once

#include "reassembler.hh"
#include "tcp_receiver_message.hh"
#include "tcp_sender_message.hh"
#include "wrapping_integers.hh"
#include <vector>

class TCPReceiver
{
public:
  // Construct with given Reassembler
  explicit TCPReceiver( Reassembler&& reassembler )
    : reassembler_( std::move( reassembler ) )
    , zero_point( 0 )
    , next( 0 )
    , start( 0 )
    , all( 0 )
    , is_start( false )
    , is_last( 999999 )
    , over()
  {}

  /*
   * The TCPReceiver receives TCPSenderMessages, inserting their payload into the Reassembler
   * at the correct stream index.
   */
  void receive( TCPSenderMessage message );

  // The TCPReceiver sends TCPReceiverMessages to the peer's TCPSender.
  TCPReceiverMessage send() const;

  // Access the output (only Reader is accessible non-const)
  const Reassembler& reassembler() const { return reassembler_; }
  Reader& reader() { return reassembler_.reader(); }
  const Reader& reader() const { return reassembler_.reader(); }
  const Writer& writer() const { return reassembler_.writer(); }

private:
  Reassembler reassembler_;
  Wrap32 zero_point;
  Wrap32 next;
  uint64_t start;
  uint64_t all;
  bool is_start;
  Wrap32 is_last;
  vector<TCPSenderMessage> over;
  bool RST_ = reassembler_.reader().has_error();
};
