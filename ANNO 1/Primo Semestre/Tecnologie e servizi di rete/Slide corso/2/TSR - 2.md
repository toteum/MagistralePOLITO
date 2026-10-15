---
marp: true
title: IPv4 addressing and routing
author: Alessio Sacco, Claudio Casetti, Guido Marchetto, Marco Rapelli
theme: default
paginate: true
---

# IPv4 addressing and routing

**Tecnologie e Servizi di Rete**
**Computer Network Technologies and Services**
**Internet Architecture and Technologies**

1859

Alessio Sacco, Claudio Casetti, Guido Marchetto, Marco Rapelli

---

## Copyright Notice

This set of transparencies, hereinafter referred to as slides, is protected by copyright laws and provisions of International Treaties. The title and copyright regarding the slides (including, but not limited to, each and every image, photography, animation, video, audio, music and text) are property of the authors specified on page 1.

The slides may be reproduced and used freely by research institutes, schools and Universities for non-profit, institutional purposes. In such cases, no authorization is requested.

Any total or partial use or reproduction (including, but not limited to, reproduction on magnetic media, computer networks, and printed reproduction) is forbidden, unless explicitly authorized by the authors by means of written license.

Information included in these slides is deemed as accurate at the date of publication. Such information is supplied for merely educational purposes and may not be used in designing systems, products, networks, etc. In any case, these slides are subject to changes without any previous notice. The authors do not assume any responsibility for the contents of these slides (including, but not limited to, accuracy, completeness, enforceability, updated-ness of information hereinafter provided).

In any case, accordance with information hereinafter included must not be declared.

In any case, this copyright notice must never be removed and must be reported even in partial uses.

---

## The IP protocol: a recap

IP (Internet Protocol): the network layer protocol of the TCP/IP architecture (RFC 791)

Defines the datagram format, the addressing plan and the forwarding rules

**Connectionless:** no connection setup, each datagram is forwarded independently of the others

Datagrams of the same flow can follow different paths and arrive out of order

**Best effort:** the network does its best to deliver datagrams, but guarantees nothing

Datagrams can be lost, duplicated, delayed, corrupted
- No guarantee on throughput or delay, no acknowledgements, no retransmissions

Error recovery, when needed, is left to the end systems (e.g., TCP)

Routers keep no per-flow state: simple core, intelligence at the edges

---

## The IP protocol: a recap

Global addressing: 32-bit addresses identifying interfaces

Hierarchical structure: network part + host part

Hop-by-hop forwarding: each router decides on its own

Based on the destination address only, looking up its routing table

Independent of the underlying technology

IP runs over any link layer: Ethernet, Wi-Fi, PPP, ...
Fragmentation adapts the datagram to the MTU of each link

Loop protection: TTL decremented at every hop, dropped at zero

Header checksum: protects header, not payload

Companion protocols: ICMP and ARP

ICMP for error reporting and diagnostics, ARP for address resolution

---

## IP addressing: terminology

- **IP address:** 32-bit identifier for host, router interfaces
- **Network part:** high order bits of the IP address
- **Host part:** low order bits of the IP address
- **IP network:** set of IP devices whose interfaces
  - Have the same network part of the IP address
  - Are connected to the same physical (link-layer) network

![Network diagram](https://via.placeholder.com/600x300?text=IP+Network+Diagram)

---

## IP addressing: special addresses

| Address Pattern | Meaning |
|---|---|
| Some value + All 0s | the (sub)network ID |
| All 1s | limited broadcast (local net) |
| Some value + All 1s | directed broadcast for net |
| 127 + Anything (often 1) | loopback |

---

## IP addressing: classful (historical)

0 1 7 8 31
0 Network Host
Class A - 128 networks - 1 byte: 0-127

0 1 2 15 16 31
1 0 Network Host
Class B - 16K networks - 1 byte: 128-191

0 1 2 3 23 24 31
1 1 0 Network Host
Class C - 2M networks - 1 byte: 192-223


---

## IP addressing: CIDR

**CIDR: Classless InterDomain Routing**

- network portion of address of arbitrary length
- address format: network ID + prefix length or netmask
- prefix length: /x, where x is # bits in network portion of address
- netmask: all '1s' in the network part, all '0s' in the host part

network part host part
11001000 00010111 00010000 00000000

200.23.16.0/23 <- prefix length notation
200.23.16.0 255.255.254.0 <- netmask notation


---

## IP addressing: CIDR

Valid netmasks: possible values in the 4 bytes composing the address

| Value | Binary | Decimal |
|---|---|---|
| 0 | 0000 0000 | (256) |
| 128 | 1000 0000 | (128) |
| 192 | 1100 0000 | (64) |
| 224 | 1110 0000 | (32) |
| 240 | 1111 0000 | (16) |
| 248 | 1111 1000 | (8) |
| 252 | 1111 1100 | (4) |
| 254 | 1111 1110 | (2) not valid in the 4° byte |
| 255 | 1111 1111 | (1) represents the single device |

---

## IP addressing: CIDR

Some examples:

- 130.192.0.0/16 - 130.192.0.0 255.255.0.0
- 130.192.0.0/24 - 130.192.0.0 255.255.255.0
- 130.192.0.0/25 - 130.192.0.0 255.255.255.128
- 130.192.2.0/23 - 130.192.2.0 255.255.254.0
- 130.192.1.4/30 - 130.192.1.4 255.255.255.252
- 130.192.1.0/31 - 130.192.1.0 255.255.255.254

Each IP network must contain at least the network ID and the broadcast address!

---

## IP addressing: CIDR

**Valid Network ID**
- 130.192.1.4/30
- 130.192.1.16/30
- 130.192.1.16/29

**Invalid Network ID**
- 130.192.1.1/30
- 130.192.1.4/29
- 130.192.1.24/28

---

## IP addressing: example
223.1.1.0/24 223.1.2.0/24
223.1.1.1 223.1.2.1
223.1.1.2 223.1.2.9
223.1.1.4 223.1.2.2
223.1.3.0/24
223.1.3.1
223.1.3.2
netmask: 255.255.255.0


---

## IP routing

The general rules:

Given a destination IP address to reach, an IP device searches its own routing table, looking for a match

In case of multiple matches, it selects the most specific one (**longest prefix matching**)

| destination | output link |
|---|---|
| 200.23.16.0/20 | 1 |
| 200.23.18.0/23 | 2 |
| 199.31.0.0/16 | 2 |

---

## A complete routing table

A complete routing table also says to whom the packet is handed on each link

![Routing diagram](https://via.placeholder.com/800x300?text=Routing+Diagram)

| Destination | Output link | Next hop |
|---|---|---|
| 200.23.16.0/20 | IF1 | direct |
| 200.23.18.0/23 | IF2 | 200.24.7.2 |
| 199.31.0.0/16 | IF2 | 200.24.7.2 |
| 200.24.7.0/30 | IF2 | direct |

**Longest prefix matching:** a packet for 200.23.19.7 matches both 200.23.16.0/20 and 200.23.18.0/23. The /23 entry is more specific, so R1 sends it on link 2 to the next hop 200.24.7.2.

**Direct routes:** networks attached to R1, including the /30 point-to-point link, need no next hop; the packet is delivered on the link itself.

---

## A real Routing Table: what about other routes?

Destinations beyond R2 can be collapsed into a single default entry

![Default route diagram](https://via.placeholder.com/800x300?text=Default+Route+Diagram)

| Destination | Output link | Next hop |
|---|---|---|
| 200.23.16.0/20 | IF1 | direct |
| 200.23.18.0/23 | IF2 | 200.24.7.2 |
| 200.24.7.0/30 | IF2 | direct |
| 0.0.0.0/0 (default) | IF2 | 200.24.7.2 |

**Default route:** 0.0.0.0/0 matches every destination with the shortest possible prefix, so it is used only when no other entry matches.

The /23 entry must stay: without it, packets for 200.23.18.0/23 would match 200.23.16.0/20 and leave on link 1.

---

## A real Routing Table: the Direct Delivery problem

ISP A holds 200.23.16.0/20 and routes it internally; 200.23.18.0/23 is now behind R2

![Direct delivery diagram](https://via.placeholder.com/800x300?text=Direct+Delivery+Diagram)

**Routing table of R0**

| Destination | Output link | Next hop |
|---|---|---|
| 200.23.16.0/24 | a | direct |
| 200.23.17.0/24 | b | direct |
| 200.24.6.0/30 | c | direct |
| 200.23.18.0/23 | c | 200.24.6.1 |
| 0.0.0.0/0 (default) | c | 200.24.6.1 |

**Routing table of R1**

| Destination | Output link | Next hop |
|---|---|---|
| 200.23.16.0/20 | 1 | 200.24.6.2 |
| 200.23.18.0/23 | 2 | 200.24.7.2 |
| 200.24.6.0/30 | 1 | direct |
| 200.24.7.0/30 | 2 | direct |
| 0.0.0.0/0 (default) | 2 | 200.24.7.2 |

---

## IP routing: an example

![Routing example](https://via.placeholder.com/600x400?text=Routing+Example)

Address range: 130.192.0.0/16

---

## IP routing: an example

**R1 routing table**

| Type | Destination | Next-hop | Cost |
|---|---|---|---|
| S | 130.192.0.0/24 | 130.192.3.2 | 1 |
| S | 130.192.1.0/24 | 130.192.3.2 | 2 |
| S | 130.192.3.8/30 | 130.192.3.2 | 1 |
| S | 0.0.0.0/0 | 80.105.10.2 | 1 |
| C | 130.192.2.0/24 | 130.192.2.1 | 0 |
| C | 130.192.3.0/30 | 130.192.3.1 | 0 |
| C | 130.192.3.4/30 | 130.192.3.5 | 0 |
| C | 80.105.10.0/30 | 80.105.10.1 | 0 |

- **remote interface!!** (S entries)
- **local interface!!** (C entries)