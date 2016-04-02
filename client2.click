//this is veth4 interface connected router(client), it will send the packets to veth1, and the packet will go from veth4 to veth3.
require(library	/home/comnetsii/elements/lossyrouterport.click);

//define($in_mac 26:37:9e:1b:73:1b); //veth4_mac
//define($out_mac ea:56:e0:b1:b0:05); //veth3_mac
//define($dev veth4);

router4::LossyRouterPort(DEV $dev4, IN_MAC $in_mac4, OUT_MAC $out_mac4, LOSS 0.8, DELAY 0.1);

//ADDRESS veth4
HelloMessage(ADDRESS 4) -> router4;
Idle -> router4 -> PacketGen(ADDRESS 4, DESTINATION 6) -> router4;
