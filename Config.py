SERVER_CONFIRMATION = ''#<16-bitové číslo v decimální notaci>\a\b	#Zpráva s potvrzovacím kódem. Může obsahovat maximálně 5 čísel a ukončovací sekvenci \a\b.
SERVER_MOVE	= '102 MOVE\a\b'.encode('utf-8')	#Příkaz pro pohyb o jedno pole vpřed
SERVER_TURN_LEFT=	'103 TURN LEFT\a\b'.encode('utf-8')	#Příkaz pro otočení doleva
SERVER_TURN_RIGHT=	'104 TURN RIGHT\a\b'.encode('utf-8')	#Příkaz pro otočení doprava
SERVER_PICK_UP=	'105 GET MESSAGE\a\b'.encode('utf-8')	#Příkaz pro vyzvednutí zprávy
SERVER_LOGOUT=	'106 LOGOUT\a\b'.encode('utf-8')	#Příkaz pro ukončení spojení po úspěšném vyzvednutí zprávy
SERVER_OK=	'200 OK\a\b'.encode('utf-8')	#ladné potvrzení
SERVER_LOGIN_FAILED=	'300 LOGIN FAILED\a\b'.encode('utf-8')	#Nezdařená autentizace
SERVER_SYNTAX_ERROR=	'301 SYNTAX ERROR\a\b'.encode('utf-8')	#Chybná syntaxe zprávy
SERVER_LOGIC_ERROR=	'302 LOGIC ERROR\a\b'.encode('utf-8')

CLIENT_RECHARGING =	'RECHARGING\a\b'	#Robot se začal dobíjet a přestal reagovat na zprávy.		12
CLIENT_FULL_POWER =	'FULL POWER\a\b'	#Robot doplnil energii a opět příjímá příkazy.

KLIENT_KEY = 45328
SERVER_KEY = 54621

UNINICIALIZED = -1
UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

