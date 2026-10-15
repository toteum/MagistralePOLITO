---
marp: true
theme: default
paginate: true
size: 16:9
footer: "Wireless and Cellular Networks — Tecnologie e Servizi di Rete"
style: |
  section { font-size: 26px; padding: 40px 56px; }
  section h1 { font-size: 1.5em; color: #1f4e79; border-bottom: 3px solid #1f4e79; padding-bottom: 6px; margin-bottom: 18px; }
  section.lead { text-align: center; justify-content: center; }
  section.lead h1 { font-size: 2em; border: none; }
  section.dense { font-size: 20px; }
  section.vdense { font-size: 16px; }
  section ul { margin: 0.2em 0; }
  section li { margin: 0.1em 0; }
  small { color: #666; font-size: 0.7em; }
  footer { font-size: 14px; }
---

<!-- _class: lead -->
<!-- _paginate: false -->

# Wireless and Cellular Networks

Tecnologie e Servizi di Rete

Computer Network Technologies and Services

Mario Baldi, Claudio Casetti, Guido Marchetto, Fulvio Valenza

---

<!-- _class: vdense -->

# Copyright Notice

- This set of transparencies, hereinafter referred to as slides, is protected by copyright laws and provisions of International Treaties. The title and copyright regarding the slides (including, but not limited to, each and every image, photography, animation, video, audio, music and text) are property of the authors specified on page 1.
- The slides may be reproduced and used freely by research institutes, schools and Universities for non-profit, institutional purposes. In such cases, no authorization is requested.
- Any total or partial use or reproduction (including, but not limited to, reproduction on magnetic media, computer networks, and printed reproduction) is forbidden, unless explicitly authorized by the authors by means of written license.
- Information included in these slides is deemed as accurate at the date of publication. Such information is supplied for merely educational purposes and may not be used in designing systems, products, networks, etc. In any case, these slides are subject to changes without any previous notice. The authors do not assume any responsibility for the contents of these slides (including, but not limited to, accuracy, completeness, enforceability, updated-ness of information hereinafter provided).
- In any case, accordance with information hereinafter included must not be declared.
- In any case, this copyright notice must never be removed and must be reported even in partial uses.

---

# Wireless and Mobile Networks: context

- more wireless (mobile) phone subscribers than fixed (wired) phone subscribers (10-to-1 in 2019)!
- more mobile-broadband-connected devices than fixed-broadband-connected devices devices (5-1 in 2019)!
  - 4G/5G cellular networks now embracing Internet protocol stack, including SDN
- two important (but different) challenges
  - wireless: communication over wireless link
  - mobility: handling the mobile user who changes point of attachment to network

---

# Elements of a wireless network

wired network  
infrastructure

---

# Elements of a wireless network

- laptop, smartphone, IoT
- run applications
- may be stationary (non-mobile) or mobile
  - wireless does not always mean mobility!

<small>*Figura: wireless hosts · wired network · infrastructure*</small>

---

# Elements of a wireless network

- typically connected to wired network
- relay - responsible for sending packets between wired network and wireless host(s) in its “area”
  - e.g., cell towers, 802.11 access points

<small>*Figura: base station · wired network · infrastructure*</small>

---

# Elements of a wireless network

- typically used to connect mobile(s) to base station, also used as backbone link
- multiple access protocol coordinates link access
- various transmission rates and distances, frequency bands

<small>*Figura: wireless link · wired network · infrastructure*</small>

---

# Characteristics of selected wireless links

<small>*Figura: 14 Gbps · 802.11ax · 10 Gbps · 5G · 3.5 Gbps 802.11ac · 802.11 af,ah · 600 Mbps · 802.11n · 4G LTE · 54 Mbps 802.11g · 11 Mbps 802.11b · 2 Mbps Bluetooth · Long range · Indoor · Outdoor · Midrange · outdoor · 50-200m · 10-30m · 200m-4Km 4Km-15Km*</small>

---

# Elements of a wireless network

- base station connects mobiles into wired network
- handoff: mobile changes base station providing connection into wired network

<small>*Figura: infrastructure mode · wired network · infrastructure*</small>

---

# Elements of a wireless network

ad hoc mode

- no base stations
- nodes can only transmit to other nodes within link coverage
- nodes organize themselves into a network: route among themselves

---

# Wireless link characteristics (1)

- important differences from wired link ….
  - decreased signal strength : radio signal attenuates as it propagates through matter (path loss)
  - interference from other sources: wireless network frequencies (e.g., 2.4 GHz) shared by many devices (e.g., WiFi, cellular, motors): interference
  - multipath propagation: radio signal reflects off objects ground, arriving at destination at slightly different times
- …. make communication across (even a point to point) wireless link much more “difficult”

---

# Wireless link characteristics (1I)

- SNR: signal-to-noise ratio
  - larger SNR – easier to extract signal from noise (a “good thing”)
- SNR versus BER tradeoffs
  - given physical layer: increase power -> increase SNR->decrease BER
  - given SNR: choose physical layer that meets BER requirement, giving highest throughput
    - SNR may change with mobility: dynamically adapt physical layer (modulation technique, rate)

<small>*Figura: 10 -1 · 10 -2 · 10 -3 · R -4 · E 10 · B · 10 -5 · 10 -6 · 10 -7 · 10 20 30 40 · SNR(dB) · QAM256 (8 Mbps) · QAM16 (4 Mbps) · BPSK (1 Mbps)*</small>

---

# Wireless link characteristics (III)

Multiple wireless senders, receivers create additional problems (beyond  
Hidden terminal problem

      - B, A hear each other
  - B, A hear each other
      - B, C hear each other
  - B, C hear each other
    - A, C can not hear each other
- A, C can not hear each other means A,

interfering at B  
C unaware of their interference at B

<small>*Figura: multiple access): · B · A · C · C ’ s signal · A ’ s signal · strength · B · A · space · Signal attenuation:*</small>

---

# Wireless LANs

*(slide con sola figura)*

---

# IEEE 802.11 Wireless LAN

802.11n (WiFi 4)  
802.11ac (WiFi 5)  
802.11ax (WiFi 6)

- all use CSMA/CA for multiple access, and have base-station and ad-hoc network versions

<small>*Figura: IEEE 802.11 · Year Max data rate Range Frequency · standard · 802.11b · 1999 11 Mbps · 30 m · 2.4 Ghz · 802.11g · 2003 54 Mbps · 30m · 2.4 Ghz · 2009 600 · 70m · 2.4, 5 Ghz · 2013 · 3.47Gpbs · 70m · 5 Ghz · 2021 14 Gbps · 70m · 2.4, 5 Ghz · 802.11af · 2014 35 – 560 Mbps 1 Km · unused TV bands (54- · 790 MHz) · 802.11ah · 2017 347Mbps · 1 Km · 900 …*</small>

---

# 802.11 LAN architecture

- wireless host communicates with base station
  - base station = access point
- Basic Service Set (BSS) (aka “cell”) in infrastructure mode contains:
  - wireless hosts
    - access point (AP): base station
      - ad hoc mode: hosts only

<small>*Figura: Internet · (AP ) · switch · or router · BSS 1 · BSS 2*</small>

---

# 802.11: Channels, association

- spectrum divided into channels at different frequencies
  - AP admin chooses frequency for AP
  - interference possible: channel can be same as that chosen by neighboring AP!
- arriving host: must associate with an AP
  - scans channels, listening for beacon frames containing AP’s name (SSID) and MAC address
  - selects AP to associate with
  - then may perform authentication [Chapter 8]
  - then typically run DHCP to get IP address in AP’s subnet

<small>*Figura: BSS*</small>

---

# 802.11: passive/active scanning

passive scanning:  
active scanning:  
(1) beacon frames sent from APs  
(1) Probe Request frame broadcast from H1  
(2) association Request frame sent: H1  
(2) Probe Response frames sent from APs  
to selected AP  
(3) Association Request frame sent: H1 to  
(3) association Response frame sent  
from selected AP to H1  
(4) Association Response frame sent from  
selected AP to H1

<small>*Figura: BBS 1 · BBS 2 · 1 · AP 2 · 1 · 2 · AP 2 · AP 1 · 2 · 3 · 4 · H1 · selected AP*</small>

---

# IEEE 802.11: multiple access

- avoid collisions: 2 + nodes transmitting at same time
- 802.11: CSMA - sense before transmitting
  - don’t collide with detected ongoing transmission by another node
- 802.11: no collision detection!
  - difficult to sense collisions: high transmitting signal, weak received signal due to fading
  - can’t sense all collisions in any case: hidden terminal, fading
  - goal: avoid collisions: CSMA/CollisionAvoidance

<small>*Figura: B · A · C · C ’ s signal · A ’ s signal · B · strength · A*</small>

---

# IEEE 802.11 MAC Protocol: CSMA/CA

802.11 sender  
1 if sense channel idle for DIFS then  
transmit entire frame (no CD)  
2 if sense channel busy then  
start random backoff time  
timer counts down while channel idle  
transmit when timer expires  
if no ACK, increase random backoff interval, repeat 2  
802.11 receiver  
if frame received OK  
return ACK after SIFS (ACK needed due to hidden

<small>*Figura: sender · receiver · DIFS · data · SIFS · ACK · terminal problem)*</small>

---

# Avoiding collisions (more)

idea: sender “reserves” channel use for data frames using small reservation packets

- sender first transmits small request-to-send (RTS) packet to BS using CSMA
  - RTSs may still collide with each other (but they’re short)
- BS broadcasts clear-to-send CTS in response to RTS
- CTS heard by all nodes
  - sender transmits data frame
  - other stations defer transmissions

---

# Collision Avoidance: RTS-CTS exchange

A  
B  
AP  
time

<small>*Figura: RT S ( B ) · R T S ( A ) · reservation collision · R T S ( A ) · C T S ( A ) · DATA (A) · defer · A C K ( A )*</small>

---

# 802.11 frame: addressing

Address 1: MAC address  
Address 4: used only in  
of wireless host or AP to  
ad hoc mode  
receive this frame  
Address 3: MAC address of  
Address 2: MAC address router interface to which AP  
of wireless host or AP  
transmitting this frame

<small>*Figura: 2 2 · 6 6 6 2 6 0 - 2312 · 4 · frame · address address address seq address · duration · payload CRC · control · 1 2 3 control 4 · is attached*</small>

---

# 802.11 frame: addressing

R1  
Internet  
H1  
802.3 Ethernet frame  
R1 MAC addr H2 MAC addr  
AP MAC addr H1 MAC addr R1 MAC addr  
802.11 WiFi frame

<small>*Figura: MAC dest addr MAC source addr · address 1 address 2 address 3*</small>

---

# 802.11 frame: addressing

duration of reserved  
frame sequence # (for reliable  
transmission time (RTS/CTS)  
frame type (RTS, CTS, ACK, data)

<small>*Figura: data transfer) · 4 · 2 2 · 6 6 6 2 6 0 - 2312 · frame · address address address seq address · duration · payload CRC · control · 1 2 3 control 4 · 2 2 · 4 1 1 1 1 1 1 1 1 · protocol · to from more · power more · type subtype · retry · WEP rsvd · version · AP AP frag · mgt data*</small>

---

# 802.11: mobility within same subnet

- H1 remains in same IP subnet: IP address can remain same
- switch: which AP is associated with H1?
- self-learning; switch will see frame from H1 and “remember” which switch port can be used to reach H1

<small>*Figura: BBS 2 · H1 · BBS 1*</small>

---

# 802.11: advanced capabilities

- base station, mobile dynamically change transmission rate (physical layer modulation technique) as mobile moves, SNR varies

1. SNR decreases, BER increase as node moves  
away from base station  
2. When BER becomes too high, switch to lower R  
transmission rate but with lower BER

<small>*Figura: Rate adaptation · 10 -1 · 10 -2 · 10 -3 · E · B 10 -4 · 10 -5 · 10 -6 · 10 -7 · 10 20 30 40 · SNR(dB) · QAM256 (8 Mbps) · QAM16 (4 Mbps) · BPSK (1 Mbps) · operating point*</small>

---

# 802.11: advanced capabilities

- node-to-AP: “I am going to sleep until next beacon frame”
  - AP knows not to transmit frames to this node
  - node wakes up before next beacon frame
- beacon frame: contains list of mobiles with AP-to-mobile frames waiting to be sent
  - node will stay awake if AP-to-mobile frames to be sent; otherwise sleep again until next beacon frame

<small>*Figura: power management*</small>

---

# Cellular Networks

*(slide con sola figura)*

---

# Definitions

- Cellular network
  - Network where a geographical area is covered by tassellation through adjacent or overlapping areas, called cells
  - User terminals can move form one cell to another without communication disruption ( handover )

---

# Cellular coverage – In theory…

- Base station at the center of the cell, equipped with isotropic antenna
- Cells: regular exagonal shape

---

# Cellular coverage – In theory…

- 3 directional antennas with a 120 ° opening, located at one extreme of each cell 3 co-located antennas

---

# Cellular coverage – In practice…

*(slide con sola figura)*

---

# Cells

- Cells are not regular exagons and do not have same size
- Cell shape and size are determined by:
  - Power emitted at the antenna
  - Antenna height
  - Antenna gain
  - Morphology of the geographical area (in urban areas: buildings height and shape)
    - Fading (multiple copies of the signal)
  - Propagation conditions
- Macrocells vs microcells
  - Different size, depending on the specific needs

---

# Example: macrocell

*(slide con sola figura)*

---

# Macrocell: received power levels

*(slide con sola figura)*

---

# Example: microcell

*(slide con sola figura)*

---

# Microcell: received power levels

*(slide con sola figura)*

---

# Channel access

- Multiple user channel access : wireless channel is a common resource that has to be shared among multiple users
- Possible techniques to share resources:
  - FDMA (Frequency Division Multiple Access)
  - TDMA (Time Division Multiple Access)
  - CDMA (Code Division Multiple Access)
  - SDMA (Space Division Multiple Access)

---

# FDMA with frequency reuse

- Given the limited number of available resources, we need to:
  - Ensure coverage
  - Serve a high number of users
- We define as cluster the set of G adjacent cells that use all the frequencies available to one

<small>*Figura: Reuse the same frequencies at · different locations*</small>

---

# 3-Cell cluster

- Green, pink and light blue cells use disjoint sets of channels
- Cells of the same color are called “co-channel” cells

<small>*Figura: CLUSTER · G =3 cells*</small>

---

# 7-cell cluster

2  
3  
7  
1  
6  
4  
5  
G =7 cells

<small>*Figura: CLUSTER · 1 2 3 4 5 6 7*</small>

---

# Fixing G and varying the cell size R

Given a cluster size, the system capacit y increases as the cell radius (i.e., cell size) decreases

---

# Fixing G and varying the cell size R

- Given G :
  - The smaller the R , the larger the capacity
  - The smaller the R , the larger the number of antennas needed to ensure same total coverage

<small>*Figura: capacity · cost · R (cell radius)*</small>

---

# Fixing R and varying the cluster size G

- Given R (i.e., given the cell size):
  - The larger the G , the smaller the number of channels per cell, the lower the system capacity
  - The larger the G , the larger the distance between co-channel cells , the less the interference, the better the quality

<small>*Figura: quality · capacity · G (cluster size)*</small>

---

# Frequency reuse

- Some techniques reduce interference and increase capacity
  - Splitting
  - Sectoring
  - Tilting
  - Creating femtocells

---

# Splitting

- Split large cells into a set of small cells
- Coexistence between
  - Microcells: small cells in highly populated areas with high traffic density (large cities). Transmit power at the base station ≈ 3 W
  - Macrocells: large cells in areas with low traffic density (rural areas). Transmit power at the base station ≈ 20-60 W

---

# Splitting

- Each large cell is replaced by a group of small cells

<small>*Figura: Reducing R leads to capacity · increase · (but also cost increase)*</small>

---

# Cell shaping

- It is possible to use directional antennas to have cells with an ad-hoc size and shape
- It is possible to create multi-layer cell coverage (umbrella coverage)
- Microcells that follow the user as she moves

---

# Cell shaping

micro-cells  
Umbrella cells

---

# Cell shaping

Highway or Railway coverage  
Other cells

---

# Power control

- Needed to reduce:
  - Interference
  - Energy consumption
- Open/ closed control

<small>*Figura: P · t · feedback · distance*</small>

---

# Power control strategies

- In uplink:
  - Closed loop power control
  - Open loop power control
  - Outer loop power control
- In downlink:
  - Downlink power control

---

# Power control: open loop (uplink)

- The user terminal controls itself
- 2-phase mechanism:
  - User measures the quality of the signal received from the BS (downlink signal)
  - The user employs an algorithm to set the transmit power to be used in uplink so that the estimated SINR is above a given threshold
- “Open Loop” since there is no feedback
- Not very accurate as uplink and downlink transmissions typically occur on different channels
  - Other techniques more accurate but more complex (e.g., closed loop)

---

# Frequency allocation

- Fixed Channel Allocation (FCA)
  - Based on the concept of cluster
  - Frequencies are assigned in a static way
  - Frequency plan is changed only rarely to improve performance and adapt to slow variations in user traffic
- Dynamic Channel Allocation (DCA)
  - Resources assigned to cells by a central controller when needed
  - Frequency plan changes over time to adapt to the system status
- Hybrid Channel allocation Scheme (HCS)
  - One portion is statically allocated (FCA)
  - One portion is dynamically allocated (DCA)

---

# Network architecture

<small>*Figura: S/R = switch/router · BS = base station · MT = mobile terminal · S/R · Data · BS · base · MT · S/R · BS · S/R · MT · Towards other · networks · users · BS · Core network · Radio access*</small>

---

# Basic procedures: Registration

- It allows a mobile terminal:
  - to connect with the network
  - to identify and authenticate itself
- It is performed:
  - When a terminal is switched on and has to associate with the network
  - Whenever a user wants to access a service (es. start a call)
  - Periodically

---

# Basic procedures: Mobility management

- Mobility support characterizes cellular networks
- We need procedures to handle mobility
  - Roaming
  - Location updating
  - Paging
  - Handover

---

# Roaming

- The user position has to be traceable even if she moves over the network area
- The system has to store the user position in a database to locate users whenever needed
- To store user positions, the network area is divided into location areas (LAs) , i.e., groups of cells

---

# Roaming

- Each location area has an ID: location area identifier (LAI)

<small>*Figura: LAI2 · LAI1 · LAI3*</small>

---

# Location updating

- Procedure through which the user position is updated
- A control channel is periodically broadcasted in each cell of an LA
- When the mobile terminal receives an LAI different from the one previously stored, the user starts a location updating procedure in order to update her position in the database

---

# Paging

- Procedure through which the system notifies a mobile terminal about an incoming call/data delivery
- The system broadcasts a paging message within the LA where the user is

---

# Handover

- Procedure that enables the transfer of an active connection from one cell to another, while the mobile terminal moves over the network area
- Complex procedure that poses constraints on the network architecture, protocols and signaling

---

<!-- _class: dense -->

# Handover classification

- Intra vs. Inter Cell
  - It indicates whether the handover is between frequencies within the same cell or different cells
- Soft vs. Hard
  - It indicates whether during handover both radio channels are active (soft) or only one at the time is active (hard)
- MT vs. BS initiated
  - It indicates whether the first control message to start a handover is sent by the mobile terminal (MT initiated) or by the BS (BS initiated), i.e., which entity performs measurements to understand where and when a handover has to be executed
- Backward vs. Forward
  - It indicates whether handover signaling occurs via the origin BS (backward) or the destination BS (forward)

---

# Cellular network evolution

<small>*Figura: bps · 1G → 2G → · 3G → 4G → 5G → · UMTS LTE · 1000k · LTE-A · HSPA · 100k · GPRS · 10k · e.g. TACS GSM · Experimental · trials · 1970 1980 1990 2000 2010 2018*</small>

---

# 1G: First generation

- Analog technology
  - FDMA
    - Voice traffic only
      - Low service quality
        - Low efficiency in frequency reuse, and low network capacity
- TACS:
  - 900 MHz
  - Channel width=25 kHz
  - In Italy, service stopped (TIM) on 31/12/05

---

# 2G: Second generation

- Main change: from analog to digital
- Advantages:
  - Integration of different services (e.g., SMS)
  - Cryptography
  - Advanced voice coding to reduce bandwidth requirements
- FDMA/TDMA in Europe, CDMA in the U.S.
- Frequency bands: 850, 900, 1800, 1900 MHz
- Active networks:
  - IS-95 in USA
  - GSM in Europe
  - PDC in Japan

---

# 2.5G: Extended second generation

- GPRS/EDGE in Europe, IS-95B in USA
- Introduction of data service
  - Packet switched
  - 170 kb/s in GPRS, 384 kb/s in EDGE
  - Traffic-based instead of time-based billing

---

# 3G: Third generation

- Improvement of data service (multimedia services)
- CDMA
- Exploit spatial diversity (simultaneous transmissions with multiple BSs) to improve quality
- High data rate (up to 2 Mb/s)
- Handover between different networks (2G-3G) is possible (vertical handover)
- Networks:
  - UMTS (Universal Mobile Telecommunication System) in Europe and Japan
  - CDMA2000 (IS-95C) in USA

---

# 3.5G: Extended third generation

- Evolution of UMTS
  - HSPA (High-Speed Packet Access), composed of HSDPA and HSUPA (downlink/uplink)
  - HSPA+ (Evolved High-Speed Packet Access)
- Mainly changes at the UMTS physical layer
- Data rates up to:
  - 56 Mb/s DL
  - 22 Mb/s UL

---

# 4G: Fourth generation

- Known as LTE (Long Term Evolution)
- Data rate up to 250 Mb/s
- Uses MIMO and high-performance modulations
- All – IP
- Initially only data service (now also voice with VoLTE )
- Standardization
  - “4G” has to satisfy ITU requirements for “IMT Advanced” (high spectrum efficiency, minimum data rate of 1 Gb/s for fixed users and 100 Mb/s for mobile users)
  - LTE does not meet such constraints yet, the right name would be “3.9 G”
  - LTE-Advanced (standard since 2011) meets such requirements

---

# 5G: Fifth generation

- Integrates different technology over the wireless segment (mainly, further evolution of LTE-A, WiFi and mmWave communications)
- Exploit the SDN ( Software defined Networking ) paradigm for network control and operation
- Exploits the NFV ( Network Function Virtualization ) paradigm for service implementation

---

# GSM: the 2 Generation

nd

---

# Services offered by GSM

- Voice full rate (13 kbit/s), half rate (6.5 kbit/s)
- SMS
- Supplementary services (call forward, recall on busy tone,….)

---

# GSM network architecture

*(slide con sola figura)*

---

# Mobile Station (MS)

- User Equipment
- several types depending on the application, e.g.:
  - Mobile phones
  - Mobile devices (e.g., laptop, tablet, etc.)
  - Antennas on vehicles
- Different transmitted power at the antenna
  - Up to 2W for mobile phones
  - Up to 8W for mobile devices
  - Up to 20W for car antennas

---

# Subscriber Identity Module (SIM)

- MS is “hardware” only, to connect to the network it needs a SIM
- SIM=Smart card with processor and memory (to be inserted in the SIM reader)
- SIM stores (encrypted) user information: phone no., accessible services, security parameters, ecc.

<small>*Figura: MT · + · = · (Mobile Terminal)*</small>

---

<!-- _class: dense -->

# Base Station Subsystem (BSS)

- Base Station (BS)
  - Base Transceiver Station (BTS)
    - Physical interface in charge of transmission and reception
    - Point of access for the MT
    - Unlike other signal sources (e.g. radio, TV), BTSs transmit signal only towards users that are active
    - Up to 32 FDM channels per BTS (half uplink, half downlink)
  - Base Station Controller (BSC)
    - Resource control on the radio interface: BSCs and BTSs communicate over a wired link
    - A BSC controls a high number of BTSs: from tens to hundreds
    - Typically, BSCs are collocated with one MSC, instead of being located near the BTSs
    - BSC main functions:
      - Voice transcoding 13 kb/s ↔ 64 kb/s
      - Paging
      - Radio resource control: dynamic frequency assignment to BTSs
      - Signal quality measurement

---

# Network and Switching Subsystem (NSS)

- Main functions:
  - Call handling
  - Service support
  - Mobility support
  - Authentication
    - Mobility support
      - Call routing between MT
        - GMSC: Interface between the GSM

<small>*Figura: AuC · Um · VLR · HLR · BSS · MT · A · (G)MSC · EIR · Mobile Switching Center · network and other networks*</small>

---

# Network and Switching Subsystem (NSS)

- Main functions:
  - Call handling
  - Service support
  - Mobility support
  - Authentication
    - Permanent user data: id, enabled services,
      - Dynamic data to handle user mobility

<small>*Figura: AuC · Um · VLR · HLR · BSS · MT · A · (G)MSC · EIR · Home Location Register · Database storing: · security parameters · (e.g., VLR identifier)*</small>

---

# Network and Switching Subsystem (NSS)

- Main functions:
  - Call handling
  - Service support
  - Mobility support
  - Authentication
    - Information related to MTs currently

<small>*Figura: AuC · Um · VLR · HLR · BSS · MT · A · (G)MSC · EIR · Visitor Location Register · Database storing: · in the area controlled by the MSC: · IDs, on/off status, LAI, routing information, · security*</small>

---

# Network and Switching Subsystem (NSS)

- Main functions:
  - Call handling
  - Service support
  - Mobility support
  - Authentication

<small>*Figura: AuC · Um · VLR · HLR · BSS · MT · A · (G)MSC · EIR · Authentication Center · Authentication based on challenge & response protocol · Generations of encryption keys for over-the-air communication*</small>

---

# Network and Switching Subsystem (NSS)

- Main functions:
  - Call handling
  - Service support
  - Mobility support
  - Authentication

<small>*Figura: AuC · Um · VLR · HLR · BSS · MT · A · (G)MSC · EIR · Equipment Identity Register · Database of stolen devices*</small>

---

# GSM frequencies (Europe)

- Allocated frequencies: 850, 900, 1800, 1900 MHz
- FDD (Frequency Division Duplex) system
  - different frequencies for UL and DL

<small>*Figura: GSM-900 primary (downlink) · DCS/1800 · uplink · GSM-900 primary (uplink) · DCS/1800 · GSM-900 extended (downlink) · downlink · GSM-900 extended uplink · F · [MHz] · 915 · 935 · 1805 · 1710 · 880 · 1880 · 960 · 1785 · 890 925*</small>

---

# GSM physical channels

- Channel access: FDMA/TDMA
- Frequency spectrum divided into FDM channels, each 200 kHz wide
- Each FDM channel is divided into TDM frames
- Each TDM frame is divided into 8 slots
- Transmission organized into “bursts”, i.e., blocks of data that are transmitted on a physical channel
  - Bursts are similar to packets…But it is still circuit switching!
- Transmission speed = 271 kbit/s

<small>*Figura: ⇒ Frequency + time slot = physical channel*</small>

---

# Channel access – Summary of FDM/TDM schema

- Slot time = 0.577 ms
  - 1 slot carries 156.25 bits (i.e., 0.577*271 kbps)
- Each time slot carries 1 transmission burst
- Slots are grouped into TDM frames, of 8 slots each
  - Frame = 4.615 ms

<small>*Figura: frequency · ... 1 2 3 4 5 6 7 0 1 2 3 4 5 6 ... n+1 · 200 kHz ... 1 2 3 4 5 6 7 0 1 2 3 4 5 6 ... n · ... 1 2 3 4 5 6 7 0 1 2 3 4 5 6 ... n-1 · time · 4.615 ms · 0.577 ms*</small>

---

# Channel access – GSM frame

- Circuit-switched network
  - Each call @full rate (13kb/s) is assigned 1 slot per frame in UL and 1 slot per frame in DL
- Each MT transmits on a carrier for one time slot, i.e., one burst of data, and remains silent during the other 7 slots
- Frames on UL and DL are synchronized on a time slot basis and shifted by 3 slots
- Separating UL/DL transmissions in frequency and time allows the use of one transceiver only

<small>*Figura: TDM Frame · downlink · 4.615 ms · 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 BTS Transmits · 45 MHz · 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 MT Transmits*</small>

---

# Channel access – Timing advance

- Non-zero propagation times
  - Bursts transmitted by MTs might arrive at the BTS when the slot is already finished
  - Possible collisions
- Solution: timing advance
  - Transmission at the MT starts before the real timeslot beginning

<small>*Figura: Without TA MT tx · BTS rx · Pt · Ta · With TA MT tx · BTS rx · 5 6 7 0 1 2 3 4 5 6 7 · … · BTS timing*</small>

---

# “Regular” burst structure

<small>*Figura: Indicate whether the burst carries user information or control · bits (stealing bits) · Set to 0, used for synchronization · and equalization · 148 bit = 546.12 µs · T Coded Data S Training S Coded Data T GP · Sequence · 3 · 57 · 1 · 26 · 1 · 57 · 3 8.25 · Set to 0 (guard period) · User bits (voice, data, etc.), 114 bits after channel coding, · …*</small>

---

# GSM Logical channels

- Physical channels
  - Combination of timeslot and carrier
  - 8 physical channels per carrier: timeslots 0 - 7
- Logical channels
  - Carry useful information, i.e., specify “ what ” is transmitted
  - Mapped into physical channels according to proper criteria
- Two types of logical channels
  - Control channels
    - Carry control information (related to user or network)
  - Traffic channels
    - Carry user information

---

# Control channels

- Network signaling
  - Cell parameters
  - Synchronization
  - Receiver tuning
- User signaling
  - Call control
  - Signal quality control (measurement delivery)

---

# LTE: the 4th Generation

*(slide con sola figura)*

---

# LTE

- First release by 3GPP as Release 8, known as LTE-Advanced since Rel. 10
- Speeds up to 300 Mb/s DL - 50 Mb/s UL with modulations up to 64 QAM
- 10-ms data latency
- Replaces WCDMA with OFDMA (DL) and SC-FDM (UL)
- Leverages high-order MIMO
- Up to 20 MHz channels
- Scalable frequency bands from 1.4MHz to 20 MHz
- “All-IP” HSDPA core network

---

# Usage of Frequency Bands

*(slide con sola figura)*

---

# LTE Terminology

- Downlink (DL): data going from the network to the user device
- Uplink (UL): data going from the user device to the network
- User plane : all the operations related to the transport of user data in DL and UL
- Control plane : all operations related to the set-up, control and maintenance of communications between user and network

<small>*Figura: UL · DL · ACCESS STRATUM · NON ACCESS STRATUM*</small>

---

# LTE Architecture

- Radio Access Network (RAN): it includes all the devices involved with the direct interaction with user devices
  - In LTE, it is called the E-UTRAN
- Core Network (CN): it includes all the devices responsible for the transport of data to/from the Internet or toward other user devices
  - In LTE, it is called EPC

<small>*Figura: Radio · Core Network · Access Network*</small>

---

# LTE Architecture

<small>*Figura: EPC · E-UTRAN · UE · UE = User Equipment UE · UE*</small>

---

# EPC – Design Principles

- Clean-slate design
- Packet-switched transport for traffic belonging to all QoS classes including conversational, streaming, real-time, non- real-time, and background
- Radio resource management for: end-to-end QoS, transport for higher layers, load sharing/balancing, policy management/enforcement across different radio access technologies
- Integration with existing 3GPP 2G and 3G networks

---

<!-- _class: dense -->

# EPC – Functions

- Network access control , including network selection, authentication, authorization, admission control, policy and charging enforcement, and lawful interception
- Packet routing and transfer
- Security , including ciphering, integrity protection, and network interface physical link protection
- Mobility management to keep track of the current location of the UE
- Radio resource management to assign, reassign, and release radio resources taking into account single and multi-cell aspects
- Network management to support operation and maintenance
- IP networking functions, connections of eNodeBs, E-UTRAN sharing, emergency session support, among others

---

# EPC - Components

- Mobility Management Entity (MME)
  - Resides in the Control Plane
  - Supports user equipment context, identity, authentication, and authorization
  - Mainly perform Non Access Stratum procedures, consisting of two main groups UE
    - Functions related to bearer management
      - Bearer can be seen as a logical communication tunnel
    - Functions related to connection and mobility management

<small>*Figura: UE*</small>

---

# EPC - Components

- Serving Gateway (SGW)
  - Resides in the User Plane
  - Receives and sends packets between the eNodeB and the core network
  - Perform packet routing and forwarding within EPC
  - Anchor point for intra LTE-mobility
  - Lawful intercept

<small>*Figura: UE*</small>

---

# EPC - Components

- Packet Data Network Gateway (PGW)
  - Resides in the User Plane
  - Connects the EPC with external networks/Internet
  - Basically, a router that performs UE IP assignment, per user packet filtering and NAT services
  - Anchor point for mobility with non- 3GPP access network
  - Lawful intercept

<small>*Figura: UE*</small>

---

# EPC - Components

- Home Subscriber Server (HSS)
  - Database of user-related and subscriber-related information
  - Used for authentication (together with MME) and authorization
  - Similar to HLR in GSM architecture

<small>*Figura: UE*</small>

---

# The LTE Bearers

- Think of a bearer as a pipe (tunnel) that carries data from the UE to other elements of the LTE architecture (e.g., the P-GW)
- one default bearer is established to the P-GW whenever the UE is activated
- the UE can establish other dedicated bearers to other networks, based on quality-of-service (QoS) requirements
  - e.g., viewing a streaming video over the Internet can be done over a dedicated bearer
  - dedicated bearers can use a bandwidth guarantee (a guaranteed bit rate, or GBR) tunnel

---

# The LTE Bearers

- The bearer is a concatenated tunnel consisting of three portions established in the following order:
  - The S5 bearer — connects the Serving Gateway (S-GW) to the P-GW. (The tunnel can extend from P-GW to the Internet)
  - The S1 bearer — connects the eNodeB with the S-GW. Handover establishes a new S1 bearer for end-to-end connectivity.
  - The radio bearer — connects the UE to the eNodeB. This bearer follows the mobile user under the direction of the MME as the radio network performs handovers when the user moves from one cell to another

---

# E-UTRAN

- Mainly consist of eNodeB
- An interface X2 interconnects between eNodeB
  - Consist of two type : X2 control and X2 user
- Main functions
  - Radio resource management: related to the radio bearer such as radio bearer control, radio mobility control, scheduling and dynamic allocation of radio resource at uplink and downlink
  - Header compression
  - Security
  - Connectivity to EPC

<small>*Figura: UE*</small>

---

# LTE Data Plane/Control Plane

*(slide con sola figura)*

---

# LTE data plane control plane separation

- new protocols for mobility management , security, authentication (later)
- new protocols at link, physical layers
- extensive use of tunneling to facilitate mobility

<small>*Figura: HSS · control plane · base station · P-GW · MME · S-GW · data plane · P-GW · base station · S-GW · IP tunnels*</small>

---

# LTE data plane protocol stack: first hop

LTE link layer protocols:

- Packet Data Convergence: header compression, encryption
- Radio Link Control (RLC) Protocol: fragmentation/reassembly, reliable data transfer
- Medium Access: requesting, use of radio transmission slots

<small>*Figura: Application · Transport · IP · Packet Data · Convergence · k · n Radio Link · Radio Link · i · L Medium Access · Medium Access · Physical · data · plane · base station · P-GW · S-GW*</small>

---

# LTE data plane protocol stack: first hop

LTE radio access network:

- downstream channel: FDM, TDM within frequency channel (OFDM - orthogonal frequency division multiplexing)
  - “orthogonal”: minimal interference between
    - upstream: FDM, TDM similar to OFDM
- each active mobile device allocated two or more 0.5 ms time slots over 12 frequencies
  - scheduling algorithm not standardized – up to
    - 100’s Mbps per device possible

<small>*Figura: Application · Transport · IP · Packet Data · Convergence · k Convergence · n Radio Link · Radio Link · i · L Medium Access · Medium Access · channels · Physical · operator · base station*</small>

---

# LTE data plane protocol stack: Physical Channels

- Transmitted bits fit into the frame structure according to predefined subdivisions called Physical Channels
- Each channel conveys specific information related to: user data, TX/RX parameters, eNB identity, network control etc., as well as to the format of the channel itself (i.e., FDD or TDD)
- Each physical channel is mapped into a portion of the LTE subframe
- Physical channels are divided into Downlink and Uplink Channels
  - Each U/D channel is further divided into Data and Control

---

<!-- _class: dense -->

# LTE Physical Downlink Channels

- Physical Broadcast Channel (PBCH)
  - MIB (Master Information Block) and RACH parameters (Radio Access Channel)
- Physical Control Format Indicator Channel (PCFICH)
  - Details on PDCCH format (e.g., number of symbols used)
- Physical Hybrid ARQ Indicator Channel (PHICH)
  - Ack/Nack to uplink frame transmission
- Physical Downlink Control Channel (PDCCH)
  - Downlink resource scheduling
  - Uplink power control instructions
  - Uplink resource grant
  - Indication for paging or system information
- Physical Downlink Shared Channel (PDSCH)
  - User data and SIB (System Information Block) for cell information

<small>*Figura: c · on · t · r · o · l · da · t · a*</small>

---

# LTE Physical Uplink Channels (control)

- Physical Random Access Channel (PRACH)
  - It carries the random access preamble a UE sends to access the network in non- synchronized mode
  - used to allow the UE to synchronize timing with the eNodeB
- Physical Uplink Control Channel (PUCCH)
  - Signaling includes HARQ ACK/NACK, channel quality indicators (CQI), MIMO feedback and scheduling requests for uplink transmission

---

# LTE Physical Uplink Channels (data)

- Physical Uplink Shared Channel (PUSCH)
  - It carries user data
  - The uplink scheduling TTI is 1 ms; it is possible to ‘bundle’ a group of 4 TTIs to improve performance at cell edge and reduce higher- layer protocol overhead

---

# LTE data plane protocol stack: packet core

- mobile datagram encapsulated using GPRS Tunneling Protocol (GTP), sent inside UDP datagram to S-GW
- S-GW re-tunnels datagrams to P-GW
- supporting mobility: only tunneling endpoints change when mobile user moves

<small>*Figura: tunneling: · GTP-U · GTP-U GTP-U · UDP · IP · Packet Data · Convergence · Radio Link · link · Medium Access · Physical Physical · \ · P-GW · base station · S-GW*</small>

---

# LTE data plane: associating with a BS

1 BS broadcasts primary synch signal every 5 ms on all frequencies

- BSs from multiple carriers may be broadcasting synch signals

2 mobile finds a primary synch signal, then locates 2 nd synch signal on this freq.

- mobile then finds info broadcast by BS: channel bandwidth, configurations; BS’s cellular carrier info
- mobile may get info from multiple base stations, multiple cellular networks

3 mobile selects which BS to associate with ( e.g., preference for home carrier)  
4 more steps still needed to authenticate, establish state, set up data plane

<small>*Figura: 1 · 2 · data · 3 · plane · P-GW · base station · S-GW*</small>

---

# LTE mobiles: sleep modes

Z Z ZZ...  
as in WiFi, Bluetooth: LTE mobile may put radio to “sleep” to conserve

- light sleep: after 100’s msec of inactivity
  - wake up periodically (100’s msec) to check for downstream transmissions
- deep sleep: after 5-10 secs of inactivity
  - mobile may change cells while deep sleeping – need to re-establish association

<small>*Figura: data · plane · battery:*</small>

---

# 5G Networks

*(slide con sola figura)*

---

# 5G objectives

- 5G will meet the requirements of a highly mobile, fully connected society.
  - proliferation of connected objects and devices
  - wide range of new services and associated business models
  - automation in various industry sectors and vertical markets (e.g. energy, e-health, smart city, connected cars, industrial manufacturing, etc.).
  - more pervasive human centric applications, e.g., virtual and augmented reality augmentation, 4k video streaming, etc.
- 5G networks will support the coexistence of
  - human-centric
  - machine type applications
- 5G networks will have to support very diverse functional and KPI/performance requirements

---

# 5G Key Requirement

Unlike previous generations of mobile  
networks, 5G will require not only  
improved networking solutions but also a  
sophisticated integration of massive  
computing and storage infrastructures.

---

# 5G Ecosystem

- Operators will have to deploy orchestrator functions that will allocate appropriate computing and logical network resources to services
- These logical networks, called network slices , will contain specialized networking and computing functions that meet the desired performance of the service providers
- 5G networks will support cross-domain orchestration of services and resources over multiple administrative domains (multiple operators) allowing flexible sharing schemes
- The implementation of these schemes will also require interworking among operators in the network function layer as well (e.g., setting up SDN rules).

---

# 5G use cases

- Enhanced Mobile Broadband (eMBB)
- Massive Machine Type Communication (mMTC)
- Ultra-Reliable Low-Latency Communication (URLLC)

---

# 5G technologies in the Radio Access

- Alternatives to pure OFDM such as RBF-OFDM, FBMC, GFDM, and UFMC
- Both co- located and distributed architectures are envisaged, with co-located massive MIMO particularly appealing to high frequency bands
- Millimeter Wave spectrum (20-80GHz) offers large chunks (up to 2GHz) of contiguous bandwidth, for ultra-high throughput and low latency scenarios.

---

# 5G technologies in the Core Network

- SDN is an approach to networking in which routing control is centralized and decoupled from the physical infrastructure (data plane), which is distributed .
- NFV moves network services (firewall, load balancing, access control) from hardware to software, creating virtual building blocks that can be easily connected (NFV chaining)
- Aka. the new network operating system : it manages function lifecycle, resources, policies and it provides system analytics

---

# 5G Architecture

- Radio Access Network (RAN): it includes all the devices involved with the direct interaction with user devices
  - In 5G, base stations are called gNodeB
- Edge Network (MEC): it hosts computing and storage elements for local services
- Core Network (CN): it includes all the devices responsible for the transport of data to/from the Internet or toward other user devices

<small>*Figura: Radio · Edge Network · Core Network · Access Network*</small>

---

# Main differences between 4G and 5G networks

- Nomenclature
  - Radio Interface E-UTRA –> New Radio (NR)
  - Radio access network: E-UTRAN –> 5G-RAN
  - Core Network: EPC -> 5GC
- Data and Control Plane split
  - LTE -> have a bit mixed CP and UP functions between different network nodes;
  - In 5G -> full CP/UP split
- Brand-new functionalities
  - network slicing implying different configurations of RAN
  - new QoS framework with flows instead of end-to-end bearers
  - new approach to 5GC using Service Based Architecture (SBA) concept

---

# 5G CORE NETWORK

*(slide con sola figura)*

---

# 5G Service Based Architecture (SBA)

AMF=Access & mobility

<small>*Figura: Management Function · 5G evolution of MME*</small>

---

# 5G Service Based Architecture (SBA)

<small>*Figura: SMF=Session Management · Function · 5G evolution of control plane of SGW and PGW*</small>

---

# 5G Service Based Architecture (SBA)

UPF=User Plane Function

<small>*Figura: 5G evolution of data plane · Performs traffic steering*</small>

---

# 5G EDGE NETWORK

*(slide con sola figura)*

---

# Multiaccess Edge Computing

- Edge Network infrastructure providing IT service environment and cloud-computing capabilities at the edge of the mobile network, in close proximity to mobile subscribers
- Standardization begun in 2014 («Mobile Edge Computing»)
  - First set of specifications published in 2017
- Expected benefits:
  - ultra-low latency
  - high bandwidth
  - real-time access to radio network
  - contextual information
  - location awareness
  - flexible and extendable framework for services

---

# MEC Architecture

<small>*Figura: MAC host contains the MEC platform and a virtualization*</small>

---

# MEC Architecture

<small>*Figura: The MAC platform offers an environment where the MEC applications*</small>

---

# MEC Architecture

<small>*Figura: MEC applications are running as · virtual machines (VM) · on top of the virtualization · infrastructure provided by the · MEC host, and can interact with the · MEC platform to consume · and provide MEC services*</small>

---

# 5G RADIO ACCESS NETWORK

*(slide con sola figura)*

---

# 5G New Radio - Overview

- Flexible slot-based framework
  - Variable number of slots per subframe
  - Transmissions can start in any part of the slot
- Different subcarrier spacing (“numerology”): shorter slots for higher spacing
- Supports slot aggregation for data-heavy transmissions

---

# 5G New Radio – Frequency bands

*(slide con sola figura)*

---

# 5G New Radio – Massive MIMO

- MIMO (Multiple Input Multiple Output): both the base station and UE have multiple antenna ports and antennas, and multiple data streams are transmitted simultaneously to the UE using same time/frequency resources, doubling (2 × 2 MIMO), or quadrupling (4 × 4 MIMO) the peak throughput of a single user
- Massive MIMO (mMIMO) is a system where the number of antennas exceeds the number of users
- Although not part of the first release, 5G NR will support distributed-MIMO, where a user can receive different parts of the same data stream from multiple sites.

---

# 5G New Radio - Beamforming

- Beamforming is the manipulation of the signals fed to and received from complex antennas to create beams in space that focus power in a particular direction
- LTE applies it only to data, 5G also to control
- At high frequencies beamforming will mostly be used to increase range by energy focus,
- At the mid and low bands below 6GHz, where attenuation is less of a problem, beamforming will be a key part of MIMO

---

# Mobility

*(slide con sola figura)*

---

# Contacting a mobile friend:

Consider friend frequently changing  
locations, how do you find him/her?

  - search all phone books?
  - expect her to let you know where he/she is?
  - call his/her parents?
  - Facebook!

The importance of having a “home”:

  - a definitive source of information about you
- a place where people can find out where you are

<small>*Figura: I wonder where · Alice moved to? · Contacting a mobile friend:*</small>

---

# Home network, visited network: 4G/5G

- (paid) service plan with cellular provider, e.g., Verizon, Orange
- home network HSS stores identify & services info
- any network other than your home network
- service agreement with other

SIM card: global  
networks: to provide access to

<small>*Figura: home network: · Home · Subscriber · Server · home mobile · carrier network · P-GW · public Internet · and · inter-carrier IPX · … · in home · … · network · visited network: · P-GW · visited mobile · carrier network · identify info · … · visiting mobile · including · roaming in · home network · visited network*</small>

---

# Home network, visited network: generic

<small>*Figura: Home Network · Visited Network · e.g.,: 128.119/16 · e.g.,: 79.129/16 · Permanent IP: Home · NAT IP: · 128.119.40.186 Subscriber · 10.0.0.99 · Mobility · IMSI · Server · IMSI · 78:4f:43:98:d9:27 · manager · 78:4f:43:98:d9:27 · Visited · Mobility · Home · network · manager · network · gateway · Home gateway · gateway · public or private · Internet …*</small>

---

# Registration: home needs to know where you are!

- visited mobility manager knows about mobile
- home HSS knows location of mobile

<small>*Figura: Home Network · Visited Network · e.g.,: 128.119/16 · e.g.,: 79.129/16 · mobile associates · 1 · Permanent IP: Home · NAT IP: · with visited · 128.119.40.186 Subscriber · 10.0.0.99 · 2 · Mobility · IMSI · Server · IMSI · 78:4f:43:98:d9:27 · mobility manager · manager · 78:4f:43:98:d9:27 · visited mobility · Visited · Mobility · Home · network · …*</small>

---

<!-- _class: dense -->

# Mobility in 4G networks: major mobility tasks

1 base station association:

    - covered earlier
    - mobile provides IMSI identifying itself, home network

2 control-plane configuration:

    - MME, home HSS establish control-plane state - mobile is in visited network

3 data-plane configuration:

  - MME configures forwarding tunnels for mobile
  - visited, home network establish tunnels from home P-GW to mobile

4 mobile handover:

- mobile device changes its point of attachment to visited network

<small>*Figura: Mobility · manager · Home · 1 · 2 · Subscriber · MME · – · Server · 3 · base station · Home · network P-GW · S-GW · 4 · Internet · P-GW · Visited network · Streaming · server*</small>

---

# Configuring LTE control-plane elements

- Mobile communicates with local MME via BS control-plane channel
- MME uses mobile’s IMSI info to contact mobile’s home HSS
  - retrieve authentication, encryption, network service information
  - home HHS knows mobile now resident in visited network
- BS, mobile select parameters for BS-mobile data-plane radio channel

<small>*Figura: Mobility · manager · Home · 2 · Subscriber · MME · Server · base station · Home · P-GW S-GW · network · P-GW · Visited network*</small>

---

# Configuring data-plane tunnels for mobile

- S-GW to BS tunnel: when mobile changes base stations, simply change endpoint IP address of tunnel
- S-GW to home P-GW tunnel: implementation of indirect routing
- tunneling via GTP (GPRS tunneling protocol): mobile’s datagram to streaming server encapsulated using GTP inside UDP, inside datagram

<small>*Figura: Mobility · manager · Home · Subscriber · MME · Server · base station · Home · network P-GW · S-GW · Internet · P-GW · Visited network · Streaming · server*</small>

---

# Handover between BSs in same cellular network

data path before handover  
data path after  
3 source BS informs mobile of new BS

- mobile can now send via new BS - handover looks complete to mobile

4 source BS stops sending datagrams to mobile, instead forwards to new BS  
(who forwards to mobile over radio channel)

<small>*Figura: source BS · 1 current (source) BS selects · 3 · target BS, sends Handover · S-GW · 1 4 · Request message to target BS · 2 · P-GW · 2 target BS pre-allocates radio · time slots, responds with HR · ACK with info for mobile · handover · target BS · MME*</small>

---

# Handover between BSs in same cellular network

5 target BS informs MME that it is  
new BS for mobile

- MME instructs S-GW to change tunnel endpoint to be (new) target BS

6 target BS ACKs back to source BS: handover complete, source BS can  
7 mobile’s datagrams now flow through new tunnel from target BS to S-

<small>*Figura: source BS · 3 · S-GW · 1 4 · 2 6 · P-GW · 5 · 7 · 5 · target BS · MME · release resources · GW*</small>
