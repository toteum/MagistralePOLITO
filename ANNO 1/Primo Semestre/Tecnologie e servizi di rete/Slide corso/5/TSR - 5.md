---
marp: true
title: IPv6
author: Claudio Casetti, Guido Marchetto, Alessio Sacco, Marco Rapelli
theme: default
paginate: true
---

# IPv6

**Tecnologie e Servizi di Rete**
**Computer Network Technologies and Services**
**Internet Architecture and Technologies**

Claudio Casetti, Guido Marchetto, Alessio Sacco, Marco Rapelli

---

## Copyright Notice

This set of transparencies, hereinafter referred to as slides, is protected by copyright laws and provisions of International Treaties. The title and copyright regarding the slides (including, but not limited to, each and every image, photography, animation, video, audio, music and text) are property of the authors specified on page 1.

The slides may be reproduced and used freely by research institutes, schools and Universities for non-profit, institutional purposes. In such cases, no authorization is requested.

Any total or partial use or reproduction (including, but not limited to, reproduction on magnetic media, computer networks, and printed reproduction) is forbidden, unless explicitly authorized by the authors by means of written license.

Information included in these slides is deemed as accurate at the date of publication. Such information is supplied for merely educational purposes and may not be used in designing systems, products, networks, etc. In any case, these slides are subject to changes without any previous notice. The authors do not assume any responsibility for the contents of these slides (including, but not limited to, accuracy, completeness, enforceability, updated-ness of information hereinafter provided).

In any case, accordance with information hereinafter included must not be declared.

In any case, this copyright notice must never be removed and must be reported even in partial uses.

---

# Motivation and History

---

## Why a new version of the IP protocol?

Only one true answer:

> "A larger address space"

---

## Motivation

Additional answers:

- More efficient on LANs
- Multicast and Anycast
- Security
- Policy routing
- Plug and Play
- Traffic Differentiation
- Mobility
- Quality of Service support

![Ported to IPv4](https://via.placeholder.com/300x150?text=Ported+to+IPv4)

---

## The long way to IPv6 adoption

Long time for defining IPv6 and migrating to it

Problems needed an interim solution in IPv4

- Port IPv6 solutions to IPv4
- Find workaround (e.g., NAT)

When IPv6 reached "production" stage, many IPv4 solutions were acceptable

---

## IPv4 address exhaustion

32-bit long addresses → about 4 billion addresses!

However:

- Only part of the addresses are assigned to stations
- Divided into Class A, B and C
- Addresses beginning by `b111` are used for multicast and otherwise
- Hence, "just" 3.5 billion addresses can be used!

They are used hierarchically
- The prefix used in a physical network cannot be used in a different one
- Lots of unused addresses

Who needs them?

- Roughly half the world populations has home access (4 billion)
- 5.5 billion mobile phones in the world require Internet connectivity
- Internet of Things (IoT) will add about another 50 billion devices in this decade

---

## Interim solutions to the saturation of address space

Introduction of network with "tailored" size

- Netmask

Private addresses

- Intranet, RFC 1918
- Not enough to solve the problem
- It should be used in conjunction with NAT or ALG

Network Address Translator (NAT)

- Extremely popular but...
- it breaks end-to-end reachability, increases processing load at gateways, adds complexity

Has all this been effective?

- Carrier-Grade NAT (CGN, RFC 6598, shared space `100.64.0.0/10`): today the main way ISPs stretch IPv4
- ALG (Application Layer Gateway)

---

## Who assigns IP addresses?

IANA assigns blocks of /8 IP addresses to each Regional Internet Registry (RIR)

- **AFRINIC** - Africa
- **APNIC** - East Asia, Australia and Oceania
- **ARIN** - USA, Canada and some Caribbean islands
- **LACNIC** - South America, Mexico and some Caribbean islands
- **RIPE NCC** - Europe, Middle East and Central Asia

![RIR map](https://via.placeholder.com/600x300?text=RIR+Map)

IANA pool ran out in Feb. 2011, only RIRs have now limited /8 blocks

Subsequently, RIRs split the blocks into smaller blocks and assign them to respective National Internet Registries (NIRs) and Local Internet Registries (LIRs)

---

## IPv4 Address Pool status

Any individual IPv4 address can be in any one of five states:

reserved for special use, or part of the IANA unallocated address pool, part of the unassigned pool held by an RIR, assigned to an end user entity but unadvertised by BGP, or assigned and advertised in BGP

![IPv4 Address Pool Status](https://via.placeholder.com/700x300?text=IPv4+Address+Pool+Status)

---

## Current IPv4 Status

![Current IPv4 Status](https://via.placeholder.com/700x300?text=Current+IPv4+Status)

---

## Routing Scalability Issues

Routing table size

- Internet size
- Each subnetwork must be advertised

Problems

- Router resource limitations
- Too much information to manage
- Routing protocol limitations
- High probability of route changes
- Mainly affecting backbone routers

---

## Growth of BGP Tables

![Growth of BGP Tables](https://via.placeholder.com/700x400?text=Growth+of+BGP+Tables)

---

## Possible solution with IPv4

Aggregate multiple routes in one
- Shorter prefix including others
- 1.2.1.0/24, 1.2.2.0/24 ... → 1.2.0.0/16

CIDR (Classless Inter-Domain Routing)

Limited by non-rational assignment of IP prefixes

---

## Interim (IPv4) solutions to routing scalability

**CIDR** (Classless Inter-Domain Routing)

Limiting the assignment of IP addresses

- Regional Internet Registry: assign address blocks only to big players
- E.g., maximum /20 (4096 addresses) network: maximum users get space from their ISP

Scalability of routing protocols

- No solution, at present
- Problem not completely solved
- It is the major problem that IPv6 wanted to solve that it is still open

---

## History of IPv6

IETF Boston Meeting (1992), "Call for proposals for IPng"
- Appointment of dedicated Working Groups

Several proposals

- **TUBA** (TCP and UDP with Bigger Addresses): adopting OSI CLNP as new IP
- **CATNIP**: integration of different network (IP, CLNP, IPX) and transport (TP4, SPX, TCP, UDP) protocols
- **SIPP**: incremental over IPv4
  - Fix some drawbacks
  - Minimal protocol changes: increasing the address field and eliminating unused ones

Winning proposal: **SIPP with 128-bit addresses**

RFC 1752 (1994) recommends SIPP; first IPv6 spec RFC 1883 (1995); current Internet Standard RFC 8200 (2017)

---

## IPv6 deployment today (2026)

- Share of users reaching Google over IPv6 passed 50% for the first time in April 2026
- BGP table, Jan. 2026: ≈ 242,000 IPv6 prefixes vs ≈ 1,050,000 IPv4 prefixes
- Adoption is very uneven across countries and operators
- Mobile networks often lead: IPv6-only access, with NAT64/464XLAT to reach IPv4 destinations
- IPv4 keeps working thanks to CGN and the address transfer market
- Dual stack is still the norm; IPv4 cannot be switched off yet
- Live statistics: google.com/ipv6, stats.labs.apnic.net/ipv6

---

# IPv6 Addresses

---

## How many addresses for IPv6?

Scientific approach followed:

What is the number of "usable" addresses, accounting for inefficiencies due to hierarchical allocation

Addressing efficiency (RFC 1715, later updated by RFC 3194):

$$HD = \frac{\log_{10}(\text{number of usable addresses})}{\log_{10}(2^{\text{number of bits}})}$$

Real-world hierarchical allocation rarely achieves an HD higher than 0.86, and values around 0.8 were typical or even optimistic. HD = 0.75 was considered pessimistic

- 64 bits usable addresses = 2.6 E+15 (optimistic), 2.8 E+14 (pessimistic)
- 128 bits usable addresses = 6.6 E+30 (optimistic), 7.9 E+28 (pessimistic)

---

## Final decision: 128 bits

Assuming one million billion networked stations

- 107 bits in the minimum efficiency case, HD ≈ 0.39 (with 64 bits: HD ≈ 0.78, at the limit)

To put it in perspective...

- 655,570,793,348,866,943,898,599 IPv6 addresses per m² of Earth surface

![Address comparison](https://via.placeholder.com/600x300?text=IPv4+vs+IPv6+Addresses)

---

## IPv6 address notation

8 hexadecimal numbers separated by ":"
`x:x:x:x:x:x:x:x`

Groups of 2 bytes

Examples:

- `FEDC:0000:0876:45FA:0562:0000:3DAF:BB01`
- `1080:0000:0000:0007:0200:A00C:3423:A089`

**Shortcut rule #1:** Leading 0s in each digit group can be omitted

`1080:0:7:200:A00C:3423:A089`

**Shortcut rule #2:** All-0s Hextets can be substituted by "::" (only once)

`1080::7:200:A00C:3423:A089`

`FEDC:0000:0876:45FA:0562:0000:3DAF:BB01` → `FEDC:0876:45FA:0562:3DAF:BB01`

---

# Routing and Addressing Principles
## Host Addresses

---

## Same routing principles as IPv4

---

## Address Structure
Prefix (n bits) | Interface ID (128-n bits)

n = 64

---

## Address/Netmask

Address/netmask pair is substituted by a "Prefix"

Address/N, where N is the prefix length [bit]

Examples:

- Address: `FEDC:0123:8700::3/48`
- Prefix: `111111101101110000000010010001110000111000000000` (also called site prefix)
- Interface ID: `00000000000000000000000000000000000000000000000000000000000000000000000000000011`

**No address classes!**

---

## Address assignment principles

- Same as IPv4 (different terminology)
- **Subnetwork**: set of hosts with same prefix
- **Link**: physical network
- Subnetwork = Link!
- On-link hosts have the same prefix
  - Direct communication
- Off-link hosts have different prefix
  - Communication through a router

---

## IPv6 Address Space - Multicast

![IPv6 Address Space](https://via.placeholder.com/600x400?text=IPv6+Address+Space)

- Unicast
- Multicast
  - Well-Known `ff00::/12`
  - Transient `ff10::/12`
  - Solicited-Node `ff02:0:0:0:0:1:ff00::/104`
- Anycast
- Global Unicast `2000::/3`
- Link-Local `fe80::/10`
- Loopback `::1/128`
- Unspecified `::/128`
- Unique Local `fc00::/7`
- Embedded IPv4 `::/80`

---

## Multicast

Multicast

`1111 1111 ...` → `FF00::/8` → `FFxx:xxx...`

equivalent to the IPv4 multicast address `224.0.0.0/4`

Further divided into:

- **Well-known Multicast** (`FF00::/12`): predefined or reserved multicast addresses for assigned groups of devices (e.g., routers)
- **Transient** (`FF10::/12`): dynamically assigned by multicast apps
- **Solicited-node Multicast** (`FF02:0:0:0:0:1:FF00::/104`): similar to IP broadcast address in ARP (see later)

---

## Multicast addresses

![Multicast address format](https://via.placeholder.com/600x200?text=Multicast+Address+Format)

- **8 Bits**: `1111 1111` (FF00::/8)
- **4 Bits**: Flag 0RPT
- **4 Bits**: Scope
- **112 Bits**: Group ID

**T Flag**
- 0 Permanent, well-known multicast address assigned by IANA
- 1 Non-permanently assigned ("transient" or "dynamically assigned")

**Scope**: allows devices to define the range of the multicast packet (how broadly to propagate the packet)

- E - Global
- 8 - Organization-local
- 5 - Site-local
- 2 - Link-local
- 1 - Interface-local

---

## IPv6 Address Space - Unicast

---

## Global Unicast Addresses

- also known as aggregatable global unicast addresses
- globally routable and reachable
- Plug and play
- equivalent to public IPv4 addresses
- Topology-based assignment with effective aggregation

![Global Unicast Address format](https://via.placeholder.com/600x200?text=Global+Unicast+Address)

- `001` (3 bits)
- Global Routing Prefix (n bits) - Assigned to site by provider
- Subnet ID (m bits) - subnets inside site
- Interface ID (128-n-m bits)

---

## Global Unicast Addresses (historical)

Today's Global Routing prefix was formerly assigned by multi-level authorities:

- Top-level Authority (Large ISP) → TLA ID (13 bits)
- Next-level Authority (Organization) → NLA ID (32 bits)
- Subnet level Authority → SLA ID (16 bits)
- Interface ID (64 bits)

`001 | TLA ID | NLA ID | SLA ID | Interface ID`

---

## Address space allocation

![Address space](https://via.placeholder.com/200x500?text=Address+Space)

- multicast
- `FF00::0`
- Site local
- Link local
- `FE80::0`
- `3FFF::`
- global unicast
- `2000::`

---

## Link local/site local addresses

**Link/site local**

`1111 1110 1...`

**Link local**

- Used for addresses on a single link for auto-address configuration, neighbor discovery, or when no routers are present
- Packets sent to these addresses are not supposed to be forwarded across local links
- `FE80::/64`

`1111 1110 10...`

**Site local**

- Deprecated
- `FEC0::/10`

---

## Unique Local Addresses

- ULA addresses can be used similarly to global unicast addresses but are for private use and should not be routed in the global Internet
- `FC00::/7`
- Used for devices that never need access to the Internet and never need to be accessible from the Internet
- The 8th bit is the "Local (L) Flag", dividing the range in:
  - `fc00::/8` (1111 1100): If L flag is 0, may be defined in the future
  - `fd00::/8` (1111 1101): If L flag is 1, the address is locally assigned
- `fd00::/8` are the only valid ULA addresses today!

![ULA format](https://via.placeholder.com/600x100?text=ULA+Format)

- `1111 1101` (8 bits)
- Randomly generated (40 bits)
- Subnet ID (16 bits)
- Interface ID (64 bits)

---

## IPv4 Embedded Addresses

- used to represent an IPv4 address inside an IPv6 address
- aid the transition from IPv4 to IPv6
- IPv4 address carried in the low-order 32 bits
- e.g., IPv6 compressed format of IPv4-mapped 20.10.4.3 address: `::ffff:20.10.4.3`

![IPv4 Embedded format](https://via.placeholder.com/600x100?text=IPv4+Embedded+Format)

- `0000...0000` (80 bits)
- `FFFF` (16 bits)
- `x.y.y.z` (32 bits) - IPv4 address

---

## Loopback Address

- Used by a node to send an IPv6 packet to itself for testing reasons
- `::1` (000...1)
- Equivalent to IPv4 address: `127.0.0.1`
- Same rules as IPv4:
  - cannot be assigned to a physical interface
  - packets with a loopback address should never be sent beyond the device
  - routers can never forward packets with a destination address that is a loopback address
  - device must drop a packet received on an interface if the destination address is a loopback address

---

## Unspecified Addresses

- An unspecified unicast address is an all-0s address
- An unspecified unicast address is used as a source address to indicate the absence of an address
- It cannot be assigned to an interface
- Used in duplicate address detection in ICMPv6

---

## Anycast Addresses

- Address that can be assigned to more than one interface (typically different devices)
- multiple devices can have the same anycast address
- A packet sent to an anycast address is routed to the "nearest" interface having that address, according to the router's routing table
- Anycast addresses use Global Unicast Addresses, with routers advertising the same prefix from multiple sites and BGP (global routing protocol) handling duplicates
- Now used extensively for public DNS and CDNs (Content Distribution Networks)
- Google Public DNS IPv4: 8.8.8.8, 8.8.4.4
- Google Public DNS IPv6 addresses: 2001:4860:4860::8888, 2001:4860:4860::8844

---

# Modified Protocols

---

## What changes in the protocol architecture?

- IP
- ICMP
- ARP → Integrated in ICMP
- IGMP → Integrated in ICMP

---

## Upgraded but not changed

- DNS (type AAAA record)
- RIP and OSPF
- BGP and IDRP
- TCP and UDP
- Socket interface

![What about layer independence?](https://via.placeholder.com/300x150?text=Layer+Independence)

---

# Packet Header Format

---

## IPv4 Header (for comparison)

| Field | Description |
|---|---|
| Ver. | Version |
| IHL | Header Length |
| ToS (DS) | Type of Service |
| Total Length | Total Length |
| Identification | Identification |
| Flags | Flags |
| Fragment Offset | Fragment Offset |
| Time to Live | Time to Live |
| Protocol | Protocol |
| Header Checksum | Header Checksum |
| Source Address | Source Address |
| Destination Address | Destination Address |
| Options | Options |
| Padding | Padding |

- Same or Similar Fields in IPv6
- Removed Fields in IPv6

---

## IPv6 Header

![IPv6 Header](https://via.placeholder.com/700x200?text=IPv6+Header)

| Field | Description |
|---|---|
| Ver. | Version (4 bits) |
| Traffic Class | Traffic Class (8 bits) |
| Flow Label | Flow Label (20 bits) |
| Payload Length | Payload Length (16 bits) |
| Next Header | Next Header (8 bits) |
| Hop Limit | Hop Limit (8 bits) |
| Source Address | Source Address (128 bits) |
| Destination Address | Destination Address (128 bits) |

- Same or Similar Fields in IPv4
- New Field in IPv6

---

## Removed fields

**Header Checksum**

- Redundant: Layer 2 data link technologies perform own checksum and error control. Upper-layer protocols such as TCP and UDP have their own checksums
- Note: UDP checksum becomes mandatory in IPv6

**Fragmentation**

- IPv6 routers do not fragment a packet unless they are the source of the packet
- Packets larger than MTU are dropped and an ICMPv6 Packet Too Big message is returned to source

**Header Length**

- Fixed to 40 bytes

---

## Extension headers

**Next Header**: similar to IPv4 "Protocol" field
- It specifies the protocol carried in the data portion of the IPv6 packet

Additional "Next Header" fields are added in header extensions to allow chaining

Protocols coded using same values as IPv4 (plus some)

- 0: Hop by Hop option
- 6: TCP
- 17: UDP
- 43: Routing extension
- 44: Fragment header
- 50: Encapsulating Security Payload
- 51: Authentication
- 60: Destination option
- 59: no next header

---

## Extension header format
Next header | Length | Extension data | Extension data
8 | 16 | 32

---

## Header Chaining

---

## Hop-by-Hop Extension Header

- Used to carry optional information that should be examined by every router along the path of the packet
- Each option contains a set of Options Type, Options Length, and Options Value fields (TLV triplets)
- If present, it immediately follows the IPv6 header
Next header | Length | Option Type | Option Length | Option Value

---

## Hop-by-Hop Extension Header - Example

![Hop-by-Hop Extension Header](https://via.placeholder.com/700x300?text=Hop-by-Hop+Extension+Header)

- Main IPv6 Header
- Hop-By-Hop Extension Header
  - Next Header: 6 (TCP)
  - Next Extension Length
  - Option Type: C2
  - Option Length: 4
  - Jumbo Payload Length
- TCP Header
- TCP Segment

> **Jumbogram**: an IPv6 packet that contains a payload greater than 65,535 bytes

---

## More extension headers...

**Routing Extension Header**

- source routing

**Fragment Extension Header**

- used when the source needs to divide the packet into fragments, each with its own main IPv6 header and a Fragment extension header
- the recipient of the packet reassembles the fragments
- Recall: unlike in IPv4, an IPv6 router does not fragment a packet unless it is the source of the packet

**Authentication and Encapsulating Security Payload Extension Headers**

- used by IPsec, a suite of protocols for securing delivery of packets in IP networks
- the Authentication Header (AH) is used to guarantee the authenticity and integrity of a packet
- the Encapsulating Security Payload (ESP) provides authentication, integrity, and encryption

---

# Interfacing with Lower Layer

---

## Encapsulation

- IPv6 packets are encapsulated in layer-2 frames
- For Ethernet, Type: `86DD`
- They are treated as a new protocol
- Enables dual stack (IPv4/IPv6) approach
- Keeps running IPv4 as-is

---

## Address Mapping

How is the destination MAC address set when an IPv6 packet is encapsulated?

- **IP unicast address**: Procedural (protocol-based) discovery - Neighbor Discovery (see later)
- **IP multicast address**: Algorithmic mapping

---

## IPv6 Multicast transmission

Based on Ethernet multicast

- Unlike an Ethernet broadcast, an Ethernet multicast can be filtered by the NIC

IPv6 multicast address mapped to MAC address

- `33-33-xx-xx-xx-xx` is the reserved Ethernet MAC address when carrying an IPv6 multicast packet (RFC 7042)
- the lower 32 bits of the MAC address (`xx-xx-xx-xx`) are copied from the lower 32 bits of the IPv6 multicast address

![Multicast MAC mapping](https://via.placeholder.com/600x150?text=Multicast+MAC+Mapping)

- IPv6: `FF...` + Last 32 bits of the IPv6 address
- MAC: `33-33` + Last 32 bit of the IPv6 address

---

## Example

When sending a packet to the IP multicast address `FF0C::89:AABB:CCDD`

The packet is encapsulated in a MAC frame with address `33:33:AA:BB:CC:DD`

---

# Neighbor Discovery and Address Resolution

---

## New function in ICMPv6

It substitutes ARP

Based on multicast

Leverages the Solicited-node Multicast Address (`FF02:0:0:0:0:1:FF00::/104`)

Given the way multicast solicited address are constructed, most likely only one station gets involved

---

## Solicited Node Multicast Address

- address automatically created for every unicast address on the interface
- subscribed to by all hosts
- mapped as
  - `FF02::1:FF/104` | 24 least significant bits of IP address
  - Likely one host per group

![Solicited Node Multicast Address](https://via.placeholder.com/600x200?text=Solicited+Node+Multicast+Address)

---

## Address Resolution

**ICMP Neighbor Solicitation** - Requester sends frame to Solicited Node Multicast Address of target IPv6 address

![Address Resolution 1](https://via.placeholder.com/700x300?text=Address+Resolution+1)

- Destination MAC: `33-33-ff-00-01-00` (mcast)
- Destination IPv6: `ff02::1:ff00:100` (Solicited-Node mcast)
- Message: `I need MAC address of 2001:db8:cafe:1::100`

---

## Address Resolution (continued)

![Address Resolution 2](https://via.placeholder.com/700x300?text=Address+Resolution+2)

- Destination MAC: `33-33-ff-00-01-00` (mcast)
- Destination IPv6: `ff02::1:ff00:100` (Solicited-Node mcast)
- Message: `I need MAC address of 2001:db8:cafe:1::100`

---

## Address Resolution (continued)

**ICMP Neighbor Solicitation**

- Requester sends frame to Solicited Node Multicast Address of target IPv6 address

**ICMP Neighbor Advertisement**

- Sent back to requester's unicast address

Mapping between IPv6 and MAC address stored in host cache

- Equivalent to ARP cache

---

# ICMPv6

---

## What is it used for?

- Diagnostics
- Neighbor Discovery
- Multicast group management
- Issue notification

Includes functions that in IPv4 were delegated to
- ARP (Address Resolution Protocol)
- IGMP (Internet Group Membership Protocol)

---

## Message Format

Encapsulated in IPv6 packets
Next Header = 58
Entire message length: max 65,495 bytes
8 | 8 | 16
Type | Code | Checksum
Message Body

---

## ICMPv6 Message Types

| Type | Description |
|---|---|
| 1 | Destination Unreachable |
| 2 | Packet too big |
| 3 | Time exceeded |
| 4 | Parameter Problem |
| 128 | Echo Request |
| 129 | Echo Reply |
| 130 | Multicast Listener Query |
| 131 | Multicast Listener Report |
| 132 | Multicast Listener Done |
| 133 | Router Solicitation |
| 134 | Router Advertisement |
| 135 | Neighbor Solicitation |
| 136 | Neighbor Advertisement |
| 137 | Redirect |

---

## Error Messages

**Destination Unreachable (type = 1)**

- Usually generated by router or firewall
- Code field provides reason (no route, wrong scope, address/port unreachable)

**Packet too big (type = 2)**

- IPv6 routers no longer fragment packets!

**Time exceeded (type = 3)**

- If router receives a packet with Hop Limit = 0

**Parameter Problem (type = 4)**

- generated when a device finds a problem with a field in the main IPv6 header or an extension header
- example: invalid value in the Next Header field

---

## Informational Messages: Echo

- Echo request (type = 128)
- Echo reply (type = 129)
- Used by ping
8 | 8 | 16
Type | Code | Checksum
Identifier | Sequence Number
Data

---

## Informational Messages: Neighbor Solicitation
Type | Code | Checksum
Reserved
Target Address
Options

---

## Informational Messages: Neighbor Advertisement
Type | Code | Checksum
Reserved
Target Address
Options

---

## Informational Messages: Neighbor Advertisement
Type | Code | Checksum
R | S | O | Reserved
Target Address
Options

---

## Multicast Group Management using ICMPv6

- Within a link, rely on data link layer multicasting service
  - Mapping of IPv6 multicast addresses onto MAC multicast addresses
- Among links, packets routed by routers
  - ICMPv6 to know on-link members
  - Hosts interests in receiving packets
  - Multicast routing protocols to know where there are off-link members

---

## Host Membership Discovery

![Host Membership Discovery](https://via.placeholder.com/700x300?text=Host+Membership+Discovery)

- R to announce multicast groups G and F
- R to forward packets to G and F

---

## Informational Messages: Group Management

**Multicast Listener Query (type=130)**, sent by router to all-nodes-on-link multicast address (`ff02::1`)

- General
- Multicast group (address) specific

**Multicast Listener Report (type=131)**, sent by Listener to all-router multicast address (`ff02::2`)

**Multicast Listener Done (type=132)**, sent by Listener to all-router multicast address
Type | Code | Checksum
Maximum Response Delay | Unused
Multicast Address

---

# Device Configuration in IPv6

---

## What information is needed?

- Address prefix
- Interface identifier
- Default gateway
- DNS server
- Hostname
- Domain name
- MTU (Maximum Transmission Unit)

---

## Options

**Manual configuration**

**Stateful configuration**

- Addresses and other parameters obtained through DHCP (DHCP6); the default gateway always comes from Router Advertisements (RA)

**Stateless configuration**

- Autogenerated
- Address prefix obtained from RA
- DNS servers can also come from the RA (RDNSS option, RFC 8106)

**Hybrid (Stateless DHCP)**

- Information other than address obtained through DHCP

---

## Interface Identifier

- Manually configured
- Obtained through DHCPv6
- Automatically generated
  - From EUI-64 MAC address
  - Privacy aware

---

## EUI-64 format

48 bit MAC address (EUI-48 format)

---

## Privacy Concerns

**Traceability**

- The least significant 64 bits of the IPv6 address of an interface never change when MAC address is used

**RFC 4941, "Privacy Extensions for Stateless Address Autoconfiguration in IPv6"**

---

## Privacy Extension Algorithm

![Privacy Extension Algorithm](https://via.placeholder.com/700x400?text=Privacy+Extension+Algorithm)

(other options are possible)

- 64 bit Random or previous "privacy" address
- 64 bit Interface ID from MAC address
- MD5
- `11111101111............111` & Interface ID
- Stored for next configuration

---

## Address Usage

A host may have several different addresses

- "default"
- "privacy-aware"

- Usable to accept/initiate connections
- Selection of address may be available to the user/application

---

## Address Prefix Configuration

- Manually configured
- Obtained from DHCPv6
- Automatically generated
  - Link local
  - Obtained from a router
Prefix (n bits) | Interface ID (128-n bits)

---

## Router/prefix Discovery

**ICMP Router Advertisement message**

- Sent by routers
- Solicited
  - Answering to Router Solicitation by host
- Unsolicited: periodic

---

## Router Solicitation
Type | Code | Checksum
Reserved
Options

Sent to the all-routers multicast address (`FF02::2`)

---

## Router Advertisement
Type | Code | Checksum
Cur Hop Limit | M | O | Reserved
Router Lifetime
Reachable Time
Retrans Timer
Options

**M (Managed Address Configuration)**
- 1 - address available through DHCP

**O (Other configuration)**
- E.g., DNS server

---

## Options

General Format
Length in multiple of 8 bytes
Type | Length | .........

---

## Prefix Information Option
Type (3) | Length | Prefix Length | L | A | Reserved
Valid Lifetime
Preferred Lifetime
Reserved
Prefix

- L - prefix is on-link
- A - prefix can be used for autonomous configuration

---

## MTU Option

Ensures all hosts on-link use the same MTU value
Type (5) | Length | Reserved
MTU

---

## Link Layer Address Option
Type | Length | Link-Layer Address
Link-Layer Address...

---

## ICMP Redirect

Sent by a router to advise a host about a best first-hop
The first-hop is always on-link, irrespective of prefix

---

## ICMP Redirect Message Format
Type | Code | Checksum
Reserved
Target Address
Destination Address
Options

---

## Redirect Header Option

Information about the packet being redirected
Type (4) | Length | Reserved
Reserved
IP header + data

---

## Duplicate Address Detection (DAD)

- Probe uniqueness of a newly-created IPv6 address
- Neighbor solicitation (NS) with address being probed as target
- Source IPv6 address set to the unspecified address (`::`)
  - Sent to corresponding IPv6 Solicited Node Multicast Address
  - Encapsulated in a frame with corresponding MAC multicast address
- Wait for a response for at least 1 sec
  - If no Neighbor Advertisement is received, the new address is considered valid
  - If a Neighbor Advertisement is received, the new address cannot be used
- Before probing, the node joins the solicited-node group (MLD Report); an NS from another node probing the same address also means "duplicate"

---

## Stateless Configuration: No Router

1. Generate a link local address
2. Probe for its uniqueness (DAD)
3. Subscribe to the corresponding IPv6 Solicited Node Multicast Address
4. Configure reception of corresponding multicast MAC
5. Send ICMP Multicast Listener Report
6. On-link communication enabled

---

## Stateless Configuration: With Router

- Possibly send Router Solicitation
- Listen to Router Advertisements
- Create address from advertised prefix
- Probe for its uniqueness (DAD)
- Subscribe to the corresponding IPv6 Solicited Node Multicast Address
- Configure reception of corresponding multicast MAC
- Send ICMP Multicast Listener Report

---

## Scoped Addresses

A scoped address is composed of an IPv6 address followed by a % and a number identifying the interface

Used by the operating system to discriminate among IPv6 addresses on different interfaces with the same prefix (and possibly with the same interface ID)

Example:

- `FE80::0237:00FF:FE02:a7FD%19`

![Scoped Address](https://via.placeholder.com/400x300?text=Scoped+Address)

---

## Examples of Scoped Addresses

(to be completed)