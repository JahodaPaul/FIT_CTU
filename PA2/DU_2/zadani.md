**Kontrolní hlášení**

Úkolem je realizovat třídu <tt>CVATRegister</tt>, která bude implementovat databázi kontrolních hlášení DPH.

Pro plánované důslednější potírání daňových úniků je zaveden systém kontrolních hlášení. V databázi jsou zavedené jednotlivé firmy, a do databáze jsou zaznamenávané jednotlivé vydané faktury, které daná firma vydala. Firmy lze do databáze zadávat a lze je rušit. Firma je identifikována svým jménem, adresou a daňovým identifikátorem (id). Daňový identifikátor je unikátní přes celou databázi. Jména a adresy se mohou opakovat, ale dvojice (jméno, adresa) je opět v databázi unikátní. Tedy v databázi může být mnoho firem <tt>ACME</tt>, mnoho firem může mít adresu <tt>Praha</tt>, ale firma <tt>ACME</tt> bydlící sídlící ve městě <tt>Praha</tt> může být v databázi pouze jedna. Při porovnávání daňových identifikátorů **rozlišujeme** malá a velká písmena, u jmen a adres naopak **nerozlišujeme** malá a velká písmena.

Veřejné rozhraní je uvedeno níže. Obsahuje následující:

*   Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).
*   Destruktor. Uvolňuje prostředky, které instance alokovala.
*   Metoda <tt>NewCompany(name, addr, id)</tt> přidá do existující databáze další záznam. Parametry <tt>name</tt> a <tt>addr</tt> reprezentují jméno a adresu, parametr <tt>id</tt> udává daňový identifikátor. Metoda vrací hodnotu <tt>true</tt>, pokud byl záznam přidán, nebo hodnotu <tt>false</tt>, pokud přidán nebyl (protože již v databázi existoval záznam se stejným jménem a adresou, nebo záznam se stejným číslem účtu).
*   Metody <tt>CancelCompany (name, addr) / CancelCompany (id)</tt> odstraní záznam z databáze. Parametrem je jednoznačná identifikace pomocí jména a adresy (první varianta) nebo pomocí daňového identifikátoru (druhá varianta). Pokud byl záznam skutečně odstraněn, vrátí metoda hodnotu <tt>true</tt>. Pokud záznam neodstraní (protože neexistovala firma s touto identifikací), vrátí metoda hodnotu <tt>false</tt>.
*   Metody <tt>Invoice (name, addres, amount) / Invoice (id, amount)</tt> zaznamenají příjem ve výši <tt>amount</tt>. Varianty jsou dvě - firma je buď identifikována svým jménem a adresou, nebo daňovým identifikátorem. Pokud metoda uspěje, vrací <tt>true</tt>, pro neúspěch vrací <tt>false</tt> (neexistující firma).
*   Metoda <tt>Audit ( name, addr, sum ) / Audit ( id, sum )</tt> vyhledá součet příjmů pro firmu se zadaným jménem a adresou nebo firmu zadanou daňovým identifikátorem. Nalezený součet uloží do výstupního parametru <tt>sum</tt>. Metoda vrátí <tt>true</tt> pro úspěch, <tt>false</tt> pro selhání (neexistující firma).
*   Metoda <tt>MedianInvoice ()</tt> vyhledá medián hodnoty faktury. Do vypočteného mediánu se započtou všechny úspěšně zpracované faktury zadané voláním <tt>Invoice</tt>. Tedy **nezapočítávají** se faktury, které nešlo přiřadit (volání <tt>Invoice</tt> selhalo), ale započítávají se všechny dosud registrované faktury, tedy při výmazu firmy se **neodstraňují** její faktury z výpočtu mediánu. Pokud je v systému zadaný sudý počet faktur, vezme se vyšší ze dvou prostředních hodnot. Pokud systém zatím nezpracoval žádnou fakturu, bude vrácena hodnota 0.

Odevzdávejte soubor, který obsahuje implementovanou třídu <tt>CVATRegister</tt>. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí kromě implementace třídy <tt>CVATRegister</tt> obsahovat nic jiného, zejména ne vkládání hlavičkových souborů a funkci <tt>main</tt> (funkce <tt>main</tt> a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu). Za základ implementace použijte přiložený zdrojový soubor.

Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje k uložení seznamu) a je omezena dobou běhu. Implementovaná třída se nemusí zabývat kopírujícím konstruktorem ani přetěžováním operátoru =. V této úloze ProgTest neprovádí testy této funkčnosti.

Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). Předpokládejte, že vytvoření a likvidace firmy jsou řádově méně časté než ostatní operace, tedy zde je lineární složitost akceptovatelná. Častá jsou volání <tt>Invoice</tt> a <tt>Audit</tt>, jejich časová složitost musí být lepší než lineární (např. logaritmická nebo amortizovaná konstantní). Dále, v povinných testech se metoda <tt>MedianInvoice</tt> volá málo často, tedy nemusí být příliš efektivní (pro úspěch v povinných testech stačí složitost lineární nebo <tt>n log n</tt>, pro bonusový test je potřeba složitost lepší než lineární).

Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor Pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou (např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.

Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor - k dispozici máte pouze část STL (viz hlavičkové soubory v přiložené ukázce). Tedy například kontejnery <tt>map</tt> / <tt>unordered_map</tt> / <tt>set</tt> / <tt>unordered_set</tt> / ... nejsou k dispozici.

V přiloženém zdrojovém kódu jsou obsažené základní testy. Tyto testy zdaleka nepokrývají všechny situace, pro odladění třídy je budete muset rozšířit. Upozorňujeme, že testy obsažené v odevzdaných zdrojových kódech považujeme za nedílnou součást Vašeho řešení. Pokud v odevzdaném řešení necháte cizí testy, může být práce vyhodnocena jako opsaná.

**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test meznich hodnot': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.021 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (Add, Search)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.011 s (limit: 9.979 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (Add, Del, Search)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.009 s (limit: 9.968 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (nahodne hodnoty)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.819 s (limit: 9.959 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami + test prace s pameti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 25.00 %
        *   Celková doba běhu: 0.035 s (limit: 4.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (nahodna jmena, fixni adresa)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 75.00 %
        *   Celková doba běhu: 0.831 s (limit: 15.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (fixni jmena, nahodna adresa)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 75.00 %
        *   Celková doba běhu: 0.707 s (limit: 14.169 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (median)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 2.062 s (limit: 5.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
*   Celkové procentní hodnocení: 120.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.20 * ( 5.00 + 0.50 ) = 6.60

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test meznich hodnot': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.031 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (Add, Search)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.015 s (limit: 9.969 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi vstupy (Add, Del, Search)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.013 s (limit: 9.954 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (nahodne hodnoty)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 1.103 s (limit: 9.941 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi hodnotami + test prace s pameti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 25.00 %
        *   Celková doba běhu: 0.032 s (limit: 4.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (nahodna jmena, fixni adresa)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 75.00 %
        *   Celková doba běhu: 1.185 s (limit: 15.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (fixni jmena, nahodna adresa)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 75.00 %
        *   Celková doba běhu: 1.011 s (limit: 13.815 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti (median)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 2.392 s (limit: 5.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 120.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.20 * ( 5.00 + 0.50 ) = 6.60

