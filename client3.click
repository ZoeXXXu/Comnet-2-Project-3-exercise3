//this is veth6 interface connected router(client), it will send the packets to veth1, and the packet will go from veth6 to veth5.
require(library	/home/comnetsii/elements/lossyrouterport.click);

//define($in_mac ba:cd:dc:fc:82:cf); //veth6_mac
//define($out_mac 82:9c:86:8e:89:6c); //veth5_mac
//define($dev veth6);

router6::LossyRouterPort(DEV $dev6, IN_MAC $in_mac6, OUT_MAC $out_mac6, LOSS 0.8, DELAY 0.1);

//
HelloMessage(ADDRESS 6) -> router6;
Idle -> router6 -> PacketGen(ADDRESS 6, DESTINATION 1) -> router6;
