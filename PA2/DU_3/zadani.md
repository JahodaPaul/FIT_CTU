**Polynomy**

Úkolem je realizovat třídu <tt>CPolynomial</tt>, která bude reprezentovat polynomy.

Třída <tt>CPolynomial</tt> ukládá polynom pomocí koeficientů u jednotlivých jeho mocnin. Předpokládáme koeficienty v podobě desetinných čísel typu <tt>double</tt>. Pomocí rozhraní (většina rozhraní má podobu přetížených operátorů) dokáže tato třída s polynomy pracovat. Realizovaná třída musí splňovat následující rozhraní:

<dl>

<dt>konstruktor implicitní</dt>

<dd>inicializuje objekt, který bude reprezentovat polynom o hodnotě 0.</dd>

<dt>kopírující konstruktor</dt>

<dd>bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.</dd>

<dt>destruktor</dt>

<dd>bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.</dd>

<dt>přetížený operátor =</dt>

<dd>bude umožňovat kopírování polynomů (pokud automaticky generovaný operátor = nevyhovuje).</dd>

<dt>operátor <<</dt>

<dd>bude umožňovat výstup objektu do C++ streamu. Výpis bude realizován v kompaktní podobě:

*   členy jsou zobrazované směrem od nejvyšší mocniny,
*   členy s nulovým koeficientem nebudou zobrazované,
*   členy s koeficientem +1 či -1 nebudou zobrazovat číslo 1, zobrazí pouze příslušnou mocninu <tt>x</tt>,
*   ve výpisu nejsou zbytečná znaménka - (tedy např. <tt>x^1 - 9</tt> nebo <tt>- x^2 + 4</tt> je správné, ale <tt>x^1 + (-9)</tt> je špatně),
*   nulový polynom se zobrazí jako samostatné číslo <tt>0</tt>.

Výchozí proměnnou v zobrazovaném polynomu bude proměnná <tt>x</tt>. Manipulátorem půjde jméno proměnné změnit (bonusové rozšíření).</dd>

<dt>operátor +</dt>

<dd>umožní sečíst dva polynomy,</dd>

<dt>operátor -</dt>

<dd>umožní odečíst dva polynomy,</dd>

<dt>operátor *</dt>

<dd>umožní vynásobit polynom desetinným číslem nebo dva polynomy,</dd>

<dt>operátory == a !=</dt>

<dd>umožní porovnat polynomy na přesnou shodu,</dd>

<dt>operátor []</dt>

<dd>umožní nastavit/zjistit hodnotu koeficientu u zadané mocniny polynomu. Čtecí varianta musí fungovat i pro konstantní polynomy,</dd>

<dt>operátor ()</dt>

<dd>umožní vyhodnotit hodnotu polynomu pro zadanou hodnotu <tt>x</tt> (<tt>x</tt> je desetinné číslo),</dd>

<dt>Degree()</dt>

<dd>metoda zjistí stupeň polynomu (např. <tt>x^3+4</tt> má stupeň 3, <tt>5</tt> má stupeň 0, <tt>0</tt> má stupeň 0).</dd>

<dt>manipulátor <tt>polynomial_variable( name )</tt></dt>

<dd>Manipulátorem půjde změnit proměnná, kterou bude zobrazovat výstup do streamu. Nebude-li manipulátor použit, zobrazí se polynom s proměnnou <tt>x</tt>. Pokud manipulátor použijeme, změní se proměnná v zobrazeni polynomu na zadaný řetězec. Toto rozšíření je testované pouze v bonusových testech. Pokud se jím nechcete zabývat, ponechte ukázkové deklarace <tt>polynomial_variable</tt> beze změn (dodaná implementace manipulátoru nic nedělá, manipulátor lze použít a program lze zkompilovat).</dd>

</dl>

Odevzdávejte zdrojový soubor, který obsahuje Vaší implementaci třídy <tt>CPolynomial</tt>. V odevzdávaném souboru nenechávejte vkládání hlavičkových souborů, Vaše testovací funkce a funkci <tt>main</tt>. Pokud v souboru chcete ponechat <tt>main</tt> nebo vkládání hlavičkových souborů, vložte je do bloku podmíněného překladu.

V tomto příkladu není poskytnutý přesný předpis pro požadované rozhraní třídy. Z textového popisu, ukázky použití v příloze a ze znalostí o přetěžování operátorů byste měli být schopni toto rozhraní vymyslet.

* * *

**Nápověda**  

*   Testovací prostředí kontroluje hodnoty ve Vašich objektech tím, že si je zašle do výstupního proudu a kontroluje jejich textovou podobu a dále pomocí operátoru []. Při porovnávání desetinných čísel jsou tolerované malé odchylky.
*   Operátor pro výstup implementujte správně -- neposílejte data na <tt>cout</tt>, posílejte je do předaného výstupního proudu. Za výstupem čísla do proudu nepřidávejte odřádkování ani jiné bílé znaky.
*   Pokud Vám program nejde zkompilovat, ujistěte se, že máte správně přetížené operátory. Zejména si zkontrolujte kvalifikátory <tt>const</tt>.
*   Manipulátor se testuje pouze v bonusovém testu. Pokud se bonusovým testem nechcete zabývat, ponechte deklaraci manipulátoru beze změn (dodaný manipulátor nefunguje, bonusovým testem neprojdete, ale program půjde zkompilovat). Pokud deklaraci dodaného manipulátoru odstraníte a nedodáte vlastní implementaci manipulátoru, program nepůjde zkompilovat.
*   Bonusový test (rychlost) vyžaduje rychlé násobení polynomů. Výpočet zkouší násobení polynomů stupně řádově 100000\. Naivní algoritmus nemá šanci tímto testem projít.
*   Testuje se i kopírování instancí <tt>CPolynomial</tt>. Pokud nevyhoví automaticky generovaný op=/copy cons, budete je muset dodělat.
*   Při implementaci můžete použít <tt>std::vector</tt> a <tt>std::string</tt>. Zbývající třídy z STL ale nejsou dostupné.



**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test meznich hodnot': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (op=, op <<)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.005 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 1.995 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru=': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 1.995 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test + test prace s pameti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.011 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test manipulatoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.013 s (limit: 4.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Test 'Test rychlosti #1': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.960 s (limit: 3.987 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Test 'Test rychlosti #2': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 4.096 s (limit: 9.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 125.00 %
    *   Celkové hodnocení: 180.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20 * 1.20 * 1.25)
*   Celkové procentní hodnocení: 180.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.80 * ( 5.00 + 0.50 ) = 9.90

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.001 s (limit: 2.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test meznich hodnot': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.001 s (limit: 1.999 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (op=, op <<)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.050 s (limit: 1.998 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 1.948 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru=': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.000 s (limit: 1.948 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Nahodny test + test prace s pameti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.019 s (limit: 2.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test manipulatoru': Neúspěch
        *   Dosaženo: 1.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.016 s (limit: 2.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246163'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246164'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246165'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246166'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246167'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246168'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246169'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (23 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246170'))
    *   Test 'Test rychlosti #1': Neúspěch
        *   Dosaženo: 65.91 %, požadováno: 100.00 %
        *   Celková doba běhu: 1.620 s (limit: 4.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
        *   Nesprávný výstup [[Zpřístupnit nápovědu (35 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246171'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (51 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246172'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (35 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246173'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (49 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246174'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (47 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246175'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (36 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246176'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (47 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246177'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (37 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246178'))
    *   Test 'Test rychlosti #2': Neúspěch
        *   Dosaženo: 52.94 %, požadováno: 100.00 %
        *   Celková doba běhu: 3.753 s (limit: 9.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
        *   Nesprávný výstup [[Zpřístupnit nápovědu (35 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246179'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (50 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246180'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (35 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246181'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (49 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246182'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (47 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246183'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (36 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246184'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (47 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246185'))
        *   Nesprávný výstup [[Zpřístupnit nápovědu (37 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1259&Tsk=1443&Unl=L2246186'))
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50

</td>

