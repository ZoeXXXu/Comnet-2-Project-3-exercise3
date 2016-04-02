#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include "HelloMessage.hh"
#include "packetss.hh"

CLICK_DECLS

HelloMessage::HelloMessage() : _timer(this) {}
HelloMessage::~HelloMessage(){}

int HelloMessage::configure(Vector<String> &conf, ErrorHandler *errh) {
	if (cp_va_kparse(conf, this, errh,
				"ADDRESS", cpkP + cpkM, cpInteger, &Address,
				cpEnd) < 0)
		return -1;
	_timer.initialize(this);
	_timer.schedule_after_msec(100);
	return 0;
}

int HelloMessage::initialize(ErrorHandler *) {
	_timer.initialize(this);   // Initialize timer object (mandatory).
	_timer.schedule_after_sec(2);
	return 0;
}

void HelloMessage::run_timer(Timer *) {
	// This function is called when the timer fires.
//	Timestamp now = Timestamp::now();
//	click_chatter("%s: %{timestamp}: timer fired!\n", declaration().c_str(), &now);
	this->hello();
	_timer.reschedule_after_sec(2);	
	
}

void HelloMessage::hello() {
//	click_chatter("Sending hello~");
	WritablePacket *packet = Packet::make(0, 0, sizeof(packet_t), 0);
	packet_t *header = (packet_t *)packet->data();
	header->type = HELLO;
	header->address = Address;
	output(0).push(packet);
}

void HelloMessage::push(int , Packet *p) {
	return;
}

CLICK_ENDDECLS
EXPORT_ELEMENT(HelloMessage)
