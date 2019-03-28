from DateTime import DateTime
from Flight import Flight

class FlightSystem:
    def __init__(self):
        self.Flights = []
        self.GenerateFlights()
        self.NumberOfLikes = 0

    def GenerateFlights(self):
        self.Flights.append(Flight(1,'PRG','SIN',DateTime('20-05-2019-10-40'),600.55,50))
        self.Flights.append(Flight(2, 'SIN', 'FRA', DateTime('22-05-2019-06-00'), 500, 45))
        self.Flights.append(Flight(3, 'SIN', 'DXB', DateTime('20-05-2019-18-40'), 500, 45))
        self.Flights.append(Flight(4, 'PRG', 'SIN', DateTime('13-05-2019-11-20'), 555.40, 100))

    def QueryFlightsBySourceAndDest(self, source, dest):
        result = []
        for item in self.Flights:
            if item.source == source and item.destination == dest:
                result.append(item.iD)
        if len(result) == 0:
            return False
        else:
            return [len(result)] + result

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

    def MakeAnReservation(self, flightID, numberOfSeats):
        success = False
        for i in range(len(self.Flights)):
            if self.Flights[i].iD == flightID and self.Flights[i].CheckSeatAvailabilityReservation(numberOfSeats) == True:
                self.Flights[i].UpdateAvailabilityReservation(numberOfSeats)
                success = True
                break
        return success