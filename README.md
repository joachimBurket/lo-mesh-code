# lo-mesh code

This is an implementation of a routing protocol over LoRa. The code runs on RAK2245 LoRa Gateways. The base firware was taken from the Semtech "LoRaNet" repo (https://github.com/Lora-net/).



There are two directories:

* `root_gw`:
  * Contains the code to deploy on a Root Gateway

* `mesh_gw`: 
  * Contains the code to deploy on a Mesh Gateway.



## Root Gateway

In the Root Gateway, the `thread_up` and `thread_down` were modified.

The *uplink thread* of the root gateways receives RF messages from the End Nodes and Mesh Gateways within range.

	* If this message is a LoRaMAC, it is parsed and filled in an UDP packet that is sent to the Network server.
 * If it is a LoRaMesh packet:
   	* Routed Data Packet: The LoRaMAC packet is decapsulated and sent to the Network Server
   	* Route Request Packet: A Route Response message is sent back



The `downlink thread` receives UPD messages from the Network Server, and must then forward it to the concerned End Device. The Gateway looks in its Device Table the Gateway ID corresponding to the Device Address. If the device was in the Root Gateway range, a LoRaWAN message is directly sent to it. Otherwise, a LoRaMesh packet is sent to the next hop gateway.



## Mesh Gateway

In the Mesh Gateway, only the `thread_up` was modified, because their is no Internet connection and therefore no communication with the network server.

Basically, the mesh gateways receives packets from LoRa RF, process them, and then depending the packet type, forward them.

