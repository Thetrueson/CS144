#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ),memory(),now(0),sum(0) {}

bool Writer::is_closed() const
{
  // Your code here.
  return !memory.empty()&&this->memory.back()=="EOF";
}

void Writer::push( string data )
{
  // Your code here.
  string::size_type index = 0;
  while(now<capacity_&&!this->is_closed()&&data.length()>index)
  {
	string str;
	if(data[index]+str == "")
	{
		break;
	}
	this->memory.push(data[index]+str);
	index++;
	this->now+=1;
	this->sum+=1;
  }
  return;
}

void Writer::close()
{
  // Your code here.
  this->memory.push("EOF");
  return;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return this->capacity_-this->now;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return this->sum;
}

bool Reader::is_finished() const
{
  // Your code here.
  return this->now==0&&this->memory.front()=="EOF";
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return this->sum-this->now;
}

string_view Reader::peek() const
{
  // Your code here.
  return this->memory.front();
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  for(uint64_t i = 0;i<len;i++){
	if(this->memory.front()!="EOF"&&!this->memory.empty()){
		this->memory.pop();
		this->now-=1;
        }
	else{
		break;
	}
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return this->now;
}
