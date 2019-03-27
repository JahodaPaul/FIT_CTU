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

    def Get_printable_string(self):
        result = '----------------------------------------------------------------------------------------------------\n'
        result += 'Flight ' + str(self.iD) + ' from ' + self.source + ' to '  + self.destination + ' will be departing on ' + self.departure_time.Get_printable_string() + '\n'
        result += 'Airfare: ' + str(self.airfare) + '\n'
        result += 'Number of seats available: ' + str(self.number_of_seats_available) + '\n'
        return result

    def CheckSeatAvailabilityReservation(self, n_of_seats_to_reserve):
        if n_of_seats_to_reserve <= self.number_of_seats_available:
            return True
        else:
            return False

    def UpdateAvailabilityReservation(self,n_of_seats_to_reserve):
        self.number_of_seats_available -= n_of_seats_to_reserve