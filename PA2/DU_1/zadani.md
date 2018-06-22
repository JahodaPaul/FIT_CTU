**Rotace obrázku**

Úkolem je vytvořit C/C++ funkci, která dokáže zpracovat obrázek uložený v souboru a otočit jej.

Pro tuto úlohu předpokládáme uložení obrázků ve formátu, který vychází z toho, jak se obrázky ukládají ve formátu JPEG. Ukládání obrázků JPEG je relativně komplikované (obrazová data jsou přeskládaná, je aplikovaná DCT, ztrátová kvantizace a vlastní bezeztrátová komprese). V této úloze budeme předpokládat pouze první krok, tedy přeskládaní obrazových dat.

Předpokládáme obdélníkový obrázek tvořený jednotlivými body (pixely). Každý pixel je popsán několika hodnotami (kanály - např. jeden kanál je schopen popsat světlost pixelu, pokud použijeme 3 kanály, jsme schopni zapsat složky barev RGB, ...). Hodnoty můžeme ukládat s různou přesností (různý počet bitů), v obecném případě budeme uvažovat 1, 4, 8 nebo 16 bitů na kanál.

Vlastní obrázek je v souboru uložen v binární podobě. Nejprve je uložena hlavička popisující velikost obrázku, počet barevných kanálů a jejich přesnost (viz níže, hlavička v této úloze neodpovídá reálnému JPEG obrázku). Za hlavičkou následují uložená obrazová data - pixely.

Vlastní pixely tvoří obdélníkovou matici. Tato matice má rozměr W x H. Při ukládání se horizontální a vertikální rozměr matice rozšíří tak, aby její šířka/výška byla násobkem 8, dodané pixely vpravo a dole se vyplní hodnotami 0\.

<center>![](./1_files/index.php)</center>

Matice se rozdělí na dlaždice velikosti 8x8 pixelů, se kterými se pracuje nezávisle. Z každé dlaždice se nejprve separují jednotlivé kanály - vybere se a uloží se 8x8 = 64 hodnot pro první kanál, následně 64 hodnot druhého kanálu, třetího kanálu, ..., teprve pak se přejde k ukládání následující dlaždice. Hodnoty v každém kanálu se do výstupu ukládají ve směru vedlejších diagonál (toto vypadá zbytečně komplikovaně, ale v reálném JPEG obrázku právě tento postup v kombinaci s DCT zajistí dobrý kompresní poměr). Po uložení všech kanálů první dlaždice se přejde na ukládání další dlaždice na řádce. Po dokončení dlaždic v horizontálním směru se přejde na ukládání druhé řady dlaždic, tento postup (row-major) se uplatňuje až do konce obrázku. Ukládání pro příklad 3 kanály/pixel je zachycené na obrázku:

<center>![](./1_files/index(1).php)</center>

Hlavička obrázku má následující strukturu:

<pre>offset   velikost     význam
+0       2B           endian (0x4949 little endian, 0x4d4d big endian)
+2       2B           šířka uloženého obrázku
+4       2B           výška uloženého obrázku
+6       2B           formát pixelů počet barevných kanálů (1, 2, 3, 4, ..., 15) a počet bitů na kanál (1, 4, 8 nebo 16)
+8       ??           vlastní obrazová data (pixely)
</pre>

*   Identifikátor little/big endian je první hodnota hlavičky. Udává pořadí ukládání bajtů pro dvou- a čtyř-bajtové hodnoty v souboru (tedy vztahuje se i na další údaje v hlavičce). Platné hodnoty jsou zvolené symetricky, tedy čtení tohoto identifikátoru správně zvládne libovolná platforma. V závazných testech bude tato hodnota vždy odpovídat little endianu (tedy HW, na kterém poběží Váš program). V nepovinném testu se pak zkouší i vstupy v big-endianu.
*   Šířka a výška udává rozměr obrázků (vždy v pixelech). Jedná se o skutečnou šířku/výšku obrázku ještě před rozšířením na násobek 8\. Výška ani šířka nesmí být nulová.
*   Formát udává způsob kódování jednotlivých pixelů. Pixely mohou být kódovány rozdílným počtem bitů, navíc každý pixel může být tvořen několika kanály. Hodnota formát je rozdělena do bitů. Bity 3, 2, 1, a 0 udávají počet kanálů na jeden pixel (1 kanál: černo/bílý nebo odstíny šedé, 3 kanály = RGB, 4 kanály = RGBA, počet kanálů nesmí být 0, může být až 15). Bity 7, 6, 5 a 4 udávají počet bitů na jeden kanál podle následující tabulky:

    <pre>    0000 -  1 bit na kanál
        0001 -  nedovolená kombinace  
        0010 -  4 bity na kanál
        0011 -  8 bitů na kanál
        0100 - 16 bitů na kanál
        0101 \
        0110  | nedovolená kombinace 
        0111  |
        1xxx /   
       </pre>

    Příklady kombinací:

    <pre>   0x34 = 0b00110100 - 4 kanály na pixel, každý kanál má 8 bitů,
       0x41 = 0b01000001 - 1 kanál na pixel, kanál má 16 bitů,
       0x23 = 0b00100011 - 3 kanály na pixel, každý kanál má 4 bity,
       ...

    <pre>   Bity 8-15 jsou nevyužité, musí být nastavené na 0\. 
       </pre>

    </pre>

Úkolem je realizovat funkci s rozhraním níže:

<pre>bool rotateImage ( const char * srcFileName, 
                   const char * dstFileName, 
                   int          angle,
                   unsigned int byteOrder );
</pre>

<dl>

<dt><tt>srcFileName</tt></dt>

<dd>je ASCIIZ řetězec se jménem zdrojového souboru (zdrojový obrázek). Funkce tento soubor může číst, nesmí jej ale modifikovat.</dd>

<dt><tt>dstFileName</tt></dt>

<dd>je ASCIIZ řetězec se jménem cílového souboru (vytvořený obrázek). Funkce tento soubor vytváří, uloží do něj zdrojový obrázek otočený o zadaný úhel.</dd>

<dt><tt>angle</tt></dt>

<dd>je požadovaný úhel otočení obrázku. Hodnota může být násobek 90 stupňů. Např. pro 90 má být obrázek otočen o 90 stupňů ve směru chodu hodinových ručiček (CW - clockwise), pro hodnotu 0 se otočení obrázku nemění. Hodnota může být i záporná, pak se otáčí proti směru chodu hodinových ručiček například -90 ~ 270 ~ 630 odpovídá otočení o 90 stupňů proti směru chodu hodinových ručiček.</dd>

<dt><tt>byteOrder</tt></dt>

<dd>bude mít hodnotu ENDIAN_LITTLE nebo ENDIAN_BIG (deklarace konstant je v přiloženém archivu). Podle tohoto příznaku funkce vytvoří cílový soubor s odpovídajícím kódováním vícebajtových hodnot. V povinných testech bude vždy použito kódování ENDIAN_LITTLE (odpovídá HW, na kterém Váš program běží).</dd>

<dt>návratová hodnota</dt>

<dd><tt>true</tt> pro úspěch, <tt>false</tt> pro neúspěch. Za neúspěch považujte:

*   chybu při práci se soubory (nelze číst, zapsat, neexistuje, ...),
*   chybný formát vstupního souboru (nesprávný obsah hlavičky, nedovolený formát pixelů, nedostatek dat, nadbytek dat, ...),
*   zadaný úhel otočení není násobek 90 stupňů.

</dd>

</dl>

Funkce podle parametrů připraví požadovaný cílový soubor. Cílový soubor bude mít:

*   kódování little/big endian podle předaného parametru. V nepovinných testech může být zdrojový a cílový soubor v různých kódováních, navíc toto kódování se může lišit od kódování používaného HW. Pro zvládnutí nepovinného testu je potřeba dodat příslušné konverze,
*   rozměr cílového obrázku bude odpovídat velikosti zdrojového souboru po požadovaném otočení,
*   formát pixelů cílového obrázku bude odpovídat formátu pixelů ve zdrojovém obrázku,
*   obrazová data budou příslušně upravena.

**Poznámky:**

*   Pečlivě ošetřujte souborové operace. Testovací prostředí úmyslně testuje Vaši implementaci pro soubory neexistující, nečitelné nebo soubory s nesprávným datovým obsahem.
*   Jména souborů jsou řetězce, které nemusíte nijak kontrolovat. Názvy souborů ani přípony nejsou nijak omezené, podstatné je pouze, zda lze soubory daného jména otevřít a číst/zapisovat.
*   Při implementaci lze použít C i C++ rozhraní pro práci se soubory, volba je na Vás.
*   V přiloženém archivu najdete sadu testovacích souborů a jim odpovídající výstupy. Dále v přiloženém zdrojovém souboru naleznete ukázkovou funkci <tt>main</tt>, která spouští konverze na ukázkových souborech. Do tohoto zdrojového souboru můžete vložit Vaši implementaci, testovat ji a odevzdat ji na Progtest. Pokud chcete upravený zdrojový soubor odevzdávat, zachovejte v něm bloky podmíněného překladu.
*   Pro manipulaci s formátem pixelů v hlavičce se hodí bitové operace (&) a bitové posuvy (<< a >>).
*   Překódování little/big endian se uplatní na složky hlavičky a případně i na datový obsah obrázku, pokud se používá formát 16 bitů na složku pixelu.
*   Rozdělte řešení do více funkcí, případně si navrhněte třídu pro reprezentaci načteného obrázku. Nezkoušejte transformovat data přímo při kopírování ze souboru do souboru. Rozumné řešení načte celý zdrojový obrázek do 2D paměťové reprezentace, provede příslušné otočení a paměťovou reprezentaci uloží do cílového souboru. Paměti na to je dostatek.
*   Pro zpracování hodnot se známou velikostí (například 2 bajty rozměru obrázku v hlavičce) se hodí datové typy s garantovanou velikostí (cstdint, např. datové typy <tt>int16_t</tt>, <tt>uint16_t</tt>).
*   Povinné testy pracují s obrázky ve formátu 8 bitů na kanál a s ukládáním dat ve formátu little endian (to odpovídá architektuře použitého procesoru). Pokud Vaše implementace dokáže s takovými vstupy správně fungovat a pro ostatní nastavení (jiný endian, jiný počet bitů na kanál) vrátí neúspěch, projde povinnými testy.
*   Další test (16 bit obrázky, little/big endian) je nepovinný. Jeho zvládnutí znamená, že můžete dostat až 100% bodů. Naopak, pokud jej Vaše implementace nezvládne, dojde ke krácení bodů. Nepovinnost testu znamená, že i pokud testem neprojdete vůbec, můžete dostat nenulové celkové hodnocení (pokud by byl povinný, pak nezvládnutí testu znamená 0 bodů).
*   Poslední test (1 bit / 4 bit obrázky) je bonusový. Jeho zvládnutí znamená, že dostanete body navíc (nad nominálních 100 %).
*   Je rozumné začít s řešením základní varianty (8 bit/kanál, little endian) a tu rozšiřovat. Takový postup je vhodný i z hlediska získání zkušeností - donutíte se navrhovat rozhraní (funkcí, metod) tak, aby byla rozšířitelná.


**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test se soubory dle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.001 s (limit: 5.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Mezni hodnoty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.113 s (limit: 4.999 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nespravne vstupy': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 4.886 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.112 s (limit: 4.886 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test osetreni I/O chyb': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.142 s (limit: 4.774 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test, 16bit, little/big endian': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 0.004 s (limit: 5.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test, 1bit / 4bit': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.007 s (limit: 5.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
*   Celkové procentní hodnocení: 120.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.20 * ( 5.00 + 0.50 ) = 6.60

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test se soubory dle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.002 s (limit: 5.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Mezni hodnoty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.387 s (limit: 4.998 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nespravne vstupy': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 4.611 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.368 s (limit: 4.611 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test osetreni I/O chyb': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.136 s (limit: 4.243 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test, 16bit, little/big endian': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 0.016 s (limit: 5.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test, 1bit / 4bit': Program provedl neplatnou operaci a byl ukončen (Segmentation fault/Bus error/Memory limit exceeded/Stack limit exceeded)
        *   Celková doba běhu: 0.005 s (limit: 5.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50
