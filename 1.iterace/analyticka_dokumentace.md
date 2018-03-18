# 3\. Model požadavků
Tato kapitola obsahuje požadavky kladené na nově vznikající hru. Požadavky jsou rozděleny na funkční a nefunkční.

## 3.1 Případy užití
Tato kapitola obsahuje případy užití v herním mechanismu. Tyto funcionality souvisejí s:
- Řízením běhu samotné hry (zde lze pro příklad uvést start nebo konec hry, herní pauzu atp.).
- Manipulací s herními objekty (například pohyb herní postavy, sbírání předmětů, užití předmětů, útok na nepřítele atp.).
- Prací s herním rozhraním (například zobrazení inventáře, zobraní mapy, vyvolání obchodu, vyvolání nápovědy, nastavení atp.).

### 3.1.1 Spuštění/ukončení hry
Hráč bude moci zapnout a následovně i vypnout hru.

### 3.1.2 Pohyb
Hráč se bude pohybovat po mapě pomocí šipek. Bude se moci pohybovat pravoúhle i diagonálně.

### 3.1.3 Útok
Hráč bude moci vystřelit střelu, která bude zranovat nepřítele.

### 3.1.4 Sbírání předmětů
Hráč bude moci sebrat předmět nacházející se v místnosti.

### 3.1.5 Otevření/zavření inventáře
Hráč bude moci otevírat či zavírat inventář, přičemž v inventáři mu bude k dispozici seznam předmětů, které má hráč u sebe. Některé předměty bude možné interaktivně využít.

### 3.1.6 Použití předmětu
Hráči bude umožněno použít některé z předmětů přítomných v inventáři.

### 3.1.7 Zahození předmětu
Hráči bude umožněno zahodit předmět z inventáře.

### 3.1.8 Obchodnovat s NPC
Hráč bude moci vstoupit do dialogu obchodu s NPC postavou nacházející se v herní místnosti.

### 3.1.9 Zobrazení statistik postavy
Hráči bude umožněno zobrazit si statistiky herní postavy.

### 3.1.10 Zobrazení mapy
Hráči bude umožněno zobrazit mapu herních místností s vyznačením jeho aktuální polohy.

### 3.1.11 Pozastavení/pokračovaní hry
Hráč bude moci hru pozastavit a následně se do hry navrátit.

### 3.1.12. Uložení hry
Hráč bude moci uložit herní postup. Tato funkcionalita bude založena na principu jediné uložitelné pozice, která bude v případě smrti herní postavy vymazána.

### 3.1.13 Načtění hry
Hráč bude moci načíst herní postup. Tato funkcionalita bude založena na principu, kdy se uložená hra po načtení vymaže (z důvodu zamezení zkoumání neznámých předmětů stylem uložení/načtení).

### 3.1.14 Nastavení hry
Hráči bude umožněno změnit nastavení hry. Jedná se například o změnu obtížnosti hry, změnu rozlišení herního okna atp..

### 3.1.15 Zobrazení nápovědy
Hráči bude umožněno vyvolat. Zde dvě možnosti: (!!! CHECK !!!)
- 1) Statická nápověda vztahující se ke hře globálně - např. ovládání.
- 2) Zobrazovat kontextové nápovědy vztahující se vždy ke konkrétnímu již známému objektu.

### 3.1.16 Nejvyší skóre
Hráči bude umožněno zobrazit seznam svých nejlepších dosažených výsledků.

## 3.2 Funkční požadavky

#### 3.2.1 Vylepšení postavy
Hra bude umožňovat vylepši svoji postavu. Toto bude umožněno prodejem/výměnnou herních surovin s NPC obchodníkem. Herní suroviny se budou nacházat volně na mapě, také je bude možné získat poražením nepřátel.

#### 3.2.2


## 3.3 Nefunkční požadavky

#### 3.3.1 N1 -  Grafické uživatelské rozhraní  
<p>
  Hra bude mít 2D grafiku s pohledem zeshora. Ovládání bude bude umožněno primárně s pomocí klávesnice.
</p>

#### 3.3.2 N2 - Žánr hry
<p>
  Hra bude real-time RPG s důrazem na obchod a směnu zboží a předmětů s herními postavami.
</p>

#### 3.3.3 N3 - Cílová platforma
<p>
Hra bude plně funkční na PC pod operačním systémem linux. Instalace bude umožněna pomocí .deb instalační systému. ( debian )
</p>

#### 3.3.4 N4 - Jazyk hry
<p>
Hra bude v Anglickém jazyce ( dialogy, předměty, menu...).
</p>
