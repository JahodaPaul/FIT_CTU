from DateTime import DateTime
from Flight import Flight

class FlightSystem:
    def __init__(self):
        self.Flights = []
        self.GenerateFlights()
        self.NumberOfLikes = 0

    def GenerateFlights(self):
        self.Flights.append(Flight(1,'PRG','SIN',DateTime('cas'),600,50))
        self.Flights.append(Flight(2, 'SIN', 'FRA', DateTime('cas'), 500, 45))
        self.Flights.append(Flight(3, 'SIN', 'DXB', DateTime('cas'), 500, 45))

    def QueryFlightsBySourceAndDest(self, source, dest):
        pass

    def QueryFlightByID(self, id):
        for item in self.Flights:
            if item.iD == id:
                return item

        return False

    def QueryNumberOfFlights(self):
        return len(self.Flights)

    def GiveUsALike(self):
        self.NumberOfLikes += 1
        return self.NumberOfLikes