
## BI-PSI

![Oppa](https://i.imgur.com/gKVE2cl.png)

Praha & EU: Investujeme do vaší budoucnosti


# <a name="domaci_uloha_c_2_-_udp_klient" id="domaci_uloha_c_2_-_udp_klient">Domácí úloha č. 2 - UDP Klient</a>

## <a name="situace" id="situace">Situace</a>

<div class="level2">

Na oběžné dráze planety Mars létá sonda, která sbírá informace a fotografie od robotů pracujících na povrchu planety (viz úloha č.1). Získané informace se poté přenášejí ze sondy do řídícího centra na Zemi.

</div>

## <a name="ukoly" id="ukoly">Úkoly</a>

<div class="level2">

Vaším úkolem je:

1.  <div class="li">načíst ze sondy poslední známou fotografii okolí, aby mohli vědci zjistit, v jakém terénu se roboti nachází</div>

2.  <div class="li">provést upload nového firmwaru do sondy</div>

</div>

## <a name="obecne_schema_komunikace" id="obecne_schema_komunikace">Obecné schema komunikace</a>

<div class="level2">

Sonda komunikuje pomocí protokolu UDP a přijímá data na portu 4000\. Proces běžící v sondě budeme nazývat serverem a proces, který se sondou komunikuje, klientem.

</div>

### <a name="format_paketu" id="format_paketu">Formát paketu</a>

<div class="level3">

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">identifikátor 'spojení'</th>

<th class="col1">sekvenční číslo</th>

<th class="col2">číslo potvrzení</th>

<th class="col3">příznak</th>

<th class="col4">data</th>

</tr>

<tr class="row1">

<td class="col0">4B</td>

<td class="col1">2B</td>

<td class="col2">2B</td>

<td class="col3">1B</td>

<td class="col4">0-255B</td>

</tr>

</tbody>

</table>

*   <div class="li">identifikátor 'spojení' - vygenerovaný serverem (pro umožnění transportu dat více souborů najednou),</div>

*   <div class="li">sekvenční číslo - číslo prvního byte v posílaných datech,</div>

*   <div class="li">číslo potvrzení - číslo očekávaného byte v přijímaných datech (číslo potvrzení + délka dat),</div>

*   <div class="li">příznak - uveden dále,</div>

*   <div class="li">data - přenášená data</div>

Identifikátor spojení a sekvenční čísla se přenášejí v reprezentaci network byte order (big endian). Příklad:

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">dekadicky</th>

<th class="col1">hexadecimálně</th>

<th class="col2">pořadí bytů</th>

</tr>

<tr class="row1">

<td class="col0 centeralign">1234</td>

<td class="col1 centeralign">04D2h</td>

<td class="col2 centeralign">04h D2h</td>

</tr>

<tr class="row2">

<td class="col0 centeralign">34566</td>

<td class="col1 centeralign">8706h</td>

<td class="col2 centeralign">87h 06h</td>

</tr>

</tbody>

</table>

</div>

#### <a name="identifikator_spojeni" id="identifikator_spojeni">Identifikátor spojení</a>

<div class="level4">

Identifikátor spojení je nenulové číslo. Při navazování spojení posílá klient identifikátor spojení nastavený na nulu. Při další komunikaci použije klient identifikátor spojení, který mu vrátí server v prvním paketu.

</div>

#### <a name="priznaky" id="priznaky">Příznaky</a>

<div class="level4">

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">číslo bitu</th>

<th class="col1">7</th>

<th class="col2">6</th>

<th class="col3">5</th>

<th class="col4">4</th>

<th class="col5">3</th>

<th class="col6 centeralign">2</th>

<th class="col7 centeralign">1</th>

<th class="col8 centeralign">0</th>

</tr>

<tr class="row1">

<td class="col0">příznak</td>

<td class="col1 centeralign">-</td>

<td class="col2 centeralign">-</td>

<td class="col3 centeralign">-</td>

<td class="col4 centeralign">-</td>

<td class="col5 centeralign">-</td>

<td class="col6 centeralign">SYN</td>

<td class="col7 centeralign">FIN</td>

<td class="col8 centeralign">RST</td>

</tr>

</tbody>

</table>

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">příznak</th>

<th class="col1">význam</th>

</tr>

<tr class="row1">

<td class="col0 centeralign">SYN</td>

<td class="col1">Otevření nového spojení. Posílá klient i server (pouze) na začátku v prvním paketu. V datové části musí být právě 1 byte s kódem příkazu.</td>

</tr>

<tr class="row2">

<td class="col0 centeralign">FIN</td>

<td class="col1 leftalign">Ukončení spojení. Posílá klient i server, pokud již nemají žádná další data k odeslání. Paket s nastaveným příznakem FIN již nemůže obsahovat žádná data. Ukončení spojení nelze odvolat. Oba směry spojení se uzavírají zvlášť. Sekvenční číslo se po odeslání FIN již nesmí zvětšit.</td>

</tr>

<tr class="row3">

<td class="col0 centeralign">RST</td>

<td class="col1">Zrušení spojení kvůli chybě. Posílá klient i server v případě detekování logické chyby v hodnotách v hlavičce. Např. přijatý paket neobsahuje příznak SYN a ID spojení není evidováno. Nebo je hodnota potvrzovacího čísla menší, než byla v posledním přijatém paketu (klesá). Pozor na přetečení sekvenčních a potvrzovacích čísel. Žádná z komunikujících stran po odeslání paketu s příznakem RST již dále neukončuje spojení standardním způsobem - spojení je přenosem paketu s příznakem RST definitivně ukončeno.</td>

</tr>

</tbody>

</table>

Jednotlivé příznaky (SYN, FIN, RST) nelze spolu kombinovat.

</div>

### <a name="sekvencni_cislo_a_cislo_potvrzeni" id="sekvencni_cislo_a_cislo_potvrzeni">Sekvenční číslo a číslo potvrzení</a>

<div class="level3">

Sekvenční číslo je pořadové číslo prvního bytu v proudu posílaných dat. Na začátku je toto číslo nastaveno na nulu. Nastavení příznaku SYN nebo FIN toto číslo nemění.

Číslo potvrzení sděluje protistraně pořadové číslo očekávaného bytu v proudu přijímaných dat. Potvrzuje zároveň všechny byty s nižším pořadovým číslem.

Tato čísla nemají znaménko a mohou přetéct. Přetečení nemá na komunikaci vliv.

</div>

### <a name="data" id="data">Data</a>

<div class="level3">

Délka dat je určena velikostí paketu mínus velikost hlavičky. Poslat lze najednou maximálně 255 bytů dat, takže nejmenší velikost datagramu je 9 B (pouze hlavička) a největší 9 + 255 = 264 B. Data lze poslat pouze v paketu bez nastaveného příznaku FIN a RST. Pokud má paket nastaven příznak SYN, musí být v datové část 1 byte s kódem příkazu.

Data poslaná klientem i serverem se v číslují pomocí sekvenčního čísla, avšak pouze tehdy, pokud není nastaven žádný příznak (zejména SYN).

</div>

## <a name="popis_protokolu" id="popis_protokolu">Popis protokolu</a>

### <a name="navazani_spojeni" id="navazani_spojeni">Navázání spojení</a>

<div class="level3">

Iniciátorem spojení je vždy klient.

Klient pošle první datagram s příznakem SYN a s identifikátorem spojení, sekvenčním číslem a číslem potvrzení nastaveným na nulu. Datová část musí obsahovat právě 1 byte s kódem příkazu:

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">příkaz</th>

<th class="col1">význam</th>

</tr>

<tr class="row1">

<td class="col0">01h</td>

<td class="col1">Download fotografie okolí</td>

</tr>

<tr class="row2">

<td class="col0">02h</td>

<td class="col1">Upload nového firmwaru</td>

</tr>

</tbody>

</table>

Server odpoví datagramem s nastaveným příznakem SYN, nenulovým identifikátorem spojení a se sekvenčním číslem a číslem potvrzení nastavenými na nulu. Datová část obsahuje 1 byte s kódem příkazu, který bude proveden.

Po přijetí tohoto datagramu klientem je navázáno spojení. V dalším paketu začne klient nebo server odesílat data (podle poslaného příkazu).

Pokud se ztratí paket s příznakem SYN odeslaný klientem, musí klient po 100 ms odeslat nový.

Pokud se ztratí paket s příznakem SYN odeslaný serverem, musí klient po 100 ms odeslat nový SYN paket. V případě downloadu začne zřejmě server odesílat data, klient však nezná číslo spojení a tak tato data nemůže přijmout. Toto serverem polootevřené spojení se po 20\. opakování stejného paketu uzavře (bude odeslán paket s příznakem RST a nastaveným identifikátorem spojení). V případě uploadu se toto spojení uzavře po 20\. opakování SYN paketu.

_Poznámka: Data odeslaná serverem budou zcela určitě doručena klientovi, který o spojení žádal. Zdálo by se tedy, že v případě downloadu nemusí server odesílat paket s příznakem SYN (mohl by odeslat rovnou část dat). Protože však klient může podle této specifikace navázat více spojení najednou, tedy odeslat více inicializačních paketů najednou (třeba s různými příkazy), musí klient počkat na SYN paket s číslem spojení. Potom si také podle kódu příkazu (v datové části v odpovědi od serveru) může správně přiřadit čísla spojení._

</div>

### <a name="prenos_dat" id="prenos_dat">Přenos dat</a>

<div class="level3">

Data lze posílat až po navázání spojení. Posílání dat je neslučitelné s nastavováním libovolných příznaků (SYN, RST, FIN) (v této terminologii nechápeme příkaz v prvním paketu poslaným klientem jako data). V dalším textu nazveme vysílačem tu stranu, která data odesílá a přijímačem protistranu.

Pokud posílá některá ze stran soubor dat delší než 255 bajtů _(což je v této uloze vždy)_, používá se okénkové potvrzovací schéma s fixní velikostí okénka W = 2040 bytů a timeoutem Tout = 100 ms.

Vysílač se snaží mít v komunikačním kanále právě tolik nepotvrzených bytů odesílaného proudu dat, jako je velikost okénka. Při zahájení komunikace zapíše do kanálu W bytů a čeká na potvrzení. Přijímač reaguje na všechny příchozí pakety odesláním potvrzovacího paketu (paketu s nastaveným potvrzovacím číslem). Potvrzovací číslo popisuje pořadové číslo očekávaného bytu v proudu přijímaných dat, takže každé potvrzovací číslo potvrzuje příjem všech dat až do tohoto pořadového čísla (bez něj). Pokud přijme přijímač data mimo pořadí, zapamatuje si je a odešle potvrzovací číslo nastavené za poslední přijatý byte v proudu dat bez mezer. Jakmile jsou mezery zaplněny nově přijatými daty, posune přijímač potvrzovací číslo tak, aby opět ukazovalo za poslední přijatý byte v celistvém proudu přijímaných dat. Data mimo pořadí jsou tedy nakonec využita, přijímač je však zprvu nepotvrzuje. Potvrzuje vždy pouze přijatý datový proud bez mezer.

Jakmile vysílací strana přijme paket s takovým potvrzením, které snižuje počet nepotvrzených dat v odesílaném proudu, odešle další data, tak, aby bylo v kanále opět W nepotvrzených bytů (říkáme, že posune okénko).

Vysílač si pamatuje čas odeslání posledního paketu (označme T). Pokud server nepřijme do času T + Tout žádné nové potvrzení, které snižuje počet nepotvrzených dat, odešle vysílač W bytů od nevyššího přijatého potvrzovacího čísla (říkáme, že odešle celé okénko). Nastaví také T na novou hodnotu.

Vysílač posílá vždy maximální možné množství dat v jednom paketu (255 bytů). Vyjímkou je poslední datový paket, který může obsahovat méně dat.

Pokud vysílač přijme 3x po sobě stejné potvrzovací číslo, odešle ihned do kanálu 1 paket s maximálním možným množstvím dat od pořadového čísla shodného s přijatým potvrzovacím číslem a nastaví T na novou hodnotu.

</div>

### <a name="ukonceni_spojeni" id="ukonceni_spojeni">Ukončení spojení</a>

<div class="level3">

Pokud vysílač odešle celý soubor a má všechna odeslaná data potvrzená, uzavře spojení nastavením příznaku FIN. Tento příznak nelze kombinovat s odesláním posledních dat. Přijímač vzápětí odešle také paket s příznakem FIN.

Spojení je oboustranně ukončeno v momentě, kdy obě strany, které již odeslaly paket s nastaveným příznakem FIN, obdrží paket s nastaveným příznakem FIN a potvrzovacím číslem se stejnou hodnotou, jako je sekvenční číslo.

Pokud dojde 20x po sobě k opakovanému odvysílání paketu se stejným sekvenčním číslem, je spojení přerušeno, klient musí vypsat chybu při přenosu. To platí i při uzavírání spojení, kdy je odesílán příznak FIN.

</div>

### <a name="prikazy" id="prikazy">Příkazy</a>

#### <a name="prikaz_01h_-_fotografie_okoli" id="prikaz_01h_-_fotografie_okoli">příkaz 01h - fotografie okolí</a>

<div class="level4">

Jakmile robot odešle první paket s nastaveným příznakem SYN, začne ihned odesílat fotografii okolí. Pokud byl první paket (SYN) ztracen, spojení po marném odeslání 20 stejných paketů expiruje (klient žádá o nové spojení posláním nového SYN paketu).

Poslaná fotografie je ve formátu <acronym title="Portable Network Graphics">PNG</acronym> a posílá se pouze její obsah, nikoliv název souboru nebo nějaká další informace. Každá odeslaná fotografie je jedinečná (fotografie získané v rámci různých spojení se liší).

</div>

#### <a name="prikaz_02h_-_upload_noveho_firmwaru" id="prikaz_02h_-_upload_noveho_firmwaru">příkaz 02h - upload nového firmwaru</a>

<div class="level4">

Jakmile klient přijme od serveru první paket s nastaveným příznakem SYN, začne odesílat obsah souboru s firmwarem. Neposílá se žádná jiná doplňující informace, jako např. jméno souboru nebo jeho délka.

</div>

### <a name="prijeti_chybneho_paketu" id="prijeti_chybneho_paketu">Přijetí chybného paketu</a>

<div class="level3">

Po přijetí chybného paketu odešle příjemce (klient i server) paket s příznakem RST. Chybný paket je paket, který:

*   <div class="li">neobsahuje platné ID spojení a nemá nastaven příznak SYN</div>

*   <div class="li">nemá potvrzovací číslo v intervalu <seq - velikost okénka, seq> kde _seq_ je sekvenční číslo příjemce</div>

*   <div class="li">má nastaven více příznaků najednou</div>

*   <div class="li">má nastaven příznak SYN a datová část neobsahuje platný příkaz (délka dat není 01h a/nebo příkaz není 01h nebo 02h)</div>

*   <div class="li">má nastaven příznak FIN a zároveň obsahuje data</div>

Pozor, sekvenční a potvrzovací čísla mohou přetéct, což nesmí mít na komunikaci vliv.

</div>

### <a name="priklady_komunikace" id="priklady_komunikace">Příklady komunikace</a>

<div class="level3">

[Příklady komunikace jsou na zvláštní stránce.](https://edux.fit.cvut.cz/courses/BI-PSI/vyuka/y36psi/cviceni/uloha2-priklady "vyuka:y36psi:cviceni:uloha2-priklady")

</div>

## <a name="chybovost_site" id="chybovost_site">Chybovost sítě</a>

<div class="level2">

Možné chyby na síti:

*   <div class="li">ztráta libovolného paketu,</div>

*   <div class="li">duplikace libovolného paketu,</div>

*   <div class="li">prohození libovolných paketů,</div>

*   <div class="li">proměnné zpoždění sítě.</div>

Server tyto chyby emuluje. Může se stát, že server 20x způsobí ztrátu stejného paketu a dojde k odeslání paketu s příznakem RST a rozpadu spojení. Tato chyba není na závadu při odevzdávání úlohy (přenos se při odevzdávání zopakuje).

</div>

## <a name="pozadavky" id="pozadavky">Požadavky</a>

<div class="level2">

*   <div class="li">program musí být stabilní a odolný proti neočekávaným vstupům,</div>

*   <div class="li">přenesený soubor (download i upload) nesmí být poškozen,</div>

*   <div class="li">program se musí umět vyrovnat s faktem, že UDP pakety se občas ztratí, zduplikují či prohodí,</div>

*   <div class="li">program by měl vypisovat alespoň základní informace o svém stavu (např. posílané a přijímané příkazy či odpovědi),</div>

*   <div class="li">IP adresa nebo <acronym title="Domain Name System">DNS</acronym> jméno serveru se zadává jako parametr v příkazové řádce při spuštění programu (tzn. není zadrátovaná ve zdrojového kódu), syntaxe viz níže,</div>

*   <div class="li">zdrojový text musí být komentovaný, v hlavičce všech zdrojových textů musí být uveden autor,</div>

*   <div class="li">lze použít libovolný programovací jazyk, jedinou podmínkou je schopnost odprezentovat funkčnost v síťové laboratoři,</div>

*   <div class="li">doporučuje se psát kód do jednoho zdrojového kódu pro snadnější uploadování,</div>

*   <div class="li">program musí přijímat parametry z příkazové řádky s následující syntaxí:</div>

**Download fotografie** (příkaz 01h): `./robot <server>`  
Výsledná fotografie bude uložena v souboru _foto.png_.

**Upload firmwaru** (příkaz 02h): `./robot <server> <firmware.bin>`

_<server>_ je jméno nebo IP adresa serveru a _<firmware>_ je soubor s novým firmwarem pro robota.

Příklad volání: `java robot.Robot 81.25.17.115 /data/firmware.bin`

</div>

## <a name="testovani" id="testovani">Testování</a>

<div class="level2">

Pro testování můžete použít testovací obraz pro virtualizační systém Virtualbox. Doporučuje se pro testovaní pod Windows, nebo OSX. Pro testovaní je třeba síťový adaptér pro virtuální stroj nastavit jako bridge adapter (síťový most) - toto je vhodné pokud jste v lokální síti, kde virtuální stroj dostane vlastní IP adresu. Pokud to není možné, použijte Host only (Síť pouze s hostem). Po naběhnutí je nutné zjistit přidělenou IP adresu virtuálního stroje, na ni se budete svým klientem připojovat. Poté stačí spustit testovací server pomocí příkazu: _Spust_server_pro_ulohu_c_2_

Testovací obraz obsahuje i klienta v binární podobě.

K dispozici je staticky přeložený UDP server, který běží v testovači. Poznámky k jeho použití:

*   <div class="li">Ověřte si občas, není-li k dispozici novější verze.</div>

*   <div class="li">Server spusťte např. takto: `./kareludp-server 1000 - foto.png firmware.bin`</div>

kde 1000 je UID uživatele (jakékoliv číslo postačí), pod kterým server poběží, _foto.png_ je cesta k fotografii a _firmware.bin_ je akceptovaný firmware.

*   <div class="li">Nebo můžete spustit server skriptem _Spust_server_pro_ulohu_c_2_, nebo _Spust_server_pro_ulohu_c_2_64bit_.</div>

</div>

## <a name="ke_stazeni" id="ke_stazeni">Ke stažení</a>

<div class="level2">

<table class="inline">

<tbody>

<tr class="row0">

<th class="col0">soubor</th>

<th class="col1">odkaz</th>

</tr>

<tr class="row1">

<td class="col0">Referenční řešení - server + klient (binárky pro linux 32bit i 64bit a windows)</td>

<td class="col1">[kareludp.zip](https://edux.fit.cvut.cz/courses/BI-PSI/_media/labs/kareludp.zip "labs:kareludp.zip")</td>

</tr>

<tr class="row2">

<td class="col0">Testovací obraz pro Virtualbox</td>

<td class="col1">[bi-psi_core_6.1.ova.zip](https://edux.fit.cvut.cz/courses/BI-PSI/_media/bi-psi_core_6.1.ova.zip "bi-psi_core_6.1.ova.zip")</td>

</tr>

</tbody>

</table>

</div>

## <a name="termin_a_zpusob_odevzdani" id="termin_a_zpusob_odevzdani">Termín a způsob odevzdání</a>

<div class="level2">

Úlohu je nutné nahrát na odevzdávací server [PSI bouda](https://bouda.felk.cvut.cz/ "https://bouda.felk.cvut.cz") a odprezentovat vyučujícímu.

Odevzdat lze pouze takový program, který je schopný úspěšně stáhnout fotografii (pro odevzdání stačí předvést úspěšné stažení souboru s fotografií bez ohledu na následky u serveru či klienta)

Úlohu lze odevzdat nejpozději v den konání zkoušky.

<div class="noteimportant">Prezentovat úlohu lze i během zkouškového období vždy v den termínu konání zkoušky. Po každé zkoušce budou probíhat prezentace v prostoru před kanceláří 1133 v budově A.</div>

</div>

## <a name="bodovani" id="bodovani">Bodování</a>

<div class="level2">

Za úlohu můžete dostat max. 8 bodů. Penalizace:

*   <div class="li">program neumí stáhnout fotografii: _nelze odevzdat !_</div>

*   <div class="li">program neumí provést upload firmwaru: -4</div>

*   <div class="li">nebylo korektně uzavřeno spojení: -1</div>

*   <div class="li">chybně implementovaný okénkový protokol: dle povahy -1 až -4</div>

*   <div class="li">nestabilita: -3</div>

*   <div class="li">malá odolnost vůči nestandardním vstupům: -3</div>

*   <div class="li">chyby v programu, které se neprojevily přímo: dle povahy -1 až -5</div>

*   <div class="li">nečistý zdrojový kód: -1</div>

*   <div class="li">zdrojový kód nebyl průběžně uploadován na server Baryk: -5</div>

</div>

## <a name="literatura" id="literatura">Literatura</a>

<div class="level2">

[Demo aplet pro lepší pochopení okénkového komunikačního schématu](http://www2.rad.com/networks/2004/sliding_window/demo.html "http://www2.rad.com/networks/2004/sliding_window/demo.html")

</div>

## <a name="doporucena_literatura" id="doporucena_literatura">Doporučená literatura</a>

<div class="level2">

*   <div class="li">[Sliding window demo](http://www2.rad.com/networks/2004/sliding_window/ "http://www2.rad.com/networks/2004/sliding_window/")</div>

*   <div class="li">[Reliable Message Transport Protocol](http://www.cs.ucsb.edu/~almeroth/classes/S00.276/hw1/hw1.html "http://www.cs.ucsb.edu/~almeroth/classes/S00.276/hw1/hw1.html")</div>

</div>

## <a name="odkazy" id="odkazy">Odkazy</a>

<div class="level2">

*   <div class="li">[Wikipedia - BSD sockets](http://en.wikipedia.org/wiki/Berkeley_sockets "http://en.wikipedia.org/wiki/Berkeley_sockets")</div>

*   <div class="li">[Rozhraní Sockets - Java](http://java.sun.com/docs/books/tutorial/networking/TOC.html "http://java.sun.com/docs/books/tutorial/networking/TOC.html")</div>

*   <div class="li">[Rozhraní Sockets klient TCP a UDP - Java](http://www.eli.sdsu.edu/courses/spring96/cs596/notes/andrew/javanet.html "http://www.eli.sdsu.edu/courses/spring96/cs596/notes/andrew/javanet.html")</div>

*   <div class="li">[Transportní rozhraní - BSD sockets](http://www.earchiv.cz/a93/a315c110.php3 "http://www.earchiv.cz/a93/a315c110.php3")</div>

*   <div class="li">**[Unix sockets FAQ - vynikající](http://www.developerweb.net/forum/forumdisplay.php?f=70 "http://www.developerweb.net/forum/forumdisplay.php?f=70")**</div>

</div>

</div>

<div class="stylefoot">

<div class="meta">

<div class="user">Přihlášen(a) jako: jahodpa1 (jahodpa1)</div>

<div class="doc">/mnt/www/courses/BI-PSI/data/pages/labs/task2.txt · Poslední úprava: 2018/04/05 19:10 autor: cernyvi2</div>

</div>

<div class="bar" id="bar__bottom">

<div class="bar-left" id="bar__bottomleft">

<form class="button btn_revs" method="get" action="/courses/BI-PSI/labs/task2">

<div class="no"><input name="do" value="revisions" type="hidden"><input value="Starší verze" class="button" accesskey="o" title="Starší verze [O]" type="submit"></div>

</form>

</div>

<div class="bar-right" id="bar__bottomright">

<form class="button btn_profile" method="get" action="/courses/BI-PSI/labs/task2">

<div class="no"><input name="do" value="profile" type="hidden"><input value="Upravit profil" class="button" title="Upravit profil" type="submit"></div>

</form>

<form class="button btn_logout" method="get" action="/courses/BI-PSI/labs/task2">

<div class="no"><input name="do" value="logout" type="hidden"><input name="sectok" value="4278e693f5d7c32e21e5320acd7630d0" type="hidden"><input value="Odhlásit se" class="button" title="Odhlásit se" type="submit"></div>

</form>

<form class="button btn_index" method="get" action="/courses/BI-PSI/labs/task2">

<div class="no"><input name="do" value="index" type="hidden"><input value="Index" class="button" accesskey="x" title="Index [X]" type="submit"></div>

</form>

[<input class="button" value="Nahoru" onclick="window.scrollTo(0, 0)" title="Nahoru" type="button">](#dokuwiki__top) </div>

</div>

</div>
