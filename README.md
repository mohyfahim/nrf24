# NRF24 

## Simple without Ack or Network Layer

**nrf24_client**: contains code that just sends a message every two seconds without any specific destinations. which means if any receiver was there, can receive the message.

**nrf24_server**: contains code that wait for a message. catches it and echoes it on its serial.

## Ack methodes without Router Layer

This folder contains code that used Address for sending and receiving data (BROADCAST_ADDRESS can be used). Also they use ACK methodes for sending data.

**nrf24_reliable_datagram_client_serial**: this module creates a client that send every line received from Serial port to a specific destination address (here Client address is set to 1 and server address is set to 2).

**nrf24_reliable_datagram_client**: this module sends a fixed message every 500ms. Everything else is like the prior.

**nrf24_reliable_datagram_server**: this module creates a listener that after receiving the message, sends its ACK to the sender.

## ACK methods with Router Layer

This folder contains codes that used address for sending and receiving data by forming a Routing table.

Here, the Routing structure is fixed and Hard coded.

We set three addresses (1,2,3) for three nodes and the mesh graph is like this:

"sender" <----> "middle" <----> "receiver"

**rf24_router_sender**: this module sends a fixed message to the receiver. handover is done automatically by RHRouter driver. if the middle node turned off, the message will not reach to destination.

**rf24_router_middle**: this module do nothing except handling the handover.

**rf24_router_receiver**: this module wait for receiving a message and after that sending it's ACK to the source address.
