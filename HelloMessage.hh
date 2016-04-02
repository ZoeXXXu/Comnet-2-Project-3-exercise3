#ifndef CLICK_HELLOMESSAGE_HH
#define CLICK_HELLOMESSAGE_HH

#include <click/element.hh>
#include <click/timer.hh>

CLICK_DECLS

class HelloMessage : public Element {

public:
	HelloMessage();
	~HelloMessage();
	
	const char *class_name() const { return "HelloMessage";}
	const char *port_count() const { return "0/1"; }
	const char *processing() const { return PUSH; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	int initialize(ErrorHandler *errh);
	void run_timer(Timer *timer);
	void hello();
	
private:
	int Address;
	Timer _timer;
};

CLICK_ENDDECLS

#endif
