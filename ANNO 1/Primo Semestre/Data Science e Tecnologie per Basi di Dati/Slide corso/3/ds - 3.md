---
marp: true
theme: default
paginate: true
---

# Data warehouse Progettazione

Elena Baralis Politecnico di Torino

---

# Fattori di rischio

• Aspettative elevate degli utenti – il data warehouse come soluzione dei problemi aziendali

• Qualità dei dati e dei processi OLTP di partenza – dati incompleti o inaffidabili – processi aziendali non integrati e ottimizzati

• Gestione “politica” del progetto – collaborazione con i “detentori” delle informazioni – accettazione del sistema da parte degli utenti finali

---

# Progettazione di data warehouse

• Approccio top-down – realizzazione di un data warehouse che fornisca una visione globale e completa dei dati aziendali – costo significativo e tempo di realizzazione lungo – analisi e progettazione complesse • Approccio bottom-up – realizzazione incrementale del data warehouse, aggiungendo data mart definiti su settori aziendali specifici – costo e tempo di consegna contenuti – focalizzato separatamente su settori aziendali specifici

---

# Business Dimensional Lifecycle (Kimball)

![Diagramma del Business Dimensional Lifecycle: Pianificazione, Definizione dei requisiti, Progetto dell'architettura, Modellazione dimensionale, Specifica applicazioni utente, Selezione e installazione prodotti, Progettazione fisica, Progettazione e sviluppo alimentazione, Sviluppo applicazioni utente, Attuazione, Manutenzione. Colonne: Tecnologia, Dati, Applicazione. Gestione progetto. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Progettazione di data mart

![Diagramma del processo di progettazione di data mart: schemi delle sorgenti operazionali -> Riconciliazione -> schema riconciliato -> Progettazione concettuale -> schema di fatto -> Progettazione logica -> schema logico -> Progettazione fisica -> schema fisico. requisiti utente, carico di lavoro volume dati modello logico, carico di lavoro volume dati DBMS. Progettazione dell'alimentazione -> schema dell'alimentazione. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Analisi dei requisiti

Elena Baralis Politecnico di Torino

---

# Analisi dei requisiti

## • Raccoglie

– le esigenze di analisi dei dati che dovranno essere soddisfatte dal data mart

– i vincoli realizzativi dovuti ai sistemi informativi esistenti

## • Fonti

– business users – amministratori del sistema informativo

• Il data mart prescelto è – strategico per l’azienda – alimentato da (poche) sorgenti affidabili

---

# Requisiti applicativi

• Descrizione degli eventi di interesse (fatti)

– ogni fatto rappresenta una categoria di eventi di interesse per l’azienda

• esempi: (per il CRM) reclami, servizi

– caratterizzati da dimensioni descrittive (granularità), intervallo di storicizzazione, misure di interesse

– informazioni raccolte in un glossario

• Descrizione del carico di lavoro

– esame della reportistica aziendale

– interrogazioni espresse in linguaggio naturale

• esempio: numero di reclami per ciascun prodotto nell’ultimo mese

---

# Requisiti strutturali

• Periodicità dell’alimentazione • Spazio disponibile – per i dati – per le strutture accessorie (indici, viste materializzate) • Tipo di architettura del sistema – numero di livelli – data mart dipendenti o indipendenti • Pianificazione del deployment – avviamento – formazione

---

# Progettazione concettuale

Elena Baralis Politecnico di Torino

---

# Progettazione concettuale

• Non esiste un formalismo di modellazione comunemente accettato

– il modello ER non è adatto

• Dimensional Fact Model (Golfarelli, Rizzi)

– per uno specifico fatto, definisce schemi di fatto che modellano

• dimensioni

• gerarchie

• misure

– modello grafico a supporto della progettazione concettuale

– offre una documentazione di progetto utile sia per la revisione dei requisiti con gli utenti, sia a posteriori

---

# Dimensional Fact Model

## • Fatto

– modella un insieme di eventi di interesse (vendite, spedizioni, reclami) – evolve nel tempo

## • Dimensione

– descrive le coordinate di analisi di un fatto (ogni vendita è descritta dalla data di effettuazione, dal negozio e dal prodotto venduto)

– è caratterizzata da numerosi attributi, tipicamente di tipo categorico

## • Misura

– descrive una proprietà numerica di un fatto, spesso oggetto di operazioni di aggregazione (ad ogni vendita è associato un incasso)

![Schema DFM: fatto VENDITA con dimensioni data, prodotto, negozio; misure quantità venduta, incasso, num. clienti, prezzo unitario. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Dimensional Fact Model

## • Gerarchia

– rappresenta una relazione di generalizzazione tra un sottoinsieme di attributi di una dimensione (gerarchia geografica per la dimensione negozio)

– è una dipendenza funzionale (relazione 1:n)

![Schema DFM con gerarchie: prodotto -> tipo -> categoria -> gruppo di marketing -> reparto; negozio -> distretto di vendita -> responsabile delle vendite; data -> mese -> trimestre -> anno; data -> settimana -> vacanza -> giorno. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Corrispondenza con l’ER

![Schema ER corrispondente al DFM: REPARTO, GRUPPO MARKETING, CATEGORIA, TIPO, PRODOTTO, MARCA, CITTÀ MARCA, NEGOZIO, RESP. VENDITE, DISTRETTO VENDITA, DATA, ANNO, TRIMESTRE, MESE, VACANZA, GIORNO, SETTIMANA, STATO, REGIONE, CITTÀ. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006. Elena Baralis Politecnico di Torino](image-placeholder)

---

# DFM: costrutti avanzati

![Schema DFM con costrutti avanzati: non-additività, arco opzionale, convergenza, attributo descrittivo, dimensione opzionale. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Aggregazione

• Processo di calcolo del valore di misure a granularità meno fine di quella presente nello schema di fatto originale

– la riduzione del livello di dettaglio è ottenuta risalendo lungo una gerarchia

– operatori di aggregazione standard: SUM, MIN, MAX, AVG, COUNT

• Caratteristiche delle misure

– additive

– non additive: non aggregabili lungo una gerarchia mediante l’operatore di somma

– non aggregabili

---

# Classificazione delle misure

## • Misure di flusso

– possono essere valutate cumulativamente alla fine di un periodo di tempo

– sono aggregabili mediante tutti gli operatori standard

– esempi: quantità di prodotti venduti, importo incassato

## • Misure di livello

– sono valutate in specifici istanti di tempo (snapshot)

– non sono additive lungo la dimensione tempo

– esempi: livello di inventario, saldo del conto corrente

## • Misure unitarie

– sono valutate in specifici istanti di tempo ed espresse in termini relativi

– non sono additive lungo nessuna dimensione

– esempio: prezzo unitario di un prodotto

---

1999 2000 1'99 II'99 III'99 IV'99 I'00 II'00 III'00 IV'00

![Operatori di aggregazione: tabelle che mostrano l'aggregazione da prodotto a categoria/tipo, e da trimestre ad anno. Database and data mining group, Politecnico di Torino. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006. Elena Baralis Politecnico di Torino](image-placeholder)

---

# Operatori di aggregazione

• Distributivi

– sempre possibile il calcolo di aggregati da dati a livello di dettaglio maggiore – esempi: sum, min, max

Elena Baralis Politecnico di Torino

---

1999 1'99 II'99 III'99 IV'99 2 2 2,2 2,5 1,5 1,5 2 2,5 - 3 3 3 1 1,2 1,5 1,5 1,5 1,5 2 - anno 1999 IV'99 II'99 III'99 IV'99 1'99 II'99 III'99 IV'99 1,75 2,17 2,40 2,67 1,25 1,35 1,75 1,50 1,50 1,76 2,08 2,09 anno 1999 trim. I'99 II'99 III'99 IV'99 1,50 1,84 2,14 2,38

![Operatori non distributivi: esempio con media. Database and data mining group, Politecnico di Torino. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006. Elena Baralis Politecnico di Torino](image-placeholder)

Operatori non distributivi

---

# Operatori di aggregazione

## • Distributivi

– sempre possibile il calcolo di aggregati da dati a livello di dettaglio maggiore – esempi: sum, min, max

## • Algebrici

– il calcolo di aggregati da dati a livello di dettaglio maggiore è possibile in presenza di misure aggiuntive di supporto

– esempi: avg (richiede count)

## • Olistici

– non è possibile il calcolo di aggregati da dati a livello di dettaglio maggiore

– esempi: moda, mediana

---

# DFM: costrutti avanzati

![Schema DFM con gerarchia condivisa e ruolo: CHIAMATA con dimensioni uso, distretto, numero telefonico, ora, data, mese, anno. Tratti da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# DFM: costrutti avanzati

![Schema DFM con arco multiplo: VENDITA con dimensioni autore, libro, genere, data, mese, anno. Tratti da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

arco multiplo

![Schema DFM con attributo configurazione: RICOVERO con dimensioni categoria, data, diagnosi, codPaz, nome, cognome, sesso, fascia d'utenza, città, anno nascita, reparto. Tratti da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Attributo configurazione

• Attributo categorico multivalore

– può assumere contemporaneamente più valori

– caratterizzato da pochi valori distinti (<=10)

• Rappresentazione mediante enumerazione dei valori possibili

– ogni attributo assume valore booleano (Y/N)

– consente scrittura più agevole di interrogazioni complesse

![Schema DFM con attributo configurazione: VIDEOGAME_SALES con dimensioni Types of Store (collectable, toys, mangas, accessories), date (holiday, month, dayOfTheWeek, 3M, 2M, year), videogame (company, genre). Attributo configurazione](image-placeholder)

---

# Schemi di fatto vuoti

• L’evento può non essere caratterizzato da misure

– schema di fatto vuoto

– registra il verificarsi di un evento

• Utile per

– conteggio di eventi accaduti

– rappresentazione di eventi non accaduti (insieme di copertura)

![Schema DFM vuoto: FREQUENZA con dimensioni studente (indirizzo, nome, nazionalità, età, sesso), corso (area, facoltà), anno, semestre. Misura (COUNT). Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Rappresentazione del tempo

• La variazione dei dati nel tempo è rappresentata esplicitamente dal verificarsi degli eventi

– presenza di una dimensione temporale

– eventi memorizzati sotto forma di fatti

• Possono variare nel tempo anche le dimensioni

– variazione tipicamente più lenta

• slowly changing dimension [Kimball]

– esempi: dati anagrafici di un cliente, descrizione di un prodotto

– necessario prevedere esplicitamente nel modello come rappresentare questo tipo di variazione

---

# Modalità di rappresentazione del tempo (tipo I)

• Fotografia dell’istante attuale – esegue la sovrascrittura del dato con il valore attuale – proietta nel passato la situazione attuale – utilizzata quando non è necessario rappresentare esplicitamente la variazione – Esempio • il cliente Mario Rossi cambia stato civile dopo il matrimonio • tutti i suoi acquisti sono attribuiti al cliente “sposato”

---

# Modalità di rappresentazione del tempo (tipo II)

• Eventi attribuiti alla situazione temporalmente corrispondente della dimensione

– per ogni variazione di stato della dimensione

• si crea di una nuova istanza nella dimensione

• i nuovi eventi sono correlati alla nuova istanza

– gli eventi sono partizionati in base alle variazioni degli attributi dimensionali

– Esempio

• il cliente Mario Rossi cambia stato civile dopo il matrimonio

• i suoi acquisti sono separati in acquisti attributi a Mario Rossi “celibe” e acquisti attribuiti a Mario Rossi “sposato” (nuova istanza di Mario Rossi)

---

# Modalità di rappresentazione del tempo (tipo III)

• Eventi attribuiti alla situazione della dimensione campionata in uno specifico istante di tempo – proietta tutti gli eventi sulla situazione della dimensione in uno specifico istante di tempo – richiede una gestione esplicita delle variazioni della dimensione nel tempo • modifica dello schema della dimensione – introduzione di una coppia di timestamp che indicano l’intervallo di validità del dato (inizio e fine validità) – introduzione di un attributo che consenta di identificare la sequenza di variazioni di una specifica istanza (capostipite o master) • ogni variazione di stato della dimensione richiede la definizione di una nuova istanza

---

# Modalità di rappresentazione del tempo (tipo III)

## – Esempio

• il cliente Mario Rossi cambia stato civile dopo il matrimonio

• la prima istanza conclude il suo periodo di validità il giorno del matrimonio

• la nuova istanza inizia la sua validità nello stesso giorno

• gli acquisti sono separati come nel caso precedente

• esiste un attributo che permette di ricostruire tutte le variazioni ascrivibili a Mario Rossi

---

# Carico di lavoro

• Carico di riferimento definito da – reportistica standard – stime discusse con gli utenti • Carico reale difficile da stimare correttamente durante la fase di progettazione – se il sistema ha successo, il numero di utenti e interrogazioni aumenta nel tempo – la tipologia di interrogazioni può variare nel tempo • Fase di tuning – dopo l’avviamento del sistema – monitoraggio del carico di lavoro reale del sistema

---

# Volume dei dati

• Stima dello spazio necessario per il data mart – per i dati – per le strutture accessorie (indici, viste materializzate)

• Si considerano

– numero di eventi di ogni fatto

– numero di valori distinti degli attributi nelle gerarchie

– lunghezza degli attributi

• Dipende dall’intervallo temporale di memorizzazione dei dati

• Valutazione affetta dal problema della sparsità

– il numero degli eventi accaduti non corrisponde a tutte le possibili combinazioni delle dimensioni

– esempio: percentuale dei prodotti effettivamente venduti in ogni negozio in un dato giorno pari circa al 10% di tutte le possibili combinazioni

---

# Sparsità

• Si riduce al crescere del livello di aggregazione dei dati • Può ridurre l’affidabilità della stima della cardinalità dei dati aggregati

![Cubi multidimensionali che mostrano la sparsità. Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Progettazione logica

Elena Baralis Politecnico di Torino

---

# Progettazione logica

• Si considera il modello relazionale (ROLAP) – inputs

• schema (di fatto) concettuale

• carico di lavoro

• volume dei dati

• vincoli di sistema

– output

• schema logico relazionale

• Basata su principi diversi rispetto alla progettazione logica tradizionale

– ridondanza dei dati

– denormalizzazione delle tabelle

---

# Schema a stella

## • Dimensioni

– una tabella per ogni dimensione

– chiave primaria generata artificialmente (surrogata)

– contiene tutti gli attributi della dimensione

– gerarchie non rappresentate esplicitamente

• gli attributi della tabella sono tutti allo stesso livello

– rappresentazione completamente denormalizzata

• presenza di ridondanza nei dati

## • Fatti

– una tabella dei fatti per ogni schema di fatto

– chiave primaria costituita dalla combinazione delle chiavi esterne delle dimensioni

– le misure sono attributi della tabella

---

# Schema a stella

![Schema a stella: VENDITE (Quantità, Guadagno) con dimensioni Prodotto (Fornitore, Tipo, Categoria), Negozio (Rappresentante, Città, Stato), Mese (Anno). Tabelle: Mese (ID_Mese, Mese, Anno), Prodotti (ID_Prodotti, Prodotto, Tipo, Categoria, Fornitore), Negozio (ID_Negozio, Negozio, Città, Stato, Rappresentante). Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Snowflake schema

• Separazione di (alcune) dipendenze funzionali frazionando i dati di una dimensione in più tabelle

– si introduce una nuova tabella che separa in due rami una gerarchia dimensionale (taglio su un attributo della gerarchia)

– una nuova chiave esterna esprime il legame tra la dimensione e la nuova tabella

• Si riduce lo spazio necessario per la memorizzazione della dimensione

– riduzione non significativa

• Aumenta il costo di ricostruzione dell’informazione della dimensione

– è necessario il calcolo di uno o più join

---

![Schema snowflake: VENDITE (Quantità, Guadagno) con dimensioni Prodotto (Fornitore, ID_Tipo, Categoria), Negozio (Rappresentante, ID_Città), Mese (Anno). Tabelle: Mese (ID_Mese, Mese, Anno), Prodotti (ID_Prodotti, Prodotto, ID_Tipo, Fornitore), Tipi (ID_Tipo, Tipo, Categoria), Negozio (ID_Negozio, Negozio, ID_Città, Rappresentante), Città (ID_Città, Città, Stato). Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Star o snowflake?

• Lo schema snowflake è normalmente sconsigliato – la riduzione di spazio occupato è scarsamente benefica • l’occupazione maggiore di spazio è dovuta alla tabella dei fatti (la differenza è pari ad alcuni ordini di grandezza) – il costo di eseguire più join può essere significativo • Lo schema snowflake è raramente utilizzato nella progettazione di data mart

---

# Archi multipli

![Schema DFM con arco multiplo: VENDITA con dimensioni autore, libro, genere, data, mese, anno](image-placeholder)

## • Soluzioni realizzative

– bridge table

• tabella aggiuntiva che modella la relazione molti a molti

• nuovo attributo che consenta di pesare la partecipazione delle tuple nella relazione

– push down

• arco multiplo integrato nella tabella dei fatti

• nuova dimensione corrispondente nella tabella dei fatti

---

# Archi multipli

![Schema archi multipli: VENDITA con dimensioni autore, libro, genere, data, mese, anno. Soluzioni: BRIDGE (ID_Libri, ID_Autori, Peso), VENDITE (ID_Libri, ID_Autori, ID_Date, Quantità, Incasso), Libri (ID_Libri, Libro, Genere), Autori (ID_Autori, Autore). Tratto da Golfarelli, Rizzi,"Data warehouse, teoria e pratica della progettazione", McGraw Hill 2006](image-placeholder)

---

# Archi multipli

• Tipologie di interrogazione

– pesate: considerano il peso dell’arco multiplo

• esempio: incasso di ciascun autore

• con bridge table

SELECT ID_AUTORI, SUM(Incasso*Peso)

• •

group by ID_Autorl

– di impatto: non considerano il peso

• esempio: numero di copie vendute per ogni autore

• con bridge table

SELECT ID_Autorl, SUM(Quantità)

• •

group by ID_Autorl

---

# Archi multipli

• Confronto tra le soluzioni realizzative – il peso è esplicitato nella bridge table, ma integrato nella tabella dei fatti per push down • (push down) difficile eseguire interrogazioni di impatto • (push down) calcolo del peso durante l’alimentazione • (push down) modifiche successive difficoltose – push down introduce una forte ridondanza nella tabella dei fatti – costo di esecuzione delle interrogazioni minore per push down • numero minore di join

---

# Dimensioni degeneri

• Dimensioni rappresentate da un solo attributo

![Schema DFM con dimensioni degeneri: LINEA ORDINE (Quantità, Importo) con dimensioni Prodotto, Ordine, Cliente, Città, Modalità Spedizione, Codice ritorno, Stato linea](image-placeholder)

---

# Dimensioni degeneri

• Soluzioni realizzative – integrazione nella tabella dei fatti • per attributi di dimensione (molto) contenuta – junk dimension • unica dimensione che integra più dimensioni degeneri • non esistono dipendenze funzionali tra gli attributi della dimensione – sono possibili tutte le combinazioni – attuabile solo per cardinalità limitate del dominio degli attributi

---

# Junk dimension

![Schema junk dimension: Linea Ordine (ID_Ordini, ID_Prodotti, ID_MCS, Quantità, Importo) con dimensioni Ordine (ID_Ordini, Ordine, Cliente, ID_Città) e MCS (ID_MCS, Modalità Sped., Codice Ritorno, Stato Linea Ordine)](image-placeholder)