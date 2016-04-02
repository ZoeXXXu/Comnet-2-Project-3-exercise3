#include <click/config.h>
#include <click/args.hh>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/timer.hh>
#include "PacketGen.hh"
#include "packetss.hh"

CLICK_DECLS

PacketGen::PacketGen() : _timer(this), cur_loop(0), ACK(1) {}
PacketGen::~PacketGen() {}

int PacketGen::configure(Vector<String> &conf, ErrorHandler *errh) {
	if (cp_va_kparse(conf, this, errh,
				"ADDRESS", cpkP + cpkM, cpInteger, &address,
				"DESTINATION", cpkP + cpkM, cpInteger, &dest,
				cpEnd) < 0) 
		return -1;
	if (address == dest)
		ACK = 222;
	_timer.initialize(this);
	_timer.schedule_after_msec(100);
	return 0;
}

int PacketGen::initialize(ErrorHandler *) {
	_timer.initialize(this);
	_timer.schedule_after_sec(3);
	return 0;
}

void PacketGen::run_timer(Timer *) {
	//This function is called when the timer fires
	//Timestamp now = Timestamp::now();
	//click_chatter("%s: %{timestamp}: timer fired!\n", declaration().c_str(), &now);
	if(ACK == 1){
		cur_loop++;
		this->sendRequest();
		ACK = 0;		
		_timer.reschedule_after_sec(5);
	}
	
	else if(ACK == 0){
		click_chatter("ACK::sequence %d ACK not received, waiting\n", cur_loop);
		this->sendRequest();
		_timer.reschedule_after_sec(5);
	}
	
	else{
		return;
	}
}

void PacketGen::sendRequest() {
	click_chatter("Sending data packet %d to client(address %d)!", cur_loop, dest);
	WritablePacket *packet = Packet::make(0, 0, sizeof(packet_t), 0);
	packet_t *header = (packet_t *)packet->data();
	header->type = DATA;
	header->dest_addr = dest;
	header->address = address;
	header->sequence = cur_loop;
	output(0).push(packet);
}

void PacketGen::push(int , Packet *p) {
	packet_t *header = (packet_t *)p->data();
	if(header->type == 2 && ACK != 222){
		click_chatter("ACK::Received data packet %d ACK from client(address %d), prepare to send next packet.", header->sequence, header->dest_addr);
		ACK = 1;
	}
	
	if(header->type == 1 && header->address != address){
		click_chatter("Received a data packet %d from client(address %d)!", header->sequence, header->address);
		WritablePacket *packet = Packet::make(0, 0, sizeof(packet_t), 0);
		packet_t *h = (packet_t *)packet->data();
		h->type = 2;
		h->dest_addr = header->address;
		h->address = header->dest_addr;
		h->sequence = header->sequence;
//		click_chatter("packet type %d, dest_addr %d, sequence %d back.", h->type, h->dest_addr, h->sequence);
		output(0).push(packet);
	}
	return;
}

CLICK_ENDDECLS

EXPORT_ELEMENT(PacketGen)