#ifndef CLICK_LEARNING_HH
#define CLICK_LEARNING_HH

#include <click/element.hh>
#include <click/hashtable.hh>

CLICK_DECLS

class Learning : public Element {

public:
	Learning();
	~Learning();
	
	const char *class_name() const { return "Learning";}
	const char *port_count() const { return "3/4"; }
	const char *processing() const { return PUSH; }
	
	int configure(Vector<String>&, ErrorHandler*);
	void push(int, Packet *);
	
private:
	HashTable<int, int> LearnTable;
};

CLICK_ENDDECLS

#endif
