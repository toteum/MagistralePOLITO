---
marp: true
theme: default
paginate: true
---

# Data science The Big Data challenge

ELENA BARALIS POLITECNICO DI TORINO

![D B G M logo and Politecnico di Torino seal](image-placeholder)

---

## Big data hype?

![Word cloud 1](image-placeholder)

![Word cloud 2](image-placeholder)

---

## Emergency management

![Diagram showing Earth Observations, Unmanned Aerial Vehicles, Historical Data, Seasonal Weather Forecast, and Social Media Data Streams feeding into a data center. Text: Improving Resilience to Emergencies Through Advanced Cyber Technologies. Logo: IREACT](image-placeholder)

---

## Emergency management

![Diagram showing First Responders and Decision Makers, Citizens, and a data center with maps and social media streams. Text: Improving Resilience to Emergencies Through Advanced Cyber Technologies. Logo: IREACT](image-placeholder)

---

## 2005 2013

![Crowd in 2005](image-placeholder)

![Crowd in 2013 with smartphones](image-placeholder)

---

## Who generates big data?

**User Generated Content (Web & Mobile)**

E.g., Facebook, Instagram, Yelp, TripAdvisor, Twitter, YouTube

![Mobile devices and social media bandwagon](image-placeholder)

**Health and scientific computing**

![Microscope, telescope, and scientific equipment](image-placeholder)

---

## Who generates big data?

**Log files**

Web server log files, machine syslog files

**Internet Of Things**

Sensor networks, RFID, smart meters

![Satellite, sensor network, smart meter, and ocean sensor networks](image-placeholder)

---

## What is big data?

![Dilbert comic strip about big data](image-placeholder)

Many different definitions

"Data whose scale, diversity and complexity require new architectures, techniques, algorithms and analytics to manage it and extract value and hidden knowledge from it"

---

## What is big data?

![Dilbert comic strip about big data](image-placeholder)

Many different definitions

"Data whose scale, diversity and complexity require new architectures, techniques, algorithms and analytics to manage it and extract value and hidden knowledge from it"

---

## What is big data?

![Dilbert comic strip about big data](image-placeholder)

Many different definitions

"Data whose scale, diversity and complexity require new architectures, techniques, algorithms and analytics to manage it and extract value and hidden knowledge from it"

---

## What is big data?

![Dilbert comic strip about big data](image-placeholder)

Many different definitions

"Data whose scale, diversity and complexity require new architectures, techniques, algorithms and analytics to manage it and extract value and hidden knowledge from it"

---

## The Vs of big data: Volume

Data volume increases exponentially over time

44x increase from 2009 to 2020 Digital data 35 ZB in 2020

![A Tidal Wave of Data infographic showing Twitter 8 TB per day, Facebook 100 TB per day, Global Businesses 1.8 ZB in 2011, US Library of Congress 235 TB, Wal-Mart 2.5 PB stored, Boeing 640 TB per flight](image-placeholder)

![The Digital Universe 2009-2020: Growing By A Factor Of 44. 2009: 0.8 Zb, 2020: 35.2 Zettabytes. Source: IDC Digital Universe Study, sponsored by EMC, May 2011. Tweets per day graph](image-placeholder)

---

## 100,000 571 websites created 684,478 47,000 shared items downloaded online 1 ONE App SECOND ON THE INTERNET 8 2 Mill 3,600 searches photos shared You Tube 48 h $ 272,000 video uploaded spent online

http://www.internetlivestats.com/

---

## Weather forecast

![World Meteorological Organization map for January 2020](image-placeholder)

![World Meteorological Organization map for May 2020](image-placeholder)

---

## The Vs of big data: Velocity

Fast data generation rate Streaming data

Very fast data processing to ensure timeliness

![Velocity infographic: The New York Stock Exchange captures 1 TB of trade information during each trading session. By 2016, it is projected there will be 18.9 billion network connections - almost 2.5 connections per person on earth. Modern car 100 sensors that monitor fuel level a](image-placeholder)

![Speedometer with very high velocities](image-placeholder)

---

## (Near) Real time processing

![Crowdsourcing: highway with mobile devices](image-placeholder)

![Computing: data center servers](image-placeholder)

![Map data: city map](image-placeholder)

![Sensing: Wireless Sensor Networks on a highway](image-placeholder)

![Real time traffic info: map with live traffic](image-placeholder)

---

## The Vs of big data: Variety

Various formats, types and structures

Numerical data, image data, audio, video, text, time series

![Various data formats including heatmap, time series graph, social media logos, and network graph](image-placeholder)

A single application may generate many different formats

---

## The Vs of big data: Veracity

Data quality

![Magnifying glass over numbers](image-placeholder)

Reliability Accuracy Currency Comparability Scope Precision Relevance Effectiveness Quantitativeness Interpretability Understandability Usefulness Usableness Clarity Content Importance

---

## The most important V: Value

**Translate data into business advantage**

![Big data: value potential index scatter plot. Example: US economy. Size of bubble indicates relative contribution to GDP. Big data: ease-of-capture index vs contribution to GDP. High: Utilities, Natural resources, Manufacturing, Health care providers, Computers and other electronic products, Information, Finance and insurance, Professional services, Transportation and warehousing, Real estate, Management of companies, Wholesale trade, Accommodation and food, Construction, Administrative services, Retail trade, Other services, Educational services, Arts and entertainment, Government. Low: Big data: value potential index](image-placeholder)

---

## Big data challenges

**Technology & infrastructure**

New architectures, programming paradigms and techniques Transfer the processing power to the data

Apache Hadoop/Spark ecosystem

**Data management & analysis New emphasis on "data"**

![Yellow elephant logo](image-placeholder)

Data science

---

# Data science

"Extracting meaning from very large quantities of data"

![Data science mind map: Statistic, Visualisation, Data Mining, Database Data process, Neuroscience, Machine Learning, Pattern recognition](image-placeholder)

![D.J. Patil](image-placeholder)

D.J. Patil coined the word data scientist

---

## The data science process

![Data science process diagram: Real World -> Observe, Gather -> Raw Data -> Process -> Clean Data -> Apply ML, Stats -> Model -> Summarize, Communicate, Build -> Data Product -> Decide, Interact](image-placeholder)

**AKA KDD process**
Knowledge Discovery in Databases

![KDD process diagram: Data -> Selection -> Target data -> Preprocessing -> Preprocessed data -> Transformation -> Transformed data -> Data mining -> Patterns/Models -> Interpretation/Evaluation -> Knowledge](image-placeholder)

**Generation -> Acquisition -> Storage -> Analysis**

![Politecnico di Torino, SD, DBG logos](image-placeholder)

---

## Generation

- Passive recording- Typically structured data- Bank trading transactions, shopping records, government sector archives
- Active generation- Semistructured or unstructured data- User-generated content, e.g., social networks
- Automatic production- Location-aware, context-dependent, highly mobile data- Sensor-based Internet-enabled devices (IoT)

![Generation -> Acquisition -> Storage -> Analysis arrows](image-placeholder)

---

## Acquisition

Collection - Pull- based, e.g., web crawler - Push- based, e.g., video surveillance, click stream

Transmission - Transfer to data center over high capacity links

Preprocessing - Integration, cleaning, redundancy elimination

![Generation -> Acquisition -> Storage -> Analysis arrows](image-placeholder)

---

## Storage

Storage infrastructure

Storage technology, e.g., HDD, SSD Networking architecture, e.g., DAS, NAS, SAN

Data management

File systems (HDFS), key- value stores (Memcached), column- oriented databases (Cassandra), document databases (MongoDB)

Programming models

Map reduce, stream processing, graph processing

![Generation -> Acquisition -> Storage -> Analysis arrows](image-placeholder)

---

## Analysis

Objectives

Descriptive analytics, predictive analytics, prescriptive analytics

Methods

Statistical analysis, machine learning and data mining, text mining, network and graph data mining

Association analysis, classification and regression, clustering

Diverse domains call for customized techniques

![Generation -> Acquisition -> Storage -> Analysis arrows](image-placeholder)

---

## Machine learning and data mining

Non trivial extraction of

implicit previously unknown potentially useful

information from available data

Extraction is automatic

performed by appropriate algorithms

Extracted information is represented by means of abstract models

denoted as pattern

---

## Example: profiling

Consumer behavior in e- commerce sites Selected products, requested information, ...

Search engines and portals

Query keywords, searched topics and objects

Social network data

Profiles (Facebook, Instagram, ...)

Dynamic data: posts on blogs, FB, tweets

Maps and georeferenced data

Localization, interesting locations for users

![Google, Yahoo, Instagram, Twitter, Foursquare, Google Maps logos](image-placeholder)

---

## Example: profiling

- User/service profiling- Recommendation systems, advertisements
- Market basket analysis
- Correlated objects for cross selling- User registration, fidelity cards
- Context-aware data analysis
- Integration of different dimensions- E.g., location, time of the day, user interest
- Text mining
- Brand reputation, sentiment analysis, topic trends

---

## Example: biological data

Microarray

expression level of genes in a cellular tissue various types (mRNA, DNA)

Patient clinical records personal and demographic data exam results

Textual data in public collections heterogeneous formats, different objectives scientific literature (PUBMed) ontologies (Gene Ontology)

![Microarray image, table of patient data, PubMed and Gene Ontology logos](image-placeholder)

---

# Biological analysis objectives

## Clinical analysis

detecting the causes of a pathology

monitoring the effect of a therapy

diagnosis improvement and definition of new specific therapies

## Bio-discovery

gene network discovery

analysis of multifactorial genetic pathologies

## Pharmacogenesis

lab design of new drugs for genic therapies

![Protein structure and molecule images](image-placeholder)

---

## Knowledge Discovery Process

![KDD process diagram: data -> selection -> selected data -> preprocessing -> preprocessed data -> transformation -> transformed data -> machine learning/data mining -> pattern -> interpretation -> knowledge](image-placeholder)

KDD = Knowledge Discovery from Data

knowledge

---

## Preprocessing

![Preprocessing diagram: selected data -> preprocessing -> preprocessed data](image-placeholder)

**data cleaning**
- reduces the effect of noise
- identifies or removes outliers
- solves inconsistencies

**data integration**
- reconciles data extracted from different sources
- integrates metadata
- identifies and solves data value conflicts
- manages redundancy

Real world data is "dirty" Without good quality data, no good quality pattern

---

# A word from practitioners

At least 80- 90% of their work involves not machine learning, but - Working with experts to understand the domain, assumptions, questions - Trying to catalog and make sense of the data sources - Wrangling, extracting, and integrating the data - Cleaning the wrangled data

---

## Association rules

**Objective**

- extraction of frequent correlations or pattern from a transactional database

Tickets at a supermarket counter

| TID | Items |
|-----|-------|
| 1 | Bread, Coke, Milk |
| 2 | Beer, Bread |
| 3 | Beer, Coke, Diapers, Milk |
| 4 | Beer, Bread, Diapers, Milk |
| 5 | Coke, Diapers, Milk |
| ... | ... |

![Sign: baby needs beers & wines](image-placeholder)

**Association rule**

diapers \(\Rightarrow\) beer

2% of transactions contains both items

30% of transactions containing diapers also contain beer

---

## Association rules

![Cartoon: Customers who bought this item also bought bananas](image-placeholder)

![Oxford Dictionary cross-sell](image-placeholder)

![Shopping basket](image-placeholder)

![Netflix recommendations](image-placeholder)

![LinkedIn jobs you may be interested in](image-placeholder)

---

## Classification

**Objectives**

prediction of a class label

definition of an interpretable model of a given phenomenon

![Classification diagram: training data -> model -> unclassified data -> classified data](image-placeholder)

---

## Classification

![CNN architecture diagram for depth image classification](image-placeholder)

![Person classification: Staff, Marie Williams, Visitor, Contractor, Pedro Luis de Souza](image-placeholder)

![Bird and frog detection](image-placeholder)

![Person, Car, Motorcycle, Helmet detection](image-placeholder)

---

## Clustering

Objectives

detecting groups of similar data objects

identifying exceptions and outliers

---

## Clustering

Objectives

detecting groups of similar data objects

identifying exceptions and outliers

![Clustering diagram with circles, triangles, and squares](image-placeholder)

![Clustering of U, S, A, and other letters](image-placeholder)

---

## Clustering

![Clustering of animal images](image-placeholder)

![Clustering of fish](image-placeholder)

![Heatmap of gene expression clustering for Human and Mouse](image-placeholder)

---

# Other data mining techniques

## Sequence mining

ordering criteria on analyzed data are taken into account

example: motif detection in proteins

![DNA motif detection](image-placeholder)

## Time series and geospatial data

temporal and spatial information are considered

example: sensor network data

![Coastal map and sensor network](image-placeholder)

## Regression

prediction of a continuous value

example: prediction of stock quotes

![Stock quote graph](image-placeholder)

## Outlier detection

example: intrusion detection in network traffic analysis

---

# The data science process

What question are you answering? What is the right scope of the project? What data will you use? What techniques are you going to try? How will you evaluate your result? What maintenance will be required?

---

## The data science recipe

Different ingredients needed Data expert Data processing, data structures Data analyst Data mining, statistics, machine learning Visualization expert Visual art design, storytelling skills Domain expert Provide understanding of the application domain Business expert Data driven decisions, new business models

![Recipe book](image-placeholder)

![Modern Data Scientist infographic: Math & Statistics, Programming & Database, Domain Knowledge & Soft Skills, Communication & Visualization](image-placeholder)

---

## Open issues

Social impact of analysis is very important

Interpretability and transparency of the analysis process

Bias in algorithms and data

Privacy preservation

---

# Interpretability in machine learning

"The ability to explain or to present in understandable terms to a human"

![Black box being opened with a magnifying glass](image-placeholder)

![Scale balancing accuracy and interpretability](image-placeholder)

Trade- off Accuracy- Interpretability

Open the black box

Model explanation: global understanding of how a model works

Prediction explanation: local understanding of why a prediction is made

Interpretable feature selection: incorporating interpretability- based criteria into the model design

---

## Interprettability

Learned decision rule in pneumonia patients dataset from USA hospital

history of asthma \(\rightarrow\) lower chance of dying from pneumonia

MD consider asthma as a serious risk factor for people who get pneumonia

Analysis

asthmatics probably notice earlier the symptoms of pneumonia

a healthcare professional is going to provide earlier pneumonia diagnosis

as high- risk patients, they're going to get high- quality treatment sooner than other people

asthmatics actually have almost half the chance of dying of non- asthmatics

Using a neural network, this model issue would never have been uncovered

---

# Algorithmic and data bias

Task: predict likelihood of an individual committing a future crime - Risk scores used by US criminal justice system

Scores computed from - Questions answered by the defendants - Information pulled by criminal records

Race was not among the questions - ... however other items may be correlated (e.g., poverty, joblessness)

Software product flagged black defendants as future criminals more frequently than white defendants

Training data was biased by a larger black defendant population

---

## Privacy

![Stravа Labs Global Heatmap, The Guardian article: Fitness tracking app Strava gives away location of secret US army bases, and article: Fitness app Strava lights up staff at military bases](image-placeholder)

---

## Open issues

- Social impact of analysis is very important- Interpretability and transparency of the analysis process- Privacy preservation
- Many technical issues are not solved
- Scalability to huge data volumes
- Data dimensionality
- Complex data structures, heterogeneous data formats
- Data quality
- Streaming data