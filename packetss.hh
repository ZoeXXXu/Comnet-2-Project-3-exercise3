
typedef enum {
	HELLO = 0,
	DATA = 1,
	ACK = 2
} m_t;

typedef struct {
	u_char type;
	int dest_addr;
	int address;
	int sequence;
	const char* payload;
} packet_t;
