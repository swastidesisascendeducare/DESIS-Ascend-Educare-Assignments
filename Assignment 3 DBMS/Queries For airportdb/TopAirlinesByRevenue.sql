CREATE INDEX idx_airline_id ON airline(airline_id);
CREATE INDEX idx_airline_id_flight ON flight(airline_id);
CREATE INDEX idx_flight_id_flight ON flight(flight_id);
CREATE INDEX idx_flight_id_booking ON booking(flight_id);
CREATE INDEX idx_price_booking ON booking(price);

SELECT 
    a.airlinename AS airline_name,
    SUM(b.price) AS total_revenue
FROM 
    airline a
JOIN 
    flight f ON a.airline_id = f.airline_id
JOIN 
    booking b ON f.flight_id = b.flight_id
GROUP BY 
    a.airline_id
ORDER BY 
    total_revenue DESC
LIMIT 20;
