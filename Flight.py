from DateTime import DateTime

class Flight:

    def __init__(self, id, source, destination, departure_time, airfare, number_of_seats_available):
        self.iD = id
        self.source = source
        self.destination = destination
        self.departure_time = departure_time
        self.airfare = airfare
        self.number_of_seats_available = number_of_seats_available

        self.stringValue = ''

    def UpdateStringValue(self):
        self.stringValue = str(self.iD) + self.source + self.destination + self.departure_time.Get_string() + str(self.airfare) + str(self.number_of_seats_available)

    def Get_string(self):
        self.UpdateStringValue()
        return self.stringValue