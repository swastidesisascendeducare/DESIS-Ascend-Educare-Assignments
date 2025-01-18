SELECT DISTINCT 
    airplane_type.description AS airline_type
FROM 
    passenger
JOIN 
    booking ON passenger.passenger_id = booking.passenger_id
JOIN 
    flight ON booking.flight_id = flight.flight_id
JOIN 
    airplane ON flight.airplane_id = airplane.airplane_id
JOIN 
    airplane_type ON airplane.type_id = airplane_type.type_id
WHERE 
    passenger.passenger_id = 16678;
