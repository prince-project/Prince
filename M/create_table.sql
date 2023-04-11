CREATE TABLE `exchange_info` (
  `id` int(11) NOT NULL,
  `exchange_name` varchar(10) NOT NULL,
  `exchange_group_name` varchar(45) DEFAULT NULL,
  `country` varchar(5) DEFAULT NULL,
  `city` varchar(100) DEFAULT NULL,
  `timezone` decimal(3,1) DEFAULT NULL,
  `change_datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
);


CREATE TABLE `exchange_trading_day_info` (
  `id` int(11) NOT NULL,
  `exchange_id` int(11) DEFAULT NULL,
  `sector_id` int(11) DEFAULT NULL,
  `market_id` int(11) DEFAULT NULL,
  `change_datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
);