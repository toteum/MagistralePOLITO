---
marp: true
title: Computer Networks Exercises - IPv4 Exercise Summary
author: Fulvio Risso, Guido Marchetto, Alessio Sacco
theme: default
paginate: true
---

# Computer Networks Exercises

**Fulvio Risso, Guido Marchetto, Alessio Sacco**

---

## Copyright Notice

This set of transparencies, hereinafter referred to as slides, is protected by copyright laws and provisions of International Treaties. The title and copyright regarding the slides (including, but not limited to, each and every image, photography, animation, video, audio, music and text) are property of the authors specified on page 1.

The slides may be reproduced and used freely by research institutes, schools and Universities for non-profit, institutional purposes. In such cases, no authorization is requested.

Any total or partial use or reproduction (including, but not limited to, reproduction on magnetic media, computer networks, and printed reproduction) is forbidden, unless explicitly authorized by the authors by means of written license.

Information included in these slides is deemed as accurate at the date of publication. Such information is supplied for merely educational purposes and may not be used in designing systems, products, networks, etc. In any case, these slides are subject to changes without any previous notice. The authors do not assume any responsibility for the contents of these slides (including, but not limited to, accuracy, completeness, enforceability, updated-ness of information hereinafter provided).

In any case, accordance with information hereinafter included must not be declared.

In any case, this copyright notice must never be removed and must be reported even in partial uses.

---

## Exercise 1

Assuming a classless addressing plan, define the netmask and the prefix length that have to be assigned to possible networks in order to contain the given number of hosts.

| Number of Hosts |
|---|
| 2 |
| 27 |
| 5 |
| 100 |
| 10 |
| 300 |
| 1010 |
| 55 |
| 167 |
| 1540 |

---

## Exercise 1: solution

| Number of Hosts | Netmask | Prefix Length | Available Addresses |
|---|---|---|---|
| 2 | 255.255.255.252 | /30 | 4 (-2) |
| 27 | 255.255.255.224 | /27 | 32 (-2) |
| 5 | 255.255.255.248 | /29 | 8 (-2) |
| 100 | 255.255.255.128 | /25 | 128 (-2) |
| 10 | 255.255.255.240 | /28 | 16 (-2) |
| 300 | 255.255.254.0 | /23 | 512 (-2) |
| 1010 | 255.255.252.0 | /22 | 1024 (-2) |
| 55 | 255.255.255.192 | /26 | 64 (-2) |
| 167 | 255.255.255.0 | /24 | 256 (-2) |
| 1540 | 255.255.248.0 | /21 | 2048 (-2) |

---

## Exercise 2

Which "IP address / Prefix length" pairs identify a valid network?

| IP / Prefix Length pair | Valid network? |
|---|---|
| 192.168.5.0/24 | |
| 192.168.4.23/24 | |
| 192.168.2.36/30 | |
| 192.168.2.36/29 | |
| 192.168.2.32/28 | |
| 192.168.2.32/27 | |
| 192.168.3.0/23 | |
| 192.168.2.0/31 | |
| 192.168.2.0/23 | |
| 192.168.16.0/21 | |
| 192.168.12.0/21 | |

---

## Exercise 2: solution

| IP / Prefix Length pair | Valid network? |
|---|---|
| 192.168.5.0/24 | YES |
| 192.168.4.23/24 | NO |
| 192.168.2.36/30 | YES |
| 192.168.2.36/29 | NO |
| 192.168.2.32/28 | YES |
| 192.168.2.32/27 | YES |
| 192.168.3.0/23 | NO |
| 192.168.2.0/31 | NO!!! |
| 192.168.2.0/23 | YES |
| 192.168.16.0/21 | YES |
| 192.168.12.0/21 | NO |

---

## Exercise 3

Find out the configuration error in the below network setup and explain why the network does not work properly.

![Network setup](https://via.placeholder.com/800x400?text=Network+Setup)

- Router: IP:192.168.0.1/24 on left, IP:192.168.1.1/28 on right
- DNS 1: IP:192.168.0.23/24, DG:192.168.0.1, DNS:192.168.0.23
- Host 1: IP:192.168.0.2/24, DG:192.168.0.1, DNS:192.168.1.23
- DNS 2: IP:192.168.1.23/28, DG:192.168.1.1, DNS:192.168.1.23

---

## Exercise 3: solution

The netmask configured in the portion of network including the router and DNS 2 is wrong because those two machines are not within the same IP network.

In this network setup, the router could directly contact DNS 2 only if DNS 2 had an IP address in the range 192.168.1.2 / 192.168.1.14. Instead, DNS 2 is currently in the 192.168.1.16/28 network. Hence, DNS 2 cannot communicate with any external destination.

**NB:** The configuration of DNS 2 as DNS server for Host 1 is not an error. The utilization of an external DNS server is perfectly fine.

---

## Exercise 4

Define an IP addressing plan for the network in the figure. Consider both a "traditional" addressing plan and a solution that could minimize the number of deployed addresses. Assume to utilize the 10.0.0.0/16 address range.

**Steps:**
1. Location of IP networks
2. Amount of required addresses
3. Amount of allocated addresses
4. Address range validity
5. Netmask / Prefix Length
6. Address Range
7. Host addresses

![Network topology](https://via.placeholder.com/800x300?text=Network+Topology)

Address range selected: 10.0.0.0/24

---

## Exercise 4: solution (1)

**Solution 1**

![Solution 1](https://via.placeholder.com/600x300?text=Solution+1)

- Link: 10.0.2.128/30 (.129, .130)
- LAN 1 (350 host): 10.0.0.0/23 (.254)
- LAN 2 (120 host): 10.0.2.0/25 (.126)

**Solution 2**

![Solution 2](https://via.placeholder.com/600x300?text=Solution+2)

- Link: 10.0.1.240/30 (.241, .242)
- LAN 1 (350 host): 10.0.0.0/24 + 10.0.1.128/26 + 10.0.1.192/27 + 10.0.1.224/28
- LAN 2 (120 host): 10.0.1.0/25 (.126)

> **Note:** Further splits on more IP networks do not give benefits!!

---

## Exercise 4: solution (2)

All solutions are fine. The third one is a trade-off between the others, although the most rational is probably the first one!

![Solution 3](https://via.placeholder.com/600x300?text=Solution+3)

- Link: 10.0.2.0/30 (.1, .2)
- LAN 1 (350 host): 10.0.0.0/24 + 10.0.1.0/25 (.254, .1126)
- LAN 2 (120 host): 10.0.1.128/25 (.1254)

---

## Exercise 5

Given the network below, define the routing table of R2. Route aggregation has to be maximized (i.e., use the least number of lines in the routing table).

![Network topology](https://via.placeholder.com/800x300?text=Network+Topology)

- R1: 130.192.2.64/28
- Link R1-R2: 130.192.3.0/30
- R2: eth0, eth1, eth2
- Link R2-R3: 130.192.3.4/30
- R3: internet
- LAN R2: 130.192.2.0/26
- LAN R2: 130.192.2.128/25

---

## Exercise 5: solution

| Destination | Next-hop | IF |
|---|---|---|
| 0.0.0.0/0 | 130.192.3.5 | eth2 |
| 130.192.2.128/25 | - | eth1 |
| 130.192.2.0/25 | 130.192.3.1 | eth0 |

---

## Exercise 6

Given the network below, define the routing table of R1. Route aggregation has to be maximized. IP addresses in the figure are related to the closest interface of a given router.

![Network topology](https://via.placeholder.com/800x400?text=Network+Topology)

- Address range: 130.192.0.0/16
- R1: .2.37/30, .2.41/30, .2.1/27
- R2: .2.33/30, .0.254/24, .1.126/25
- R3: .1.254/25
- Weights: R1-R2 = 1, R1-R3 = 5, R2-R3 = 1

---

## Exercise 6: solution

| Type | Destination | Next-hop | Cost |
|---|---|---|---|
| S | 0.0.0.0/0 | 130.192.2.38 | 2 |
| C | 130.192.2.0/27 | 130.192.2.1 | 0 |
| C | 130.192.2.36/30 | 130.192.2.37 | 0 |
| C | 130.192.2.40/30 | 130.192.2.41 | 0 |

---

## Exercise 7

Define an IP addressing plan that maximizes route aggregation on R1. Derive the resulting routing table of R1.

![Network topology](https://via.placeholder.com/800x400?text=Network+Topology)

- Address range: 130.192.0.0/16
- R1 connected to R3 (weight 1) and R2 (weight 2)
- R3: LAN A (27 host), LAN B (120 host)
- R2: LAN E (60 host), LAN F (10 host)
- Networks C and D between R1-R3 and R1-R2

---

## Exercise 7: solution

Networks C and D are reachable from R1 using direct routes, thus not affecting aggregation on R1. Hence, we temporarily neglect them while evaluating the total amount of addresses required for the two defined areas.

We obtain:

- Area 1: 32 + 128 = 160 → 256 addresses
- Area 2: 64 + 16 = 80 → 128 addresses

We can therefore select the following address ranges:

- Area 1: 130.192.0.0/24
- Area 2: 130.192.1.0/25

Networks C and D are now included in Area 1, which can contain two additional /30 networks.

Notice that they would have been included in Area 2 as well!

---

## Exercise 7: solution (continued)

By keeping in mind the general rule of minimizing the amount of deployed addresses (in this case within each area), we can apply the traditional methodology to define the following addressing plan:

**Area 1**
- B: 130.192.0.0/25
- A: 130.192.0.128/27
- C: 130.192.0.160/30
- D: 130.192.0.164/30

**Area 2**
- E: 130.192.1.0/26
- F: 130.192.1.64/28

---

## Exercise 7: solution (routing table)

We derive the following routing table for R1 (in this case we chose to avoid the utilization of the default route):

| Type | Destination | Next-hop | Cost |
|---|---|---|---|
| S | 130.192.0.0/24 | 130.192.0.161 | 1 |
| S | 130.192.1.0/25 | 130.192.0.165 | 2 |
| C | 130.192.0.160/30 | 130.192.0.162 | 0 |
| C | 130.192.0.164/30 | 130.192.0.166 | 0 |

---

## Exercise 8

Repeat the previous exercise by defining an IP addressing plan which minimizes the total amount of deployed addresses. Notice how the routing table of R1 changes with respect to the previous exercise.

![Network topology](https://via.placeholder.com/800x400?text=Network+Topology)

- Address range: 130.192.0.0/16
- R1 connected to R3 (weight 1) and R2 (weight 2)
- R3: LAN A (27 host), LAN B (120 host)
- R2: LAN E (60 host), LAN F (10 host)

---

## Exercise 8: solution

![Solution](https://via.placeholder.com/800x400?text=Solution)

- A: 130.192.0.192/27
- B: 130.192.0.0/25
- C: 130.192.0.240/30
- D: 130.192.0.244/30
- E: 130.192.0.128/26
- F: 130.192.0.224/28

**R1 routing table:**

(to be completed)

---

## Exercise 9

Assuming that all caches are empty, indicate the number and the type of the frames captured by a sniffer located on the network cable of Host A.

**Solution:** 10 frames (if MS Windows host)

![Network](https://via.placeholder.com/800x300?text=Network)

- Host A: MAC AA:AA:[...]:AA, IP 130.192.16.81/24, DG 130.192.16.1, DNS 130.192.16.2
- Host B: MAC BB:BB:[...]:BB, IP 130.192.16.2/24, DG 130.192.16.1, DNS 130.192.16.2
- Command: ping 130.192.16.2
- Ethernet LAN (shared bus)

---

## Exercise 10

Assuming that all caches are empty, indicate the number and the type of the frames captured by a sniffer located on the network cable of Host A.

![Network](https://via.placeholder.com/800x300?text=Network)

- Host A: MAC AA:AA:[...]:AA, IP 130.192.16.81/24, DG 130.192.16.1, DNS 130.192.16.3
- Host B: MAC BB:BB:[...]:BB, IP 130.192.16.2/24, DG 130.192.16.1, DNS 130.192.16.3
- DNS: MAC DD:DD:[...]:DD, IP 130.192.16.3/24, DG 130.192.16.1, DNS 130.192.16.3
- www.polito.it → 130.192.16.2
- Command: ping www.polito.it
- Ethernet LAN (shared)

---

## Exercise 11

Assuming that all caches are empty, indicate the number and the type of the frames captured by a sniffer located on the network cable of Host A.

![Network](https://via.placeholder.com/800x300?text=Network)

- Host A: MAC AA:AA:[...]:AA, IP 130.192.16.81/24, DG 130.192.16.1, DNS 130.192.16.3
- Host B: MAC BB:BB:[...]:BB, IP 130.192.16.2/24, DG 130.192.16.1, DNS 130.192.16.3
- Host C: MAC CC:CC:[...]:CC, IP 130.192.16.5/24, DG 130.192.16.1, DNS 130.192.16.3
- Command: ping 130.192.16.5
- Ethernet LAN (switched)

---

## Exercise 12

Assuming that all caches are empty (except that of the DNS server), indicate the number and the type of the frames captured by a sniffer located on the network cable of Host A.

**Solution:** 17 frames (if MS Windows host)

![Network](https://via.placeholder.com/800x400?text=Network)

- Host A: IP 130.192.16.81/24, DG 130.192.16.1, DNS 130.192.17.2
- DNS: IP 130.192.17.2/23, DG 130.192.17.1, DNS 130.192.17.2
- Router: IP 130.192.16.1/24, IP 130.192.17.1/24
- Internet server: IP 180.112.4.3/24, DG 180.112.4.254, DNS 180.112.3.2
- www.google.com
- Command: ping www.google.com
- Ethernet LAN (shared bus)