questionFormat = "How important is it for you that country"

threeChooseTwo = ['Sunny', 'Beautiful nature', 'Great food']

finalQuestionsTopic = ["EDUCATION","INTERNET","RESEARCH, SPENDING","DEMOGRAPHICS","CAREER","TAXES","OTHER"]

finalQuestions = [
    ["pays it's teachers well?", "has educated population?", "has high tertiary education spending per student?"],  #EDUCATION

    ["has high percentage of people with access to the internet?", "has increased internet access to its people?"], #INTERNET

    ["spends a lot on research and development?", "has low debt to GDP ratio?",
    "has high percentage of it's energy source from renewable sources?", "increased output of its renewable energy sources?",
     "has increased its spending on research and development?"], #ENERGY AND RESEARCH AND GOVERNEMNT SPENDING

    ["has high percentage of vaccinated children?", "has high fertility rate?","has increased it's fertility rate over last five years?",
     "has low percentage of elderly people?", "has slow growth of percentage of elderly people?"],  #CARE OF CHILDREN

    ["has low unemployment rate?", "has low poverty rate?","has low income inequality?","has high average salary?"],  #CAREER

    ["has low tax on personal income","has low tax on property?","has low tax on services?",
     "has reduced it's taxes on services over the last few years?","has reduced it's taxes on personal income over the last few years?",
     "has reduced it's taxes on properties over the last few years?"],  #TAXES

    ["has low number of deaths caused by road accidents?",
     "has lowered the number of deaths caused by road accidents in last few years?"] #OTHER
]

finalQuestionsReferences = [
    ["TEACHER","POPULATION_WITH","EDUCATION_SPENDING"],

    ["ACCESS","ACCESS;OVER_THE_YEARS"],

    ["RESEARCH","DEBT","RENEWABLE", "RENEWABLE;OVER_THE_YEARS","RESEARCH;OVER_THE_YEARS"],

    ["VACCINATION","FERTILITY","FERTILITY;OVER_THE_YEARS","ELDERLY","ELDERLY;OVER_THE_YEARS"],

    ["UNEMPLOYMENT","POVERTY","INEQUALITY","AVERAGE_SALARY"],

    ["PERSONAL_INCOME","TAX_ON_PROPERTY","ON_SERVICES","ON_SERVICES;OVER_THE_YEARS","PERSONAL_INCOME;OVER_THE_YEARS", "TAX_ON_PROPERTY;OVER_THE_YEARS"],

    ["ROAD_","ROAD_;OVER_THE_YEARS"]
]

CountryFullName = {
    '"ESP"' : 'Spain', '"GRC"' : 'Greece', '"HUN"' : 'Hungary', '"FRA"': 'France', '"ISR"': 'Israel', '"CAN"' : 'Canada',
                      '"DNK"' : 'Denmark', '"LUX"' : 'Luxembourg', '"LVA"' : 'Latvia', '"CZE"' : 'Czechia',
                          '"NOR"' : 'Norway', '"DEU"' : 'Germany', '"NLD"' : 'Netherlands', '"AUT"' : 'Austria',
                      '"POL"' : 'Poland', '"ITA"' : 'Italy', '"SVN"' : 'Slovenia', '"SWE"' : 'Sweden', '"FIN"' : 'Finland',
                      '"USA"': 'United States', '"AUS"' : 'Australia', '"PRT"' : 'Portugal'
}

finalQuestionshigherBetter = [
    [1,1,1],

    [1,1],

    [1,-1,1,1,1],

    [1,1,1,-1,-1],

    [-1,-1,-1,1],

    [-1,-1,-1,-1,-1,-1],

    [-1,-1]
]