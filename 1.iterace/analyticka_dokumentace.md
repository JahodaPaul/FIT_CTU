#### TODO
- Přepsat bod 3.1.2 do češtiny ( tohle se tváří jako čeština, ale nejde to pochopit )
- Pokuste se rozvést UC 4.2.1 - 4.2.4



# 3\. Model požadavků
Tato kapitola obsahuje požadavky kladené na nově vznikající hru. Požadavky jsou rozděleny na funkční a nefunkční.


## 3.1 Funkční požadavky

### 3.1.1 Ovládání běhu hry
Hráč bude moci ovládat běh hry. Tento aspekt hry bude zpřístupněný pomocí funkcionalit, které umožní začít novou hru, ukončit hru, uložit a načíst hru a hru pozastavit.

### 3.1.2 Ovladání herní postavy a interakce s herním světem
Hráč bude moci ovládat herní postavu. Ovládání herní postavy úzce souvisí s požadavkem na interakci s herním světem, jelikož akce herní postavy můžu vyvolat interakci s tímto světem.
Tato rozsáhlejší funkce hry bude umožněna pohybem (pohyb herní postavy napříč herní místností a přesun herní postavy mezi jednotlivými místnostmi).  

Dále hráč bude mít možnost útočit na nepřátele.  

Herní postava bude mít možnost sbírat předmět (přepdměty se mohou oběvit po zabití nepřítele, nebo ležet v místnosti hry již od jejího vygenerování ). Tyto předměty půjdou prodat NPC obchodníkovi za využití herního obchodu.

### 3.1.3 Správa inventáře herní postavy
Hráč bude moci otevřít/uzavřít inventář postavy. Uvnitř inventáře bude mít zobrazané všechny předměty, které aktuálně vlastní. Všechny ředměty bude moct hráč z inventáře zahodit na zem. Vybrané předmětu půjdou aktivně využít (např.: lektvar léčení), nebo obléknout ( nová zbroj ).

### 3.1.4 Vylepšení herní postavy
Hra bude hráči umožňovat vylepšit jeho postavu. Toto bude umožněno prodejem/výměnou herních surovin s NPC obchodníkem a následním nakoupením lepší výbavy.  Herní suroviny se budou nacházat volně na mapě, také je bude možné získat poražením nepřátel.

### 3.1.5 Nastavení hry
Nastavení hry bude rozděleno do dvou kategorií.

1. Nastavení při zahájení nové hry.
  - Při startu nové hry si hráč zvolí jméno postavy, její vyhled a obtížnost hry.
2. Globální nastavení
  - V hlavním menu bude možné kdykoli v průběhu hraní nastavit parametry hry. Například nastavit rozlišení, hlasitost, nebo zapnout/vypnout hudbu.

### 3.1.6 Přístup do informační sekce hry
Hra umožní zobrazovat statistiky o postavě ( množství poražených nepřátal, celkem vyléčených životů...) Dále si hráč během hry bude moci zobrazit statickou herní nápovědu. Některé předměty také budou mít interaktivní nápovědu, která se zobrazí po najetí myši na předmět v inventáři.  

Další informační prvkek bude minimapa. Minimapa bude obsahovat všechy čássti herní mapy, které již hráč navšívil.

## 3.2 Nefunkční požadavky

### 3.2.1 N1 -  Grafické uživatelské rozhraní  
  Hra bude mít 2D grafiku s pohledem zeshora. Ovládání bude bude umožněno primárně s pomocí klávesnice.

### 3.2.2 N2 - Žánr hry
  Hra bude real-time RPG s důrazem na obchod a směnu zboží a předmětů s herními postavami.

### 3.2.3 N3 - Cílová platforma
Hra bude plně funkční na PC pod operačním systémem linux. Instalace bude umožněna pomocí .deb instalační systému. ( debian )

### 3.2.4 N4 - Jazyk hry
Hra bude v anglickém jazyce ( dialogy, předměty, menu...).


# 4\.  Model Případů užití
V táto kapitole jsou popsány případy užití v herních mechanismů hráčem. Tyto funcionality souvisejí především s:
- Řízením běhu samotné hry (zde lze pro příklad uvést start nebo konec hry, herní pauzu atp.).
- Manipulací s herními objekty (například pohyb herní postavy, sbírání předmětů, užití předmětů, útok na nepřítele atp.).
- Prací s herním rozhraním (například zobrazení inventáře, zobraní mapy, vyvolání obchodu, vyvolání nápovědy, nastavení atp.).

Dále tato kapitola obsahuje popis všech účastníků.

## 4.1 Účastníci
Tato kapitola obsahuje popis účastníka, který bude hru hrát.

### 4.1.1 Hráč
Osoba pohybující se v rozhraní hry a ovládající herní postavu. Hráč využívá funkcionalit poskytovaných hrou.

## 4.2 Případy užití

### 4.2.1 Spuštění/ukončení hry
Hráč bude moci zapnout a následovně i vypnout hru.

### 4.2.2 Pohyb
Hráč se bude pohybovat po mapě pomocí šipek. Bude se moci pohybovat pravoúhle i diagonálně.

### 4.2.3 Útok
Hráč bude moci vystřelit střelu, která bude zranovat nepřítele.

### 4.2.4 Sbírání předmětů
Hráč bude moci sebrat předmět nacházející se v místnosti.

### 4.2.5 Otevření/zavření inventáře
Hráč bude moci otevírat či zavírat inventář, přičemž v inventáři mu bude k dispozici seznam předmětů, které má hráč u sebe. Některé předměty bude možné interaktivně využít.

### 4.2.6 Použití předmětu
Hráči bude umožněno použít některé z předmětů přítomných v inventáři.

### 4.2.7 Zahození předmětu
Hráči bude umožněno zahodit předmět z inventáře.

### 4.2.8 Obchodnovat s NPC
Hráč bude moci vstoupit do dialogu obchodu s NPC postavou nacházející se v herní místnosti.

### 4.2.9 Zobrazení statistik postavy
Hráči bude umožněno zobrazit si statistiky herní postavy.

### 4.2.10 Zobrazení mapy
Hráči bude umožněno zobrazit mapu herních místností s vyznačením jeho aktuální polohy.

### 4.2.11 Pozastavení/pokračovaní hry
Hráč bude moci hru pozastavit a následně se do hry navrátit.

### 4.2.12. Uložení hry
Hráč bude moci uložit herní postup. Tato funkcionalita bude založena na principu jediné uložitelné pozice, která bude v případě smrti herní postavy vymazána.

### 4.2.13 Načtění hry
Hráč bude moci načíst herní postup. Tato funkcionalita bude založena na principu, kdy se uložená hra po načtení vymaže (z důvodu zamezení zkoumání neznámých předmětů stylem uložení/načtení).

### 4.2.14 Nastavení hry
Hráči bude umožněno změnit nastavení hry. Jedná se například o změnu obtížnosti hry, změnu rozlišení herního okna atp..

### 4.2.15 Zobrazení statické nápovědy
Hráč si bude moci kdzkoliv v průběhu hry zobrazit nápovědu, ta bude obsahovat informaci vztahující se ke hře globálně. Například ovládání, nebo legendu k minimapě.

### 4.2.16 Nejvyšší skóre
Hráči bude umožněno zobrazit seznam svých nejlepších dosažených výsledků.
