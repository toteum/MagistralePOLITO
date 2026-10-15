---
marp: true
theme: default
paginate: true
header: 'Transizione da IPv4 a IPv6'
footer: 'Computer Network Technologies and Services - 1859'
---

<!-- _class: lead -->

# Transizione da IPv4 a IPv6

**Computer Network Technologies and Services**
**Tecnologie e Servizi di Rete**
**Internet Architecture and Technologies**

1859

Claudio Casetti, Guido Marchetto, Alessio Sacco, Marco Rapelli

---

## Copyright Notice

This set of transparencies, hereinafter referred to as slides, is protected by copyright laws and provisions of International Treaties. The title and copyright regarding the slides (including, but not limited to, each and every image, photography, animation, video, audio, music and text) are property of the authors specified on page 1. The slides may be reproduced and used freely by research institutes, schools and Universities for non-profit, institutional purposes. In such cases, no authorization is requested. Any total or partial use or reproduction (including, but not limited to, reproduction on magnetic media, computer networks, and printed reproduction) is forbidden, unless explicitly authorized by the authors by means of written license. Information included in these slides is deemed as accurate at the date of publication. Such information is supplied for merely educational purposes and may not be used in designing systems, products, networks, etc. In any case, these slides are subject to changes without any previous notice. The authors do not assume any responsibility for the contents of these slides (including, but not limited to, accuracy, completeness, enforceability, updated-ness of information hereinafter provided). In any case, accordance with information hereinafter included must not be declared. In any case, this copyright notice must never be removed and must be reported even in partial uses.

---

## The road to IPv6

![bg right:50% 80%](images/page3_img.png)

---

## 4 to IPv6 transition

Idealmente:

*   Incremental
*   Seamless
*   Smooth

---

## How can it be achieved?

*   **Dual-stack approach**
    *   IPv6 come nuovo protocollo di layer 3
    *   Genera/riceve pacchetti v6 o v4 secondo necessità
*   **Address mapping**
*   **Tunneling**
*   **Translation mechanisms**

![bg right:40% 90%](images/page5_img.png)

---

## Step 1: isolated IPv6 networks

![bg 90%](images/page6_img.png)

*   Dual-stack Hosts
*   IPv6 in IPv4 Tunnel

---

## Step 2: IPv6 islands grow

![bg 90%](images/page7_img.png)

*   IPv6-only Hosts
*   Dual-stack Translating Devices

---

## Step 3: Native IPv6 connectivity

![bg 90%](images/page8_img.png)

*   IPv6-only Hosts
*   Dual-stack Translating Devices

---

## Step 4: IPv6 takes over

![bg 90%](images/page9_img.png)

*   IPv4 in IPv6 Tunnel

---

## Are we ready?

Quasi!

*   **Prima specifica:** RFC 1883 (1995); **Internet Standard:** RFC 8200 (2017)
*   **IPv6 implementato sui router**
    *   Maturo come IPv4 oggi, forwarded in hardware at line rate
    *   Gap rimangono principalmente in dispositivi vecchi o low-end
    *   Anche implementazioni hardware (Layer-3 switches)
*   **IPv6 implementato nei sistemi finali**
    *   Windows (preview in 2000/XP; on by default and preferred since Vista, 2007)
    *   Linux: Ubuntu, Debian, FreeBSD...
    *   macOS (since Mac OS X 10.2, 2002)
    *   Android e iOS: Apple richiede che le app App Store funzionino su reti IPv6-only (dal 2016)

---

## When will it happen?

*   Grande base installata IPv4
*   A ottobre 2023, secondo Google, il tasso di adozione globale di IPv6 è circa **45%**

![bg 80%](images/page11_img.png)

---

## When will it happen?

*   Grande base installata IPv4
*   Nel 2026, secondo Google, il tasso di adozione globale di IPv6 è circa **50%**
    *   **54%** solo negli U.S.
*   Solo una vera motivazione: **Address space depletion**
*   Nessuna data ufficiale di switch-off
*   Avverrà gradualmente
    *   Ma esistono obiettivi: U.S. federal IT **80% IPv6-only** entro la fine dell'anno fiscale 2025 (OMB M-21-07); i servizi governativi cechi abbandoneranno IPv4 il **6 giugno 2032**

![bg right:50% 80%](images/page12_img.png)

---

## When will it happen? (Europa)

*   Grande base installata IPv4
*   Nel 2026, secondo Google, il tasso di adozione globale di IPv6 è circa **50%**
    *   **54%** solo negli U.S.
    *   **17%** in Italia
    *   **≈ 86%** in Francia (Feb. 2026)
    *   **70%+** in Germania e India

![bg 80%](images/page13_img.png)

---

## Assumption (and problem to solve)

**IPv4 e IPv6 coesisteranno (almeno per un po')**

---

## Dual Stack Approach

*   Entrambe le capacità IPv4 e IPv6
    *   Tutti gli host e router supportano IPv6
    *   Il supporto IPv4 può essere (gradualmente) rimosso (e incluso nei nuovi host) una volta che tutti gli host hanno IPv6
*   Gli host comunicano nativamente con entrambi
*   Completa duplicazione di tutti i componenti dello stack protocollare
    *   Protocolli di routing
    *   Tabella di routing
    *   Access lists

![bg right:40% 80%](images/page15_img.png)

---

## Dual Stack Limitations

*   Non riduce la necessità di indirizzi IPv4
    *   Ogni host necessita ancora di un indirizzo IPv4 per usare IPv4
*   Le applicazioni hanno la responsabilità di scegliere se usare IPv4 o IPv6
*   Tutto viene gestito due volte: piani di indirizzamento, routing, regole firewall, monitoraggio
*   In pratica, il SO decide

---

## Not all hosts will be dual stack

*   Gli host IPv6 devono comunicare con host IPv6 attraverso una rete IPv4
*   Lo stesso per host IPv4 attraverso una rete IPv6
*   Gli host IPv6 devono comunicare con host IPv4
    *   Devono essere usati meccanismi di traduzione
    *   Non finalizzati a host IPv4 che contattano host IPv6
    *   Difficile mappare il grande spazio di indirizzi IPv6 sul più piccolo spazio IPv4

---

## Tunneling Solutions

*   Host dual stack e IPv6 nativi scambiano pacchetti IPv6 attraverso una rete IPv4

![bg 80%](images/page18_img.png)

---

## First stage: isolated IPv6 networks

![bg 90%](images/page19_img.png)

*   IPv6 in IPv4 Tunnel

---

## Traversing a IPv4-only Network

*   **Tunnelling**
    *   Incapsulamento di pacchetti IP(v6) in pacchetti IP(v4)
    *   Emula un link "diretto" tra dispositivi IPv6

![bg 80%](images/page20_img.png)

---

## End points: hosts and routers

*   **Protocolli**
    *   GRE (Generic Routing Encapsulation)
        *   IPv6 in IPv4
        *   Protocol type = 41
*   **Set up:** manuale e automatico
*   IPv4-compatible addresses, 6over4 (RFC 2529), 6to4, Tunnel Broker (RFC 3053), ISATAP, Teredo

![bg right:30% 50%](images/page21_img1.png)
![bg right:30% 50%](images/page21_img2.png)

Queste soluzioni sono oggi deprecate o inutilizzate

---

## 6to4

![bg 80%](images/page22_img.png)

*   Ogni router 6to4 è assegnato un indirizzo IPv6 unico che inizia con il prefisso "2002::/16" seguito dal suo indirizzo IPv4 a 32 bit
*   I pacchetti inviati da un host IPv6 sono incapsulati in IPv4 da un router 6to4 e instradati attraverso Internet IPv4 verso un altro router 6to4
*   Il router 6to4 decapsula per rivelare il pacchetto IPv6 originale e lo instrada alla destinazione

---

## Basic 6to4 Scenario

*   Non pensato per la comunicazione tra un host IPv4 e un host IPv6

![bg 80%](images/page23_img.png)

---

## Scalable, Carrier-grade Solutions

*   Host nativi IPv6 (IPv4) scambiano pacchetti IPv6 (IPv4) attraverso una rete IPv4 (IPv6)

![bg 80%](images/page24_img.png)

---

## Several Options

*   Si deve ancora supportare
    *   Server IPv4 che possibilmente comunicano con host IPv6
    *   Client IPv4
*   Diverse opzioni
    *   DS-Lite
    *   A+P (Address plus Port)
    *   MAP-T e MAP-E
    *   NAT64
    *   464XLAT

---

## NAT is widely used today

![bg 80%](images/page26_img.png)

*   NAT44
*   Carrier Grade NAT
*   Large Scale NAT
*   IPv4 Provider Private: 100.64.0.0/10 shared address space (RFC 6598), not RFC 1918, so it cannot clash with customers' addresses

---

## How do we like NAT?

*   Problematico con sessioni in entrata
    *   Es. server
    *   NAT + STUN/TURN può essere ok per sessioni peer-to-peer
*   Collo di bottiglia e single point of failure
*   Tuttavia
    *   Diverse istanze (indipendenti) di NAT a cascata sono ora molto comuni
        *   A partire dalle macchine virtuali
    *   Difficile farne a meno a causa della scarsità di indirizzi

---

## Same Architecture with IPv6

![bg 80%](images/page28_img.png)

*   **DS-Lite**
*   **A+P**
*   **NAT64**
*   CPE: Customer Premises Equipment
*   AFTR: Address Family Transition Router

---

## AFTR: Address Family Transition Router

*   Permette a un host IPv4 di comunicare con host IPv4 su un'infrastruttura carrier IPv6
    *   Host residenziale e provider attuali
*   Funge da concentratore di tunnel IPv6 e possibilmente da NAT su larga scala
*   In uso in DS-Lite e A+P

![bg 80%](images/page29_img.png)

---

## DS-Lite (Dual-Stack Lite)

*   Dual-stack all'edge (RFC 6333)
*   Backbone del Service Provider IPv6-only
*   DS-LITE CPE: chiamato B4 (Basic Bridging BroadBand element)
    *   Endpoint del tunnel IPv4-in-IPv6
    *   Router IPv6

![bg 80%](images/page30_img.png)

---

## DS-Lite (continua)

*   Riduce il requisito di indirizzi IPv4 rispetto all'approccio dual-stack
*   Dual-stack richiede un indirizzo IPv4 pubblico per cliente (CPE con NAT44), o un CGN
*   Extended NAT abilita indirizzamento assegnato al cliente (cioè sovrapposto)
*   Indirizzo IPv6 del CPE nella tabella NAT

---

## Limitations

*   NAT non è sotto il controllo del cliente
    *   Stesso problema del CGN
*   Problematico con i server
    *   Mapping statico e port forwarding non possono essere configurati
*   AFTR mantiene lo stato per-flusso, e deve registrare indirizzo, porta e tempo di ogni sessione per motivi legali

---

## A+P (Address plus Port)

*   NAT è sotto il controllo del cliente
*   Range di porte TCP/UDP sono assegnati a ciascun cliente
*   Solo le porte usate dal NAT all'esterno

![bg 80%](images/page33_img.png)

---

## A+P (continua)

*   Nessun problema con spazi di indirizzi privati sovrapposti presso i clienti
*   Le porte possono essere assegnate automaticamente al CPE usando il Port Control Protocol (PCP) (RFC 6887), o via DHCPv6 (RFC 7598)
*   Il CPE può negoziare più porte in qualsiasi momento
*   AFTR è solo un terminatore di tunnel IPv4-in-IPv6 (IPv6 Next Header = 4; proto-41 è IPv6-in-IPv4)
*   NAT44 non è più necessario nell'AFTR: un binding per cliente (indirizzo IPv6 ↔ indirizzo IPv4 + set di porte), nessuno stato per-flusso

---

## MAP-E and MAP-T: stateless A+P

*   Mapping of Address and Port: MAP-E (RFC 7597, Encapsulation), MAP-T (RFC 7599, Translation)
*   Ogni CPE ottiene un indirizzo IPv4 pubblico condiviso e un set di porte (PSID), entrambi embedded nel suo prefisso IPv6 delegato
*   Il CPE esegue NAT44 nel proprio set di porte; il Border Relay (BR) è stateless, spesso anycast
*   MAP-E: pacchetto IPv4 incapsulato in IPv6 (come in DS-Lite). MAP-T: header IPv4 tradotto in IPv6, quindi l'indirizzo di destinazione IPv6 porta l'indirizzo di destinazione IPv4
*   Nessuno stato per-flusso o per-cliente presso il provider; MAP-E è ampiamente usato in Giappone (es. "v6 Plus")

![bg 90%](images/page35_img.png)

---

## NAT64 + DNS64: Deployment Scenarios

![bg 80%](images/page36_img1.png)
![bg 80%](images/page36_img2.png)

---

## NAT64 + DNS64: Principles

*   Un prefisso IPv6 è dedicato agli indirizzi IPv4 mappati
    *   Well-known o specifico della rete: RFC 6052: well-known 64:ff9b::/96; local-use 64:ff9b:1::/48 (RFC 8215)
*   DNS64 mappa i record A in AAAA usando il prefisso NAT64, solo se il nome non ha un AAAA nativo (DNS64: RFC 6147)
*   Il router NAT64 annuncia il prefisso NAT64 nella rete IPv6 per attrarre traffico verso host IPv4
*   Gli host possono apprendere il prefisso dall'opzione RA PREF64 (RFC 8781) o risolvendo ipv4only.arpa (RFC 7050)
*   Stateful NAT64: RFC 6146; header translation come in SIIT (RFC 7915)

---

## DNS64: Name Resolution

![bg 80%](images/page38_img.png)

*   Well-known or deployment specific prefix (configured on DNS64 and possibly NAT64)

---

## NAT64: Packet Forwarding

**NAT64 (outbound)**

*   Traduce indirizzo IPv6 e pacchetto in IPv4
*   Sceglie un indirizzo IPv4/porta libero dal suo pool
*   Costruisce una entry di sessione NAT

---

## NAT64: Limitazioni

*   Funziona solo quando il DNS è coinvolto
    *   Cioè, vengono usati hostname
    *   Es. non funziona se l'utente specifica direttamente un indirizzo IPv4
    *   Es. `ping 1.2.3.4`
*   Lo stesso quando IPv4 appare in URL e applicazioni IPv4-only: 464XLAT risolve questo (prossima slide)
*   Conflitto con DNSSEC
    *   In DNSSEC il DNS autoritativo firma il record
    *   Ma DNS64 modifica i record: un client validante rifiuta l'AAAA sintetizzato; funziona se il resolver DNS64 valida invece (RFC 6147)

---

## 464XLAT (RFC 6877) and IPv6-only access

*   Risolve i limiti di NAT64/DNS64: IPv4 in URL e applicazioni IPv4-only continuano a funzionare
*   **CLAT** (Lato cliente: telefono, laptop o CPE): traduzione stateless 4-6 (SIIT, RFC 7915) verso il prefisso NAT64
*   **PLAT** (Lato provider): un normale NAT64 stateful
*   Le reti mobili funzionano in questo modo IPv6-only
*   LAN IPv6-maggiore: l'opzione DHCPv4 108 (RFC 8925) dice agli host capaci di saltare IPv4; prefisso NAT64 da RA PREF64 (RFC 8781). Windows 11 CLAT è in distribuzione per Wi-Fi/Ethernet da Settembre 2026

![bg 80%](images/page41_img.png)