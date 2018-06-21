Úkolem je realizovat třídu, která bude umožňovat rychle těžit kryptoměnu.

Boom kryptoměn zaznamenalo i ČVUT a naše fakulta a probíhá příprava na ICO této virtuální měny. Pro zajištění transakcí se používají výpočetně náročné operace, které zároveň umožňují takovou měnu těžit. Vaším úkolem je implementovat program, který dokáže tuto těžbu pomocí vláken rozkládat na všechny dostupné procesory.

Protože nedošlo k dohodě mezi ČVUT a FIT, má plánovaná měna dva různé algoritmy těžení. Vznikají tak různé varianty měny, které budeme pracovně nazývat fitCoin a čvutCoin.

<dl>

<dt>fitCoin</dt>

<dd>dostane na vstupu pole 32 bitových neznaménkových celých čísel - bitových vektorů. Dále má parametrem zadanou vzdálenost <tt>dist</tt>. Algoritmus těžení hledá, kolik existuje různých 32 bitových čísel <tt>x</tt> takových, že se liší od každého ze zadaných vektorů nejvýše v <tt>dist</tt> bitech. Výpočet je demonstrován na příkladu, pouze pro přehlednost uvažujeme pouze 4 bitová čísla. Pokud budou zadané vektory:

<pre>  0011
  0101
  0110
  </pre>

Pak dostaneme pro čísla <tt>x</tt> následující počty odlišných bitů:

<pre>          ≤0     ≤1     ≤2     ≤3     ≤4
  0000                   *      *      *
  0001                          *      *
  0010                          *      *
  0011                   *      *      *
  0100                          *      *
  0101                   *      *      *
  0110                   *      *      *
  0111            *      *      *      *
  1000                          *      *
  1001                                 *
  1010                                 *
  1011                          *      *
  1100                                 *
  1101                          *      *
  1110                          *      *
  1111                   *      *      *
  Celkem:  0      1      6     13     16
  </pre>

Bude-li tedy vstupem algoritmu předložená sada vektorů a <tt>dist</tt> nastaveno na 3, je výsledkem výpočtu číslo 13 (platí pro ukázku se 4-bitovými vektory).</dd>

<dt>čvutCoin</dt>

<dd>dostane na vstupu pole bajtů. Algoritmus výpočtu toto pole chápe jako posloupnost bitů počínaje LSB (nejméně významným bitem) prvního bajtu a konče MSB (nejvíce významným bitem) posledního bajtu. Pro vstup délky <tt>n</tt> bajtů tedy máme posloupnost délky <tt>8n</tt> bitů. Dále jsou parametrem dvě celá čísla <tt>distMin</tt> a <tt>distMax</tt>. Úkolem je vyzkoušet všechny neprázdné předpony (prefixy) této bitové posloupnosti a všechny neprázdné suffixy této posloupnosti, pro každou dvojici (prefix x suffix) je potřeba určit jejich editační vzdálenost. Výsledkem je počet dvojic, jejichž editační vzdálenost patří do zadaného uzavřeného intervalu <tt>< minDist ; maxDist ></tt>. Editační vzdálenost dvojice bitových řetězců chápeme jako nejmenší počet operací mazání/vkládání/změny bitu tak, aby z jednoho bitového řetězce vznikl druhý.</dd>

</dl>

Vaším úkolem je realizovat třídu <tt>CRig</tt>, která dokáže takové problémy řešit. Oba uvedené problémy jsou výpočetně náročnější a oba problémy je potřeba řešit rychle. Proto bude využito vláken k rozdělení výpočetní zátěže na více CPU a asynchronního modelu výpočtu.

Třída <tt>CRig</tt> má modelovat opakované výpočty obou výše popsaných problémů v těžebním poolu. Problémy zadávají zákazníci (instance třídy <tt>CCustomer</tt>, vytvořené testovacím prostředím a předané <tt>CRig</tt>). Zákazníci předávají problémy (instance tříd <tt>CFITCoin</tt> a <tt>CCVUTCoin</tt>), Vaše implementace <tt>CRig</tt> si instance problému převezme, zpracuje je a vyřešené je zadávajícímu vrátí.

Vaše implementace si vytvoří pracovní vlákna, jejich počet je předán při spouštění výpočtu. Dále, pro načítání problémů si vytvořte tři pomocná vlákna pro každého zákazníka. Tato vlákna budou volat odpovídající metody instance <tt>CCustomer</tt>, jedno vlákno bude volat funkci pro doručování problémů typu fitCoin, druhé pro doručování problémů čvutCoin a třetí vlákno bude doručovat zpět oba druhy vyřešených problémů. Zadaný problém má podobu instance třídy <tt>CFITCoin</tt> nebo třídy <tt>CCVUTCoin</tt> (podle typu úlohy, instance jsou předané jako smart pointery - <tt>shared_ptr<CFITCoin></tt> a <tt>shared_ptr<CCVUTCoin></tt>, pro zkrácení zápisu jsou pro smart pointery vytvořené aliasy <tt>AFITCoin</tt> a <tt>ACVUTCoin</tt>). Vlákna, která přebírají zadávané problémy, nejsou určena k tomu, aby počítala řešení, jejich úkolem je pouze předání problémů dále k pracovním vláknům.

Pracovních vláken vytvoříte více (podle parametrů při inicializaci). Pracovní vlákna vyřeší zadanou instanci problémů a podle výsledků vyplní příslušné složky instance <tt>AFITCoin</tt> / <tt>ACVUTCoin</tt>. Po vyplnění předají instanci vyřešeného problému vyčleněnému předávacímu vláknu daného zákazníka. Předávací vlákno zajistí zavolání příslušné metody rozhraní zákazníka a zajistí serializaci odevzdávaní vyřešených úloh.

Jak již bylo řečeno, načítací a odevzdávací vlákna slouží pouze k odebírání požadavků od zákazníků a k předávání těchto požadavků pracovním vláknům. Celkový počet načítacích vláken bude dvojnásobkem počtu zákazníků, celkový počet odevzdávacích vláken bude roven počtu zákazníků. Pokud by načítací/odevzdávací vlákna rovnou řešila zadávané problémy a zákazníků bylo mnoho, vedlo by takové řešení k neefektivnímu využívání CPU (mnoho rozpracovaných problémů, časté přepínání kontextu, ...). Proto požadované řešení ponechává výpočty pouze na pracovních vláknech, kterých je pouze zadaný fixní počet.

Rozhraním Vaší implementace bude třída <tt>CRig</tt>. V této třídě musí být k dispozici metody podle popisu níže (mohou existovat i další privátní metody potřebné pro Vaši implementaci):

<dl>

<dt><tt>implicitní konstruktor</tt></dt>

<dd>inicializuje instanci třídy.</dd>

<dt><tt>destruktor</tt></dt>

<dd>uvolní prostředky alokované instancí <tt>CRig</tt>.</dd>

<dt><tt>Start (thr)</tt></dt>

<dd>metoda spustí vlastní výpočet. V této metodě vytvoříte potřebná pracovní vlákna pro výpočty. Pracovních vláken vytvořte celkem <tt>thr</tt> podle hodnoty parametru. Tím se spustí obsluha požadavků od zákazníků. Metoda <tt>Start</tt> se po spuštění pracovních vláken okamžitě vrací (tedy nečeká na doběhnutí výpočtů).</dd>

<dt><tt>Stop ()</tt></dt>

<dd>metoda informuje, že se mají ukončit výpočty. Tedy je potřeba převzít zbývající požadavky od existujících zákazníků, počkat na jejich vypočtení a vrácení výsledků. Metoda <tt>Stop</tt> se vrátí volajícímu po doběhnutí a uvolnění jak načítacích, předávacích, tak pracovních vláken. Metoda <tt>Stop</tt> se musí vrátit do volajícího. Neukončujte celý program (nevolejte <tt>exit</tt> a podobné funkce), pokud ukončíte celý program, budete hodnoceni 0 body.</dd>

<dt><tt>AddCustomer ( c )</tt></dt>

<dd>metoda přidá dalšího zákazníka do seznamu zákazníků obsluhovaných touto instancí. Parametrem je smart pointer (<tt>shared_ptr<CCustomer></tt>, zkráceně <tt>ACustomer</tt>) začleňovaného zákazníka. Metoda <tt>AddCustomer</tt> musí mj. vytvořit dvě pomocná načítací vlákna, která budou tohoto nového zákazníka obsluhovat a předávací vlákno pro odevzdávání vyřešených zadání. Pozor: metodu lze zavolat ještě před voláním <tt>Start</tt> (tedy zákazníci jsou obsluhovaní, ale výpočetní vlákna ještě neexistují), tak i po spuštění <tt>Start</tt> (nový zákazník je přidán k existujícím a je zahájena jeho obsluha).</dd>

<dt><tt>Solve (fitCoin)</tt></dt>

<dd>- metoda vypočte sekvenčně jeden zadaný problém typu <tt>AFITCoin</tt> (parametr). Testovací prostředí nejprve zkouší sekvenční řešení, abyste případně snáze odhalili chyby v implementaci algoritmu.</dd>

<dt><tt>Solve (cvutCoin)</tt></dt>

<dd>- metoda vypočte sekvenčně jeden zadaný problém typu <tt>ACVUTCoin</tt> (parametr). Testovací prostředí nejprve zkouší sekvenční řešení, abyste případně snáze odhalili chyby v implementaci algoritmu.</dd>

</dl>

Třída <tt>CCustomer</tt> definuje rozhraní jednoho zákazníka. Zákazník je implementován v testovacím prostředí a je předán Vaší implementaci v podobě smart pointeru (<tt>shared_ptr<CCustomer></tt> alias <tt>ACustomer</tt>). Rozhraní <tt>CCustomer</tt> má následující metody:

<dl>

<dt>destruktor</dt>

<dd>uvolňuje prostředky alokované pro zákazníka,</dd>

<dt><tt>FITCoinGen() / CVUTCoinGen()</tt></dt>

<dd>metoda po zavolání vrací další instanci problému fitCoin/čvutCoin ke zpracování. Návratovou hodnotou je smart pointer (<tt>shared_ptr<CFITCoin></tt> alias <tt>AFITCoin</tt> případně <tt>shared_ptr<CCVUTCoin></tt> alias <tt>ACVUTCoin</tt>) s popisem problému k vyřešení. Pokud je vrácen prázdný smart pointer (obsahuje NULL), znamená to, že daný zákazník již nemá žádný další problém tohoto typu k vyřešení (ale stále může dodávat problémy typu druhého typu). Pokud metoda vrátí prázdný ukazatel, lze ukončit příslušné načítací vlákno.</dd>

<dt><tt>FITCoinAccept ( fitCoin ) / CVUTCoinAccept (cvutCoin)</tt></dt>

<dd>metodou se předá vyřešený problém typu fitCoin/čvutCoin zpět zákazníkovi. Je potřeba vrátit vyřešený problém tomu zákazníkovi, který problém zadal. Dále, je potřeba vrátit tu samou instanci problému, kterou dříve předala metoda <tt>FITCoinGen / CVUTCoinGen</tt>, pouze je v ní potřeba vyplnit vypočítané hodnoty. Metody <tt>FITCoinAccept / CVUTCoinAccept</tt> je potřeba volat serializovaně z odevzdávacího vlákna, toto vlákno musí být pro daného zákazníka stále stejné.</dd>

</dl>

Třída <tt>CFITCoin</tt> je deklarovaná a implementovaná v testovacím prostředí. Pro testování Vaší implementace je k dispozici v bloku podmíněného překladu (ponechte jej tak). Význam složek je následující:

<dl>

<dt><tt>m_Vectors</tt></dt>

<dd>seznam 32 bitových vektorů zadání úlohy. Tato hodnota je vyplněna při vytváření zadání, **Vaše implementace ji nesmí měnit**.</dd>

<dt><tt>m_DistMax</tt></dt>

<dd>maximální vzdálenost od zadaných bitových vektorů. Tato hodnota je vyplněna při vytváření zadání, **Vaše implementace ji nesmí měnit**.</dd>

<dt><tt>m_Count</tt></dt>

<dd>je výsledkem výpočtu - počet 32 bitových hodnot <tt>x</tt> takových, že jejich vzdálenost od zadaných vektorů je nejvýše <tt>m_DistMax</tt>. Tuto hodnotu má vyplnit pracovní vlákno.</dd>

<dt><tt>implicitní konstruktor</tt></dt>

<dd>existuje pro usnadnění vytváření instance problému.</dd>

</dl>

Třída <tt>CCVUTCoin</tt> je deklarovaná a implementovaná v testovacím prostředí. Pro testování Vaší implementace je k dispozici v bloku podmíněného překladu (ponechte jej tak). Význam složek je následující:

<dl>

<dt><tt>m_Data</tt></dt>

<dd>bajty tvořící bitovou posloupnost k analýze (bity čteme směrem od nejnižšího k nejvyššímu). Tato hodnota je vyplněna při vytváření zadání, **Vaše implementace ji nesmí měnit**.</dd>

<dt><tt>m_DistMin, m_DistMax</tt></dt>

<dd>Rozmezí hodnot odlišnosti bitových řetězců při porovnávání. Tyto hodnoty jsou vyplněné při vytváření zadání, **Vaše implementace je nesmí měnit**.</dd>

<dt><tt>m_Count</tt></dt>

<dd>je výsledek výpočtu, který má vyplnit pracovní vlákno. Hodnota má udávat počet dvojic (předpona, přípona) zadané bitové posloupnosti takových, že jejich editační vzdálenost patří do intervalu hodnot <tt>< m_DistMin ; m_DistMax ></tt>.</dd>

<dt><tt>implicitní konstruktor</tt></dt>

<dd>existuje pro usnadnění vytváření instance problému.</dd>

</dl>

* * *

Odevzdávejte zdrojový kód s implementací požadované třídy <tt>CRig</tt> s požadovanými metodami. Můžete samozřejmě přidat i další podpůrné třídy a funkce. Do Vaší implementace nevkládejte funkci <tt>main</tt> ani direktivy pro vkládání hlavičkových souborů. Funkci <tt>main</tt> a hlavičkové soubory lze ponechat pouze v případě, že jsou zabalené v bloku podmíněného překladu.

Využijte přiložený ukázkový soubor. Celá implementace patří do souboru <tt>solution.cpp</tt>, dodaný soubor je pouze mustr. Pokud zachováte bloky podmíněného překladu, můžete soubor <tt>solution.cpp</tt> odevzdávat jako řešení úlohy.

Při řešení lze využít pthread nebo C++11 API pro práci s vlákny (viz vložené hlavičkové soubory). Dostupný kompilátor g++ verze 4.9, tato verze kompilátoru zvládá většinu C++11 a část C++14 konstrukcí.

* * *

**Nápověda:**  

*   Nejprve implementujte sekvenční funkce řešení problémů fitCoin/čvutCoin. Správnost implementace lze ověřit lokálně pomocí infrastruktury v přiloženém archivu. Až budete mít funkce lokálně otestované, můžete je zkusit odevzdat na Progtest (pro tento pokus nechte ostatní metody třídy <tt>CRig</tt> s prázdným tělem). Takové řešení samozřejmě nedostane žádné body, ale uvidíte, zda správně projde sekvenčními testy.
*   Abyste zapojili co nejvíce jader, zpracovávejte několik problémů najednou. Vyzvedněte je pomocí opakovaného volání <tt>FITCoinGen/CVUTCoinGen</tt> jednotlivých zákazníků, zajistěte si odevzdávací vlákno a zprovozněte komunikaci mezi přebíracími/pracovními a odevzdávacími vlákny. Není potřeba dodržovat pořadí při vracení řešení. Pokud budete najednou zpracovávat pouze jeden problém, nejspíše zaměstnáte pouze jedno vlákno a ostatní vlákna budou čekat bez užitku.
*   Instance <tt>CRig</tt> je vytvářená opakovaně, pro různé vstupy. Nespoléhejte se na inicializaci globálních proměnných - při druhém a dalším zavolání budou mít globální proměnné hodnotu jinou. Je rozumné případné globální proměnné vždy inicializovat v konstruktoru nebo na začátku metody <tt>Start</tt>. Ještě lepší je nepoužívat globální proměnné vůbec.
*   Nepoužívejte mutexy a podmíněné proměnné inicializované pomocí <tt>PTHREAD_MUTEX_INITIALIZER</tt>, důvod je stejný jako v minulém odstavci. Použijte raději <tt>pthread_mutex_init()</tt> nebo C++11 API.
*   Testovací prostředí samo o sobě nevytváří žádná vlákna, tedy metoda <tt>Start</tt> sama o sobě nemusí být reentrantní (může používat globální proměnné, s omezením výše).
*   Instance tříd CFITCoin / CCVUTCoin alokovalo testovací prostředí při vytváření příslušných smart pointerů. K uvolnění dojde automaticky po zrušení všech odkazů. Uvolnění těchto instancí tedy není Vaší starostí, stačí zrušit všechny odkazy na takto předané smart pointery. Váš program je ale zodpovědný za uvolnění všech ostatních prostředků, které si alokoval.
*   Problémy musíte načítat, zpracovávat a odevzdávat průběžně. Postup, kdy si všechny problémy načtete do paměťových struktur a teprve pak je začnete zpracovávat, nebude fungovat. Takové řešení skončí deadlockem v prvním testu s více vlákny. Musíte zároveň obsluhovat požadavky typu fitCoin i čvutCoin. Řešení, které se bude snažit nejprve vyřešit všechny problémy jednoho typu a pak začne obsluhovat problémy druhého typu, skončí taktéž deadlockem.
*   Musíte najednou obsluhovat více přidaných zákazníků. Pokud se budete snažit nejprve obsloužit zákazníka A, následně pouze zákazníka B, ..., skončíte taktéž v deadlocku.
*   Volání metod <tt>FITCoinAccept/CVUTCoinAccept</tt> není reentrantní. Je potřeba volání obsluhovat pouze z jediného vlákna, toto vlákno musí být vytvořené zvlášť pro každého zákazníka.
*   Neukončujte metodu <tt>Stop</tt> pomocí <tt>exit</tt>, <tt>pthread_exit</tt> a podobných funkcí. Pokud se funkce <tt>Stop</tt> nevrátí do volajícího, bude Vaše implementace vyhodnocena jako nesprávná.
*   Využijte přiložená vzorová data. V archivu jednak naleznete ukázku volání rozhraní a dále několik testovacích vstupů a odpovídajících výsledků.
*   V testovacím prostředí je k dispozici STL. Myslete ale na to, že ten samý STL kontejner nelze najednou zpřístupnit z více vláken. Více si o omezeních přečtěte např. na [C++ reference - thread safety.](http://en.cppreference.com/w/cpp/container)
*   Testovací prostředí je omezené velikostí paměti. Není uplatňován žádný explicitní limit, ale VM, ve které testy běží, je omezena 4 GiB celkové dostupné RAM. Úloha může být dost paměťově náročná, zejména pokud se rozhodnete pro jemné členění úlohy na jednotlivá vlákna. Pokud se rozhodnete pro takové jemné rozčlenění úlohy, možná budete muset přidat synchronizaci běhu vláken tak, aby celková potřebná paměť v žádný okamžik nepřesáhla rozumný limit. Pro běh máte garantováno, že Váš program má k dispozici nejméně 500 MiB pro Vaše data (data segment + stack + heap). Pro zvídavé - zbytek do 4GiB je zabraný běžícím OS, dalšími procesy, zásobníky Vašich vláken a nějakou rezervou.
*   Pokud se rozhodnete pro všechny bonusy, je potřeba velmi pečlivě nastavovat granularitu řešeného problému. Pokud řešený problém rozdělíte na příliš mnoho drobných podproblémů, začne se příliš mnoho uplatňovat režie. Dále, pokud máte najednou rozpracováno příliš mnoho problémů (a každý je rozdělen na velké množství podproblémů), začne se výpočet dále zpomalovat (mj. se začnou hůře využívat cache CPU). Aby se tomu zabránilo, řídí referenční řešení počet najednou rozpracovaných úloh (navíc dynamicky podle velikosti rozpracované úlohy).

* * *

**Co znamenají jednotlivé testy:**  

<dl>

<dt>**Test algoritmu (sekvencni)**</dt>

<dd>Testovací prostředí opakovaně volá metody <tt>Solve(fitCoin)/Solve(cvutCoin)</tt> pro různé vstupy a kontroluje vypočtené výsledky. Slouží pro otestování implementace Vašeho algoritmu. Není vytvářena instance <tt>CRig</tt> a není volaná metoda <tt>Start</tt>. Na tomto testu můžete ověřit, zda Vaše implementace algoritmu je dostatečně rychlá. Testují se náhodně generované problémy, nejedná se o data z dodané ukázky.</dd>

<dt>**Základní test/test několika/test mnoha thready**</dt>

<dd>Testovací prostředí vytváří instanci <tt>CRig</tt> pro různý počet vláken a zákazníků.</dd>

<dt>**Test zahlcení**</dt>

<dd>Testovací prostředí generuje velké množství požadavků a kontroluje, zda si s tím Vaše implementace poradí. Pokud nebudete rozumně řídit počet rozpracovaných požadavků, překročíte paměťový limit.</dd>

<dt>**Test zrychleni vypoctu**</dt>

<dd>Testovací prostředí spouští Vaši implementaci pro ta samá vstupní data s různým počtem vláken. Měří se čas běhu (wall i CPU). S rostoucím počtem vláken by měl wall time klesat, CPU time mírně růst (vlákna mají možnost běžet na dalších CPU). Pokud wall time neklesne, nebo klesne málo (např. pro 2 vlákna by měl ideálně klesnout na 0.5, existuje určitá rezerva), test není splněn.</dd>

<dt>**Busy waiting - pomale pozadavky**</dt>

<dd>Do volání <tt>FITCoinGen/CVUTCoinGen</tt> testovací prostředí vkládá uspávání vlákna (např. na 100 ms). Výpočetní vlákna tím nemají práci. Pokud výpočetní vlákna nejsou synchronizovaná blokujícím způsobem, výrazně vzroste CPU time a test selže.</dd>

<dt>**Busy waiting - pomale odevzdani**</dt>

<dd>Do volání <tt>FITCoinAccept/CVUTCoinAccept</tt> je vložena pauza. Pokud jsou špatně blokována vlákna načítající vstup, výrazně vzroste CPU time. (Tento scénář je zde méně pravděpodobný.)</dd>

<dt>**Busy waiting - complex**</dt>

<dd>Je kombinací dvou posledně jmenovaných testů.</dd>

<dt>**Velmi mnoho zákazníků**</dt>

<dd>Testovací prostředí zkouší přidávat mnoho zákazníků, každý zákazník má pouze několik málo požadavků a skončí. Po skončení zákazníka je potřeba průběžně ukončovat a uvolňovat načítací vlákna. Pokud se uvolnění načítacích vláken neděje průběžně, enormně vzroste paměťová náročnost a program spadne. Vzhledem k použitému HW je rozumné najednou obsluhovat přibližně 5-10 zákazníků. Jedná se o test bonusový.</dd>

<dt>**Rozlozeni zateze FITCoin**</dt>

<dd>Testovací prostředí zkouší, zda se do řešení jednoho problému typu fitCoin dokáže zapojit více dostupných vláken. Pokud chcete v tomto testu uspět, musíte Váš program navrhnout tak, aby bylo možné využít více vláken i při analýze jedné instance problému. Jedná se o test bonusový.</dd>

<dt>**Rozlozeni zateze CVUTCoin**</dt>

<dd>Testovací prostředí zkouší, zda se do řešení jednoho problému typu čvutCoin dokáže zapojit více dostupných vláken. Pokud chcete v tomto testu uspět, musíte Váš program navrhnout tak, aby bylo možné využít více vláken i při analýze jedné instance problému. Jedná se o test bonusový.</dd>

</dl>

* * *

**Jak to vyřešit - pozor, SPOILER**

Pokud se nechcete obrat o dobrý pocit, že jste úlohu vyřešili zcela sami, nečtěte dále.

*   Oba problémy jsou výpočetně náročnější a vyžadují používání bitových operátorů.
*   Problém typu fitCoin je v principu potřeba řešit hrubou silou, tedy odzkoušet všechny možnosti a spočítat, ty, které vyhovují podmínce vzdálenosti. Pro <tt>n</tt> vektorů velikosti 32 bitů to dává <tt>n 2<sup>32</sup></tt> porovnání. To je pro praktické nasazení příliš, takový výpočet by trval desítky sekund pro jedno zadání. Proto je potřeba zadané vektory předzpracovat. Pokud je ve všech vektorech hodnota nějakého bitu stejná, lze tento bit v testování vyloučit. Například pokud je ve všech vektorech nastaven bit č. 17 na hodnotu 0, pak bit 17 nebude ovlivňovat výsledek. Ze zadané sady vektorů tedy nejprve odstraňte fixní bity a teprve na takto omezeném vstupu spusťte hledání hrubou silou. Většinou se tím zmenší rozsah úlohy na cca <tt>n 2<sup>20</sup></tt>, což je časově mnohem lepší.
*   Pokud provedete úpravu zadání z minulého odstavce, dostanete mnohem menší rozmezí testovaných hodnot. Zároveň ale tímto postupem nezískáte přímo výsledek. Například máme zadané bitové vektory s 18 fixními bity (tedy budeme testovat celkem 2<sup>32-18</sup> hodnot) a máme zadáno <tt>distMax=6</tt>. Pokud zpracujeme hodnotu <tt>x</tt>, která se od upravených bitových vektorů liší v 6 bitech, pak se do výsledku započte právě 1x. Pokud by se ale lišila v méně bitech, např. v 5 bitech, pak se do výsledku započte celkem 19 krát (4 odlišnosti - 172x, 3 odlišnosti - 988x, ...). Rozmyslete si, o jaký kombinatorický problém zde jde.
*   Problém typu čvutCoin je postaven na problému porovnání editační vzdálenosti řetězců. Tedy na problému LCS, který znáte jako aplikaci dynamického programování. Protože prefixů i suffixů existuje celkem <tt>8n</tt> (n je počet bajtů problému, prázdný řetězec netestujeme), lze problém vyřešit testováním <tt>64n<sup>2</sup></tt> párů řetězců, každé porovnání spotřebuje řádově <tt>n<sup>2</sup></tt> operací. Celkem tedy řešení jednoho problému čvutCoin má složitost <tt>n<sup>4</sup></tt>, vhodnou úpravou se dá složitost snížit na <tt>n<sup>3</sup></tt>.
*   Testovací prostředí si nejprve sekvenčně otestuje rychlost odevzdaného řešení, podle toho pak upraví rozsah zadávaných dat. Úprava rozsahu testovacích dat ale není neomezená, odevzdané řešení musí být rozumně efektivní. Výpočet fitCoinu musí redukovat fixní bity, naivní řešení s <tt>n 2<sup>32</sup></tt> operacemi časově neprojde. Pro čvutCoin lze těsně projít i s řešením se složitostí <tt>n<sup>4</sup></tt>.
*   Vzhledem k heterogennímu charakteru vstupních dat se hodí objektový návrh s polymorfismem.

**Další nápověda - SUPERSPOILER**  

Podle potřeby v průběhu řešení úlohy zveřejníme další nápovědy pro tápající studenty.

**Referenční řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Test algoritmu FITCoin (sekvencni)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.003 s (limit: 5.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test algoritmu CVUTCoin (sekvencni)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.000 s (limit: 4.997 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Zakladni test (1x thread, 1x customer)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.682 s (limit: 30.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nekolika thready (1x customer)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.199 s (limit: 29.318 s)
        *   CPU time: 0.760 s (limit: 29.316 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test mnoha thready (n customers)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 0.391 s (limit: 29.119 s)
        *   CPU time: 3.076 s (limit: 28.556 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test zahlceni': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 0.899 s (limit: 28.728 s)
        *   CPU time: 3.636 s (limit: 25.480 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test zrychleni vypoctu': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 1.665 s (limit: 27.829 s)
        *   CPU time: 3.736 s (limit: 21.844 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (pomale pozadavky)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 3.012 s (limit: 30.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (pomale akceptace)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 2.372 s (limit: 26.988 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (complex)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 3.105 s (limit: 24.616 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Velmi mnoho zakazniku': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 1.939 s (limit: 10.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Test 'Rozlozeni zateze FITCoin': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.223 s (limit: 10.000 s)
        *   CPU time: 0.820 s (limit: 10.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Test 'Rozlozeni zateze CVUTCoin': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.179 s (limit: 9.777 s)
        *   CPU time: 0.700 s (limit: 9.180 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Celkové hodnocení: 172.80 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20 * 1.20 * 1.20)
*   Celkové procentní hodnocení: 172.80 %
*   Bonus za včasné odevzdání: 3.00
*   Celkem bodů: 1.73 * ( 30.00 + 3.00 ) = 57.02

**Moje řešení**

*   **Hodnotitel: automat**
    *   Program zkompilován
    *   Test 'Test algoritmu FITCoin (sekvencni)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.015 s (limit: 5.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test algoritmu CVUTCoin (sekvencni)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.001 s (limit: 4.985 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Zakladni test (1x thread, 1x customer)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.871 s (limit: 30.000 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test nekolika thready (1x customer)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 0.322 s (limit: 29.129 s)
        *   CPU time: 0.928 s (limit: 29.128 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test mnoha thready (n customers)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 0.812 s (limit: 28.807 s)
        *   CPU time: 4.488 s (limit: 28.200 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test zahlceni': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 80.00 %
        *   Celková doba běhu: 1.472 s (limit: 27.995 s)
        *   CPU time: 6.400 s (limit: 23.712 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Test zrychleni vypoctu': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 2.682 s (limit: 26.523 s)
        *   CPU time: 5.764 s (limit: 17.312 s)
        *   Úspěch v závazném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (pomale pozadavky)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 3.017 s (limit: 30.000 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (pomale akceptace)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 5.230 s (limit: 26.983 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Busy waiting test (complex)': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 50.00 %
        *   Celková doba běhu: 3.107 s (limit: 21.753 s)
        *   Úspěch v nepovinném testu, hodnocení: 100.00 %
    *   Test 'Velmi mnoho zakazniku': Úspěch
        *   Dosaženo: 100.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 6.157 s (limit: 10.000 s)
        *   Úspěch v bonusovém testu, hodnocení: 120.00 %
    *   Test 'Rozlozeni zateze FITCoin': Neúspěch
        *   Dosaženo: 50.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 1.546 s (limit: 10.000 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
        *   Nesprávný výstup
    *   Test 'Rozlozeni zateze CVUTCoin': Neúspěch
        *   Dosaženo: 50.00 %, požadováno: 100.00 %
        *   Celková doba běhu: 1.249 s (limit: 8.454 s)
        *   Neúspěch v bonusovém testu, hodnocení: Bonus nebude udělen
        *   Nesprávný výstup
    *   Celkové hodnocení: 120.00 % (= 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.00 * 1.20)
*   Celkové procentní hodnocení: 120.00 %
*   Celkem bodů: 1.20 * 30.00 = 36.00

</td>

