

class DateTime:
    def __init__(self, string):
        self.string_format = string

    def Get_string(self):
        return self.string_format

    def Get_printable_string(self):
        return self.string_format