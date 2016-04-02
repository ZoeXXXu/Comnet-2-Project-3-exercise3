#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include <click/hashtable.hh>
#include "Learning.hh"
#include "packetss.hh"

CLICK_DECLS

Learning::Learning() : LearnTable(3) {}
Learning::~Learning(){}

int Learning::configure(Vector<String> &, ErrorHandler *) {
	return 0;
}

void Learning::push(int port, Packet *p) {
//	click_chatter("run push here! port %d", port);
	packet_t *header = (packet_t *)p->data();
	if (header->type == 0){
//		header->type = ACK;
		LearnTable.find_insert(header->address, port);
//		output(port).push(p);
	}
	if(header->type != 0){
		int i = LearnTable.get(header->dest_addr);
		click_chatter("Packet receive from port %d, sending to port %d", port, i);
		if(i == 0 || i == 1 || i == 2){
			output(i).push(p);
		}
		else{
			click_chatter("Cannot find this address.");
			output(3).push(p);
		}
	}
	for (HashTable<int, int>::iterator it = LearnTable.begin(); it; ++it)
		click_chatter("client(address: %d) connected to %d port\n", it.key(), it.value());
}

CLICK_ENDDECLS
EXPORT_ELEMENT(Learning)
