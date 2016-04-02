//router with two interfaces: veth2, veth3
require(library /home/comnetsii/elements/lossyrouterport.click);

router2::LossyRouterPort(DEV $dev2, IN_MAC $in_mac2, OUT_MAC $out_mac2, LOSS 0.8, DELAY 0.1);
router3::LossyRouterPort(DEV $dev3, IN_MAC $in_mac3, OUT_MAC $out_mac3, LOSS 0.8, DELAY 0.1);
router5::LossyRouterPort(DEV $dev5, IN_MAC $in_mac5, OUT_MAC $out_mac5, LOSS 0.8, DELAY 0.1);

Learn::Learning;

Idle -> router2 -> [0]Learn;
Idle -> router3 -> [1]Learn;
Idle -> router5 -> [2]Learn;

Learn[0] -> Print(0) -> router2;
Learn[1] -> Print(1) -> router3;
Learn[2] -> Print(2) -> router5;
Learn[3] -> Discard;