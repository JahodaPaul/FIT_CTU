# 1 Návrh Architektury
Architektura aplikace bude fungovat jako MVC(Model-View-Controler). Vybrali jsme tuto architekturu protože rozděluje aplikaci do tří komponent.
-Model ( správa dat, fyzical engine )
-View ( vykreslení herních objektů, uživatelské rozhraní )
-Controller ( řídící logika, v našem případě je kontroler velice tenktý a v zásadě jen spojuje View a model )
Hlavní výhody které do našeho projektu architektura MVC přináší je snadná práce v teamu. Programátoři kteří pracují
na prezenční vrstvě nemusejí nijak znát logiku hry a strukturu dat, stačí jim pouza znát navržené rozhraní a implementovat vůči němu.
Déle nám také architektura umožňuje jednoduše vyměnit prezenční vrstvu ( například přejít na jinou grafickou knihovnu )

Pro lepší představu je architektura MVC znázorněna na následujícím obrázku.
TODO přidat obrázek

## 1.1 Prezentační vrstva - View
View je komponenta, která dostává data z modelu a zobrazuje je uživateli. Dále také zpracováva  vstupy od uživatele a na jejich základě
volá metody Controleru. View je dále rozdělen do "Scén", příkladem takové scény je například herní menu, nebo vlastní herní obrazovka.

## 1.2 Datová vrstva - Model
Model reprezentuje veškará data herního světa a mimo to se i stará a fyzický engine hry ( například kolize ). Model je v našem návrhu
plně nezávslý na zbylých dvou komponentách a komunikace s ním probíhá na základě předem definovaného rozhraní. Model bude také umožňovat
ukládání respektive načítání hry.

## 1.3 Controller
Controller primárně zajištǔje komunikaci mezi prezenční a datovou vrstou, v našem návrhu je velice "tenký".

# 2 Volba knihoven
Pro implementování aplikace jsme se rozhodli použít tyto technologie:

- Správa buildů -> Cmake
- Grafická knihovna -> sfml
- Grafické uživatelské rozhraní -> dear imgui
- Fyzika a kolize -> Box2D

Kombinace těchto knihoven můžu v budoucnu umožnit jednoduchý přenos aplikace na jiný operační systém ( zatím je podporován je Linux ),
protože všechny námi zvolené knihovny jsou plně multiplatformní (linux|MacOS|Windows|Android...)  Samozřejmě by například
pro impementaci na andriod bylo potřeba změnit uživatelské vstupy, to by ale díky plně izolované prezenční vrstvě neměl být velký problém.

# 2.1 build systém
Jako software na správu buildů jsme zvolili CMake. S nástrojem CMake již byli v našem týmu částěnčné skušenosti, plně
splňuje všechny naše požadavky na build systém a v současnoti je to pro větší projekty v C++v zásadě standard.

# 2.2 grafická knihovna
Jako grafické knihovny jsme zvažovali SDL2 a SFML. Obě dvě knihovny nabízejí velice podobné možnosti, ale s přihlédnutím
k jednodušímu používání a lepší dokumentaci jsme nakonec zvolily SFML.

# 2.3 grafické uživatelské rozhraní
Vzhledem k tomu, že pro naši hru není uživatelské rozhraní příliš velká priorita jsme volili GUI s větším důrazem na jednoduchost
použití. Dear imgui je takzvaná imediate gui library, to znamené že jednotlivé prcky rozhraní jsou v zásadě bezestavové a je
nutné je neustále znovu updatovat a vykreslovat ( i přesto je knihovna velice efiktivní z pohledu  využití procesoru ). Tato
její vlastnost pro nás ovšem není žádná překažka, protož naše hra je real time, tudíž zde bude probáhat mnoho updatů za sekundu.  

Naopak přínosem této knihovny je její extrémně jednoduché používání a i zapojení do projektu. Celá knihovna se v zásadě skládá
ze sdvou souborů a bindingu a aby ji bylo možné použív v SFML.

# 2.4 Fyzickal engine
Hra má být 2D a to bylo také jedno z klíčových kritérijí na fyzikal engine. V sočasnosti sice takových knioven pro c++ existuje množství,
ale Box2D je pravděpodobně nejlepší z nich a má velice kvalitní dokumentaci a tutorály, vybrali jsme tudíž tu.
