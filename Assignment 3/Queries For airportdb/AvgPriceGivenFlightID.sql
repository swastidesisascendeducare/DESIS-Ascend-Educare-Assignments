SELECT 
    flight_id,
    AVG(price) AS average_booking_price
FROM 
    booking
WHERE 
    flight_id = 3863
GROUP BY 
    flight_id;
