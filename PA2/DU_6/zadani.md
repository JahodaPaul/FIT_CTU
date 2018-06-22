**Výsledková listina**

Úkolem je realizovat šablonu třídy, která dokáže sestavovat výsledkové listiny v závislosti na zadaných vstupech - výsledcích zápasů dvojic soupeřů.

Předpokládáme, že máme několik soupeřů. V jednom zápase se utká dvojice soupeřů, výsledek zápasu je nějak popsán (například booleovskou hodnotou, dvojicí počtu bodů, dvojicí časů, ...). Protože chceme mít třídu obecnou, bude výsledek zápasu reprezentován jako generický datový typ. Takto bude do třídy vloženo několik výsledků pro zadané dvojice soupeřů (soupeři jsou jednoznačně identifikováni jménem - řetězcem). Následně chceme zjistit, zda na základě zadaných výsledků lze sestavit jednoznačnou výsledkovou listinu a případně tuto listinu i vypočítat. Trikem je, že při sestavování výsledku chceme vycházet pouze z informací o vítězi/poraženém ze zadaných zápasů.

Výsledková listina je určena jednoznačně, pokud pro každého soupeře <tt>X<sub>i</sub></tt> na pozici <tt>i</tt> platí:

*   <tt>X<sub>i</sub></tt> porazil všechny soupeře <tt>X<sub>j</sub></tt>, <tt>i+1 ≤ j ≤ n</tt>. Soupeře porazil buď přímo, nebo zprostředkovaně (<tt>X<sub>i</sub></tt> porazil <tt>X<sub>a</sub></tt>, <tt>X<sub>a</sub></tt> porazil <tt>X<sub>b</sub></tt>, ..., <tt>X<sub>z</sub></tt> porazil <tt>X<sub>j</sub></tt>, <tt>i+1 ≤ a < b < ... < j ≤ n</tt>),
*   <tt>X<sub>i</sub></tt> nevyhrál ani neremizoval se žádným soupeřem <tt>X<sub>k</sub></tt>, <tt>0 ≤ k ≤ i-1</tt>.

Vezměme příklad, kdy bylo zadáno, že A porazí B a B porazí C. Pak je zřejmě správná výsledková listina <tt>A B C</tt>. Pokud by ale bylo zadáno, že:

<pre>A porazí B
B porazí C
C porazí A
</pre>

případně:

<pre>A porazí B
A porazí C
</pre>

případně:

<pre>A porazí B
B remizuje s C
</pre>

pak výsledkovou listinu nelze jednoznačně určit (museli bychom dodat informace o dalších zápasech nebo pořadí stanovit i na základě dalších kritérií, to v této úloze nebudeme dělat).

Bylo zmíněno, že zápas je zadaný jako trojice (soupeř1, soupeř2, výsledek), kde výsledek je nějaký datový typ popisující například skóre, časy nebo cokoliv jiného. Výsledek je potřeba převést na informaci o vítězi/remíze/poraženém, to bude mít na starosti porovnávač (komparátor) předaný metodě pro určení výsledkové listiny. Porovnávač je funkce, funktor nebo lambda-výraz, který pro daný výsledek vrací návratovou hodnotu:

*   zápornou, pokud soupeř1 prohrál,
*   nulovou, pokud soupeř1 a soupeř2 remizovali,
*   kladnou, pokud soupeř1 vyhrál.

Celkové rozhraní šablony třídy <tt>CContest</tt> bude:

<dl>

<dt>šablona je parametrizovaná generickým parametrem <tt>_M</tt></dt>

<dd>tento typ popisuje výsledek zápasu. Pro datový typ <tt>_M</tt> je garantováno, že je přesouvatelný, kopírovatelný a zrušitelný (CopyConstructibe, MoveConstructible, CopyAssignable, MoveAssignable a Destructible). Další vlastnosti typu nejsou garantované, speciálně, není garantované, že typ <tt>_M</tt> má implicitní konstruktor (nemusí být DefaultConstructible).</dd>

<dt>implicitní konstruktor</dt>

<dd>vytvoří prázdnou instanci <tt>CContest</tt>,</dd>

<dt><tt>AddMatch(contestant1, contestant2, result)</tt></dt>

<dd>metoda přidá výsledek mezi soupeřem <tt>contestant1</tt> a <tt>contestant2</tt>. Soupeři jsou zadaní v podobě řetězců. Výsledek <tt>result</tt> je datového typu <tt>_M</tt>. Metoda si uloží informaci o tomto zápasu do nějakého úložiště ve své instanci. Volání <tt>AddMatch</tt> lze řetězit. Metoda vyvolá výjimku <tt>DuplicateMatchException</tt>, pokud byl výsledek zápasu mezi <tt>contestant1</tt> a <tt>contestant2</tt> již dříve zadán.</dd>

<dt><tt>IsOrdered (comparator)</tt></dt>

<dd>metoda rozhodne, zda vyplněné výsledky zápasů vedou k jednoznačné výsledkové listině nebo ne. Návratovou hodnotou je <tt>true</tt> pokud je výsledková listina jednoznačná, <tt>false</tt> pokud ne. Parametrem volání je <tt>comparator</tt> - funkce, funktor nebo lambda výraz, který bude volán při získávání výsledku zápasu (převede _M na záporné číslo / nulu / kladné číslo podle popisu výše). Metoda nesmí modifikovat instanci <tt>CContest</tt> a nesmí házet výjimky.</dd>

<dt><tt>Results (comparator)</tt></dt>

<dd>metoda vypočte výsledkovou listinu. Výsledkem je STL seznam (<tt>std::list</tt>) řetězců se jmény soupeřů v pořadí od prvního (celkového vítěze) k poslednímu. Pokud nelze výsledkovou listinu sestavit (není jednoznačná), metoda vyhodí výjimku <tt>OrderingDoesNotExistException</tt>. Parametr <tt>comparator</tt> má stejný význam jako u metody <tt>IsOrdered</tt>.</dd>

</dl>

* * *

Odevzdávejte zdrojový kód s implementací šablony třídy <tt>CContest</tt>. Za základ implementace použijte přiložený zdrojový kód. Pokud v kódu ponecháte bloky podmíněného překladu, lze takový zdrojový kód lokálně testovat a zároveň jej odevzdávat Progtestu.

Hodnocení je rozděleno na povinnou a bonusovou část. V povinné části se testují instance s malým počtem soupeřů a zápasů. Pro jeho úspěšné zvládnutí stačí základní algoritmus pracující v čase <tt>počet_soupeřů x počet_zápasů</tt>. Pro zvládnutí bonusového testu je potřeba použít algoritmus efektivnější.

Pro základní řešení se může hodit vyhledání všech přímo nebo zprostředkovaně poražených soupeřů. Toto dokáže algoritmus BFS (prohledávání do šířky). Pro inspiraci si připomeňte proseminář PA1, ve kterém jsme probírali datové struktury, příklad s cestou v bludišti.

Zdrojový kód s ukázkou práce šablony naleznete v přiloženém archivu.


**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.001 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.799 s (limit: 9.999 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 6.999 s (limit: 15.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 130.00 %
    *   Celkové hodnocení: 130.00 % (= 1.00 * 1.00 * 1.30)
*   Celkové procentní hodnocení: 130.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.30 * ( 5.00 + 0.50 ) = 7.15

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.542 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 4.287 s (limit: 15.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 130.00 %
    *   Celkové hodnocení: 130.00 % (= 1.00 * 1.00 * 1.30)
*   Použité nápovědy: 1
*   Penalizace za vyčerpané nápovědy: Není (1 <= 2 limit)
*   Celkové procentní hodnocení: 130.00 %
*   Celkem bodů: 1.30 * 5.00 = 6.50

