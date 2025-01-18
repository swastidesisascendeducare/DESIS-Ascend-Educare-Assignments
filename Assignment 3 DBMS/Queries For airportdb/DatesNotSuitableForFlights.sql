SELECT 
    log_date, COUNT(*) AS unsuitable_days
FROM 
    weatherdata
WHERE 
    airpressure > 1015 AND 
    humidity >= 98
GROUP BY 
    log_date;
