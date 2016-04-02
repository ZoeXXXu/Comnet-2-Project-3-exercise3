//Write an element every 3 seconds create such packet and assign 
//either 0 or 1 to the type field.
//author @Haoyuan 2/29/2016
#ifndef CLICK_PACKETGEN_HH
#define CLICK_PACKETGEN_HH

#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class PacketGen : public Element{
public:
	PacketGen();
	~PacketGen();

	const char *class_name() const { return "PacketGen"; }
	const char *port_count() const { return "1/1"; }
	const char *processing() const { return AGNOSTIC; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	int initialize(ErrorHandler *errh);
	void run_timer(Timer *timer);
	void sendRequest();

private:
	int cur_loop;
	int address;
	Timer _timer;
	int dest;
	int ACK;
};

CLICK_ENDDECLS

#endif
