from DateTime import DateTime
from Flight import Flight

class FlightSystem:
    def __init__(self):
        self.Flights = []
        self.GenerateFlights()

    def GenerateFlights(self):
        self.Flights.append(Flight(1,'PRG','SIN','cas',600,50))
        self.Flights.append(Flight(2, 'SIN', 'FRA', 'cas', 500, 45))
        self.Flights.append(Flight(3, 'SIN', 'DXB', 'cas', 500, 45))

    def QueryFlightsBySourceAndDest(self, source, dest):
        pass

    def QueryFlightByID(self, id):
        for item in self.Flights:
            if item.iD == id:
                return item

        return self.Flights[0] #TODO return error message