# Data structure used to show the time of departure of a flights
class DateTime:
    def __init__(self, string):
        self.string_format = string

    def Get_string(self):
        return self.string_format

    def Get_printable_string(self):
        items = self.string_format.split('-')
        result_str = items[0]+'.'+items[1]+'.'+items[2]+' at '+items[3]+':'+items[4]
        return result_str