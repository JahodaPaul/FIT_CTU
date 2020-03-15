\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{FITthesis}[2019/12/23 CTU FIT standard class for theses]

% created by Ondrej Guth <ondrej.guth@fit.cvut.cz>

% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
% options
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
\newif\if@thesistypedefined
\DeclareOption{thesis=B}{\gdef\@thesistype{B}\@thesistypedefinedtrue}
\DeclareOption{thesis=M}{\gdef\@thesistype{M}\@thesistypedefinedtrue}

\DeclareOption{czech}{
	\AtBeginDocument{\selectlanguage{czech}}
	\PassOptionsToPackage{english,main=czech}{babel}
	\def\@lang{1}
}
\DeclareOption{english}{
	\AtBeginDocument{\selectlanguage{english}}
	\PassOptionsToPackage{czech,main=english}{babel}
	\def\@lang{0}
}
\DeclareOption{slovak}{
	\AtBeginDocument{\selectlanguage{slovak}}
	\PassOptionsToPackage{english,main=slovak}{babel}
	\def\@lang{2}
}
\DeclareOption{10pt}{\PassOptionsToClass{\CurrentOption}{memoir}}
\DeclareOption{11pt}{\PassOptionsToClass{\CurrentOption}{memoir}}
\DeclareOption{12pt}{\PassOptionsToClass{\CurrentOption}{memoir}}

\ExecuteOptions{11pt}
\ProcessOptions


\ifx\@lang\undefined
	\ClassError{FITthesis}{Language not specified}{Add option czech for Czech language or option english for English language or option slovak for Slovak language.}
\fi

\LoadClass[a4paper,twoside]{memoir}[2016/05/16]


\RequirePackage{babel}[2017/05/19]

\RequirePackage[unicode,pdfusetitle]{hyperref}[2017/03/14]
% line breaks in URL
\def\UrlBreaks{\do\/\do\-\do\_}

\RequirePackage{ellipsis}[2004/9/28]

\RequirePackage{chngcntr}[2008/07/23]
\counterwithout*{footnote}{chapter}


\RequirePackage{lmodern}[2009/10/30]
\RequirePackage{graphicx}[2014/10/28]


\RequirePackage{etoolbox}[2017/01/02]
\AtEndEnvironment{table}{\gdef\there@is@a@table{}}
\AtEndDocument{\ifdefined\there@is@a@table\label{tab:was:used:in:doc}\fi}
\DeclareRobustCommand{\listoftablescond}{\@ifundefined{r@tab:was:used:in:doc}{}{\listoftables*}}


% heading numbering (memoir-style settings)
\setsecnumdepth{subsubsection}

% table of contents depth (memoir-style settings)
\settocdepth{subsubsection}

% chapter head design (memoir-style settings)
\chapterstyle{madsen}

% layout of the page (memoir-style settings)
\setlrmargins{4cm}{*}{*}\checkandfixthelayout


% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
% general commands
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

\DeclareRobustCommand{\chapterstyletitle}[1]{
	\@makechapterhead{#1}
	\noindent
}

\newenvironment{introduction}{
	\setsecnumdepth{part}
	\if\@lang1\chapter{{\' U}vod}\else\if\@lang2\chapter{{\' U}vod}\else\chapter{Introduction}\fi\fi
}{
	\setsecnumdepth{subsubsection}
}

\newenvironment{conclusion}{
	\setsecnumdepth{part}
	\if\@lang1\chapter{Z{\' a}v{\v e}r}\else\if\@lang2\chapter{Z{\' a}ver}\else\chapter{Conclusion}\fi\fi
}{
	\setsecnumdepth{subsubsection}
}

% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
% template
% % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %

\newif\if@supervisordefined
\DeclareRobustCommand{\supervisor}[1]{
	\def\thesupervisor{#1}
	\@supervisordefinedtrue
}

\newif\if@departmentdefined
\DeclareRobustCommand{\department}[1]{
	\def\thedepartment{#1}
	\@departmentdefinedtrue
}

\newif \if@websitedefined
\DeclareRobustCommand {\website}[1] {
	\def\thewebsite{#1}
	\@websitedefinedtrue
}

\newif\if@acknowledgementsdefined
\DeclareRobustCommand{\acknowledgements}[1]{
	\def\theacknowledgements{#1}
	\@acknowledgementsdefinedtrue
}

\newif\if@abstractcsdefined
\DeclareRobustCommand{\abstractCS}[1]{
	\def\theabstractcs{\iflanguage{english}{\begin{otherlanguage}{czech}#1\end{otherlanguage}}{#1}}
	\@abstractcsdefinedtrue
}

\newif\if@abstractendefined
\DeclareRobustCommand{\abstractEN}[1]{
	\def\theabstracten{\iflanguage{english}{#1}{\begin{otherlanguage}{english}#1\end{otherlanguage}}}
	\@abstractendefinedtrue
}

% \newif\if@declarationofauthenticitydefined
% \DeclareRobustCommand{\declarationOfAuthenticity}[1]{
% 	\def\thedeclarationofauthenticity{#1}
% 	\@declarationofauthenticitydefinedtrue
% }

\newif\if@cityfordeclarationdefined
\DeclareRobustCommand{\placeForDeclarationOfAuthenticity}[1]{
	\def\thecityfordeclaration{#1}
	\@cityfordeclarationdefinedtrue
}

\newif\if@keywordscsdefined
\DeclareRobustCommand{\keywordsCS}[1]{
	\def\thekeywordscs{\iflanguage{english}{\begin{otherlanguage}{czech}#1\end{otherlanguage}}{#1}}
	\@keywordscsdefinedtrue
}

\newif\if@keywordsendefined
\DeclareRobustCommand{\keywordsEN}[1]{
	\def\thekeywordsen{\iflanguage{english}{#1}{\begin{otherlanguage}{english}#1\end{otherlanguage}}}
	\@keywordsendefinedtrue
}

\newif\if@authorwithdegreesdefined
\DeclareRobustCommand{\authorWithDegrees}[1]{
	\def\theauthorwithdegrees{#1}
	\@authorwithdegreesdefinedtrue
}

\newif\if@authorGNdefined
\DeclareRobustCommand{\authorGN}[1]{
	\def\theauthorGN{#1}
	\@authorGNdefinedtrue
}

\newif\if@authorFNdefined
\DeclareRobustCommand{\authorFN}[1]{
	\def\theauthorFN{#1}
	\@authorFNdefinedtrue
}

\DeclareRobustCommand{\thesistype}{\if@thesistypedefined\if\@thesistype B\if\@lang1{Bakal{\' a}{\v r}sk{\' a} pr{\' a}ce}\else\if\@lang2{Bakal{\' a}rska pr{\' a}ca}\else{Bachelor's thesis}\fi\fi\else\if\@thesistype M\if\@lang1{Diplomov{\' a} pr{\' a}ce}\else\if\@lang2{Diplomov{\' a} pr{\' a}ca}\else{Master's thesis}\fi\fi\else\ClassError{FITthesis}{Thesis type not specified}{Add option thesis=B for bachelor's thesis or option thesis=M for master's thesis.}\fi\fi\else\ClassError{FITthesis}{Thesis type not specified}{Add option thesis=B for bachelor's thesis or option thesis=M for master's thesis.}\fi}

\newif\if@declarationOptionSelected
\DeclareRobustCommand{\declarationOfAuthenticityOption}[1]{
	\ifx1#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni1.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo~z\'akona \v c.~121/2000~Sb., autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov,  a~skuto\v cnos\v t, \v ze \v Cesk\'e vysok\'e u\v cen\'\i{} technick\'e v~Praze m\'a pr\'avo na uzavrenie licen\v cnej zmluvy o~pou\v zit\'\i\ tejto pr\'ace ako \v skolsk\'eho diela pod\v la \S{}~60 odst.~1 autorsk\'eho z\'akona.
		}\else{%
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended, in particular that the Czech Technical University in Prague has the right to conclude a license agreement on the utilization of this thesis as a school work under the provisions of Article~60~(1) of the Act.
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	\ifx2#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni2.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo z\'akona \v c.~121/2000~Sb, autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov. V s\'ulade s ustanoven\'\i m \S{}~46 odst.~6 tohoto z\'akona t\'ymto ude\v lujem bezv\'yhradn\'e opr\'avnenie (licenciu) k~pou\v z\'\i vaniu tejto mojej pr\'ace, a to vr\'atane v\v setk\'ych po\v c\'\i ta\v cov\'ych programov ktor\'e s\'u jej s\'u\v cas\v tou alebo pr\'\i lohou a tie\v z v\v setkej ich dokument\'acie (\v dalej len \uv{Dielo}), a to v\v setk\'ym osob\'am, ktor\'e si praj\'u Dielo pou\v z\'iva\v t. Tieto osoby s\'u opr\'avnen\'e Dielo pou\v z\'\i va\v t ak\'ymko\v lvek 
sp\^ osobom, ktor\'y nezni\v zuje hodnotu Diela, ale len pre~nez\'arobkov\'e \'u\v cely. Toto opr\'avnenie je \v casovo, \'uzemne a mno\v zstevne ne\-ob\-me\-dze\-n\'e.
		}\else{%
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended. In accordance with Article~46~(6) of the Act, I hereby grant a nonexclusive authorization (license) to utilize this thesis, including any and all computer programs incorporated therein or attached thereto and all corresponding documentation (hereinafter collectively referred to as the ``Work''), to any and all persons that wish to utilize the Work. Such persons are entitled to use the Work for non-profit purposes only, in any way that does not detract from its value. This authorization is not limited in terms of time, location and quantity.
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	\ifx3#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni3.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo z\'akona \v c.~121/2000~Sb., autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov. \v Dalej prehlasujem, \v ze som s~\v Cesk\'ym vysok\'ym u\v cen\'\i m technick\'ym uzavrel licen\v cn\'u zmluvu o~pou\v zit\'\i\ tejto pr\'ace ako \v skolsk\'eho diela pod\v la \S{}~60 odst.~1 autorsk\'eho z\'akona. T\'ato skuto\v cnos\v t nem\'a vplyv na ust. \S{}~47b z\'akona \v c.~111/1998~Sb. o~vysok\'ych \v skol\'ach.
		}\else{%
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended. I further declare that I have concluded a license agreement with the Czech Technical University in Prague on the utilization of this thesis as a school work under the provisions of Article~60~(1) of the Act. This fact shall not affect the provisions of Article~47b of the Act No.\,111/1998~Coll., the Higher Education Act, as amended. 
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	\ifx4#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni4.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo z\'akona \v c.~121/2000~Sb., autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov.  V~s\'ulade s ustanoven\'\i m \S{}~46 odst.~6 tohoto z\'akona t\'ymto ude\v lujem bezv\'yhradn\'e opr\'avnenie (licenciu) k~u\v z\'\i vaniu tejto mojej pr\'ace, a to vr\'atane v\v setk\'ych po\v c\'\i ta\v cov\'ych programov ktor\'e s\'u jej s\'u\v cas\v tou alebo pr\'\i lohou a tie\v z v\v setkej ich dokument\'acie (\v dalej len \uv{Dielo}), a to v\v setk\'ym osob\'am, ktor\'e si praj\'u Dielo u\v z\'iva\v t. 

Tieto osoby s\'u opr\'avnen\'e Dielo pou\v z\'\i va\v t ak\'ymko\v lvek 
sp\^ osobom, ktor\'y nezni\v zuje hodnotu Diela, a za ak\'ymko\v lvek \'u\v celom (vr\'atane komer\v cn\'eho vyu\v zitia). Toto opr\'avnenie je \v casovo, \'uzemne a mno\v zstevne neobmedzen\'e.
Ka\v zd\'a osoba, ktor\'a vyu\v zije vy\v s\v sie uveden\'u licenciu, sa v\v sak zav\"azuje priradi\v t ka\v zd\'emu dielu, ktor\'e vznikne (\v co i len \v ciasto\v cne) na z\'aklade Diela, \'upravou
Diela, spojen\'\i m Diela s~in\'ym dielom, zaraden\'\i m Diela do diela s\'uborn\'eho \v ci zpracovan\'\i m Diela (vr\'atane prekladu), licenciu aspo\v n vo vy\v s\v sie uvedenom rozsahu
a~z\'arove\v n sa zav\"azuje spr\'\i stupni\v t zdrojov\'y k\'od tak\'eho diela aspo\v n zrovnate\v ln\'ym sp\^osobom a v~zrovnate\v lnom rozsahu ako je zpr\'\i stupnen\'y zdrojov\'y k\'od Diela.
		}\else{%
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended. In accordance with Article~46~(6) of the Act, I hereby grant a nonexclusive authorization (license) to utilize this thesis, including any and all computer programs incorporated therein or attached thereto and all corresponding documentation (hereinafter collectively referred to as the ``Work''), to any and all persons that wish to utilize the Work. Such persons are entitled to use the Work in any way (including for-profit purposes) that does not detract from its value. This authorization is not limited in terms of time, location and quantity. However, all persons that makes use of the above license shall be obliged to grant a license at least in the same scope as defined above with respect to each and every work that is created (wholly or in part) based on the Work, by modifying the Work, by combining the Work with another work, by including the Work in a collection of works or by adapting the Work (including translation), and at the same time make available the source code of such work at least in a way and scope that are comparable to the way and scope in which the source code of the Work is made available.
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	\ifx5#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni5.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo z\'akona \v c.~121/2000~Sb., autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov.  V~s\'ulade s ustanoven\'\i m \S{}~46 odst.~6 tohoto z\'akona t\'ymto ude\v lujem bezv\'yhradn\'e opr\'avnenie (licenciu) k~u\v z\'\i vaniu tejto mojej pr\'ace, a to vr\'atane v\v setk\'ych po\v c\'\i ta\v cov\'ych programov ktor\'e s\'u jej s\'u\v cas\v tou alebo pr\'\i lohou a tie\v z v\v setkej ich dokument\'acie (\v dalej len \uv{Dielo}), a to v\v setk\'ym osob\'am, ktor\'e si praj\'u Dielo u\v z\'iva\v t. Tieto osoby s\'u opr\'avnen\'e Dielo pou\v z\'\i va\v t ak\'ymko\v lvek 
sp\^ osobom, ktor\'y nezni\v zuje hodnotu Diela (vr\'atane komer\v cn\'eho vyu\v zitia). Toto opr\'avnenie je \v casovo, \'uzemne a~mno\v zstevne neobmedzen\'e.
		}\else{
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended. In accordance with Article~46~(6) of the Act, I hereby grant a nonexclusive authorization (license) to utilize this thesis, including any and all computer programs incorporated therein or attached thereto and all corresponding documentation (hereinafter collectively referred to as the ``Work''), to any and all persons that wish to utilize the Work. Such persons are entitled to use the Work in any way (including for-profit purposes) that does not detract from its value. This authorization is not limited in terms of time, location and quantity.
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	\ifx6#1 \DeclareRobustCommand{\thedeclarationofauthenticity}{\if\@lang1{%
		\input{prohlaseni6.tex.txt}
		}\else\if\@lang2{%
		Prehlasujem, \v ze som predlo\v zen\'u pr\'acu vypracoval(a) samostatne a \v ze som uviedol(uviedla) v\v setky informa\v cn\'e zdroje v~s\'ulade s~Metodick\'ym pokynom o~etickej pr\'iprave vysoko\v skolsk\'ych z\'avere\v cn\'ych pr\'ac.

		Beriem na vedomie, \v ze sa na moju pr\'acu vz\v tahuj\'u pr\'ava a povinnosti vypl\'yvaj\'uce zo z\'akona \v c.~121/2000~Sb., autorsk\'eho z\'akona, v znen\'\i\ neskor\v s\'\i ch predpisov.  \v Dalej prehlasujem, \v ze som s~\v CVUT uzavrel dohodu, na z\'aklade ktorej sa \v CVUT vzdalo pr\'ava na uzavrenie licen\v cnej zmluvy o~pou\v z\'\i van\'\i\ tejto pr\'ace ako \v skolsk\'eho diela pod\v la \S{}~60 odst.~1 autorsk\'eho z\'akona. T\'ato skuto\v cnos\v t nem\'a vplyv na ust. \S{}~47b z\'akona \v c.~111/1998~Sb. o~vysok\'ych \v skol\'ach.
		}\else{
		I hereby declare that the presented thesis is my own work and that I have cited all sources of information in accordance with the Guideline for adhering to ethical principles when elaborating an academic final thesis.
		
		I acknowledge that my thesis is subject to the rights and obligations stipulated by the Act No.\,121/2000~Coll., the Copyright Act, as amended. I further declare that I have concluded an agreement with the Czech Technical University in Prague, on the basis of which the Czech Technical University in Prague has waived its right to conclude a license agreement on the utilization of this thesis as a school work under the provisions of Article~60~(1) of the Act. This fact shall not affect the provisions of Article~47b of the Act No.\,111/1998~Coll., the Higher Education Act, as amended. 
		}\fi\fi
	}\@declarationOptionSelectedtrue\fi
	
}

% \DeclareRobustCommand{\titlepage}{
% 	\begin{titlingpage}
% 		\begin{center}
% 			\noindent\begin{tabular*}{\textwidth}{m{.77\textwidth}m{.165\textwidth}}
% 				{\large\scshape \if\@lang1{
% 						{\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze
% 					}\else\if\@lang2{
% 						{\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze
% 					}\else{
% 						Czech Technical University in Prague
% 					}\fi\fi
% 					
% 					\vspace{3mm}
% 					
% 					\if\@lang1{
% 						Fakulta informa{\v c}n{\' i}ch technologi{\' i}
% 					}\else\if\@lang2{
% 						Fakulta informa{\v c}n{\' i}ch technologi{\' i}
% 					}\else{
% 						Faculty of Information Technology
% 					}\fi\fi
% 					
% 					\vspace{4mm}
% 					
% 					\if@departmentdefined
% 						\thedepartment
% 					\else
% 						\ClassError{FITthesis}{Department unspecified}{Specify the department using the \department command.}
% 					\fi
% 				} & \hfill\includegraphics[width=.16\textwidth]{cvut-logo-bw}
% 			\end{tabular*}
% 		\end{center}
% 		
% 
% 		\vfill
% 
% 		{\Large
% 			\noindent\thesistype
% 		}
% 		\vspace{1cm}
% 
% 		\if\thetitle\empty
% 			\ClassError{FITthesis}{Thesis' title unspecified}{Specify title of this thesis using the \protect\title\space command.}
% 		\else
% 			\noindent\textbf{\LARGE \begin{flushleft}\thetitle\end{flushleft}}
% 		\fi
% 
% 		\vspace{4mm}
% 
% 		\if@authorwithdegreesdefined
% 			\noindent\textbf{\Large \textit{\theauthorwithdegrees}}
% 		\else
% 			\ClassError{FITthesis}{Thesis' author with degrees unspecified}{Specify author of this thesis (i.e. your name \& degrees) using the \protect\theauthorwithdegrees\space command.}
% 		\fi
% 
% 		\vfill
% 
% 		\noindent\if\@lang1{Vedouc{\' i} pr{\' a}ce:}\else\if\@lang2{Ved\'uci pr{\' a}ce:}\else{Supervisor:}\fi\fi
% 			\if@supervisordefined%
% 				~\thesupervisor
% 			\else
% 				\ClassError{FITthesis}{Thesis' supervisor unspecified}{Specify the supervisor of this thesis using the \protect\thesupervisor\space command.}
% 			\fi
% 
% 		\vspace{1cm}
% 
% 		\noindent\today
% 	\end{titlingpage}
% }

\DeclareRobustCommand{\titlepage}{
        \begin{titlingpage}
        \noindent
        \if\@lang1{\includegraphics[width=0.5\textwidth]{FITtemplates/cvut-logo-bw}}\else\if\@lang2{\includegraphics[width=0.5\textwidth]{FITtemplates/cvut-logo-bw}}\else{\includegraphics[width=0.5\textwidth]{images/LOGO_FIT}}\fi\fi
        
        \vfill
		
		{\Large\noindent\thesistype}

               \vspace{1cm}

               \if\thetitle\empty
                       \ClassError{FITthesis}{Thesis' title unspecified}{Specify title of this thesis using the \protect\title\space command.}
               \else
                       \noindent\textbf{\LARGE \begin{flushleft}\thetitle\end{flushleft}}
               \fi

 

               \vspace{4mm}

               \if@authorwithdegreesdefined

                       \noindent\textbf{\Large \textit{\theauthorwithdegrees}}

               \else

                       \ClassError{FITthesis}{Thesis' author with degrees unspecified}{Specify author of this thesis (i.e. your name \& degrees) using the \protect\theauthorwithdegrees\space command.}

               \fi

               \vfill

\if@departmentdefined

                                              \noindent \thedepartment

                                      \else

                                              \ClassError{FITthesis}{Department unspecified}{Specify the department using the \department command.}

                                      \fi

                              

\vspace{0.1cm}

               \noindent\if\@lang1{Vedouc{\' i} pr{\' a}ce:}\else\if\@lang2{Ved\'uci pr{\' a}ce:}\else{Supervisor:}\fi\fi
                       \if@supervisordefined%
                              ~\thesupervisor
                       \else

                               \ClassError{FITthesis}{Thesis' supervisor unspecified}{Specify the supervisor of this thesis using the \protect\thesupervisor\space command.}

                       \fi           

 

               \vspace{1cm}

 

                \noindent\today

        \end{titlingpage}

}

\DeclareRobustCommand{\acknowledgementspage}{
	\if@acknowledgementsdefined
		\cleardoublepage
		\thispagestyle{empty}
		
		~
		
		\vfill
		
		\if\@lang1\chapterstyletitle{Pod{\v e}kov{\' a}n{\' i}}\else\if\@lang2\chapterstyletitle{Po\v dakovanie}\else\chapterstyletitle{Acknowledgements}\fi\fi\theacknowledgements
	\fi
}

\DeclareRobustCommand{\declarationofauthenticitypage}{
	\cleardoublepage
	\thispagestyle{empty}

	~
	
	\vfill
		
	\if@declarationOptionSelected
		\if\@lang1\chapterstyletitle{Prohl{\' a}{\v s}en{\' i}}\else\if\@lang2\chapterstyletitle{Prehl{\' a}senie}\else\chapterstyletitle{Declaration}\fi\fi\thedeclarationofauthenticity{}
		
		\vspace{2cm}

		\noindent
			\if@cityfordeclarationdefined
				\if\@lang1{}\else\if\@lang2{}\else{In }\fi\fi\thecityfordeclaration{} \if\@lang1{dne}\else\if\@lang2{}\else{on}\fi\fi~\today \hfill \dots\dots\dots\dots\dots\dots\dots
			\else
				\ClassError{FITthesis}{M{\' i}sto prohl{\' a}{\v s}en{\' i} nebylo zad{\' a}no}{Nastavte m{\' i}sto, kde bylo podeps{\' a}no prohl{\' a}{\v s}en{\' i}, v{\v c}etn{\v e} p{\v r}edlo{\v z}ky (nap{\v r}. V~Praze) pomoc{\' i} p{\v r}{\' i}kazu \placeForDeclaration.}
			\fi

	\else
		\ClassError{FITthesis}{Declaration of authenticity unspecified}{Select the declaration of authenticity using the \declarationOfAuthenticityOption command.}
	\fi
}

\DeclareRobustCommand{\imprintpage}{
	\clearpage
	\thispagestyle{empty}
	
	~
	
	\vfill
	
	\if\@lang1{
		\noindent {\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze

		\noindent Fakulta informa{\v c}n{\' i}ch technologi{\' i}}\else\if\@lang2{
		\noindent {\v C}esk{\' e} vysok{\' e} u{\v c}en{\' i} technick{\' e} v~Praze

		\noindent Fakulta informa{\v c}n{\' i}ch technologi{\' i}}\else{
		\noindent Czech Technical University in Prague
		
		\noindent Faculty of Information Technology
	}\fi\fi
	
	\noindent \textcopyright{} \the\year{} \theauthorGN{} \theauthorFN{}. \if\@lang1{V{\v s}echna pr{\' a}va vyhrazena.}\else\if\@lang2{V{\v s}etky pr{\' a}va vyhraden\'e.}\else{All rights reserved.}\fi\fi
	
	\if\@lang1{
		\noindent \textit{Tato pr{\' a}ce vznikla jako {\v s}koln{\' i} d{\' i}lo na {\v C}esk{\' e}m vysok{\' e}m u{\v c}en{\' i} technick{\' e}m v~Praze, Fakult{\v e} informa{\v c}n{\' i}ch technologi{\' i}. Pr{\' a}ce je chr{\' a}n{\v e}na pr{\' a}vn{\' i}mi p{\v r}edpisy a mezin{\' a}rodn{\' i}mi {\' u}mluvami o~pr{\' a}vu autorsk{\' e}m a pr{\' a}vech souvisej{\' i}c{\' i}ch s~pr{\' a}vem autorsk{\' y}m. K~jej\'\i{}mu u\v zit\'\i{}, s~v\'yjimkou bez\'uplatn\'ych z\'akonn\'ych licenc\'\i{} a nad r\'amec opr\'avn\v en\'\i{} uveden\'ych v~Prohl\'a\v sen\'\i{} na p\v redchoz\'\i{} stran\v e, je nezbytn\'y souhlas autora.}}\else\if\@lang2{
		\noindent \textit{T\'ato pr\'aca vznikla ako \v skolsk\'e dielo na  FIT \v CVUT v Prahe. Pr\'aca je chr\'anen\'a medzin\'arodn\'ymi predpismi a zmluvami o autorskom pr\'ave a pr\'avach s\'uvisiacich s autorsk\'ym pr\'avom. Na jej vyu\v zitie, s~v\'ynimkou bezplatn\'ych z\'akonn\'ych licenci\'\i, je nutn\'y s\'uhlas autora.}}\else{
		\noindent \textit{This thesis is school work as defined by Copyright Act of the Czech Republic. It has been submitted at Czech Technical University in Prague, Faculty of Information Technology. The thesis is protected by the Copyright Act and its usage without author's permission is prohibited (with exceptions defined by the Copyright Act).}
	}\fi\fi
	
	\if\@lang1{\subsection*{Odkaz na tuto pr{\' a}ci} \theauthorFN{}, \theauthorGN{}. \textit{\thetitle{}}. \thesistype{}. Praha: {\v C}esk\'e vysok\'e u\v cen\'\i{} technick\'e v~Praze, Fakulta informa{\v c}n{\' i}ch technologi{\' i}, \the\year.\if@websitedefined{ Dostupn\'y tak\'e z~WWW: $\langle$\url{\thewebsite}$\rangle$.}\fi}\else\if\@lang2{\subsection*{Odkaz na t\'uto pr{\' a}cu} \theauthorFN{}, \theauthorGN{}. \textit{\thetitle{}}. \thesistype{}. Praha: {\v C}esk\'e vysok\'e u\v cen\'\i{} technick\'e v~Praze, Fakulta informa{\v c}n{\' i}ch technologi{\' i}, \the\year.\if@websitedefined{ Dostupn\'y aj z~WWW: $\langle$\url{\thewebsite}$\rangle$.}\fi}\else{\subsection*{Citation of this thesis} \theauthorFN{}, \theauthorGN{}. \textit{\thetitle{}}. \thesistype{}. Czech Technical University in Prague, Faculty of Information Technology, \the\year.\if@websitedefined{ Also available from: $\langle$\url{\thewebsite}$\rangle$.}\fi}\fi\fi
}

\DeclareRobustCommand{\abstractpage}{
	\chapter*{Abstrakt}
	\if@abstractcsdefined
		\theabstractcs
	\else
		\ClassError{FITthesis}{Abstract in Czech unspecified}{Specify abstract in Czech language using the \abstractCS command.}
	\fi

	\if@keywordscsdefined
		\paragraph*{Kl{\' i}{\v c}ov{\' a} slova} \thekeywordscs{}
	\else
		\ClassError{FITthesis}{Czech keywords unspecified}{Specify the keywords in Czech of your thesis using \keywordsCS command.}
	\fi

	\vfil

	\if@abstractendefined
		\chapterstyletitle{Abstract}\theabstracten
	\else
		\ClassError{FITthesis}{Abstract in English unspecified}{Specify abstract in English using the \abstractEN command.}
	\fi

	\if@keywordsendefined
		\paragraph*{Keywords} \thekeywordsen{}
	\else
		\ClassError{FITthesis}{English keywords unspecified}{Specify the keywords in English of your thesis using \keywordsEN command.}
	\fi
}

\AfterEndPreamble{
% fix the memoir bug generating structured numbers (e.g., a figure number) without dot
\renewcommand{\counterwithin}{\@ifstar{\@csinstar}{\@csin}}

	\thispagestyle{empty}
	\if\@lang1{Sem vlo{\v z}te zad{\' a}n{\' i} Va{\v s}{\' i} pr{\' a}ce.}\else\if\@lang2{Sem vlo{\v z}te zadanie Va{\v s}ej pr{\' a}ce.}\else{Insert here your thesis' task.}\fi\fi

	\frontmatter
	\pagestyle{plain}
	\cleardoublepage
% 	\setcounter{page}{3}
	\titlepage
	
	\setcounter{page}{3}
	\acknowledgementspage

	\declarationofauthenticitypage
	\imprintpage

	\abstractpage

	\cleardoublepage
	\tableofcontents*

	\cleardoublepage
	\listoffigures*

	\cleardoublepage
	\listoftablescond

	\pagestyle{ruled}
	\mainmatter
}
