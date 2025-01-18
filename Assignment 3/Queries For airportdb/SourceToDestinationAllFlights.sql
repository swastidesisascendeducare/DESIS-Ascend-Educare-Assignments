SELECT 
    f.flight_id,
    f.flightno,
    a_from.name AS source_airport,
    a_to.name AS destination_airport,
    f.departure,
    f.arrival
FROM 
    flight f
JOIN 
    airport a_from ON f.from = a_from.airport_id
JOIN 
    airport a_to ON f.to = a_to.airport_id
WHERE 
    a_from.name = 'BORG EL ARAB INTL' 
    AND a_to.name = 'LABUAN';
