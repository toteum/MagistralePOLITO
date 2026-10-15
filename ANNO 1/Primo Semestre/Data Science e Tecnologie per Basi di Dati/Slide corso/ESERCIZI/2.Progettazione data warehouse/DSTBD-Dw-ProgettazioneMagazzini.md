---
marp: true
theme: default
paginate: true
size: 16:9
style: |
  section { font-size: 24px; }
  section.small { font-size: 20px; }
  h1, h2 { color: #1f4e79; }
---

# Esercizio: Progettazione di un data warehouse

Progettare un data warehouse per la gestione delle problematiche illustrate nei punti seguenti relative ai magazzini di una ditta di elettrodomestici italiana con sedi in tutta Italia.

---

<!-- _class: small -->

## Descrizione del problema (1/5)

Una grande ditta di elettrodomestici ha magazzini sparsi in tutta Italia. La dirigenza dell'azienda ha la necessità di analizzare l'attuale uso dei magazzini al fine di capire se e quanto i vari magazzini sono effettivamente utilizzati in funzione della loro dislocazione geografica.

La finalità dell'azienda è quella di decidere quali magazzini ampliare, quali ridimensionare e quali chiudere o affittare, anche solo parzialmente, a terze parti.

---

<!-- _class: small -->

## Descrizione del problema (2/5)

La dirigenza della ditta stipula periodicamente delle polizze assicurative per coprire i danni dei furti che si verificano nei magazzini. I prezzi delle polizze contro i furti sono legati alla quantità media giornaliera di prodotti presenti nei magazzini e al loro valore.

Esistono diverse tipologie di polizze e la dirigenza vuole capire quali sono le polizze più adeguate per i propri magazzini analizzando quali modelli di prodotti e in quali quantità sono mediamente presenti a livello giornaliero nei magazzini.

Alcune polizze sono specifiche per un singolo magazzino mentre altre sono relative ad insiemi di magazzini che si trovano nella stessa città, regione o provincia.

---

## Descrizione del problema (3/5)

I premi assicurativi delle polizze sono calcolati considerando, su base media giornaliera:

- il numero di prodotti presenti nei magazzini per ogni modello di prodotto presente
- il valore dei prodotti presenti nei magazzini per ogni modello di prodotti

Viste le problematiche appena descritte la ditta ha deciso di creare un apposito data warehouse per gestire le informazioni relative all'uso dei magazzini e al loro contenuto.

---

<!-- _class: small -->

## Descrizione del problema (4/5)

**Analisi dell'uso dei magazzini (superficie utilizzata)**

La dirigenza è interessata ad analizzare la percentuale giornaliera di superficie libera rispetto alla superficie totale disponibile in ogni magazzino in funzione del magazzino e del luogo in cui esso si trova (città, provincia, regione).

La superficie totale disponibile per ogni magazzino può variare di giorno in quanto alcune aree dei magazzini possono essere affittate a terzi o essere temporaneamente inagibili (queste aree non fanno parte della superficie totale disponibile).

L'analisi deve essere possibile a livello di singola data, ma anche a livello di mese, trimestre, quadrimestre, semestre e anno.

---

<!-- _class: small -->

## Descrizione del problema (5/5)

**Stima dei costi delle polizze assicurative**

La ditta deve poter analizzare il numero medio giornaliero di prodotti presenti nei magazzini e il loro valore complessivo giornaliero a livello di singola data, a livello di mese, di trimestre, quadrimestre, di semestre e di anno.

Tali informazioni devono essere disponibili in funzione del modello dei prodotti e della loro categoria (scopa elettrica, impastatrice, ..), del magazzino e del luogo in cui si trova (città, provincia, regione).

---

<!-- _class: small -->

## Interrogazioni frequenti (a, b, c)

Alcune delle interrogazioni frequenti di interesse per la dirigenza:

**a)** Relativamente al primo trimestre dell'anno 2013, considerando solo i magazzini della città di Torino, trovare per ogni coppia (magazzino, data) il valore complessivo di prodotti presenti in tale data nel magazzino e il valore complessivo medio giornaliero di prodotti presenti nel magazzino nel corso della settimana precedente la data in esame (data in esame inclusa).

**b)** Relativamente all'anno 2004, trovare per ogni coppia (città, data) la percentuale di superficie libera giornaliera nella città. Associare ad ogni coppia un attributo di rank legato alla percentuale di superficie libera giornaliera nella città (1 per la coppia con la più bassa percentuale di superficie libera giornaliera).

**c)** Relativamente ai primi sei mesi dell'anno 2014, trovare per ogni coppia (magazzino, data) la percentuale di superficie libera giornaliera.

---

## Interrogazioni frequenti (d, e, f)

**d)** Relativamente all'anno 2013, trovare per ogni coppia (magazzino, mese) il valore complessivo medio giornaliero di prodotti presenti.

**e)** Relativamente all'anno 2015, trovare per ogni regione il valore complessivo medio giornaliero di prodotti presenti nella regione.

**f)** Relativamente all'anno 2014, trovare per ogni coppia (mese, regione) la percentuale di superficie libera giornaliera nella regione.

---

## Progettazione

**1.** Progettare il data warehouse necessario per gestire le necessità della ditta di elettrodomestici in modo da soddisfare le richieste descritte nelle specifiche del problema.

Il data warehouse progettato deve inoltre permettere di rispondere in modo efficiente a tutte le interrogazioni frequenti proposte nelle specifiche del problema.

---

## Dati per la realizzazione

Il data warehouse realizzato deve contenere le informazioni relative agli **ultimi 10 anni**. Informazioni fornite:

| Elemento | Numero |
|---|---|
| Modelli diversi di prodotti | ~100 |
| Categorie diverse di prodotti | ~10 |
| Magazzini | ~500 |
| Magazzini di Torino | ~5 |
| Città | ~200 |
| Regioni | ~20 |
| Province | ~90 |

---

## Progettazione (punti 2 e 3)

**2.** Esprimere tutte le interrogazioni utilizzando il linguaggio SQL esteso.

**3.** Definire la vista materializzata che potrebbe essere utilizzata per rispondere efficientemente a tutte le seguenti interrogazioni:

---

<!-- _class: small -->

## Interrogazioni per la vista materializzata

- Relativamente al primo semestre degli anni 2015 e 2016, considerando solo i magazzini nella regione Piemonte, trovare per ogni coppia (provincia del magazzino, mese) il valore complessivo di prodotti presenti e il relativo numero.

- Relativamente all'anno 2013, trovare per ogni provincia del magazzino e semestre il valore medio mensile di prodotti.

- Relativamente all'anno 2014, trovare per ogni regione del magazzino e trimestre il valore complessivo di prodotti presenti nella regione.
