type = 0: hello message
type = 1: data message
type = 2: ACK

If parameters ADDRESS and DESTINATION in PacketGen is equal, means no data packets will be sending out.

Below is command format needed:
router:
sudo ./userlevel/click ./conf/router.click dev2=veth2 dev3=veth3 dev5=veth5 in_mac2=a6:c8:0f:d7:a7:18 out_mac2=ba:45:07:30:94:e2 in_mac3=f2:60:e8:e8:06:6f out_mac3=86:d2:cb:f7:4b:9b in_mac5=16:1e:5a:3b:a5:a5 out_mac5=d6:09:7c:da:45:ad

client1:
sudo ./userlevel/click ./conf/client1.click dev1=veth1 in_mac1=ba:45:07:30:94:e2 out_mac1=a6:c8:0f:d7:a7:18

client2:
sudo ./userlevel/click ./conf/client2.click dev4=veth4 in_mac4=86:d2:cb:f7:4b:9b out_mac4=f2:60:e8:e8:06:6f

client3:
sudo ./userlevel/click ./conf/client3.click dev6=veth6 in_mac6=d6:09:7c:da:45:ad out_mac6=16:1e:5a:3b:a5:a5

In lossyrouterport, the loss probability is 0.2, delay time is 0.1 sec. Please open client1.click client2.click client3.click router.click to change these parameters.

@Author Haoyuan Xu