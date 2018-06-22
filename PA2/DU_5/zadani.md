**Kontrola kontrolního hlášení**

Úkolem je realizovat třídy, které implementují správu daně z přidané hodnoty.

Předpokládáme, že firmy si předávají faktury. Firma, která vydá fakturu, musí z fakturované částky odvést státu DPH. Analogicky, firma, která přijme (a zaplatí fakturu) může po státu nárokovat vratku DPH (za určitých okolností). Právě vracení DPH je slabým místem, které lze využít ke krácení daně a daňovým podvodům. Proto je úkolem implementovat jádro systému, který bude takové krácení daně ztěžovat.

Vydané a přijaté faktury eviduje třída <tt>CVATRegister</tt>. Firmy musí registrovat vydávané a přijímané faktury. Registr páruje dvojice sobě odpovídajících faktur a je schopen najít faktury nespárované. Fakturu lze do registru jednak přidat a dále i zrušit (např. při chybně zadaných údajích). Rozhraní třídy je následující:

<dl>

<dt>implicitní konstruktor</dt>

<dd>inicializuje prázdnou instanci registru,</dd>

<dt>RegisterCompany ( name )</dt>

<dd>metoda zavede zadanou firmu do registru. Předané jméno je oficiální název firmy, toto jméno bude používané v exportech z registru. Návratovou hodnotou je indikátor úspěchu (<tt>true</tt>)/neúspěchu (<tt>false</tt>). Za neúspěch považujte, pokud v registru již existuje firma stejného jména. Při porovnávání jména firmy je registr docela tolerantní:

*   při porovnávání nerozlišuje malá a velká písmena,
*   při porovnávání neuvažuje nadbytečné mezery.

Tato pravidla jsou používána při zakládání nové firmy i vkládání / mazání faktur. Například názvy "My Company", "mY CoMpAnY", " My Company " a " mY CoMPAnY " jsou považované za jednu firmu, ale názvy "My Company" a "MyCompany" označují dvě rozdílné firmy.</dd>

<dt>AddIssued ( invoice )</dt>

<dd>metoda přidá fakturu do registru. Tuto metodu volá firma, která fakturu vydala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>). Za chybu je považováno, pokud prodávající / kupující ve faktuře nejsou registrované, prodávající a kupující je ta samá firma nebo pokud stejná faktura již byla pomocí <tt>AddIssued</tt> zadaná (dvě faktury se musí lišit alespoň v jednom z: prodávající/kupující/datum/částka/DPH).</dd>

<dt>AddAccepted ( invoice )</dt>

<dd>metoda přidá fakturu do registru, tuto metodu volá firma, která fakturu přijala (kupující). Jinak se metoda chová stejně jako <tt>AddIssued</tt>.</dd>

<dt>DelIssued ( invoice )</dt>

<dd>metoda odebere fakturu z registru. Tuto metodu volá firma, která fakturu vydala a dříve zaregistrovala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>). Za chybu je považováno, pokud identická faktura nebyla dříve registrovaná metodou <tt>AddIssued</tt>.</dd>

<dt>DelAccepted ( invoice )</dt>

<dd>metoda odebere fakturu z registru. Tuto metodu volá firma, která fakturu přijala a dříve zaregistrovala. Návratovou hodnotou je příznak úspěch (<tt>true</tt>)/neúspěch (<tt>false</tt>). Za chybu je považováno, pokud identická faktura nebyla dříve registrovaná metodou <tt>AddAccepted</tt>.</dd>

<dt>Unmatched ( company, sortOpt )</dt>

<dd>metoda nalezne všechny faktury, které se týkají zadané firmy <tt>company</tt> a nebyly spárované (tedy byly registrované pouze pomocí AddIssued nebo pouze pomocí AddAccepted). Metoda vrátí seznam těchto faktur, faktury budou seřazené podle kritérií udaných <tt>sortOpt</tt>. Faktury vrácené touto metodou budou mít na místě názvu firmy "oficiální" název, tedy ten název, který byl zadán při registraci firmy metodou <tt>RegisterCompany</tt>. Tento oficiální název bude rovněž použit při řazení.</dd>

</dl>

Třída <tt>CInvoice</tt> reprezentuje jednu fakturu. Rozhraní musí splňovat:

<dl>

<dt>konstruktor ( date, seller, buyer, amount, vat )</dt>

<dd>inicializace fakturu datem, jménem prodávající a kupující firmy, fakturovanou částkou a DPH.</dd>

<dt>Date, Seller, Buyer, Amount, VAT</dt>

<dd>přístupové metody ke čtení jednotlivých složek faktury.</dd>

<dt>další</dt>

<dd>do rozhraní faktury si můžete doplnit další veřejné/neveřejné metody a členské proměnné, které pro implementaci budete potřebovat.</dd>

</dl>

Třída <tt>CSortOpt</tt> určuje kritéria pro řazení. Pro řazení lze použít všechny složky faktury. Pokud například vytvoříme instanci:

<pre>CSortOpt () . AddKey ( CSortOpt::BY_AMOUNT, true ) . AddKey ( CSortOpt::BY_SELLER, false )</pre>

pak se řadí podle fakturované částky vzestupně (první řadicí kritérium) a pro stejné hodnoty fakturované částky se použije řazení podle jména prodávajícího sestupně (druhé řadicí kritérium). Pokud by ani takto nebylo pořadí jednoznačně určené, použije se jako řadicí kritérium pořadí zavedení faktury do registru. Rozhraní třídy <tt>CSortOpt</tt> je:

<dl>

<dt>implicitní konstruktor</dt>

<dd>inicializuje prázdnou instanci třídy</dd>

<dt>AddKey ( sortBy, ascending )</dt>

<dd>přidá další řadicí kritérium <tt>sortBy</tt>, směr řazení je daný příznakem <tt>ascending</tt> (<tt>true</tt> = vzestupně, <tt>false</tt> = sestupně). Řadit lze podle:

*   <tt>BY_DATE</tt> - podle data faktury,
*   <tt>BY_SELLER</tt> - podle oficiálního jména prodávající firmy, řadí se bez ohledu na malá/velká písmena,
*   <tt>BY_BUYER</tt> - podle oficiálního jména kupující firmy, řadí se bez ohledu na malá/velká písmena,
*   <tt>BY_AMOUNT</tt> - podle fakturované částky,
*   <tt>BY_VAT</tt> - podle DPH

</dd>

</dl>

Třída <tt>CDate</tt> implementuje jednoduché datum, její implementace je hotová v testovacím prostředí a pro testování ji máte dodanou v přiloženém archivu. Její implementaci nelze měnit, dodaná implementace musí zůstat v bloku podmíněného překladu.

Odevzdávejte zdrojový kód s implementací tříd <tt>CVATRegister</tt>, <tt>CInvoice</tt> a <tt>CSortOpt</tt>. Za základ implementace použijte přiložený soubor s deklarací metod a se sadou základních testů. Pro implementaci se může hodit doplnit i další pomocné třídy.

Zadání se trochu podobá dřívější domácí úloze. Předpokládáme, že při implementaci použijete vhodné kontejnery z STL (je k dispozici téměř celá), dále předpokládáme, že Vaše implementace bude časově a paměťově efektivní. Veškeré vkládání a mazání by mělo být rychlejší než lineární, řazení pak <tt>n log n</tt>. Není rozumné na všechny vnitřní struktury používat kolekci <tt>vector</tt>. Pokud chcete využívat C++11 kontejnery <tt>unordered_set / unordered_map</tt>, pak hashovací funktor neodvozujte jako specializaci <tt>std::hash</tt>. Hashovací funkci/funktor deklarujte explicitně při vytváření instance <tt>unordered_set / unordered_map</tt>. (Specializace <tt>std::hash</tt> předpokládá opětovné otevření jmenného prostoru <tt>std</tt>. To se těžko realizuje, pokud jste uzavřeni do jiného jmenného prostoru. Návody dostupné na internetu (stack overflow, cpp reference) implicitně předpokládají, že jmenné prostory nepoužíváte, na nich doporučovaná řešení nejsou ideálně kompatibilní.)



**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty (bez vymazu)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.443 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.516 s (limit: 9.557 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty + mem dbg': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.504 s (limit: 4.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 25.00 %
        *   Celková doba běhu: 5.412 s (limit: 15.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Zakladni test s parametry podle ukazky': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty (bez vymazu)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 0.984 s (limit: 10.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 1.220 s (limit: 9.016 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nahodnymi daty + mem dbg': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 1.078 s (limit: 4.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Test rychlosti': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 25.00 %
        *   Celková doba běhu: 9.995 s (limit: 15.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Celkové hodnocení: 100.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00)
*   Použité nápovědy: 2
*   Penalizace za vyčerpané nápovědy: Není (2 <= 2 limit)
*   Celkové procentní hodnocení: 100.00 %
*   Bonus za včasné odevzdání: 0.50
*   Celkem bodů: 1.00 * ( 5.00 + 0.50 ) = 5.50


