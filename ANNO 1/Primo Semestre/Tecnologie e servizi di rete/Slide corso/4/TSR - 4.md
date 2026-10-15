---
marp: true
title: IPv4 Multicast
author: Alessio Sacco, Claudio Casetti, Guido Marchetto, Marco Rapelli
theme: default
paginate: true
---

# IPv4 Multicast

**Tecnologie e Servizi di Rete**
**Computer Network Technologies and Services**
**Internet Architecture and Technologies**

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

## Introduction

Packets are routed from a source to multiple destinations, collectively identified by an IP multicast address

Key for group communication e.g., videoconferencing, video broadcasting

- An IP Multicast Address identifies a group of hosts
- Hosts actively join/leave a group
- Hosts can selectively choose which source(s) in the group they receive traffic from
- Routers keep track of which groups have active listeners and route packets to individual members

![Multicast overview](https://via.placeholder.com/700x300?text=Multicast+Overview)

---

## Multicast addressing

**Class D addresses**

Begin with `1110` → 224.0.0.0 - 239.255.255.255

- Address identifies a host group
- Packet is delivered to all hosts in the group
- Anywhere in the network (across routers), where multicast routing is enabled

**Notable ranges (IANA, RFC 5771):**

- `224.0.0.0/24`: link-local control, never forwarded
  - 224.0.0.1 all hosts
  - 224.0.0.2 all routers
  - 224.0.0.22 IGMPv3
  - 224.0.0.251 mDNS
- `232.0.0.0/8`: source-specific multicast (RFC 4607)
- `239.0.0.0/8`: administratively scoped, the "private" multicast range (RFC 2365)

---

## Host Group Membership

Hosts join and leave dynamically

**IGMP (Internet Group Management Protocol)** protocol (encapsulated in IPv4 datagrams) handles membership within a local network

- Used by hosts and routers; IP datagrams with TTL = 1

Recipients of a multicast datagram establish which hosts receive a packet

- In unicast, it is the source
- Controlling traffic reach is more difficult

![IGMP membership](https://via.placeholder.com/700x300?text=IGMP+Membership)

---

## Within a Local IEEE 802 Network

Group delivery delegated to lower level (MAC)

IP multicast address mapped to a MAC multicast address (RFC 7042), built as:

- 25 fixed most significant bits: `01-00-5E-0`
- 23 least significant bits are taken from the corresponding bits in the IP address

![MAC mapping](https://via.placeholder.com/600x300?text=MAC+Mapping)

MAC address collisions are resolved at the IP layer

---

## Within a Local IEEE 802 Network

- Interface card configured to receive MAC multicast
- Recipient-initiated group join through IGMP
- Switch support through **IGMP Snooping**
  - Multicast delivery only on ports connected to a group member requires cross-layer approach

![IGMP Snooping](https://via.placeholder.com/700x300?text=IGMP+Snooping)

---

## Beyond single networks

Routers manage host groups on each LAN using IGMP

- Hosts send IGMP Membership Report messages to `224.0.0.22` (multicast address for routers)
- Routers periodically send IGMP General Query messages to discover which groups are active on the Local Network

Routers announce host groups to others

**Multicast routing protocols**

Routers build a distribution tree for each host group

- To all LANs with at least a member

---

## Example: Multicast DNS (mDNS)

Name resolution on a single link, without a DNS server (RFC 6762)

- Standard DNS messages sent to `224.0.0.251`
- Names end in `.local`
- Responses are usually multicast too: every host on the link can cache them
- Before using a name, a host probes it then announces it

Paired with **DNS-SD** (RFC 6763) it also discovers services: printers, AirPlay, Chromecast

- Apple Bonjour, Avahi on Linux, native since Windows 10
- E.g.: "any Airplay receivers out there?"

`224.0.0.0/24` is link-local: routers never forward it, so discovery stops at the subnet

![mDNS example](https://via.placeholder.com/700x300?text=mDNS+Example)

> On large Wi-Fi networks every announcement reaches every device: campuses often filter or proxy mDNS

---

## Deployment status

Not widely supported

Not suitable for common traffic control/engineering practice in the Internet at large

- Inter-domain multicast traffic is practically absent

Mostly limited to controlled environments

- Video broadcasting within an ISP network
- Local network service discovery
- Data center and enterprise networks