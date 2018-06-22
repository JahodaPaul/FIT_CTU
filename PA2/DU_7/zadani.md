**Prázdniny se blíží I**

Blíží se doba prázdnin a po dvou semestrech programování na oblíbeném automatickém vyhodnocovacím systému je potřeba změna. Na prázdniny je potřeba se připravit a sbalit. Jako poslední domácí úlohu z programování proto realizujete program, který Vám s balením na dovolenou pomůže.

Předpokládáme, že na dovolenou s sebou balíme do kufru nebo do batohu následující věci:

*   <tt>CClothes</tt> - oblečení, hmotnost 500g/ks. Samozřejmě je potřeba mít evidovaný i jeho stručný popis (řetězec).
*   <tt>CShoes</tt> - boty, hmotnost 750g/ks.
*   <tt>CKnife</tt> - nůž o hmotnosti 100g/ks. Poznamenáme si délku jeho čepele (v cm).
*   <tt>CMobile</tt> - naprostá nezbytnost, hmotnost 150g/ks, samozřejmě si pamatujeme značku a model.

Veškeré nezbytnosti si balíme do kufru <tt>CSuitcase</tt> nebo do batohu <tt>CBackpack</tt>. Obě zavazadla mají obrovskou výhodu - vejde se do něj naprosto cokoliv, a to při hmotnosti pouze 2000g (kufr) resp. 1000g (batoh). Navíc v naší implementaci bude schopen poskytovat cenné výstupy díky svému rozhraní:

*   Konstruktor <tt>CSuitcase(w,h,d)</tt> ma 3 celočíselné parametry, které udávají max. velikost kufru. Tyto údaje je potřeba uložit a zobrazovat. Konstruktor <tt>CBackpack</tt> nemá parametry žádné. Zbytek rozhraní je pak pro obě třídy shodný.
*   Metodou <tt>Add</tt> půjde do kufru/batohu přidat libovolné vybavení výše.
*   Metodou <tt>Weight</tt> půjde zjistit hmotnost celého kufru/batohu (včetně obsahu). Metoda vrací celé číslo - hmotnost v gramech.
*   Metodou <tt>Danger</tt> nám kufr/batoh zjistí, zda se v něm nenachází nebezpečná věc (to se hodí např. při kontrole na letišti). Za nebezpečnou věc v naší implementaci považujeme nůž s čepelí delší než 7 cm a mobilní telefon Samsung Galaxy Note S7\. Pokud je v zavazadle nebezpečná věc, metoda vrátí <tt>true</tt>.
*   Metodu <tt>Count</tt>, která nám zjistí počet věcí v kufru (vrací celé číslo).
*   Metodu <tt>IdenticalContents (x)</tt>, která zjistí, zda je obsah dvou zavazadel stejný. Porovnává se pouze obsah (tedy ne zavazadlo samotné), navíc nás nezajímá pořadí věcí v zavazadle. Metoda vrací <tt>true</tt> pro shodný obsah, <tt>false</tt> pro odlišný.
*   Operátor <tt><<</tt>, kterým půjde zobrazit obsah celého kufru/batohu (viz ukázka níže).
*   Dále od našeho kufru/batohu požadujeme standardní vlastnosti (aby se sám dokázal správně zničit, aby se dokázal správně zkopírovat - to se hodí jako prevence ztráty, ...).

Vaším úkolem je navrhnout vhodné rozhraní tříd <tt>CKnife</tt>, <tt>CMobile</tt>, <tt>CShoes</tt>, <tt>CClothes</tt>, <tt>CSuitcase</tt> a <tt>CBackpack</tt>. Při realizaci se zaměřte zejména na čistotu objektového návrhu. Implementace vyžaduje, abyste využili dědění a polymorfismu a dále vyžaduje, abyste atributy (členské proměnné) umístili právě jen do těch tříd, které je potřebují. Rozhodně nebude fungovat pokud všechny atributy umístíte do základní třídy.

Odevzdávejte zdrojový soubor, který obsahuje implementaci všech požadovaných tříd. Do odevzdávaného souboru nepřidávejte vkládání hlavičkových souborů a funkci <tt>main</tt>. Pokud vkládání hlavičkových souborů nebo funkci <tt>main</tt> v odevzdávaném souboru necháte, umístěte je do bloku podmíněného překladu (<tt>#ifndef __PROGTEST__</tt> / <tt>#endif</tt>). Využijte přiložený archiv jako základ Vaší implementace.

* * *

**Poznámky:**  

*   Prvním řádkem ve výpisu je označení zavazadla <tt>Suitcase</tt> se zadanými rozměry nebo <tt>Backpack</tt> (bez rozměrů, rozměry si udržujeme pouze pro kufr).
*   Poslední prvek ve výpisu nemá značku <tt>+-</tt>, ale značku <tt>\-</tt>.
*   Pořadí věcí ve výpisu je shodné jako pořadí vkládání pomocí metody <tt>Add</tt>.
*   Výstupy operátorů jsou porovnávány řetězcově, dodržte formátování včetně bílých znaků.
*   Nepoužívejte <tt>typeid</tt> operátor. Pro vyřešení této úlohy není potřeba (jeho použití zde svědčí o nesprávném návrhu). V testovacím prostředí úmyslně není vložen hlavičkový soubor <tt>typeinfo</tt>, použití <tt>typeid</tt> tedy povede k chybě při kompilaci.
*   Místo pracné kaskády <tt>if</tt>/<tt>if else</tt> použijte pro kopírování věcí v kufru polymorfismus.


**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test navrhu trid': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.005 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru=': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty + mem debugger': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.005 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test navrhu trid': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.005 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru=': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty + mem debugger': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.006 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50

