**e-Banking**

Úkolem je realizovat třídu <tt>CBank</tt>, která bude implementovat internetové bankovnictví.

Uvažovaná třída je specifická tím, že chceme ukládat všechny změny (všechny transakce). Dále, pro účely archivace chceme ukládat nezávislé kopie instancí.

Úloha je směřována k procvičení pochopení mělké a hluboké kopie objektu. Má části povinné, dobrovolné a bonusové. Pro splnění povinné části úlohy postačuje vytvořit funkční třídu, která bude splňovat požadované rozhraní. Pro zvládnutí nepovinných a bonusových částí je potřeba rozmyslet ukládání dat tak, aby se při kopírování zbytečně neplýtvalo pamětí.

Úloha má procvičit práci s kopírováním objektů. Z tohoto důvodu jsou v úloze potlačené části standardní C++ knihovny, zejména STL a datový typ C++ string.

Požadovaná třída <tt>CBank</tt> má následující rozhraní:

<dl>

<dt><tt>implicitní konstruktor</tt></dt>

<dd>vytvoří prázdnou instanci el. bankovnictví,</dd>

<dt><tt>kopírující konstruktor</tt></dt>

<dd>vytvoří hlubokou kopii instance. Implementujte jej, pokud kompilátorem automaticky vytvořený kopírující konstruktor nevyhovuje (zkuste si odhadnout - bude potřeba?),</dd>

<dt><tt>destruktor</tt></dt>

<dd>uvolní prostředky alokované instancí.</dd>

<dt><tt>operátor =</tt></dt>

<dd>zkopíruje obsah jedné instance do druhé (hluboká kopie). Implementujte jej, pokud kompilátorem automaticky vytvořený operátor = nevyhoví,</dd>

<dt><tt>NewAccount(accID,initBalance)</tt></dt>

<dd>metoda přidá nové konto:

*   <tt>accID</tt> udává jednoznačný identifikátor konta. Jedná se o řetězec, délka a obsah může být libovolný, je požadována pouze unikátnost,
*   <tt>initBalance</tt> udává počáteční vklad (celé číslo). Implementovaná banka je velmi vstřícná, za založení konta je ochotna i vyplatit prémii, tedy počáteční vklad může být i záporný.

Metoda <tt>NewAccount</tt> vrací hodnotu <tt>true</tt> pro signalizaci úspěchu, <tt>false</tt> pro neúspěch (konto se stejným <tt>id</tt> již bylo zadané).</dd>

<dt><tt>Transaction(debitAcc,creditAcct,amount,sign)</tt></dt>

<dd>metoda realizuje bezhotovostní převod z jednoho konta na druhé. Parametry jsou:

*   <tt>debitAcc</tt> udává identifikátor konta plátce (z něj se částka odečte),
*   <tt>creditAcc</tt> udává identifikátor konta příjemce (na něj se částka přičte),
*   <tt>amount</tt> udává převáděnou částku (není záporná, může být nulová nebo kladná),
*   <tt>sign</tt> udává elektronický podpis autorizace převodu. Jedná se o řetězec, který je potřeba uložit pro účely dokladovaní (aplikace s ním jinak nemusí nijak pracovat).

Metoda <tt>Transaction</tt> vrací hodnotu <tt>true</tt> pro signalizaci úspěchu, <tt>false</tt> pro neúspěch (zadané konto neexistuje). Metoda nekontroluje zůstatek na účtu, předpokládáme, že lze konto bez problémů přečerpat. Převod ale selže, pokud se konto plátce shoduje s kontem příjemce.</dd>

<dt><tt>TrimAccount(accID)</tt></dt>

<dd>metoda odmaže archivované transakce z daného konta. Tedy aktuální zůstatek na kontě se stane počátečním stavem a archivované transakce zmizí. Volání lze chápat tak, že klient potvrdil předchozí transakce, tedy nemá cenu je dále archivovat. Metoda <tt>TrimAccount</tt> vrací hodnotu <tt>true</tt> pro signalizaci úspěchu, <tt>false</tt> pro neúspěch (zadané konto neexistuje).</dd>

<dt><tt>cout << Account(accID)</tt></dt>

<dd>výstup metody <tt>Account</tt> zaslaný do streamu zobrazí počáteční stav konta, seznam archivovaných transakcí a konečný stav konta. Formát je zřejmý z ukázky. Pokud účet zadaného čísla neexistuje, je vyhozena (libovolná) výjimka.</dd>

<dt><tt>Account(accID) . Balance()</tt></dt>

<dd>výstup metody <tt>Account</tt> musí reagovat na volání <tt>Balance</tt>, toto volání vrátí konečný stav zadaného konta. Pokud účet zadaného čísla neexistuje, je vyhozena (libovolná) výjimka.</dd>

</dl>

* * *

Odevzdávejte soubor, který obsahuje implementovanou třídu <tt>CBank</tt> a další Vaše podpůrné třídy. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci <tt>main</tt>. Funkce <tt>main</tt> a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu jako v ukázce níže.

Pokud se rozhodnete řešit i nepovinné a bonusové části úlohy, můžete pro nalezení vhodné reprezentace využít následující pozorování:

*   Vzniká mnoho kopií instance, které ale dále nejsou měněné. Tedy vyplatí se uvažovat realizaci, kde jsou data sdílená s originálem dokud nedojde k první modifikaci originálu nebo kopie.
*   Změny v instanci jsou "malé", tedy velká část obsahu zůstane stejná jako v originálu. Vyplatí se tedy i uvažovat o sdílení nezměněných částí instance. Pokud byste si např. konta realizovali jako třídy, dá se předpokládat, že mezi originálem a kopií se změní pouze několik kont.

Rozhraní a ukázka použití třídy je dostupná v přiloženém archivu.



**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.127 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.197 s (limit: 9.873 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru =': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.229 s (limit: 9.676 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami + mem debugger': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.422 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Efektivita - kopie beze zmen': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 70.00 %
        *   Celková doba běhu: 0.011 s (limit: 5.000 s)
        *   Využití paměti: 16832 KiB (limit: 111017 KiB)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Efektivita - kopie + malo zmen': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.387 s (limit: 5.000 s)
        *   Využití paměti: 76412 KiB (limit: 111017 KiB)
        *   Úspěch v bonusovém testu, hodnocení: 125.00 %
    *   Celkové hodnocení: 125.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.25)
*   Celkové procentní hodnocení: 125.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.25 * ( 5.00 + 0.50 ) = 6.88

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.135 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test kopirujiciho konstruktoru': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.210 s (limit: 9.865 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test operatoru =': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.243 s (limit: 9.655 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami + mem debugger': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.435 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Efektivita - kopie beze zmen': Neúspěch
        *   Dosaženo: 0.00 %, požadováno: 70.00 %
        *   Celková doba běhu: 0.047 s (limit: 5.000 s)
        *   Využití paměti: 23596 KiB (limit: 111017 KiB)
        *   Neúspěch v nepovinném testu, hodnocení: 70.00 %
        *   Nesprávný výstup [[Zpřístupnit nápovědu (72 B)]](javascript: unlockAdvice('?X=Unlock&Cou=202&Tgr=1260&Tsk=1061&Unl=L2262572'))
    *   Test 'Efektivita - kopie + malo zmen': Program překročil přidělenou maximální dobu běhu
        *   Vyčerpání limitu na celý test, program násilně ukončen po: 5.005 s (limit: 5.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
    *   Bylo detekováno celkem 186 neuvolněných bloků paměti - penalizace 30%
    *   Celkové hodnocení: 49.00 % (= (1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 0.70) * 0.7)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 49.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 0.49 * ( 5.00 + 0.50 ) = 2.69

