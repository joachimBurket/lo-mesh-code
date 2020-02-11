# lo-mesh code

This is an implementation of a routing protocol over LoRa. The code runs on RAK2245 LoRa Gateways. The base firware was taken from the Semtech "LoRaNet" repo (https://github.com/Lora-net/).



## Project Tree

There are two folders in the implementation code, `mesh_gw/` and `root_gw/`, each containing the code to deploy on the Mesh Gateways respectively the Root Gateway.

Both directories contain the `packet_forwarder`, which is the program running on the Gateway that forward RF and UDP packets, and the `lora_gateway` code which is the driver/HAL for the SX1301 modem and SX1257/SX1255 tranceivers. Only the `packet_forwarder` is modified.

#### packet_forwarder/:

* `LoRaMac/`:                  Directory that contains the files related to the packets at the MAC layer. It contains the packet definition and the parser/serializer codes
* `LoRaMesh/`:               Directory that contains the files related to the packets at the MESH layer (routing layer). It contains the packet definition and the parser/serializer codes
* `lora_pkt_fwd.c`:    Contains the main program of the Gateway which is composed of 6 threads:
  * `thread_up()`:  Poll the concentrator for RF packets received, form the UDP messages and send them to the Network Server.
  * `thread_down()`: Poll the Network Server for downlink message, form the RF LoRaWAN packets and send them through the JIT scheduler
  * `thread_gps()`: Parses GPS message and keep gateway synced 
  * `thread_valid()`: Checks the time reference and calculates XTAL correction
  * `thread_jit()`: Just In Time downlink scheduler. Puts the downlink packets in a queue and send them over the air at the proper time.
  * `thread_timersync()`: Synchronization between unix, concentrator and gps clocks



## Root Gateway

In the Root Gateway, the `thread_up` and `thread_down` of the `packet_forwarder` were modified.

The *uplink thread* of the root gateways receives RF messages from the End Nodes and Mesh Gateways within range.

* If this message is a LoRaMAC, it is parsed and filled in an UDP packet that is sent to the Network server.

 * If it is a LoRaMesh packet:
   	* Routed Data Packet: The LoRaMAC packet is decapsulated and sent to the Network Server
      	* Route Request Packet: A Route Response message is sent back



The *downlink thread* receives UPD messages from the Network Server, and must then forward it to the concerned End Device. The Gateway looks in its Device Table the Gateway ID corresponding to the Device Address. If the device was in the Root Gateway range, a LoRaWAN message is directly sent to it. Otherwise, a LoRaMesh packet is sent to the next hop gateway.



## Mesh Gateway

In the Mesh Gateway, only the `thread_up` of the `packet_forwarder` was modified, because their is no Internet connection and therefore no communication with the network server.

Basically, the mesh gateways receives packets from LoRa RF, process them, and then depending the packet type, forward them.

