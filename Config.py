questionFormat = "How important is it for you that country"

threeChooseTwo = ['Sunny', 'Beautiful nature', 'Great food']

finalQuestionsTopic = ["EDUCATION","INTERNET","ENERGY, RESEARCH & SPENDING","CARE OF CHILDREN","CAREER","TAXES","OTHER"]

finalQuestions = [
    ["pays it's teachers well?", "has educated population?", "has high tertiary education spending per student?"],  #EDUCATION

    ["has high percentage of people with access to the internet?"], #INTERNET

    ["spends a lot on research and development?", "has low debt to GDP ratio?",
    "has high percentage of it's energy source from renewable sources?", "increased output of its renewable energy sources?"], #ENERGY AND RESEARCH AND GOVERNEMNT SPENDING

    ["has high percentage of vaccinated children?", "has high fertility rate?"],  #CARE OF CHILDREN

    ["has low unemployment rate?", "has low poverty rate?","has low income inequality?","has high average salary?"],  #CAREER

    ["has low tax on personal income","has low tax on property?","has low tax on services?"],  #TAXES

    ["has low number of deaths caused by road accidents?"] #OTHER
]

finalQuestionsReferences = [
    ["TEACHER","POPULATION_WITH","EDUCATION_SPENDING"],

    ["ACCESS"],

    ["RESEARCH","DEBT","RENEWABLE","RENEWABLE"],

    ["VACCINATION","FERTILITY"],

    ["UNEMPLOYMENT","POVERTY","INEQUALITY","AVERAGE_SALARY"],

    ["PERSONAL_INCOME","TAX_ON_PROPERTY","ON_SERVICES"],

    ["ROAD_"]
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

    [1],

    [1,-1,1,1],

    [1,1],

    [-1,-1,-1,1],

    [-1,-1,-1],

    [-1]
]