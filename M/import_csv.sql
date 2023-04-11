LOAD DATA LOCAL INFILE '/Users/smlee/OneDrive/Downloads/exchange_info.csv' 
INTO TABLE exchange_info 
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n' 
IGNORE 1 ROWS 
(id, exchange_name, exchange_group_name, country, city, timezone, @change_datetime);

LOAD DATA LOCAL INFILE '/Users/smlee/OneDrive/Downloads/exchange_trading_day_info.csv' 
INTO TABLE exchange_trading_day_info 
FIELDS TERMINATED BY ',' 
LINES TERMINATED BY '\n' 
IGNORE 1 ROWS 
(id, exchange_id, sector_id, market_id, @change_datetime);
