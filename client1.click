//this is veth1 interface connected router(client), it will send the packets to veth1, and the packet will go from veth1 to veth2.
require(library	/home/comnetsii/elements/lossyrouterport.click);

//define($in_mac 26:37:9e:1b:73:1b); //veth1_mac
//define($out_mac ea:56:e0:b1:b0:05); //veth2_mac
//define($dev veth1);

router1::LossyRouterPort(DEV $dev1, IN_MAC $in_mac1, OUT_MAC $out_mac1, LOSS 0.8, DELAY 0.1);

//ADDRESS veth1_mac
HelloMessage(ADDRESS 1) -> router1;
Idle -> router1 -> PacketGen(ADDRESS 1, DESTINATION 4) -> router1;